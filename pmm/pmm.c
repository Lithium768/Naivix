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
#include <pmm/pmm.h>
#include <kernel/debug/debug.h>

VOID PmmInitialize(PPMM_MEMORY_MAP mmap, ADDRESS freeSpaceStart) {
	DbgPrint("Initializing phisical memory manager ...\n", DBG_PREFIX_TYPE_NONE);

	SIZE_T memSize = 0;
	DbgPrint("Memory ranges:\n", DBG_PREFIX_TYPE_INFO);
	for (SIZE_T i = 0; i < mmap->EntriesNum; i++) {
		DbgPrint("  [mem 0x%016x-0x%016x] %s\n", DBG_PREFIX_TYPE_INFO, mmap->Entries[i].Base, mmap->Entries[i].Base + mmap->Entries[i].Size, mmap->Entries[i].Type == PMM_MEMORY_TYPE_AVAILABLE ? "usable" : "reserved");
		memSize += mmap->Entries[i].Type == PMM_MEMORY_TYPE_AVAILABLE ? mmap->Entries[i].Size : 0;
	}
	DbgPrint("Memory size: %u GB(s), %u MB(s), %u KB(s), %u Byte(s)\n", DBG_PREFIX_TYPE_INFO,
			memSize / 0x40000000,
			(memSize % 0x40000000) / 0x100000,
			(memSize % 0x100000) / 0x400,
			(memSize % 0x400) / 1
			);

	DbgPrint("Initialized phisical memory manager.\n", DBG_PREFIX_TYPE_OK);
}

