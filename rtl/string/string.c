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
#include <common/vaarg.h>
#include <rtl/string/string.h>
#include <rtl/rtl.h>

SIZE_T RtlvFormatString(STRING str, SIZE_T size, CSTRING fmt, VA_LIST ap) {
	SIZE_T lenght;
	for (lenght = 0; (lenght < size) && (*fmt); fmt++) {
		if (*fmt == '%') {
			fmt++;

			BOOL isLeft = false;
			for (CHAR c = *fmt; (c == '-') || (c == ' ') || (c == '0'); c = *++fmt) {
				if (c == '-') {
					isLeft = true;
				}
			}
			CHAR paddingChar = isLeft ? ' ' : fmt[-1];

			SIZE_T paddingWidth = 0;
			for (CHAR c = *fmt; (c >= '0') && (c <= '9'); c = *++fmt) {
				paddingWidth = paddingWidth * 10 + c - '0';
			}

			switch (*fmt) {
				case 'c': {
					*str++ = VA_ARG(ap, UINT64);
					lenght++;
					break;
				}

				case 's': {
					STRING arg = VA_ARG(ap, STRING);
					SIZE_T n = RtlpCopyStringWithPadding(str, size - lenght, arg, isLeft, paddingChar, paddingWidth);
					str += n;
					lenght += n;
					break;
				}

				case 'u': {
					CHAR buffer[21];
					RtlParseIntToString(buffer, 21, VA_ARG(ap, UINT64), 10);
					SIZE_T n = RtlpCopyStringWithPadding(str, size - lenght, buffer, isLeft, paddingChar, paddingWidth);
					str += n;
					lenght += n;
					break;
				}

				case 'd': {
					CHAR buffer[20];
					INT64 arg = VA_ARG(ap, INT64);
					if (arg < 0) {
						arg = -arg;
						RtlParseIntToString(buffer, 20, arg, 10);
						*str++ = '-';
						lenght++;
						paddingWidth > 0 ? paddingWidth-- : false;
					} else {
						RtlParseIntToString(buffer, 20, arg, 10);
					}
					SIZE_T n = RtlpCopyStringWithPadding(str, size - lenght, buffer, isLeft, paddingChar, paddingWidth);
					str += n;
					lenght += n;
					break;
				}

				case 'x': {
					CHAR buffer[17];
					RtlParseIntToString(buffer, 17, VA_ARG(ap, UINT64), 16);
					SIZE_T n = RtlpCopyStringWithPadding(str, size - lenght, buffer, isLeft, paddingChar, paddingWidth);
					str += n;
					lenght += n;
					break;
				}

				case 'b': {
					CHAR buffer[65];
					RtlParseIntToString(buffer, 65, VA_ARG(ap, UINT64), 2);
					SIZE_T n = RtlpCopyStringWithPadding(str, size - lenght, buffer, isLeft, paddingChar, paddingWidth);
					str += n;
					lenght += n;
					break;
				}

				case 'o': {
					CHAR buffer[23];
					RtlParseIntToString(buffer, 23, VA_ARG(ap, UINT64), 8);
					SIZE_T n = RtlpCopyStringWithPadding(str, size - lenght, buffer, isLeft, paddingChar, paddingWidth);
					str += n;
					lenght += n;
					break;
				}

				default: {
					*str++ = *fmt;
					lenght++;
					break;
				}
			}

		} else {
			*str++ = *fmt;
			lenght++;
		}
	}

	if (lenght < size) {
		*str = '\0';
		return lenght;
	} else {
		str[size - lenght - 1] = '\0';
		return size;
	}
}

SIZE_T RtlFormatString(STRING str, SIZE_T size, CSTRING fmt, ...) {
	VA_LIST ap;
	VA_START(ap, fmt);

	SIZE_T lenght = RtlvFormatString(str, size, fmt, ap);

	VA_END(ap);

	return lenght;
}

SIZE_T RtlpCopyStringWithPadding(STRING dest, SIZE_T size, CSTRING src, BOOL isLeft, CHAR paddingChar, SIZE_T paddingWidth) {
	SIZE_T paddingLenght = paddingWidth > RtlGetStringLenght(src) ? paddingWidth - RtlGetStringLenght(src) : 0;
	SIZE_T position = 0;

	if (!isLeft) {
		position += RtlpFillString(dest, size, paddingChar, paddingLenght);
	}

	position += RtlCopyString(dest + position, src, size - position);

	if (isLeft) {
		position += RtlpFillString(dest + position, size - position, paddingChar, paddingLenght);
	}

	return position;
}

SIZE_T RtlGetStringLenght(CSTRING string) {
	SIZE_T lenght = 0;
	while (*string++) {
		lenght++;
	}
	return lenght;
}

SIZE_T RtlpFillString(STRING str, SIZE_T size, CHAR fillChar, SIZE_T fillLenght) {
	SIZE_T lenght;
	for (lenght = 0; (lenght < size) && (fillLenght != 0); lenght++, str++, fillLenght--) {
		*str = fillChar;
	}

	return lenght;
}

SIZE_T RtlCopyString(STRING dest, CSTRING str, SIZE_T lenght) {
	SIZE_T copiedLenght;
	for (copiedLenght = 0; (copiedLenght < lenght) && (*str != '\0'); copiedLenght++, str++, dest++) {
		*dest = *str;
	}

	return copiedLenght;
}

SIZE_T RtlParseIntToString(STRING str, SIZE_T size, UINT64 integer, UINT8 base) {
	CHAR buffer[64];

	if ((base > 16) && (base < 2)) {
		return 0;
	}

	SIZE_T position = 64;
	do {
		UINT64 remainder = integer % base;
		integer /= base;

		if (remainder < 10) {
			buffer[--position] = remainder + '0';
		} else {
			buffer[--position] = remainder + 'A' - 10;
		}
	} while (integer != 0);

	if (64 - position > size - 1) {
		return 0;
	}

	RtlCopyString(str, buffer + position, 64 - position);
	str[64 - position] = '\0';

	return 64 - position;
}
