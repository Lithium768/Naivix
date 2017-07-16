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

#ifndef __MISC_H__
#define __MISC_H__

#include <common/types.h>

#define			GDT_SELECTOR_KERNEL_DATA		0x0000
#define			GDT_SELECTOR_KERNEL_CODE64		0x0008

#define			KERNEL_DPL						0
#define			USER_DPL						3

#ifndef __ASM__

static inline UINT8 HalpInByte(UINT16 port) {
	UINT8 value;
	__asm__ __volatile__("in %1, %0":"=a"(value):"d"(port));
	return value;
}

static inline VOID HalpOutByte(UINT16 port, UINT8 value) {
	__asm__ __volatile__("out %0, %1"::"a"(value), "d"(port));
}

#endif /* __ASM__ */

#endif /* __MISC_H__ */
