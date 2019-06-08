deps_config := \
	/home/joao/esp/esp-idf/components/app_trace/Kconfig \
	/home/joao/esp/esp-idf/components/aws_iot/Kconfig \
	/home/joao/esp/esp-idf/components/bt/Kconfig \
	/home/joao/esp/esp-idf/components/driver/Kconfig \
	/home/joao/esp/esp-idf/components/esp32/Kconfig \
	/home/joao/esp/esp-idf/components/esp_adc_cal/Kconfig \
	/home/joao/esp/esp-idf/components/esp_event/Kconfig \
	/home/joao/esp/esp-idf/components/esp_http_client/Kconfig \
	/home/joao/esp/esp-idf/components/esp_http_server/Kconfig \
	/home/joao/esp/esp-idf/components/ethernet/Kconfig \
	/home/joao/esp/esp-idf/components/fatfs/Kconfig \
	/home/joao/esp/esp-idf/components/freemodbus/Kconfig \
	/home/joao/esp/esp-idf/components/freertos/Kconfig \
	/home/joao/esp/esp-idf/components/heap/Kconfig \
	/home/joao/esp/esp-idf/components/libsodium/Kconfig \
	/home/joao/esp/esp-idf/components/log/Kconfig \
	/home/joao/esp/esp-idf/components/lwip/Kconfig \
	/home/joao/esp/esp-idf/components/mbedtls/Kconfig \
	/home/joao/esp/esp-idf/components/mdns/Kconfig \
	/home/joao/esp/esp-idf/components/mqtt/Kconfig \
	/home/joao/esp/esp-idf/components/nvs_flash/Kconfig \
	/home/joao/esp/esp-idf/components/openssl/Kconfig \
	/home/joao/esp/esp-idf/components/pthread/Kconfig \
	/home/joao/esp/esp-idf/components/spi_flash/Kconfig \
	/home/joao/esp/esp-idf/components/spiffs/Kconfig \
	/home/joao/esp/esp-idf/components/tcpip_adapter/Kconfig \
	/home/joao/esp/esp-idf/components/vfs/Kconfig \
	/home/joao/esp/esp-idf/components/wear_levelling/Kconfig \
	/home/joao/esp/esp-idf/components/bootloader/Kconfig.projbuild \
	/home/joao/esp/esp-idf/components/esptool_py/Kconfig.projbuild \
	/home/joao/esp/esp-idf/components/partition_table/Kconfig.projbuild \
	/home/joao/esp/esp-idf/Kconfig

include/config/auto.conf: \
	$(deps_config)

ifneq "$(IDF_CMAKE)" "n"
include/config/auto.conf: FORCE
endif

$(deps_config): ;
