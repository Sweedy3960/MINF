# The following functions contains all the flags passed to the different build stages.

set(PACK_REPO_PATH "C:/Users/aymer/.mchp_packs" CACHE PATH "Path to the root of a pack repository.")

function(A_2414_DES_SP7_TestSprinkler_default_default_XC32_assemble_rule target)
    set(options
        "-g"
        "${ASSEMBLER_PRE}"
        "-mprocessor=32MX795F512L"
        "-Wa,--defsym=__MPLAB_BUILD=1${MP_EXTRA_AS_POST},-I${CMAKE_CURRENT_SOURCE_DIR}/../../../firmware/2414-DES_SP7_TestSprinkler.X"
        "-mdfp=${PACK_REPO_PATH}/Microchip/PIC32MX_DFP/1.5.259")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_include_directories(${target} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../firmware/2414-DES_SP7_TestSprinkler.X")
endfunction()
function(A_2414_DES_SP7_TestSprinkler_default_default_XC32_assembleWithPreprocess_rule target)
    set(options
        "-x"
        "assembler-with-cpp"
        "-g"
        "${MP_EXTRA_AS_PRE}"
        "-mprocessor=32MX795F512L"
        "-Wa,--defsym=__MPLAB_BUILD=1${MP_EXTRA_AS_POST},-I${CMAKE_CURRENT_SOURCE_DIR}/../../../firmware/2414-DES_SP7_TestSprinkler.X")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target} PRIVATE "XPRJ_default=default")
    target_include_directories(${target} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../firmware/2414-DES_SP7_TestSprinkler.X")
endfunction()
function(A_2414_DES_SP7_TestSprinkler_default_default_XC32_compile_rule target)
    set(options
        "-g"
        "${CC_PRE}"
        "-x"
        "c"
        "-c"
        "-mprocessor=32MX795F512L"
        "-ffunction-sections"
        "-Wall"
        "-mdfp=${PACK_REPO_PATH}/Microchip/PIC32MX_DFP/1.5.259")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target} PRIVATE "XPRJ_default=default")
    target_include_directories(${target}
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../firmware/src"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../firmware/src/system_config/default"
        PRIVATE "firmware/src/default"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../framework"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../firmware/src/system_config/default/framework"
        PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../firmware/2414-DES_SP7_TestSprinkler.X")
endfunction()
function(A_2414_DES_SP7_TestSprinkler_default_default_XC32_compile_cpp_rule target)
    set(options
        "-g"
        "${CC_PRE}"
        "-mprocessor=32MX795F512L"
        "-frtti"
        "-fexceptions"
        "-fno-check-new"
        "-fenforce-eh-specs"
        "-ffunction-sections"
        "-O1"
        "-fno-common"
        "-mdfp=${PACK_REPO_PATH}/Microchip/PIC32MX_DFP/1.5.259")
    list(REMOVE_ITEM options "")
    target_compile_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target} PRIVATE "XPRJ_default=default")
    target_include_directories(${target} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../../../firmware/2414-DES_SP7_TestSprinkler.X")
endfunction()
function(A_2414_DES_SP7_TestSprinkler_default_link_rule target)
    set(options
        "-g"
        "${MP_EXTRA_LD_PRE}"
        "-mprocessor=32MX795F512L"
        "-Wl,--defsym=__MPLAB_BUILD=1${MP_EXTRA_LD_POST},--defsym=_min_heap_size=0,--gc-sections,--no-code-in-dinit,--no-dinit-in-serial-mem,-L${CMAKE_CURRENT_SOURCE_DIR}/../../../firmware/2414-DES_SP7_TestSprinkler.X,--memorysummary,memoryfile.xml"
        "-mdfp=${PACK_REPO_PATH}/Microchip/PIC32MX_DFP/1.5.259")
    list(REMOVE_ITEM options "")
    target_link_options(${target} PRIVATE "${options}")
    target_compile_definitions(${target} PRIVATE "XPRJ_default=default")
endfunction()
