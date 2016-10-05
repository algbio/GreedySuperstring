/*
 Copyright (c) 2016 Tuukka Norri
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


#ifndef TRIBBLE_FIND_SUPERSTRING_HH
#define TRIBBLE_FIND_SUPERSTRING_HH

#include <istream>
#include <sdsl/cst_sct3.hpp>

#ifndef DEBUGGING_OUTPUT
#define DEBUGGING_OUTPUT 0
#endif

// FIXME: check that the LCP structure is the most suitable one.
typedef sdsl::cst_sct3 <>	cst_type;
typedef cst_type::csa_type	csa_type;

typedef std::function <
	bool(
		std::size_t read_lex_rank,
		std::size_t match_length,
		std::size_t match_sa_begin,
		std::size_t match_sa_end
	)
> find_superstring_match_callback;

extern "C" void create_index(std::istream &source_stream, char const sentinel);
extern "C" void sort_strings_by_length(
	csa_type const &csa,
	char const sentinel,
	/* out */ sdsl::int_vector <> &sorted_bwt_indices,
	/* out */ sdsl::int_vector <> &sorted_bwt_start_indices,
	/* out */ sdsl::int_vector <> &string_lengths
);
extern "C" void find_superstring(char const *source_fname, char const sentinel, find_superstring_match_callback cb);
extern "C" void handle_error();

#endif
