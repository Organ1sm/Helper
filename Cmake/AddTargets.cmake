include(AddTargetsImpl)

# Builds an executable.
# Parameters include:
# Target target_name                  Name of the object being built.
# Filename /path/to/file              Path to the file that is being built.
# Include cmake_package+              List of imported CMake packages the target requires.
# Compiler_options options+           List of options to be passed to the compiler.
# Compiler_definitions definitions+   List of macro definitions to be passed to the compiler.
function(CxxExecutable)
    PROJECT_TEMPLATE_EXTRACT_ADD_TARGET_ARGS(${ARGN})

    add_executable(
        "${addTargetArgs_Target}"
        "${addTargetArgs_FileName}"
    )

    PROJECT_TEMPLATE_CALL_ADD_IMPL()
endfunction()

# Builds a library.
# Accepts the same parameters as `cxx_executable`, as well as:
# LIBRARY_TYPE (STATIC|SHARED|MODULE|OBJECT)         Specifies how the library is to be built.
function(CxxLibrary)
    PROJECT_TEMPLATE_EXTRACT_ADD_TARGET_ARGS(${ARGN})

    set(LegalLibraryTypes "" STATIC SHARED MODULE OBJECT)
    list(FIND LegalLibraryTypes "${addTargetArgs_LibraryType}" libraryTyperesult)

    if(libraryTypeResult EQUAL -1)
        message(FATAL_ERROR "Cannot add a library of type \"${addTargetArgs_LibraryType}\"")
    endif()

    add_library(
        "${addTargetArgs_Target}"
        ${addTargetArgs_LibraryType}
        "${addTargetArgs_FileName}"
    )

    PROJECT_TEMPLATE_CALL_ADD_IMPL()
endfunction(CxxLibrary)

function(CxxTest)
    CxxExecutable(${ARGN})
    PROJECT_TEMPLATE_EXTRACT_ADD_TARGET_ARGS(${ARGN})

    target_link_libraries(
        "${addTargetArgs_Target}"
        PRIVATE
        "${addTargetArgs_TestLibrary}"
        test_main
    )

    add_test(
        "test.${addTargetArgs_Target}"
        "${addTargetArgs_Target}"
    )
endfunction()


function (CxxBenchmark)
    CxxExecutable(${ARGN})
    PROJECT_TEMPLATE_EXTRACT_ADD_TARGET_ARGS(${ARGN})

    target_compile_options(
        "${addTargetArgs_Target}"
        PRIVATE
        -fno-inline
    )
    
    target_link_libraries(
        ${addTargetArgs_Target}
        PRIVATE
        benchmark::benchmark
        benchmark::benchmark_main
    )

endfunction()