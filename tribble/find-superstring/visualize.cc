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

#include "find_superstring.hh"


namespace tribble {

	void visualize(std::istream &stream, std::ostream &memory_chart_stream)
	{
		index_type index;
		index.load(stream);
		sdsl::write_structure <sdsl::HTML_FORMAT>(index, memory_chart_stream);
	}
}
