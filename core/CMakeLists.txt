cmake_minimum_required(VERSION 3.14)
# Beetree Embedded Behavior Tree Library
# ======================================
#
# Core library for the Beetree Behavior Tree System
#
# ```
# Target Name    beetree
# Package Name   Beetree::Beetree
# ```
#
# Contents
# --------
# - Engine
# - BTOS
# - Trace
# - Units
# - Registry
# - Core Nodes
#
add_library(beetree STATIC)
add_library(Beetree::Beetree ALIAS beetree)
set_target_properties(beetree PROPERTIES EXPORT_NAME Beetree)

# BTOS Source
# -----------
target_sources(
    beetree
    PRIVATE
        src/btos/memory.cpp
        src/btos/clock.cpp
        src/btos/assert.cpp
        src/btos/app-runner.cpp
)

# Trace Source
# ------------
target_sources(
    beetree
    PRIVATE
        src/trace/trace-stream.cpp
        src/trace/trace-manager.cpp
        src/trace/trace.cpp
        src/trace/serial-listener.cpp
        src/trace/trace-protocol.cpp
)

# Units Source
# ------------
target_sources(beetree PRIVATE src/units/methods.cpp src/units/floating-pt-math.cpp)

# Engine Source
# -------------
target_sources(
    beetree
    PRIVATE
        src/engine/stack.cpp
        src/engine/stack-memory-pool.cpp
        src/engine/engine.cpp
        src/engine/builder.cpp
        src/engine/port.cpp
        src/engine/port-internal.hpp
        src/engine/helpers.cpp
        src/engine/helpers.hpp
        src/engine/branch-reader.cpp
        src/engine/select-algorithm.cpp
        src/engine/try-catch.cpp
        src/engine/try-catch-internal.hpp
        src/engine/notifier.cpp
        src/engine/runner.cpp
        src/engine/tree-extensions.cpp
)

# Registry Source
# ---------------
target_sources(beetree PRIVATE src/registry/item.cpp src/registry/register-trace.cpp)

# Nodes
# -----
target_sources(
    beetree
    PRIVATE
        src/nodes/blackboard.cpp
        src/nodes/inverter.cpp
        src/nodes/repeat-for.cpp
        src/nodes/repeat-until.cpp
        src/nodes/select.cpp
        src/nodes/sequence.cpp
        src/nodes/select-if.cpp
        src/nodes/succeeder.cpp
        src/nodes/null-success-fail.cpp
        src/nodes/idle.cpp
        src/services/locator.cpp
)

# Dependencies
# ------------
target_link_libraries(beetree PUBLIC Beetree::Platform::Interface)
# build include dirs
target_include_directories(beetree PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
# install/packaging include dirs
target_include_directories(beetree PUBLIC $<INSTALL_INTERFACE:include>)

# Tokens
# ------

find_package(BeeTreeTools REQUIRED)

add_custom_command(
    OUTPUT
        ${CMAKE_CURRENT_BINARY_DIR}/include/beetree/core/tokens.hpp
        ${CMAKE_CURRENT_BINARY_DIR}/beetree-token-map.json
    COMMAND ${CMAKE_COMMAND} -E echo "Generating tokens for beetree-core"
    COMMAND
        python3
        ${BeeTreeTools_MAKE_TOKENS}
        ${CMAKE_CURRENT_BINARY_DIR}/include/beetree/core/tokens.hpp
        ${CMAKE_CURRENT_BINARY_DIR}/beetree-token-map.json
        ${CMAKE_CURRENT_SOURCE_DIR}/tokens.json
        ${CMAKE_CURRENT_SOURCE_DIR}/tokens-engine.json
    DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/tokens.json ${CMAKE_CURRENT_SOURCE_DIR}/tokens-engine.json
        ${BeeTreeTools_MAKE_TOKENS}
)

add_custom_target(
    beetree-generated
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/include/beetree/core/tokens.hpp
    SOURCES ${CMAKE_CURRENT_BINARY_DIR}/include/beetree/core/tokens.hpp
)
target_include_directories(beetree PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>)
add_dependencies(beetree beetree-generated)

# Test
# ----
if(BUILD_TESTING)
    add_subdirectory(test)
endif()

# Install
# -------
include(GNUInstallDirs)
install(TARGETS beetree COMPONENT Development EXPORT Beetree)
install(
    DIRECTORY include/ ${CMAKE_CURRENT_BINARY_DIR}/include/
    TYPE INCLUDE
    COMPONENT Development
)
install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/beetree-token-map.json
    DESTINATION ${CMAKE_INSTALL_DATADIR}/beetree
    COMPONENT beetree-view
)