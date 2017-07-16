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

#ifndef __EARLY_PRINT_H__
#define __EARLY_PRINT_H__

#include <common/types.h>

#define SCREEN_ALIGN_TAB 4

#define SCREEN_COL 80
#define SCREEN_LN 25

#define CRTC_ADDR_REG 0x3d4
#define CRTC_STARTADDR_H_ADDR 0xc
#define CRTC_STARTADDR_L_ADDR 0xd
#define CRTC_CURSOR_H_ADDR 0xe
#define CRTC_CURSOR_L_ADDR 0xf

#define CRTC_DATA_REG 0x3d5

#ifndef __ASM__

#define HalpScreen ((PSCREEN)0xffffc000000B8000)

typedef struct _SCREEN_WORD {
	UINT8 Char;
	union {
		UINT8 CharAttr;
		struct {
			UINT8 CharColor:3;
			UINT8 Bold:1;
			UINT8 BackgroundColor:3;
			UINT8 Blink:1;
		};
	};
} SCREEN_WORD, *PSCREEN_WORD;

typedef struct _SCREEN {
	SCREEN_WORD Word[4080];

	union {
		UINT16 Cursor;
		struct {
			UINT16 Cursor_L:8;
			UINT16 Cursor_H:8;
		};
	};

	union {
		UINT16 ScreenStart;
		struct {
			UINT16 ScreenStart_L:8;
			UINT16 ScreenStart_H:8;
		};
	};

	SCREEN_WORD WordType;
} SCREEN, *PSCREEN;

VOID HalpUpdateScreen(VOID);
VOID HalpPutChar(CHAR);

VOID HalpScreenCursorFixup(VOID);

#endif /* __ASM__ */

#endif /* __EARLY_PRINT_H__ */
