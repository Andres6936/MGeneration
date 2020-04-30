# CPM.cmake - CMake's missing package manager
# ===========================================
# See https://github.com/TheLartians/CPM.cmake for usage and update instructions.
#
# MIT License
# ----------- 
#[[
  Copyright (c) 2019 Lars Melchior

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
]]

CMAKE_MINIMUM_REQUIRED(VERSION 3.14 FATAL_ERROR)

SET(CURRENT_CPM_VERSION 0.22)

IF (CPM_DIRECTORY)
    IF (NOT ${CPM_DIRECTORY} MATCHES ../../../Descargas)
        IF (${CPM_VERSION} VERSION_LESS ${CURRENT_CPM_VERSION})
            MESSAGE(AUTHOR_WARNING "${CPM_INDENT} \
A dependency is using a more recent CPM version (${CURRENT_CPM_VERSION}) than the current project (${CPM_VERSION}). \
It is recommended to upgrade CPM to the most recent version. \
See https://github.com/TheLartians/CPM.cmake for more information."
                    )
        ENDIF ()
        RETURN()
    ENDIF ()

    GET_PROPERTY(CPM_INITIALIZED GLOBAL "" PROPERTY CPM_INITIALIZED SET)
    IF (CPM_INITIALIZED)
        RETURN()
    ENDIF ()
ENDIF ()

SET_PROPERTY(GLOBAL PROPERTY CPM_INITIALIZED true)

OPTION(CPM_USE_LOCAL_PACKAGES "Always try to use `find_package` to get dependencies" $ENV{CPM_USE_LOCAL_PACKAGES})
OPTION(CPM_LOCAL_PACKAGES_ONLY "Only use `find_package` to get dependencies" $ENV{CPM_LOCAL_PACKAGES_ONLY})
OPTION(CPM_DOWNLOAD_ALL "Always download dependencies from source" $ENV{CPM_DOWNLOAD_ALL})
OPTION(CPM_DONT_UPDATE_MODULE_PATH "Don't update the module path to allow using find_package" $ENV{CPM_DONT_UPDATE_MODULE_PATH})

SET(CPM_VERSION ${CURRENT_CPM_VERSION} CACHE INTERNAL "")
SET(CPM_DIRECTORY ../../../Descargas CACHE INTERNAL "")
SET(CPM_FILE CPM.cmake CACHE INTERNAL "")
SET(CPM_PACKAGES "" CACHE INTERNAL "")
SET(CPM_DRY_RUN OFF CACHE INTERNAL "Don't download or configure dependencies (for testing)")

IF (DEFINED ENV{CPM_SOURCE_CACHE})
    SET(CPM_SOURCE_CACHE_DEFAULT $ENV{CPM_SOURCE_CACHE})
ELSE ()
    SET(CPM_SOURCE_CACHE_DEFAULT OFF)
ENDIF ()

SET(CPM_SOURCE_CACHE ${CPM_SOURCE_CACHE_DEFAULT} CACHE PATH "Directory to downlaod CPM dependencies")

IF (NOT CPM_DONT_UPDATE_MODULE_PATH)
    SET(CPM_MODULE_PATH "${CMAKE_BINARY_DIR}/CPM_modules" CACHE INTERNAL "")
    # remove old modules
    FILE(REMOVE_RECURSE ${CPM_MODULE_PATH})
    FILE(MAKE_DIRECTORY ${CPM_MODULE_PATH})
    # locally added CPM modules should override global packages
    SET(CMAKE_MODULE_PATH "${CPM_MODULE_PATH};${CMAKE_MODULE_PATH}")
ENDIF ()

INCLUDE(FetchContent)
INCLUDE(CMakeParseArguments)

# Initialize logging prefix
IF (NOT CPM_INDENT)
    SET(CPM_INDENT "CPM:")
ENDIF ()

