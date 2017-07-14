/*
	  Copyright 2017, Lithium768 <tianxiangli768@gmail.com>

	  This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	  This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	  You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include		<header/multiboot2.h>

.section		.multiboot2_header
.align			MULTIBOOT2_HEADER_ALIGN

_multiboot2_header:
.long			MULTIBOOT2_HEADER_MAGIC
.long			MULTIBOOT2_HEADER_ARCHITECTURE
.long			_multiboot2_header_end - _multiboot2_header
.long			-(MULTIBOOT2_HEADER_MAGIC + MULTIBOOT2_HEADER_ARCHITECTURE + _multiboot2_header_end - _multiboot2_header)

_multiboot2_header_tag:
.word			MULTIBOOT2_HEADER_TAG_END_TYPE
.word			MULTIBOOT2_HEADER_TAG_OPTIONAL
.long			_multiboot2_header_end - _multiboot2_header_tag

_multiboot2_header_end:
