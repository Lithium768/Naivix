OUTPUT_FORMAT("elf64-x86-64", "elf64-x86-64", "elf64-x86-64")
OUTPUT_ARCH(i386:x86-64)
ENTRY(HalpSystemStartup)
SECTIONS
{	
	PROVIDE(__executable32_start = SEGMENT_START("text32-segment", 0x400000));
	. = __executable32_start + SIZEOF_HEADERS;
	
	.multiboot2_header 0x0 : AT(0x0)
	{
		*(.multiboot2_header)
	}
	
	.text.32 :
	{
		*(.text.32)
	}
	
	.rodata.32 :
	{
		*(.rodata.32)
	}
	
	PROVIDE(__executable_start = SEGMENT_START("text-segment", 0xffffc00000400000));
	PROVIDE(__executable_base = __executable_start - __executable32_start);
	. += __executable_base;
	
	.text : AT(__text_lma_start)
	{
		__text_lma_start = . - __executable_start + __executable32_start;
		*(.text)
	}
	
	.rodata : AT(__rodata_lma_start)
	{
		__rodata_lma_start = . - __executable_start + __executable32_start;
		*(.rodata)
	}
	
	.data : AT(__data_lma_start)
	{
		__data_lma_start = . - __executable_start + __executable32_start;
		*(.data)
	}
	
	.bss : AT(__bss_lma_start)
	{
		__bss_lma_start = . - __executable_start + __executable32_start;
		*(.bss)
		. = ALIGN(4K);
	}
	
	PROVIDE(lma_end = . - __executable_start + __executable32_start);
}
