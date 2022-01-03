
function(AddImpl)
    set(optionalValues "")
    set(singleValueArgs Target)
    set(multiValueArgs Include Link CompilerOptions CompilerDefinitions)

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

    # message(STATUS "optional - ${addTargetArgs_}")
    # message(STATUS "Target - ${addTargetArgs_Target}")
    # message(STATUS "Include - ${addTargetArgs_Include}")
    # message(STATUS "Link - ${addTargetArgs_Link}")
    # message(STATUS "CompilerOptions - ${addTargetArgs_CompilerOptions}")
    # message(STATUS "CompilerDefinitions - ${addTargetArgs_CompilerDefinitions}")

    message(STATUS "ProjectSourceDir - ${PROJECT_SOURCE_DIR}/")
    target_include_directories(
        "${addTargetArgs_Target}"
        PUBLIC
        "${PROJECT_SOURCE_DIR}/include"
    )

    target_include_directories(
        "${addTargetArgs_Target}"
        PRIVATE
        "${addTargetArgs_Include}"
    )

    target_compile_options(
        "${addTargetArgs_Target}"
        PRIVATE
        "${addTargetArgs_CompilerOptions}"
    )

    target_compile_definitions(
        "${addTargetArgs_Target}"
        PRIVATE
        "${addTargetArgs_CompilerDefinitions}"
    )

    target_link_libraries(
        "${addTargetArgs_Target}"
        PRIVATE
        "${addTargetArgs_Link}"
    )
endfunction()

macro(PROJECT_TEMPLATE_EXTRACT_ADD_TARGET_ARGS)
    set(optionalValues "")
    set(singleValueArgs Target FileName LibraryType TestLibrary)
    set(multiValueArgs Include Link CompilerOptions CompilerDefinitions)

    cmake_parse_arguments(addTargetArgs
        "${optionalValues}"
        "${singleValueArgs}"
        "${multiValueArgs}"
        ${ARGN}
    )

    if("${addTargetArgs_Target}" STREQUAL "")
        message(FATAL_ERROR "Target is not set. Can't build a target without naming it! ")
    endif()

    if("${addTargetArgs_FileName}" STREQUAL "")
        message (FATAL_ERROR "Filename is not set. Can't build target ${addTargetArgs_Target} without a filename!")
    endif()
endmacro()


macro(PROJECT_TEMPLATE_CALL_ADD_IMPL)
    AddImpl(
        Target              "${addTargetArgs_Target}"
        Include             "${addTargetArgs_Include}"
        Link                "${addTargetArgs_Link}"
        CompilerOptions     "${addTargetArgs_CompilerOptions}"
        CompilerDefinitions "${addTargetArgs_CompilerDefinitions}"
    )

endmacro()