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
#include <kernel/debug/debug.h>

VOID KeSystemStartup(PMULTIBOOT2_INFO mbi, ADDRESS freeSpaceStart) {
	// TODO: Phase 1 of the kernel startup code here...
	DbgInitialize();

	for (UINT64 i = 30; i < 38; i++) {
		for (UINT64 j = 40; j < 48; j++) {
			DbgPrint("\033[1;%u;%umEarly print test ...", i, j);
		}
	}
}
