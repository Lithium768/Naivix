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

#include <common/types.h>
#include <header/multiboot2.h>
#include <hal/hal.h>
#include <rtl/rtl.h>

VOID KeSystemStartup(PMULTIBOOT2_INFO mbi, ADDRESS freeSpaceStart) {
	// TODO: Phase 1 of the kernel startup code here...
	HalEarlyPrintInit();

	CHAR buffer[1024];
	for (UINT64 i = 30; i < 38; i++) {
		for (UINT64 j = 40; j < 48; j++) {
			buffer[RtlFormatString(buffer, 1024, "\033[1m\033[%um\033[%umEarly print test ...", i, j)] = '\0';
			HalEarlyPrint(buffer);
		}
	}
}
