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
#include <hal/ep/ep.h>
#include <hal/misc.h>

VOID HalEarlyPrintInit(VOID) {
	for (SIZE_T i = 0; i < sizeof(HalpScreen->Word) / sizeof(HalpScreen->Word[0]); i++) {
		HalpScreen->Word[i].Char = ' ';
		HalpScreen->Word[i].CharAttr = 0x07;
	}

	HalpScreen->Cursor = 0;
	HalpScreen->ScreenStart = 0;
	HalpScreen->WordType.Char = ' ';
	HalpScreen->WordType.CharAttr = 0x07;

	HalpUpdateScreen();
}

SIZE_T HalEarlyPrint(CSTRING string) {
	SIZE_T n = 0;
	for (; *string != '\0'; string++) {
		if (*string < ' ') {
			switch (*string) {
				case '\n': {
					HalpScreen->Cursor += SCREEN_COL;
					HalpScreen->Cursor /= SCREEN_COL;
					HalpScreen->Cursor *= SCREEN_COL;
					break;
				}

				case '\r': {
					HalpScreen->Cursor /= SCREEN_COL;
					HalpScreen->Cursor *= SCREEN_COL;
					break;
				}

				case '\t': {
					HalpScreen->Cursor += SCREEN_ALIGN_TAB;
					HalpScreen->Cursor /= SCREEN_ALIGN_TAB;
					HalpScreen->Cursor *= SCREEN_ALIGN_TAB;
					break;
				}

				case '\033': {
					switch (*++string) {
						case '[': {
							SIZE_T operandNum = 0;
							CHAR operator;
							for (CSTRING position = string + 1; ((*position >= '0') && (*position <= '9')) || (operandNum++, operator = *position, *position == ';'); position++);

							UINT64 operand[operandNum];
							SIZE_T operandIndex = 0;
							do {
								operand[operandIndex] = 0;
								for (CHAR c = *++string; (c >= '0') && (c <= '9'); c = *++string) {
									operand[operandIndex] = operand[operandIndex] * 10 + c - '0';
								}
								operandIndex++;
							} while (*string == ';');

							switch (operator) {
								case 'm': {
									for (SIZE_T i = 0; i < operandNum; i++) {
										switch (operand[i]) {
											case 0: {
												HalpScreen->WordType.CharAttr = 0x07;
												break;
											}

											case 1: {
												HalpScreen->WordType.Bold = true;
												break;
											}

											case 5: {
												HalpScreen->WordType.Blink = true;
												break;
											}

											default: {
												if ((operand[i] >= 30) && (operand[i] <= 37)) {
													operand[i] -= 30;

													UINT64 blue = (operand[i] & 0x4) >> 2;
													operand[i] &= -0x5;
													operand[i] |= (operand[i] & 0x1) << 2;
													operand[i] &= -0x2;
													operand[i] |= blue;

													HalpScreen->WordType.CharColor = operand[i];
												} else if ((operand[i] >= 40) && (operand[i] <= 47)) {
													operand[i] -= 40;

													UINT64 blue = (operand[i] & 0x4) >> 2;
													operand[i] &= -0x5;
													operand[i] |= operand[i] & 0x1;
													operand[i] &= -0x2;
													operand[i] |= blue;

													HalpScreen->WordType.BackgroundColor = operand[i];
												}
												break;
											}
										}
									}
									break;
								}

								default: {
									break;
								}
							}
							break;
						}

						default: {
							HalpPutChar('?');
							string--;
						}
					}
					break;
				}

				default: {
					HalpPutChar('?');
					break;
				}
			}
			HalpScreenCursorFixup();
		} else {
			HalpPutChar(*string);
		}

		n++;
	}

	HalpUpdateScreen();

	return n;
}

VOID HalpPutChar(CHAR c) {
	HalpScreen->Word[HalpScreen->Cursor] = HalpScreen->WordType;
	HalpScreen->Word[HalpScreen->Cursor].Char = c;

	HalpScreen->Cursor++;
	HalpScreenCursorFixup();
}

VOID HalpScreenCursorFixup(VOID) {
	if (HalpScreen->Cursor == sizeof(HalpScreen->Word) / sizeof(HalpScreen->Word[0])) {
		HalFastMemoryCopy(&HalpScreen->Word[0], &HalpScreen->Word[SCREEN_COL], sizeof(HalpScreen->Word) - SCREEN_COL * sizeof(HalpScreen->Word[0]));
		for (SIZE_T i = sizeof(HalpScreen->Word) / sizeof(HalpScreen->Word[0]) - SCREEN_COL; i < sizeof(HalpScreen->Word) / sizeof(HalpScreen->Word[0]); i++) {
			HalpScreen->Word[HalpScreen->Cursor] = HalpScreen->WordType;
			HalpScreen->Word[i].Char = ' ';
		}
		HalpScreen->Cursor = sizeof(HalpScreen->Word) / sizeof(HalpScreen->Word[0]) - SCREEN_COL;
	}

	if (HalpScreen->Cursor - HalpScreen->ScreenStart >= SCREEN_COL * SCREEN_LN) {
		HalpScreen->ScreenStart  = (HalpScreen->Cursor + SCREEN_COL) / SCREEN_COL * SCREEN_COL - SCREEN_COL * SCREEN_LN;
	}
}

VOID HalpUpdateScreen(VOID) {
	HalpOutByte(CRTC_ADDR_REG, CRTC_STARTADDR_H_ADDR);
	HalpOutByte(CRTC_DATA_REG, HalpScreen->ScreenStart_H);

	HalpOutByte(CRTC_ADDR_REG, CRTC_STARTADDR_L_ADDR);
	HalpOutByte(CRTC_DATA_REG, HalpScreen->ScreenStart_L);

	HalpOutByte(CRTC_ADDR_REG, CRTC_CURSOR_H_ADDR);
	HalpOutByte(CRTC_DATA_REG, HalpScreen->Cursor_H);

	HalpOutByte(CRTC_ADDR_REG, CRTC_CURSOR_L_ADDR);
	HalpOutByte(CRTC_DATA_REG, HalpScreen->Cursor_L);
}
