PROGRAM = 0x20000_espresso_switch
EXPORT_DIR = export

# generate UUID for the build
UUID = $(shell cat uuid.dat | sed 's/\(.*\)/\\"\1\\"/g' )
PROTO_UUID = $(shell cat uuid.dat | sed 's/^\(.\{8\}\)//g' | sed 's/\(.*\)/\\"\1\\"/g' )


EXTRA_COMPONENTS = \
	extras/http-parser \
	extras/dhcpserver \
	$(abspath ../../components/esp-8266/esp-wifi-config) \
	$(abspath ../../components/esp-8266/esp-serial-cmdline) \
	$(abspath ../../components/common/wolfssl) \
	$(abspath ../../components/common/cJSON) \
	$(abspath ../../components/common/homekit) \
	$(abspath ../../components/common/esp-button)

FLASH_SIZE ?= 32


EXTRA_CFLAGS += -I../.. -DHOMEKIT_SHORT_APPLE_UUIDS 
#-DUUID=$(UUID) -DPROTO_UUID=$(PROTO_UUID)
include $(SDK_PATH)/common.mk

monitor:
	$(FILTEROUTPUT) --port $(ESPPORT) --baud 115200 --elf $(PROGRAM_OUT)

copy:
	cp firmware/$(PROGRAM).bin $(EXPORT_DIR)/

blank:
	dd if=/dev/zero of=firmware/0x10000_blank_0x00_1M.bin count=1 bs=1MB 

bootloader:
	cp $(SDK_PATH)/bootloader/firmware_prebuilt/rboot.bin firmware/0x00000_rboot.bin

suite: blank all bootloader


#regenerate the uuid
uuid:
	cat /proc/sys/kernel/random/uuid > uuid.dat
