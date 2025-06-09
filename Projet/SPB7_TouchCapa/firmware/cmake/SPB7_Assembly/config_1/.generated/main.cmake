# cmake files support debug production
include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(SPB7_Assembly_config_1_library_list )

# Handle files with suffix s, for group config_1_toolchain
if(SPB7_Assembly_config_1_config_1_toolchain_FILE_TYPE_assemble)
add_library(SPB7_Assembly_config_1_config_1_toolchain_assemble OBJECT ${SPB7_Assembly_config_1_config_1_toolchain_FILE_TYPE_assemble})
    SPB7_Assembly_config_1_config_1_toolchain_assemble_rule(SPB7_Assembly_config_1_config_1_toolchain_assemble)
    list(APPEND SPB7_Assembly_config_1_library_list "$<TARGET_OBJECTS:SPB7_Assembly_config_1_config_1_toolchain_assemble>")
endif()

# Handle files with suffix S, for group config_1_toolchain
if(SPB7_Assembly_config_1_config_1_toolchain_FILE_TYPE_assembleWithPreprocess)
add_library(SPB7_Assembly_config_1_config_1_toolchain_assembleWithPreprocess OBJECT ${SPB7_Assembly_config_1_config_1_toolchain_FILE_TYPE_assembleWithPreprocess})
    SPB7_Assembly_config_1_config_1_toolchain_assembleWithPreprocess_rule(SPB7_Assembly_config_1_config_1_toolchain_assembleWithPreprocess)
    list(APPEND SPB7_Assembly_config_1_library_list "$<TARGET_OBJECTS:SPB7_Assembly_config_1_config_1_toolchain_assembleWithPreprocess>")
endif()

# Handle files with suffix [cC], for group config_1_toolchain
if(SPB7_Assembly_config_1_config_1_toolchain_FILE_TYPE_compile)
add_library(SPB7_Assembly_config_1_config_1_toolchain_compile OBJECT ${SPB7_Assembly_config_1_config_1_toolchain_FILE_TYPE_compile})
    SPB7_Assembly_config_1_config_1_toolchain_compile_rule(SPB7_Assembly_config_1_config_1_toolchain_compile)
    list(APPEND SPB7_Assembly_config_1_library_list "$<TARGET_OBJECTS:SPB7_Assembly_config_1_config_1_toolchain_compile>")
endif()

# Handle files with suffix cpp, for group config_1_toolchain
if(SPB7_Assembly_config_1_config_1_toolchain_FILE_TYPE_compile_cpp)
add_library(SPB7_Assembly_config_1_config_1_toolchain_compile_cpp OBJECT ${SPB7_Assembly_config_1_config_1_toolchain_FILE_TYPE_compile_cpp})
    SPB7_Assembly_config_1_config_1_toolchain_compile_cpp_rule(SPB7_Assembly_config_1_config_1_toolchain_compile_cpp)
    list(APPEND SPB7_Assembly_config_1_library_list "$<TARGET_OBJECTS:SPB7_Assembly_config_1_config_1_toolchain_compile_cpp>")
endif()


add_executable(${SPB7_Assembly_config_1_image_name} ${SPB7_Assembly_config_1_library_list})
set_target_properties(${SPB7_Assembly_config_1_image_name} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${SPB7_Assembly_config_1_output_dir})

target_link_libraries(${SPB7_Assembly_config_1_image_name} PRIVATE ${SPB7_Assembly_config_1_config_1_toolchain_FILE_TYPE_link})

# Add the link options from the rule file.
SPB7_Assembly_config_1_link_rule(${SPB7_Assembly_config_1_image_name})

# Add bin2hex target for converting built file to a .hex file.
string(REGEX REPLACE [.]elf$ .hex SPB7_Assembly_config_1_image_name_hex ${SPB7_Assembly_config_1_image_name})
add_custom_target(SPB7_Assembly_config_1_Bin2Hex ALL
    COMMAND ${MP_BIN2HEX} ${SPB7_Assembly_config_1_output_dir}/${SPB7_Assembly_config_1_image_name}
    BYPRODUCTS ${SPB7_Assembly_config_1_output_dir}/${SPB7_Assembly_config_1_image_name_hex}
    COMMENT Convert built file to .hex)
add_dependencies(SPB7_Assembly_config_1_Bin2Hex ${SPB7_Assembly_config_1_image_name})



