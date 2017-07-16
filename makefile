.PHONY : clean

rwildcard						=	$(wildcard $1$2) $(foreach d,$(wildcard $1*),$(call rwildcard,$d/,$2))

OBJECTS							=	$(patsubst %.c,%.o,$(call rwildcard,./,*.c)) $(patsubst %.S,%.o,$(call rwildcard,./,*.S))
TARGET							=	naivix
TARGET_MAP						=	$(TARGET).map
TARGET_ASM						=	$(TARGET).txt
TARGET_SYM						=	$(TARGET).sym

INCLUDE							=	./

NM								=	nm
NMFLAGS							=	

SED								=	sed
SEDFLAGS						=	-e 's/ffffc000/00000000/g'

RM								=	rm
RMFLAGS							=	-f

DISASM							=	objdump
DISASMFLAGS						=	-S

AS								=	gcc
ASFLAGS							=	-I$(INCLUDE) -m64 -c -D__ASM__ -mcmodel=large

CC								=	gcc
CCFLAGS							=	-c -std=c99 -m64 -Wall -Wextra -fno-builtin -fno-stack-protector -mcmodel=large
CPPFLAGS						=	-I$(INCLUDE)

LD								=	ld
LDSCRIPT						=	naivix.lds
LDFLAGS							=	-T$(LDSCRIPT) -melf_x86_64 -x

ifndef RELEASE
CCFLAGS							+=	-g -O1
CPPFLAGS						+=	-DDEBUG
else
CCFLAGS							+=	-O2
endif

$(TARGET) : $(OBJECTS)
	@echo "linking $@..."
	@$(LD) -o $@ -Map $(TARGET_MAP) $^ $(LDFLAGS)
	@$(DISASM) $@ $(DISASMFLAGS) > $(TARGET_ASM)
	@$(NM) $@ $(NMFLAGS) > $(TARGET_SYM).tmp
	@$(SED) $(TARGET_SYM).tmp $(SEDFLAGS) > $(TARGET_SYM)
	@$(RM) $(TARGET_SYM).tmp $(RMFLAGS)
	
clean :
	-@$(RM) $(TARGET) $(TARGET_MAP) $(TARGET_ASM) $(TARGET_SYM) $(OBJECTS) $(RMFLAGS)
	
%.o : %.c makefile
	@echo "compiling $<..."
	@$(CC) -o $@ $< $(CCFLAGS) $(CPPFLAGS)
	
%.o : %.S makefile
	@echo "assembling $<..."
	@$(AS) -o $@ $< $(ASFLAGS)
	
