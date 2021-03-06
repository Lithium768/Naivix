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

#include		<common/config.h>

.global			KiSystemStartup
.extern			KeSystemStartup

.section		.bss

.align			8

.lcomm			KiStack, KERNEL_STACK_SIZE

.section		.text
.code64

KiSystemStartup:movq	$0x0000000000000000, 0xfffffffffffff000
				invlpg	0x0000000000000000
				
				movabsq	$(KiStack + KERNEL_STACK_SIZE), %rsp
				push	%rbp
				movq	%rsp, %rbp
				
				movabsq	$KERNEL_BASE, %rbx
				leaq	(%rbx, %rdi), %rdi
				
				movabsq	$KeSystemStartup, %rax
				callq	*%rax
				
				leaveq
_halt:			hlt
				jmp		_halt
