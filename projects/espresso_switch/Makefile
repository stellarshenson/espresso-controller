PROGRAM = 0x2000_espresso_switch

# spiffs configuration
SPIFFS_BASE_ADDR = 0x200000
SPIFFS_SIZE = 0x010000

BLANK_1M_FIRMWARE_NAME = 0x1000_blank_0x00_1M.bin
BOOTLOADER_FIRMWARE_NAME = 0x0000_rboot.bin 
BLANK_CONFIG_FIRMWARE_NAME = 0x1000_blank_config.bin
SPIFFS_FIRMWARE_NAME = $(SPIFFS_BASE_ADDR)_spiffs.bin

EXPORT_DIR = export

# generate UUID for the build
UUID = $(shell cat uuid.dat | sed 's/\(.*\)/\\"\1\\"/g' )
PROTO_UUID = $(shell cat uuid.dat | sed 's/^\(.\{8\}\)//g' | sed 's/\(.*\)/\\"\1\\"/g' )


EXTRA_COMPONENTS = \
	extras/http-parser \
	extras/dhcpserver \
	extras/sntp \
	extras/spiffs \
	$(abspath ../../components/esp-8266/esp-wifi-config) \
	$(abspath ../../components/esp-8266/esp-serial-cmdline) \
	$(abspath ../../components/esp-8266/led-status) \
	$(abspath ../../components/common/wolfssl) \
	$(abspath ../../components/common/cJSON) \
	$(abspath ../../components/common/homekit) \
	$(abspath ../../components/common/esp-adv-button)

FLASH_SIZE ?= 32


EXTRA_CFLAGS += -I../.. -DHOMEKIT_SHORT_APPLE_UUIDS -DUUID=$(UUID) -DPROTO_UUID=$(PROTO_UUID) -DWIFI_CONFIG_DEBUG

include $(SDK_PATH)/common.mk

$(eval $(call make_spiffs_image,files))


monitor:
	$(FILTEROUTPUT) --port $(ESPPORT) --baud 115200 --elf $(PROGRAM_OUT)

copy:
	cp firmware/$(PROGRAM).bin $(EXPORT_DIR)/

blank:
	dd if=/dev/zero of=firmware/$(BLANK_1M_FIRMWARE_NAME)  count=1 bs=1MB 

bootloader:
	cp $(SDK_PATH)/bootloader/firmware_prebuilt/rboot.bin firmware/$(BOOTLOADER_FIRMWARE_NAME)
	cp $(SDK_PATH)/bootloader/firmware_prebuilt/blank_config.bin firmware/$(BLANK_CONFIG_FIRMWARE_NAME)

suite: blank all bootloader 
	mv firmware/spiffs.bin firmware/$(SPIFFS_FIRMWARE_NAME)
	
#regenerate the uuid
uuid:
	cat /proc/sys/kernel/random/uuid > uuid.dat



