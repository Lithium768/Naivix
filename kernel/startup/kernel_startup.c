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
#include <pmm/pmm.h>
#include <common/assert.h>

VOID KeSystemStartup(PMULTIBOOT2_INFO mbi, ADDRESS freeSpaceStart) {
	DbgInitialize();

	for (PMULTIBOOT2_INFO_TAG_HEADER header = mbi->Tags; header->Type != TAG_TYPE_END; header += (header->Size + sizeof(MULTIBOOT2_INFO_TAG_HEADER) - 1) / sizeof(MULTIBOOT2_INFO_TAG_HEADER)) {
		switch (header->Type) {
			case TAG_TYPE_BOOT_LOADER_NAME: {
				PMULTIBOOT2_INFO_BOOT_LOADER_NAME tag = (PMULTIBOOT2_INFO_BOOT_LOADER_NAME)header;
				DbgPrint("[\033[1mINFO\033[m ] Boot loader name: `%s'\n", tag->LoaderName);
				break;
			}

			case TAG_TYPE_MEMORY_MAP: {
				PMULTIBOOT2_INFO_MEMORY_MAP tag = (PMULTIBOOT2_INFO_MEMORY_MAP)header;
				if (24 != tag->EntrySize) {
					DbgPanic("[\033[31;1mERROR\033[m] Unsupported size of `MULTIBOOT2_INFO_MEMORY_MAP'.");
				}

				SIZE_T memoryMapEntriesNum = (header->Size - sizeof(MULTIBOOT2_INFO_MEMORY_MAP)) / tag->EntrySize;

				UINT8 buffer[memoryMapEntriesNum * sizeof(PMM_MEMORY_MAP_ENTRY) + sizeof(PMM_MEMORY_MAP)];
				PPMM_MEMORY_MAP mmap = (PPMM_MEMORY_MAP)&buffer;

				mmap->EntriesNum = memoryMapEntriesNum;

				for (SIZE_T i = 0; i < memoryMapEntriesNum; i++) {
					mmap->Entries[i].Base = tag->Entries[i].Base;
					mmap->Entries[i].Size = tag->Entries[i].Lenght;

					switch (tag->Entries[i].Type) {
						case MEMORY_TYPE_AVAILABLE: {
							mmap->Entries[i].Type = PMM_MEMORY_TYPE_AVAILABLE;
							break;
						}

						case MEMORY_TYPE_RESERVED:
						case MEMORY_TYPE_ACPI_RECLAIMABLE:
						case MEMORY_TYPE_NVS: {
							mmap->Entries[i].Type = PMM_MEMORY_TYPE_RESERVED;
							break;
						}
					}
				}

				PmmInitialize(mmap, freeSpaceStart);

				break;
			}
		}
	}
}
