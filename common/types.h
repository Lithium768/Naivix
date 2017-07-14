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

#ifndef __TYPES_H__
#define __TYPES_H__

#ifndef __ASM__

typedef unsigned char UINT8, *UINT8_PTR;
typedef   signed char  INT8, * INT8_PTR;

typedef unsigned short int UINT16, *UINT16_PTR;
typedef   signed short int  INT16, * INT16_PTR;

typedef unsigned int UINT32, *UINT32_PTR;
typedef   signed int  INT32, * INT32_PTR;

typedef unsigned long int UINT64, *UINT64_PTR;
typedef   signed long int  INT64, * INT64_PTR;

typedef void VOID, *PVOID;

typedef       char * STRING, CHAR;
typedef const char *CSTRING;

typedef unsigned long long int ADDRESS, *ADDRESS_PTR;
typedef unsigned long long int SIZE_T;

typedef enum _BOOL {
	false = 0,
	true = !false
} BOOL;

typedef VOID (*FUNCTION)(VOID);

#define null 0

#endif /* __ASM__ */

#endif /* __TYPES_H__ */
