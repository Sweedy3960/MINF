include("${CMAKE_CURRENT_LIST_DIR}/rule.cmake")
include("${CMAKE_CURRENT_LIST_DIR}/file.cmake")

set(Ex5_2_default_library_list )

# Handle files with suffix s, for group default-XC32
if(Ex5_2_default_default_XC32_FILE_TYPE_assemble)
add_library(Ex5_2_default_default_XC32_assemble OBJECT ${Ex5_2_default_default_XC32_FILE_TYPE_assemble})
    Ex5_2_default_default_XC32_assemble_rule(Ex5_2_default_default_XC32_assemble)
    list(APPEND Ex5_2_default_library_list "$<TARGET_OBJECTS:Ex5_2_default_default_XC32_assemble>")
endif()

# Handle files with suffix S, for group default-XC32
if(Ex5_2_default_default_XC32_FILE_TYPE_assembleWithPreprocess)
add_library(Ex5_2_default_default_XC32_assembleWithPreprocess OBJECT ${Ex5_2_default_default_XC32_FILE_TYPE_assembleWithPreprocess})
    Ex5_2_default_default_XC32_assembleWithPreprocess_rule(Ex5_2_default_default_XC32_assembleWithPreprocess)
    list(APPEND Ex5_2_default_library_list "$<TARGET_OBJECTS:Ex5_2_default_default_XC32_assembleWithPreprocess>")
endif()

# Handle files with suffix [cC], for group default-XC32
if(Ex5_2_default_default_XC32_FILE_TYPE_compile)
add_library(Ex5_2_default_default_XC32_compile OBJECT ${Ex5_2_default_default_XC32_FILE_TYPE_compile})
    Ex5_2_default_default_XC32_compile_rule(Ex5_2_default_default_XC32_compile)
    list(APPEND Ex5_2_default_library_list "$<TARGET_OBJECTS:Ex5_2_default_default_XC32_compile>")
endif()

# Handle files with suffix cpp, for group default-XC32
if(Ex5_2_default_default_XC32_FILE_TYPE_compile_cpp)
add_library(Ex5_2_default_default_XC32_compile_cpp OBJECT ${Ex5_2_default_default_XC32_FILE_TYPE_compile_cpp})
    Ex5_2_default_default_XC32_compile_cpp_rule(Ex5_2_default_default_XC32_compile_cpp)
    list(APPEND Ex5_2_default_library_list "$<TARGET_OBJECTS:Ex5_2_default_default_XC32_compile_cpp>")
endif()

add_executable(${Ex5_2_default_image_name} ${Ex5_2_default_library_list})

target_link_libraries(${Ex5_2_default_image_name} PRIVATE ${Ex5_2_default_default_XC32_FILE_TYPE_link})

# Add the link options from the rule file.
Ex5_2_default_link_rule(${Ex5_2_default_image_name})

# Add bin2hex target for converting built file to a .hex file.
add_custom_target(Ex5_2_default_Bin2Hex ALL
    ${MP_BIN2HEX} ${Ex5_2_default_image_name})
add_dependencies(Ex5_2_default_Bin2Hex ${Ex5_2_default_image_name})

# Post build target to copy built file to the output directory.
add_custom_command(TARGET ${Ex5_2_default_image_name} POST_BUILD
                    COMMAND ${CMAKE_COMMAND} -E make_directory ${Ex5_2_default_output_dir}
                    COMMAND ${CMAKE_COMMAND} -E copy ${Ex5_2_default_image_name} ${Ex5_2_default_output_dir}/${Ex5_2_default_original_image_name}
                    BYPRODUCTS ${Ex5_2_default_output_dir}/${Ex5_2_default_original_image_name})
