 #####
 # Project: OpenPilot
 #    
 #  
 # Makefile for OpenPilot project build PiOS and the AP.
 #
 # dRonin, http://dRonin.org/, Copyright (C) 2016
 # The OpenPilot Team, http://www.openpilot.org, Copyright (C) 2009.
 #    
 # 
 # This program is free software; you can redistribute it and/or modify 
 # it under the terms of the GNU General Public License as published by 
 # the Free Software Foundation; either version 3 of the License, or 
 # (at your option) any later version.
 # 
 # This program is distributed in the hope that it will be useful, but 
 # WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 # or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License 
 # for more details.
 # 
 # You should have received a copy of the GNU General Public License along 
 # with this program; if not, see <http://www.gnu.org/licenses/>
 #
 # Additional note on redistribution: The copyright and license notices above
 # must be maintained in each individual source file that is a derivative work
 # of this source file; otherwise redistribution is prohibited.
 #
 #####

ifndef MAKE_INC_DIR
$(error This Makefile cannot be run directly)
endif
include $(MAKE_INC_DIR)/firmware-defs.mk

# Paths
PIOSINC = $(PIOS)/inc
PIOSSTM32F10X = $(PIOS)/STM32F10x
PIOSCOMMON = $(PIOS)/Common
PIOSCOMMONLIB = $(PIOSCOMMON)/Libraries
STMLIBDIR = $(PIOSSTM32F10X)/Libraries
STMSPDDIR = $(STMLIBDIR)/STM32F10x_StdPeriph_Driver
STMSPDSRCDIR = $(STMSPDDIR)/src
STMSPDINCDIR = $(STMSPDDIR)/inc
CMSISDIR  = $(STMLIBDIR)/CMSIS/Core/CM3

# List C source files here. (C dependencies are automatically generated.)
# use file-extension c for "c-only"-files

## Bootloader Updater (common)
SRC += $(BUCOMMONDIR)/main.c
SRC += $(BUCOMMONDIR)/bu_payload.c
SRC += $(BUCOMMONDIR)/pios_board.c

## Bootloader Updater (architecture specific)
#SRC += $(BUARCHDIR)/pios_board.c

## Bootloader Updater (board specific implementations)

## PIOS Hardware (STM32F10x)
SRC += pios_sys.c
SRC += pios_annunc.c
SRC += pios_flash_internal.c

## PIOS Hardware (Common)
SRC += pios_delay.c
SRC += pios_flash.c
SRC += pios_heap.c
SRC += pios_semaphore.c
SRC += pios_irq.c


## CMSIS for STM32
include $(PIOSCOMMONLIB)/CMSIS/library.mk
SRC += $(BOARD_INFO_DIR)/cmsis_system.c

## Used parts of the STM-Library
SRC += $(STMSPDSRCDIR)/stm32f10x_flash.c
SRC += $(STMSPDSRCDIR)/stm32f10x_gpio.c
SRC += $(STMSPDSRCDIR)/stm32f10x_rcc.c
SRC += $(STMSPDSRCDIR)/stm32f10x_rtc.c
SRC += $(STMSPDSRCDIR)/stm32f10x_tim.c
SRC += $(STMSPDSRCDIR)/misc.c

# List Assembler source files here.
# Make them always end in a capital .S. Files ending in a lowercase .s
# will not be considered source files but generated files (assembler
# output from the compiler), and will be deleted upon "make clean"!
# Even though the DOS/Win* filesystem matches both .s and .S the same,
# it will preserve the spelling of the filenames, and gcc itself does
# care about how the name is spelled on its command-line.
ASRC = $(PIOSSTM32F10X)/startup_stm32f10x_$(MODEL)$(MODEL_SUFFIX).S

# List any extra directories to look for include files here.
#    Each directory must be seperated by a space.
EXTRAINCDIRS  += $(PIOS)
EXTRAINCDIRS  += $(PIOSINC)
EXTRAINCDIRS  += $(PIOSSTM32F10X)/inc
EXTRAINCDIRS  += $(STMSPDINCDIR)
EXTRAINCDIRS  += $(CMSISDIR)
EXTRAINCDIRS  += $(BOARD_INFO_DIR)
EXTRAINCDIRS  += $(BUBOARDDIR)
EXTRAINCDIRS  += $(BUARCHDIR)
EXTRAINCDIRS  += $(BUCOMMONDIR)

# Path to Linker-Scripts
LINKERSCRIPTPATH = $(PIOSSTM32F10X)


PAYLOAD_FILE = $(ROOT_DIR)/build/bl_$(BOARD_NAME)/bl_$(BOARD_NAME).bin

# Place project-specific -D (define) and/or 
# -U options for C here.
#
# This exists to prevent ccache from caching compilation results when the file
# has changed.  md5sum is used on linux and Windows; cksum is used on mac.
CDEFS += -DBU_HASH=$(shell md5sum "$(PAYLOAD_FILE)" 2>/dev/null | cut -d ' ' -f 1 || cksum "$(PAYLOAD_FILE)" | cut -d ' ' -f 1)
CDEFS = -DSTM32F10X_$(MODEL)
#CDEFS += -DHSE_VALUE=$(OSCILLATOR_FREQ)
CDEFS += -DUSE_STDPERIPH_DRIVER
CDEFS += -DUSE_$(BOARD)
CDEFS += -DBU_PAYLOAD_FILE=$(PAYLOAD_FILE)

