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
#include <hal/hal.h>
#include <rtl/rtl.h>
#include <common/vaarg.h>
#include <kernel/debug/debug.h>

VOID DbgInitialize(VOID) {
	HalEarlyPrintInit();
}

SIZE_T DbgPrint(CSTRING fmt, DBG_PREFIX_TYPE ptype, ...) {
	CHAR buffer[1024];
	VA_LIST ap;
	VA_START(ap, ptype);

	RtlvFormatString(buffer, 1024, fmt, ap);

	VA_END(ap);

	switch (ptype) {
		case DBG_PREFIX_TYPE_INFO: {
			HalEarlyPrint("[  INFO  ] ");
			break;
		}

		case DBG_PREFIX_TYPE_OK: {
			HalEarlyPrint("[   \033[32mOK\033[m   ] ");
			break;
		}

		case DBG_PREFIX_TYPE_ERROR: {
			HalEarlyPrint("[  \033[31mERROR\033[m ] ");
			break;
		}

		case DBG_PREFIX_TYPE_NONE: {
			HalEarlyPrint("           ");
			break;
		}
	}

	return HalEarlyPrint(buffer);
}

VOID DbgPanic(CSTRING fmt, ...) {
	CHAR buffer[1024];
	VA_LIST ap;
	VA_START(ap, fmt);

	RtlvFormatString(buffer, 1024, fmt, ap);

	VA_END(ap);

	HalEarlyPrint("[  \033[31mPANIC\033[m ] ");
	HalEarlyPrint(buffer);

	while (1) __asm__ __volatile__("hlt");
}
