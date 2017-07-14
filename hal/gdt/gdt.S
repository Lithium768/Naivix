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

.global			HalGDTREarly, HalGDTR

.section		.rodata.32

.align			8

HalGDTEarly:
.quad			0x0000000000000000
.quad			0x0020980000000000

HalGDTREarly:
.word			HalGDTREarly - HalGDTEarly - 1
.long			HalGDTEarly

.section		.rodata

.align			8

HalGDT:
.quad			0x0000000000000000
.quad			0x0020980000000000

HalGDTR:
.word			HalGDTR - HalGDT - 1
.quad			HalGDT
