/*
 Copyright (c) 2017 Tuukka Norri
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see http://www.gnu.org/licenses/ .
 */


#include <tribble/fasta_reader.hh>
#include <tribble/line_reader.hh>
#include "read_input.hh"


namespace tribble { namespace detail {
	class create_index_cb {
		
	protected:
		string_list_type	*m_strings{nullptr};
		trie_type			*m_trie{nullptr};
		string_map_type		*m_strings_by_state{nullptr};
		state_map_type		*m_states_by_string{nullptr};
		std::size_t			m_idx{0};
		std::size_t			m_seqno{0};
		
	public:
		create_index_cb(
			string_list_type &strings,
			trie_type &trie,
			string_map_type &strings_by_state,
			state_map_type &states_by_string
		):
			m_strings(&strings),
			m_trie(&trie),
			m_strings_by_state(&strings_by_state),
			m_states_by_string(&states_by_string)
		{
		}
		
		void insert_and_check(std::string &str)
		{
			if (insert(*m_trie, *m_strings_by_state, str, m_idx))
			{
				m_strings->emplace_back(std::move(str));
				++m_idx;
			}
		}
		
		// For fasta_reader.
		void handle_sequence(
			std::string const &identifier,
			std::unique_ptr <vector_source::vector_type> &seq,
			std::size_t const &seq_length,
			vector_source &vector_source
		)
		{
			std::string str(reinterpret_cast <char const *>(seq->data()), seq_length);
			insert_and_check(str);
			vector_source.put_vector(seq);

			++m_seqno;
			if (0 == m_seqno % 10000)
				std::cerr << " " << m_seqno << std::flush;
		}
		
		// For line_reader.
		void handle_sequence(
			uint32_t lineno,
			std::unique_ptr <vector_source::vector_type> &seq,
			std::size_t const &seq_length,
			vector_source &vector_source
		)
		{
			std::string str(reinterpret_cast <char const *>(seq->data()), seq_length);
			insert_and_check(str);
			vector_source.put_vector(seq);

			if (0 == lineno % 10000)
				std::cerr << " " << lineno << std::flush;
		}
		
		void finish()
		{
			m_states_by_string->resize(m_strings_by_state->size());
			for (auto const &kv : *m_strings_by_state)
			{
				assert(nullptr == (*m_states_by_string)[kv.second]);
				(*m_states_by_string)[kv.second] = kv.first;
			}
		}
	};

}}


namespace tribble {
	
	void read_input(
		tribble::file_istream &source_stream,
		enum_source_format const source_format,
		tribble::string_list_type &strings,
		tribble::trie_type &trie,
		tribble::string_map_type &strings_by_state,
		tribble::state_map_type &states_by_string
	)
	{
		// Read the sequence from input and create the index in the callback.
		vector_source vs(1, false);
		detail::create_index_cb cb(strings, trie, strings_by_state, states_by_string);

		if (source_format_arg_FASTA == source_format)
		{
			fasta_reader <detail::create_index_cb> reader;
			reader.read_from_stream(source_stream, vs, cb);
		}
		else if (source_format_arg_text == source_format)
		{
			line_reader <detail::create_index_cb> reader;
			reader.read_from_stream(source_stream, vs, cb);
		}
		else
		{
			std::stringstream output;
			output << "Unexpected source file format '" << source_format << "'.";

			throw std::runtime_error(output.str());
		}
	}
}
