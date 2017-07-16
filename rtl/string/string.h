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

#ifndef __STRING_H__
#define __STRING_H__

#include <common/types.h>

#ifndef __ASM__

SIZE_T RtlpCopyStringWithPadding(STRING, SIZE_T, CSTRING, BOOL, CHAR, SIZE_T);
SIZE_T RtlpFillString(STRING, SIZE_T, CHAR, SIZE_T);

#endif /* __ASM__ */

#endif /* __STRING_H__ */
