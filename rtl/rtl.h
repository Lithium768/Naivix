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

#ifndef __RTL_H__
#define __RTL_H__

#include <common/types.h>
#include <common/vaarg.h>

#ifndef __ASM__

SIZE_T RtlFormatString(STRING, SIZE_T, CSTRING, ...);
SIZE_T RtlvFormatString(STRING, SIZE_T, CSTRING, VA_LIST);
SIZE_T RtlGetStringLenght(CSTRING);
SIZE_T RtlCopyString(STRING, CSTRING, SIZE_T);
SIZE_T RtlParseIntToString(STRING, SIZE_T, UINT64, UINT8);

#endif /* __ASM__ */

#endif /* __RTL_H__ */