FUNCTION(CPM_FIND_PACKAGE NAME VERSION)
    STRING(REPLACE " " ";" EXTRA_ARGS "${ARGN}")
    FIND_PACKAGE(${NAME} ${VERSION} ${EXTRA_ARGS} QUIET)
    IF (${CPM_ARGS_NAME}_FOUND)
        MESSAGE(STATUS "${CPM_INDENT} using local package ${CPM_ARGS_NAME}@${${CPM_ARGS_NAME}_VERSION}")
        CPMREGISTERPACKAGE(${CPM_ARGS_NAME} "${${CPM_ARGS_NAME}_VERSION}")
        SET(CPM_PACKAGE_FOUND YES PARENT_SCOPE)
    ELSE ()
        SET(CPM_PACKAGE_FOUND NO PARENT_SCOPE)
    ENDIF ()
ENDFUNCTION()

# Create a custom FindXXX.cmake module for a CPM package
# This prevents `find_package(NAME)` from finding the system library
FUNCTION(CPMCREATEMODULEFILE Name)
    IF (NOT CPM_DONT_UPDATE_MODULE_PATH)
        # erase any previous modules
        FILE(WRITE ${CPM_MODULE_PATH}/Find${Name}.cmake "include(${CPM_FILE})\n${ARGN}\nset(${Name}_FOUND TRUE)")
    ENDIF ()
ENDFUNCTION()

# Find a package locally or fallback to CPMAddPackage
FUNCTION(CPMFINDPACKAGE)
    SET(oneValueArgs
            NAME
            VERSION
            FIND_PACKAGE_ARGUMENTS
            )

    CMAKE_PARSE_ARGUMENTS(CPM_ARGS "" "${oneValueArgs}" "" ${ARGN})

    IF (CPM_DOWNLOAD_ALL)
        CPMADDPACKAGE(${ARGN})
        CPM_EXPORT_VARIABLES()
        RETURN()
    ENDIF ()

    CPM_FIND_PACKAGE(${CPM_ARGS_NAME} "${CPM_ARGS_VERSION}" ${CPM_ARGS_FIND_PACKAGE_ARGUMENTS})

    IF (NOT CPM_PACKAGE_FOUND)
        CPMADDPACKAGE(${ARGN})
        CPM_EXPORT_VARIABLES()
    ENDIF ()

ENDFUNCTION()

