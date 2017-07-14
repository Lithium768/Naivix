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

#include		<header/multiboot2.h>
#include		<hal/misc.h>
#include		<hal/msr.h>

.global			HalpSystemStartup, HalpLongMode
.extern			KiSystemStartup
.extern			HalGDTREarly

.extern			lma_end

.section		.text.32
.align			8
.code32

HalpSystemStartup:
				cmpl	$MULTIBOOT2_LOADER_MAGIC, %eax
				jne		_invalid_magic_number

				movl	%ebx, %edi

				movl	$0x80000000, %eax
				cpuid
				cmpl	$0x80000001, %eax
				jb		_no_support_long_mode
				movl	$0x80000001, %eax
				cpuid
				btl		$29, %edx
				jnc		_no_support_long_mode

				movl	$lma_end, %ebx

				addl	$0x00000fff, %ebx
				andl	$0xfffff000, %ebx
				movl	%ebx, %eax
				andl	$0xffe00000, %eax
				orl		$0x00000603, %eax
				xorl	%ecx, %ecx
_pt_init_loop:	cmpl	%ebx, %eax
				jae		_pt_init_loop_end

				movl	%eax, (%ebx, %ecx, 8)
				movl	$0x00000000, 4(%ebx, %ecx, 8)

				addl	$0x00001000, %eax
				incl	%ecx

				jmp		_pt_init_loop
_pt_init_loop_end:
				testl	$511, %ecx
				jz		_pt_fill_loop_end

				movl	$0x00000000, (%ebx, %ecx, 8)
				movl	$0x00000000, 4(%ebx, %ecx, 8)

				incl	%ecx

				jmp		_pt_init_loop_end
_pt_fill_loop_end:

				movl	%ebx, %edx
				leal	(%ebx, %ecx, 8), %ebx
				movl	$0x00000683, %eax
				xorl	%ecx, %ecx
_pdt_init_loop:	cmpl	%ebx, %eax
				jae		_pdt_init_loop_end

				movl	%eax, (%ebx, %ecx, 8)
				movl	$0x00000000, 4(%ebx, %ecx, 8)

				addl	$0x00200000, %eax
				incl	%ecx

				jmp		_pdt_init_loop
_pdt_init_loop_end:
				cmpl	%ebx, %edx
				je		_pdt_fill_loop

				orl		$0x00000003, %edx
				movl	%edx, -8(%ebx, %ecx, 8)
				movl	$0x00000000, -4(%ebx, %ecx, 8)

_pdt_fill_loop:	testl	$511, %ecx
				jz		_pdt_fill_loop_end

				movl	$0x00000000, (%ebx, %ecx, 8)
				movl	$0x00000000, 4(%ebx, %ecx, 8)

				incl	%ecx

				jmp		_pdt_fill_loop
_pdt_fill_loop_end:

				movl	%ebx, %eax
				orl		$0x00000603, %eax
				leal	(%ebx, %ecx, 8), %ebx
				xorl	%ecx, %ecx
_pdpt_init_loop:cmpl	%ebx, %eax
				jae		_pdpt_init_loop_end

				movl	%eax, (%ebx, %ecx, 8)
				movl	$0x00000000, 4(%ebx, %ecx, 8)

				addl	$0x00001000, %eax
				incl	%ecx

				jmp		_pdpt_init_loop
_pdpt_init_loop_end:
				testl	$511, %ecx
				jz		_pdpt_fill_loop_end

				movl	$0x00000000, (%ebx, %ecx, 8)
				movl	$0x00000000, 4(%ebx, %ecx, 8)

				incl	%ecx

				jmp		_pdpt_init_loop_end
_pdpt_fill_loop_end:

				movl	%ebx, %eax
				orl		$0x00000603, %eax
				leal	(%ebx, %ecx, 8), %ebx
				xorl	%ecx, %ecx
_pml4t_fill_loop:
				testl	$511, %ecx
				jz		_pml4t_fill_loop_end

				movl	$0x00000000, (%ebx, %ecx, 8)
				movl	$0x00000000, 4(%ebx, %ecx, 8)

				incl	%ecx

				jmp		_pml4t_fill_loop
_pml4t_fill_loop_end:
				movl	%eax, (%ebx)
				movl	$0x00000000, 4(%ebx)

				movl	%eax, 3072(%ebx)
				movl	$0x00000000, 3076(%ebx)

				movl	%ebx, 4088(%ebx)
				orl		$0x00000603, 4088(%ebx)
				movl	$0x00000000, 4092(%ebx)

				movl	%ebx, %cr3

				movl	%ebx, %esi
				addl	$0x00001000, %esi

				movl	%cr4, %eax
				orl		$0x00000020, %eax
				movl	%eax, %cr4

				movl	$IA32_EFER, %ecx
				rdmsr
				orl		$0x00000100, %eax
				wrmsr

				movl	$0x80000023, %eax
				movl	%eax, %cr0

				lgdtl	HalGDTREarly
				ljmpl	$GDT_SELECTOR_KERNEL_CODE64, $HalpLongMode

_invalid_magic_number:
_no_support_long_mode:
				hlt
				jmp		_no_support_long_mode

.code64
.align			8

HalpLongMode:	movw	$GDT_SELECTOR_KERNEL_DATA, %cx
				movw	%cx, %ds
				movw	%cx, %es
				movw	%cx, %fs
				movw	%cx, %gs
				movw	%cx, %ss

				movabsq	$HalGDTR, %rax
				lgdtq	(%rax)

				movabsq	$KiSystemStartup, %rax
				jmp		*%rax
