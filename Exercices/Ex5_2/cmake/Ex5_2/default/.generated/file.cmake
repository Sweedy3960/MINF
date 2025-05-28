# The following variables contains the files used by the different stages of the build process.
set(Ex5_2_default_default_XC32_FILE_TYPE_assemble)
set_source_files_properties(${Ex5_2_default_default_XC32_FILE_TYPE_assemble} PROPERTIES LANGUAGE ASM)
set(Ex5_2_default_default_XC32_FILE_TYPE_assembleWithPreprocess)
set_source_files_properties(${Ex5_2_default_default_XC32_FILE_TYPE_assembleWithPreprocess} PROPERTIES LANGUAGE ASM)
set(Ex5_2_default_default_XC32_FILE_TYPE_compile
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../bsp/pic32mx_skes/Mc32CoreTimer.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../bsp/pic32mx_skes/Mc32Delays.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../bsp/pic32mx_skes/Mc32DriverAdc.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../bsp/pic32mx_skes/Mc32DriverAdcAlt.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../bsp/pic32mx_skes/Mc32DriverLcd.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../bsp/pic32mx_skes/bsp.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../framework/system/int/src/sys_int_pic32.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../firmware/src/app.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../firmware/src/main.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../firmware/src/system_config/default/framework/driver/tmr/src/drv_tmr_mapping.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../firmware/src/system_config/default/framework/driver/tmr/src/drv_tmr_static.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../firmware/src/system_config/default/framework/system/clk/src/sys_clk_pic32mx.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../firmware/src/system_config/default/framework/system/devcon/src/sys_devcon.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../firmware/src/system_config/default/framework/system/devcon/src/sys_devcon_pic32mx.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../firmware/src/system_config/default/framework/system/ports/src/sys_ports_static.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../firmware/src/system_config/default/system_exceptions.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../firmware/src/system_config/default/system_init.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../firmware/src/system_config/default/system_interrupt.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../firmware/src/system_config/default/system_tasks.c")
set_source_files_properties(${Ex5_2_default_default_XC32_FILE_TYPE_compile} PROPERTIES LANGUAGE C)
set(Ex5_2_default_default_XC32_FILE_TYPE_compile_cpp)
set_source_files_properties(${Ex5_2_default_default_XC32_FILE_TYPE_compile_cpp} PROPERTIES LANGUAGE CXX)
set(Ex5_2_default_default_XC32_FILE_TYPE_link "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../bin/framework/peripheral/PIC32MX795F512L_peripherals.a")

# The (internal) path to the resulting build image.
set(Ex5_2_default_internal_image_name "${CMAKE_CURRENT_SOURCE_DIR}/../../../_build/Ex5_2/default/default.elf")

# The name of the resulting image, including namespace for configuration.
set(Ex5_2_default_image_name "Ex5_2_default_default.elf")

# The name of the image, excluding the namespace for configuration.
set(Ex5_2_default_original_image_name "default.elf")

# The output directory of the final image.
set(Ex5_2_default_output_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../out/Ex5_2")
