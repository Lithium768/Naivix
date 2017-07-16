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

#ifndef __MULTIBOOT2_H__
#define __MULTIBOOT2_H__

#include <common/types.h>

#define			MULTIBOOT2_HEADER_ALIGN			8
#define 		MULTIBOOT2_HEADER_MAGIC			0xe85250d6
#define			MULTIBOOT2_HEADER_ARCHITECTURE	0x00000000

#define			MULTIBOOT2_HEADER_TAG_OPTIONAL	0x00000000

#define			MULTIBOOT2_LOADER_MAGIC			0x36d76289

#define			MULTIBOOT2_HEADER_TAG_END_TYPE	0x00000000

#ifndef __ASM__

typedef enum _MULTIBOOT2_INFO_TAG_TYPE {
	TAG_TYPE_END = 0,
	TAG_TYPE_BOOT_COMMAND_LINE = 1,
	TAG_TYPE_BOOT_LOADER_NAME = 2,
	TAG_TYPE_MEMORY_MAP = 6
} MULTIBOOT2_INFO_TAG_TYPE;

typedef struct _MULTIBOOT2_INFO_TAG_HEADER {
	UINT32 Type;
	UINT32 Size;
} MULTIBOOT2_INFO_TAG_HEADER, *PMULTIBOOT2_INFO_TAG_HEADER;

typedef struct _MULTIBOOT2_INFO {
	SIZE_T TotalSize:32;
	SIZE_T _TotalSize:32;

	MULTIBOOT2_INFO_TAG_HEADER Tags[];
} MULTIBOOT2_INFO, *PMULTIBOOT2_INFO;

typedef struct _MULTIBOOT2_INFO_BOOT_COMMAND_LINE {
	MULTIBOOT2_INFO_TAG_HEADER Header;
	CHAR CommandLine[];
} MULTIBOOT2_INFO_BOOT_COMMAND_LINE, *PMULTIBOOT2_INFO_BOOT_COMMAND_LINE;

typedef enum _MEMORY_MAP_ENTRY_TYPE {
	MEMORY_TYPE_AVAILABLE = 1,
	MEMORY_TYPE_RESERVED = 2,
	MEMORY_TYPE_ACPI_RECLAIMABLE = 3,
	MEMORY_TYPE_NVS = 4
} MEMORY_MAP_ENTRY_TYPE;

typedef struct _MULTIBOOT2_INFO_MEMORY_MAP {
	MULTIBOOT2_INFO_TAG_HEADER Header;
	UINT32 EntrySize;
	UINT32 EntryVersion;

	struct {
		UINT64 Base;
		UINT64 Lenght;
		UINT64 Type:32;
		UINT64 _Type:32;
	} Entries[];
} MULTIBOOT2_INFO_MEMORY_MAP, *PMULTIBOOT2_INFO_MEMORY_MAP;

typedef struct _MULTIBOOT2_INFO_BOOT_LOADER_NAME {
	MULTIBOOT2_INFO_TAG_HEADER Header;
	CHAR LoaderName[];
} MULTIBOOT2_INFO_BOOT_LOADER_NAME, *PMULTIBOOT2_INFO_BOOT_LOADER_NAME;

#endif /* __ASM__ */

#endif /* __MULTIBOOT2_H__ */
