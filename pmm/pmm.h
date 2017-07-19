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

#ifndef __PMM__

#include <common/types.h>

#ifndef __ASM__

#define			PmmPageTable				((PPAGING_PTE)0xffffff8000000000)
#define			PmmPageDirectoryTable		(PmmPageTable + 0xff8000000)
#define			PmmPageDirectoryPtrTable	(PmmPageDirectoryTable + 0x7fc0000)
#define			PmmPageMapLevel4Table		(PmmPageDirectoryPtrTable + 0x3fe00)

#define			PAGE_INDEX(addr)				(((addr) & 0x0000ffffffffffff) >> 12)
#define			PAGE_DIRECTORY_INDEX			(((addr) & 0x0000ffffffffffff) >> 21)
#define			PAGE_DIRECTORY_PTR_INDEX(addr)	(((addr) & 0x0000ffffffffffff) >> 30)
#define			PAGE_MAP_LEVEL_4_INDEX(addr)	(((addr) & 0x0000ffffffffffff) >> 39)

typedef struct _PAGING_PTE {
	union {
		struct {
			UINT64 Valid:1;
			UINT64 Writable:1;
			UINT64 Owner:1;
			UINT64 WriteThrough:1;
			UINT64 CacheDisable:1;
			UINT64 Accessed:1;
			UINT64 Dirty:1;
			UINT64 LargePage:1;
			UINT64 Global:1;
			UINT64 Type:3;
			UINT64 PageFrame:40;
			UINT64 _resvered_0:7;
			UINT64 ExecuteDisable:1;
		} Hardware;
	};
} PAGING_PTE, *PPAGING_PTE;

typedef enum _PMM_MEMORY_TYPE {
	PMM_MEMORY_TYPE_AVAILABLE,
	PMM_MEMORY_TYPE_RESERVED,
} PMM_MEMORY_TYPE;

typedef struct _PMM_MEMORY_MAP_ENTRY {
	ADDRESS Base;
	SIZE_T Size;
	PMM_MEMORY_TYPE Type;
} PMM_MEMORY_MAP_ENTRY, *PPMM_MEMORY_MAP_ENTRY;

typedef struct _PMM_MEMORY_MAP {
	SIZE_T EntriesNum;
	PMM_MEMORY_MAP_ENTRY Entries[];
} PMM_MEMORY_MAP, *PPMM_MEMORY_MAP;

VOID PmmInitialize(PPMM_MEMORY_MAP, ADDRESS);

#endif /* __ASM__ */

#endif /* __PMM__ */