# Download and add a package from source
FUNCTION(CPMADDPACKAGE)

    SET(oneValueArgs
            NAME
            VERSION
            GIT_TAG
            DOWNLOAD_ONLY
            GITHUB_REPOSITORY
            GITLAB_REPOSITORY
            SOURCE_DIR
            DOWNLOAD_COMMAND
            FIND_PACKAGE_ARGUMENTS
            )

    SET(multiValueArgs
            OPTIONS
            )

    CMAKE_PARSE_ARGUMENTS(CPM_ARGS "" "${oneValueArgs}" "${multiValueArgs}" "${ARGN}")

    IF (CPM_USE_LOCAL_PACKAGES OR CPM_LOCAL_PACKAGES_ONLY)
        CPM_FIND_PACKAGE(${CPM_ARGS_NAME} "${CPM_ARGS_VERSION}" ${CPM_ARGS_FIND_PACKAGE_ARGUMENTS})

        IF (CPM_PACKAGE_FOUND)
            RETURN()
        ENDIF ()

        IF (CPM_LOCAL_PACKAGES_ONLY)
            MESSAGE(SEND_ERROR "CPM: ${CPM_ARGS_NAME} not found via find_package(${CPM_ARGS_NAME} ${CPM_ARGS_VERSION})")
        ENDIF ()
    ENDIF ()

    IF (NOT DEFINED CPM_ARGS_VERSION)
        IF (DEFINED CPM_ARGS_GIT_TAG)
            CPM_GET_VERSION_FROM_GIT_TAG("${CPM_ARGS_GIT_TAG}" CPM_ARGS_VERSION)
        ENDIF ()
        IF (NOT DEFINED CPM_ARGS_VERSION)
            SET(CPM_ARGS_VERSION 0)
        ENDIF ()
    ENDIF ()

    IF (NOT DEFINED CPM_ARGS_GIT_TAG)
        SET(CPM_ARGS_GIT_TAG v${CPM_ARGS_VERSION})
    ENDIF ()

    LIST(APPEND CPM_ARGS_UNPARSED_ARGUMENTS GIT_TAG ${CPM_ARGS_GIT_TAG})

    IF (CPM_ARGS_DOWNLOAD_ONLY)
        SET(DOWNLOAD_ONLY ${CPM_ARGS_DOWNLOAD_ONLY})
    ELSE ()
        SET(DOWNLOAD_ONLY NO)
    ENDIF ()

    IF (CPM_ARGS_GITHUB_REPOSITORY)
        LIST(APPEND CPM_ARGS_UNPARSED_ARGUMENTS GIT_REPOSITORY "https://github.com/${CPM_ARGS_GITHUB_REPOSITORY}.git")
    ENDIF ()

    IF (CPM_ARGS_GITLAB_REPOSITORY)
        LIST(APPEND CPM_ARGS_UNPARSED_ARGUMENTS GIT_REPOSITORY "https://gitlab.com/${CPM_ARGS_GITLAB_REPOSITORY}.git")
    ENDIF ()

    IF ("${CPM_ARGS_NAME}" IN_LIST CPM_PACKAGES)
        CPMGETPACKAGEVERSION(${CPM_ARGS_NAME} CPM_PACKAGE_VERSION)
        IF (${CPM_PACKAGE_VERSION} VERSION_LESS ${CPM_ARGS_VERSION})
            MESSAGE(WARNING "${CPM_INDENT} requires a newer version of ${CPM_ARGS_NAME} (${CPM_ARGS_VERSION}) than currently included (${CPM_PACKAGE_VERSION}).")
        ENDIF ()
        IF (CPM_ARGS_OPTIONS)
            FOREACH (OPTION ${CPM_ARGS_OPTIONS})
                CPM_PARSE_OPTION(${OPTION})
                IF (NOT "${${OPTION_KEY}}" STREQUAL ${OPTION_VALUE})
                    MESSAGE(WARNING "${CPM_INDENT} ignoring package option for ${CPM_ARGS_NAME}: ${OPTION_KEY} = ${OPTION_VALUE} (${${OPTION_KEY}})")
                ENDIF ()
            ENDFOREACH ()
        ENDIF ()
        CPM_FETCH_PACKAGE(${CPM_ARGS_NAME} ${DOWNLOAD_ONLY})
        CPM_GET_FETCH_PROPERTIES(${CPM_ARGS_NAME})
        SET(${CPM_ARGS_NAME}_SOURCE_DIR "${${CPM_ARGS_NAME}_SOURCE_DIR}")
        SET(${CPM_ARGS_NAME}_BINARY_DIR "${${CPM_ARGS_NAME}_BINARY_DIR}")
        SET(${CPM_ARGS_NAME}_ADDED NO)
        CPM_EXPORT_VARIABLES()
        RETURN()
    ENDIF ()

    CPMREGISTERPACKAGE(${CPM_ARGS_NAME} ${CPM_ARGS_VERSION})

    IF (CPM_ARGS_OPTIONS)
        FOREACH (OPTION ${CPM_ARGS_OPTIONS})
            CPM_PARSE_OPTION(${OPTION})
            SET(${OPTION_KEY} ${OPTION_VALUE} CACHE INTERNAL "")
        ENDFOREACH ()
    ENDIF ()

    SET(FETCH_CONTENT_DECLARE_EXTRA_OPTS "")

    IF (DEFINED CPM_ARGS_GIT_TAG)
        SET(PACKAGE_INFO "${CPM_ARGS_GIT_TAG}")
    ELSE ()
        SET(PACKAGE_INFO "${CPM_ARGS_VERSION}")
    ENDIF ()

    IF (DEFINED CPM_ARGS_DOWNLOAD_COMMAND)
        SET(FETCH_CONTENT_DECLARE_EXTRA_OPTS DOWNLOAD_COMMAND ${CPM_ARGS_DOWNLOAD_COMMAND})
    ELSEIF (DEFINED CPM_ARGS_SOURCE_DIR)
        SET(FETCH_CONTENT_DECLARE_EXTRA_OPTS SOURCE_DIR ${CPM_ARGS_SOURCE_DIR})
    ELSEIF (CPM_SOURCE_CACHE)
        STRING(TOLOWER ${CPM_ARGS_NAME} lower_case_name)
        SET(origin_parameters ${CPM_ARGS_UNPARSED_ARGUMENTS})
        LIST(SORT origin_parameters)
        STRING(SHA1 origin_hash "${origin_parameters}")
        SET(download_directory ${CPM_SOURCE_CACHE}/${lower_case_name}/${origin_hash})
        LIST(APPEND FETCH_CONTENT_DECLARE_EXTRA_OPTS SOURCE_DIR ${download_directory})
        IF (EXISTS ${download_directory})
            # disable the download command to allow offline builds
            LIST(APPEND FETCH_CONTENT_DECLARE_EXTRA_OPTS DOWNLOAD_COMMAND "${CMAKE_COMMAND}")
            SET(PACKAGE_INFO "${download_directory}")
        ELSE ()
            # remove timestamps so CMake will re-download the dependency
            FILE(REMOVE_RECURSE ${CMAKE_BINARY_DIR}/_deps/${lower_case_name}-subbuild)
            SET(PACKAGE_INFO "${PACKAGE_INFO} -> ${download_directory}")
        ENDIF ()
    ENDIF ()

    CPM_DECLARE_FETCH(${CPM_ARGS_NAME} ${CPM_ARGS_VERSION} ${PACKAGE_INFO} "${CPM_ARGS_UNPARSED_ARGUMENTS}" ${FETCH_CONTENT_DECLARE_EXTRA_OPTS})
    CPM_FETCH_PACKAGE(${CPM_ARGS_NAME} ${DOWNLOAD_ONLY})
    CPM_GET_FETCH_PROPERTIES(${CPM_ARGS_NAME})
    CPMCREATEMODULEFILE(${CPM_ARGS_NAME} "CPMAddPackage(${ARGN})")
    SET(${CPM_ARGS_NAME}_ADDED YES)
    CPM_EXPORT_VARIABLES()
