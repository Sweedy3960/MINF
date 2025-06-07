# The following variables contains the files used by the different stages of the build process.
set(SPB7_Screen_default_default_XC32_FILE_TYPE_assemble)
set_source_files_properties(${SPB7_Screen_default_default_XC32_FILE_TYPE_assemble} PROPERTIES LANGUAGE ASM)
set(SPB7_Screen_default_default_XC32_FILE_TYPE_assembleWithPreprocess)
set_source_files_properties(${SPB7_Screen_default_default_XC32_FILE_TYPE_assembleWithPreprocess} PROPERTIES LANGUAGE ASM)
set(SPB7_Screen_default_default_XC32_FILE_TYPE_compile
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../../framework/system/int/src/sys_int_pic32.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/Display.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/LCD_Driver.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/app.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/main.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/bsp/bsp.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/framework/driver/spi/static/src/drv_spi_mapping.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/framework/driver/spi/static/src/drv_spi_static.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/framework/driver/spi/static/src/drv_spi_static_ebm_tasks.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/framework/driver/spi/static/src/drv_spi_static_sys_queue.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/framework/driver/spi/static/src/drv_spi_static_tasks.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/framework/driver/tmr/src/drv_tmr_mapping.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/framework/driver/tmr/src/drv_tmr_static.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/framework/system/clk/src/sys_clk_pic32mx.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/framework/system/devcon/src/sys_devcon.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/framework/system/devcon/src/sys_devcon_pic32mx.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/framework/system/ports/src/sys_ports_static.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/system_exceptions.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/system_init.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/system_interrupt.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/system_tasks.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/ugui.c")
set_source_files_properties(${SPB7_Screen_default_default_XC32_FILE_TYPE_compile} PROPERTIES LANGUAGE C)
set(SPB7_Screen_default_default_XC32_FILE_TYPE_compile_cpp)
set_source_files_properties(${SPB7_Screen_default_default_XC32_FILE_TYPE_compile_cpp} PROPERTIES LANGUAGE CXX)
set(SPB7_Screen_default_default_XC32_FILE_TYPE_link "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../../bin/framework/peripheral/PIC32MX795F512L_peripherals.a")
set(SPB7_Screen_default_image_name "default.elf")


# The output directory of the final image.
set(SPB7_Screen_default_output_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../out/SPB7_Screen")
