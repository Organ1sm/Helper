
function(addImpl)
    set(optionalValues op1)
    set(singleValueArgs TARGET)
    set(multiValueArgs INCLUDE LINK COMPILER_OPTIONS COMPILER_DEFINITIONS)

    message(STATUS "ARGN : ${ARGN}")
    message(STATUS "options: ${optionalValues}")
    message(STATUS "singleV: ${singleValueArgs}")
    message(STATUS "multiV: ${multiValueArgs}")
    
    cmake_parse_arguments(addTargetArgs
        "${optionalValues}"
        "${singleValueArgs}"
        "${multiValueArgs}"
        ${ARGN}
    )

    message(STATUS "optional - ${addTargetArgs_op1}")
    message(STATUS "Target - ${addTargetArgs_TARGET}")
    message(STATUS "Include - ${addTargetArgs_INCLUDE}")
    message(STATUS "Link - ${addTargetArgs_LINK}")
    message(STATUS "CompilerOptions - ${addTargetArgs_COMPILER_OPTIONS}")
    message(STATUS "CompilerDefintions - ${addTargetArgs_COMPILER_DEFINITIONS}")

endfunction()