ENDFUNCTION()

# export variables available to the caller to the parent scope
# expects ${CPM_ARGS_NAME} to be set
MACRO(CPM_EXPORT_VARIABLES)
    SET(${CPM_ARGS_NAME}_SOURCE_DIR "${${CPM_ARGS_NAME}_SOURCE_DIR}" PARENT_SCOPE)
    SET(${CPM_ARGS_NAME}_BINARY_DIR "${${CPM_ARGS_NAME}_BINARY_DIR}" PARENT_SCOPE)
    SET(${CPM_ARGS_NAME}_ADDED "${${CPM_ARGS_NAME}_ADDED}" PARENT_SCOPE)
ENDMACRO()

# declares that a package has been added to CPM
FUNCTION(CPMREGISTERPACKAGE PACKAGE VERSION)
    LIST(APPEND CPM_PACKAGES ${PACKAGE})
    SET(CPM_PACKAGES ${CPM_PACKAGES} CACHE INTERNAL "")
    SET("CPM_PACKAGE_${PACKAGE}_VERSION" ${VERSION} CACHE INTERNAL "")
ENDFUNCTION()

# retrieve the current version of the package to ${OUTPUT}
FUNCTION(CPMGETPACKAGEVERSION PACKAGE OUTPUT)
    SET(${OUTPUT} "${CPM_PACKAGE_${PACKAGE}_VERSION}" PARENT_SCOPE)
