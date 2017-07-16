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

#ifndef __HAL_H__
#define __HAL_H__

#include <common/types.h>

#ifndef __ASM__

static inline PVOID HalFastMemoryCopy(PVOID dest, PVOID src, SIZE_T lenght) {
	SIZE_T remainder = lenght % sizeof(UINT64);
	lenght = lenght / sizeof(UINT64);
	UINT64_PTR d = (UINT64_PTR)dest, s = (UINT64_PTR)src;
	__asm__ __volatile__("cld; rep; movsq":"+c"(lenght), "+D"(d), "+S"(s)::"memory", "cc");
	__asm__ __volatile__("cld; rep; movsb":"+c"(remainder), "+D"(d), "+S"(s)::"memory", "cc");
	return dest;
}

VOID HalEarlyPrintInit(VOID);
SIZE_T HalEarlyPrint(CSTRING);

#endif /* __ASM__ */

#endif /* __HAL_H__ */
