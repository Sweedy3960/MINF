# The following variables contains the files used by the different stages of the build process.
set(SPB7_TouchCapa_default_default_XC32_FILE_TYPE_assemble)
set_source_files_properties(${SPB7_TouchCapa_default_default_XC32_FILE_TYPE_assemble} PROPERTIES LANGUAGE ASM)
set(SPB7_TouchCapa_default_default_XC32_FILE_TYPE_assembleWithPreprocess)
set_source_files_properties(${SPB7_TouchCapa_default_default_XC32_FILE_TYPE_assembleWithPreprocess} PROPERTIES LANGUAGE ASM)
set(SPB7_TouchCapa_default_default_XC32_FILE_TYPE_compile
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../../framework/system/int/src/sys_int_pic32.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/Mc32_I2cUtilCCS.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/PIC32130_AT42QT2120_I2C.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/appTouch.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/app_taskctrl.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/main.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/bsp/bsp.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/framework/driver/tmr/src/drv_tmr_mapping.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/framework/driver/tmr/src/drv_tmr_static.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/framework/system/clk/src/sys_clk_pic32mx.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/framework/system/devcon/src/sys_devcon.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/framework/system/devcon/src/sys_devcon_pic32mx.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/framework/system/ports/src/sys_ports_static.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/system_exceptions.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/system_init.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/system_interrupt.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../../src/system_config/default/system_tasks.c")
set_source_files_properties(${SPB7_TouchCapa_default_default_XC32_FILE_TYPE_compile} PROPERTIES LANGUAGE C)
set(SPB7_TouchCapa_default_default_XC32_FILE_TYPE_compile_cpp)
set_source_files_properties(${SPB7_TouchCapa_default_default_XC32_FILE_TYPE_compile_cpp} PROPERTIES LANGUAGE CXX)
set(SPB7_TouchCapa_default_default_XC32_FILE_TYPE_link "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../../bin/framework/peripheral/PIC32MX795F512L_peripherals.a")
set(SPB7_TouchCapa_default_image_name "default.elf")


# The output directory of the final image.
set(SPB7_TouchCapa_default_output_dir "${CMAKE_CURRENT_SOURCE_DIR}/../../../out/SPB7_TouchCapa")