ENDFUNCTION()

# declares a package in FetchContent_Declare 
FUNCTION(CPM_DECLARE_FETCH PACKAGE VERSION INFO)
    MESSAGE(STATUS "${CPM_INDENT} adding package ${PACKAGE}@${VERSION} (${INFO})")

    IF (${CPM_DRY_RUN})
        MESSAGE(STATUS "${CPM_INDENT} package not declared (dry run)")
        RETURN()
    ENDIF ()

    FETCHCONTENT_DECLARE(
            ${PACKAGE}
            ${ARGN}
    )
ENDFUNCTION()

# returns properties for a package previously defined by cpm_declare_fetch
FUNCTION(CPM_GET_FETCH_PROPERTIES PACKAGE)
    IF (${CPM_DRY_RUN})
        RETURN()
    ENDIF ()
    FETCHCONTENT_GETPROPERTIES(${PACKAGE})
    STRING(TOLOWER ${PACKAGE} lpackage)
    SET(${PACKAGE}_SOURCE_DIR "${${lpackage}_SOURCE_DIR}" PARENT_SCOPE)
    SET(${PACKAGE}_BINARY_DIR "${${lpackage}_BINARY_DIR}" PARENT_SCOPE)
ENDFUNCTION()

# downloads a previously declared package via FetchContent
FUNCTION(CPM_FETCH_PACKAGE PACKAGE DOWNLOAD_ONLY)

    IF (${CPM_DRY_RUN})
        MESSAGE(STATUS "${CPM_INDENT} package ${PACKAGE} not fetched (dry run)")
        RETURN()
    ENDIF ()

    SET(CPM_OLD_INDENT "${CPM_INDENT}")
    SET(CPM_INDENT "${CPM_INDENT} ${PACKAGE}:")
    IF (${DOWNLOAD_ONLY})
        FETCHCONTENT_GETPROPERTIES(${PACKAGE})
        IF (NOT ${PACKAGE}_POPULATED)
            FETCHCONTENT_POPULATE(${PACKAGE})
        ENDIF ()
    ELSE ()
        FETCHCONTENT_MAKEAVAILABLE(${PACKAGE})
    ENDIF ()
    SET(CPM_INDENT "${CPM_OLD_INDENT}")
ENDFUNCTION()

# splits a package option
FUNCTION(CPM_PARSE_OPTION OPTION)
    STRING(REGEX MATCH "^[^ ]+" OPTION_KEY ${OPTION})
    STRING(LENGTH ${OPTION} OPTION_LENGTH)
    STRING(LENGTH ${OPTION_KEY} OPTION_KEY_LENGTH)
    IF (OPTION_KEY_LENGTH STREQUAL OPTION_LENGTH)
        # no value for key provided, assume user wants to set option to "ON"
        SET(OPTION_VALUE "ON")
    ELSE ()
        MATH(EXPR OPTION_KEY_LENGTH "${OPTION_KEY_LENGTH}+1")
        STRING(SUBSTRING ${OPTION} "${OPTION_KEY_LENGTH}" "-1" OPTION_VALUE)
    ENDIF ()
    SET(OPTION_KEY "${OPTION_KEY}" PARENT_SCOPE)
    SET(OPTION_VALUE "${OPTION_VALUE}" PARENT_SCOPE)
ENDFUNCTION()

# guesses the package version from a git tag
FUNCTION(CPM_GET_VERSION_FROM_GIT_TAG GIT_TAG RESULT)
    STRING(LENGTH ${GIT_TAG} length)
    IF (length EQUAL 40)
        # GIT_TAG is probably a git hash
        SET(${RESULT} 0 PARENT_SCOPE)
    ELSE ()
        STRING(REGEX MATCH "v?([0123456789.]*).*" _ ${GIT_TAG})
        SET(${RESULT} ${CMAKE_MATCH_1} PARENT_SCOPE)
    ENDIF ()
ENDFUNCTION()