# Place project-specific -D and/or -U options for 
# Assembler with preprocessor here.
ADEFS = -D__ASSEMBLY__

#-----

# Compiler flags.

#  -g*:          generate debugging information
#  -O*:          optimization level
#  -f...:        tuning, see GCC manual and avr-libc documentation
#  -Wall...:     warning level
#  -Wa,...:      tell GCC to pass this to the assembler.
#    -adhlns...: create assembler listing
#
# Flags for C and C++ (arm-elf-gcc/arm-elf-g++)

CFLAGS += -gdwarf-2
CFLAGS += -Os -fconserve-stack
CFLAGS += -ffunction-sections

CFLAGS += -mcpu=$(MCU) -mthumb
CFLAGS += $(CDEFS)
CFLAGS += $(patsubst %,-I%,$(EXTRAINCDIRS)) -I.

CFLAGS += -mapcs-frame 
CFLAGS += -fomit-frame-pointer

CFLAGS += -Wall 
CFLAGS += -Werror
CFLAGS += -Wa,-adhlns=$(addprefix $(OUTDIR)/, $(notdir $(addsuffix .lst, $(basename $<))))
# Compiler flags to generate dependency files:
CFLAGS += -MD -MP -MF $(OUTDIR)/dep/$(@F).d

# flags only for C
CONLYFLAGS += -std=gnu99

# Assembler flags.
#  -Wa,...:    tell GCC to pass this to the assembler.
#  -ahlns:     create listing
ASFLAGS  = -mcpu=$(MCU) -mthumb -I. -x assembler-with-cpp
ASFLAGS += $(ADEFS)
ASFLAGS += -Wa,-adhlns=$(addprefix $(OUTDIR)/, $(notdir $(addsuffix .lst, $(basename $<))))
ASFLAGS += $(patsubst %,-I%,$(EXTRAINCDIRS))

# Linker flags.
#  -Wl,...:     tell GCC to pass this to linker.
#    -Map:      create map file
#    --cref:    add cross reference to  map file
LDFLAGS = -nostartfiles -Wl,-Map=$(OUTDIR)/$(TARGET).map,--cref,--gc-sections
LDFLAGS += -Wl,-static
LDFLAGS += -lc_nano -lgcc 
LDFLAGS += -Wl,--warn-common
LDFLAGS += -Wl,--fatal-warnings

# Set linker-script name depending on selected submodel name
LDFLAGS += -T$(LINKERSCRIPTPATH)/link_$(BOARD)_memory.ld
LDFLAGS += -T$(LINKERSCRIPTPATH)/link_$(BOARD)_sections.ld

# List of all source files.
ALLSRC     = $(ASRC) $(SRC)
# List of all source files without directory and file-extension.
ALLSRCBASE = $(notdir $(basename $(ALLSRC)))

# Define all object files.
ALLOBJ     = $(addprefix $(OUTDIR)/, $(addsuffix .o, $(ALLSRCBASE)))

# Link: create ELF output file from object files.
$(eval $(call LINK_TEMPLATE, $(OUTDIR)/$(TARGET).elf, $(ALLOBJ)))

# Assemble: create object files from assembler source files.
$(foreach src, $(ASRC), $(eval $(call ASSEMBLE_TEMPLATE, $(src)))) 

# Compile: create object files from C source files.
$(foreach src, $(SRC), $(eval $(call COMPILE_C_TEMPLATE, $(src)))) 

# Compile: create assembler files from C source files. ARM/Thumb
$(eval $(call PARTIAL_COMPILE_TEMPLATE, SRC))

$(eval $(call TLFW_TEMPLATE,$(OUTDIR)/$(TARGET).bin,$(BOARD_TYPE),$(BOARD_REVISION)))

.PHONY: elf hex bin tlfw
elf: $(OUTDIR)/$(TARGET).elf
hex: $(OUTDIR)/$(TARGET).hex
bin: $(OUTDIR)/$(TARGET).bin
tlfw: $(OUTDIR)/$(TARGET).tlfw

# Display sizes of sections.
$(eval $(call SIZE_TEMPLATE, $(OUTDIR)/$(TARGET).elf))

# Generate Doxygen documents
docs:
	doxygen  $(DOXYGENDIR)/doxygen.cfg

# Create output files directory
# all known MS Windows OS define the ComSpec environment variable
ifdef ComSpec
$(shell md $(subst /,\\,$(OUTDIR)) 2>NUL)
else
$(shell mkdir -p $(OUTDIR) 2>/dev/null)
endif

# Include the dependency files.
ifdef ComSpec
-include $(shell md $(subst /,\\,$(OUTDIR))\dep 2>NUL) $(wildcard $(OUTDIR)/dep/*)
else
-include $(shell mkdir -p $(OUTDIR) 2>/dev/null) $(shell mkdir $(OUTDIR)/dep 2>/dev/null) $(wildcard $(OUTDIR)/dep/*)
endif

ifneq ($(BU_PAD_AND_REPEAT_OFFS),)
# This pads the bin to have two entry locations.  Used on PlayUAV OSD where
# we could be running from PX4 loader (16k offset) or our loader (128k offset)
%.padded.bin: %.bin
	$(V1) $(OBJCOPY) --pad-to=$(BU_PAD_AND_REPEAT_OFFS) -I binary -O binary $< $@
	$(V1) cat $< >> $@
else
%.padded.bin: %.bin
	$(V1) cp $< $@
endif
