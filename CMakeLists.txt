cmake_minimum_required(VERSION 3.20)

project(
    slotchain
    VERSION 0.1.0
    LANGUAGES CXX
)

# ============================================================
# Header-only library target
# ============================================================

add_library(slotchain INTERFACE)
add_library(slotchain::slotchain ALIAS slotchain)

target_include_directories(slotchain
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(slotchain
    INTERFACE
        cxx_std_20
)

# Optional warnings for development (OFF by default)
option(SLOTCHAIN_ENABLE_WARNINGS "Enable warnings for slotchain headers" OFF)

if(SLOTCHAIN_ENABLE_WARNINGS)
    target_compile_options(slotchain
        INTERFACE
            $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
    )
endif()

# ============================================================
# Examples
# ============================================================

option(SLOTCHAIN_BUILD_EXAMPLES "Build slotchain examples" ON)

if(SLOTCHAIN_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()

# ============================================================
# Tests
# ============================================================

option(SLOTCHAIN_BUILD_TESTS "Build slotchain tests" ON)

if(SLOTCHAIN_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

# ============================================================
# Installation (header-only)
# ============================================================

include(GNUInstallDirs)

install(
    TARGETS slotchain
    EXPORT slotchainTargets
)

install(
    DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
    EXPORT slotchainTargets
    FILE slotchainTargets.cmake
    NAMESPACE slotchain::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/slotchain
)

# ============================================================
# Package config files
# ============================================================

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/slotchainConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake/slotchainConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/slotchainConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/slotchain
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/slotchainConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/slotchainConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/slotchain
)
