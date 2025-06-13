# The following variables contains the files used by the different stages of the build process.
set(2414_DES_SP7_TestSprinkler_default_default_XC32_FILE_TYPE_assemble)
set_source_files_properties(${2414_DES_SP7_TestSprinkler_default_default_XC32_FILE_TYPE_assemble} PROPERTIES LANGUAGE ASM)
set(2414_DES_SP7_TestSprinkler_default_default_XC32_FILE_TYPE_assembleWithPreprocess)
set_source_files_properties(${2414_DES_SP7_TestSprinkler_default_default_XC32_FILE_TYPE_assembleWithPreprocess} PROPERTIES LANGUAGE ASM)
set(2414_DES_SP7_TestSprinkler_default_default_XC32_FILE_TYPE_compile
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../../framework/driver/sdcard/src/dynamic/drv_sdcard.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../../framework/driver/spi/src/drv_spi_sys_queue_fifo.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../../framework/driver/spi/src/dynamic/drv_spi.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../../framework/system/fs/fat_fs/src/file_system/ff.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../../framework/system/fs/fat_fs/src/hardware_access/diskio.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../../framework/system/fs/src/dynamic/sys_fs.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../../framework/system/fs/src/dynamic/sys_fs_media_manager.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../../framework/system/int/src/sys_int_pic32.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../../framework/system/tmr/src/sys_tmr.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/Driver_SR_SN74HCS596QPWRQ1.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/GesFifoTh32.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/Mc32_I2cUtilCCS.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/Mc32_sdFatGest.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/Mc32gestI2cSeeprom.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/Mc32gest_RS232.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/PIC32130_AT42QT2120_I2C.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/app.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/main.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/mcp79411.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/framework/driver/adc/src/drv_adc_static.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/framework/driver/spi/dynamic/drv_spi_api.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/framework/driver/spi/dynamic/drv_spi_master_ebm_tasks.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/framework/driver/spi/dynamic/drv_spi_tasks.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/framework/driver/tmr/src/drv_tmr_mapping.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/framework/driver/tmr/src/drv_tmr_static.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/framework/driver/usart/src/drv_usart_mapping.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/framework/driver/usart/src/drv_usart_static.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/framework/driver/usart/src/drv_usart_static_byte_model.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/framework/system/clk/src/sys_clk_pic32mx.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/framework/system/devcon/src/sys_devcon.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/framework/system/devcon/src/sys_devcon_pic32mx.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/framework/system/ports/src/sys_ports_static.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/system_exceptions.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/system_init.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/system_interrupt.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/system_tasks.c")
set_source_files_properties(${2414_DES_SP7_TestSprinkler_default_default_XC32_FILE_TYPE_compile} PROPERTIES LANGUAGE C)
set(2414_DES_SP7_TestSprinkler_default_default_XC32_FILE_TYPE_compile_cpp)
set_source_files_properties(${2414_DES_SP7_TestSprinkler_default_default_XC32_FILE_TYPE_compile_cpp} PROPERTIES LANGUAGE CXX)
set(2414_DES_SP7_TestSprinkler_default_default_XC32_FILE_TYPE_link "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../../bin/framework/peripheral/PIC32MX795F512L_peripherals.a")
set(2414_DES_SP7_TestSprinkler_default_image_name "default.elf")


# The output directory of the final image.
set(2414_DES_SP7_TestSprinkler_default_output_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../out/2414-DES_SP7_TestSprinkler")
