#*****************************************************************************
# Copyright (c) 2021-2022, NVIDIA CORPORATION. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
#  * Neither the name of NVIDIA CORPORATION nor the names of its
#    contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
# OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#*****************************************************************************

# create Visual Studio code launch.json
get_property(BINDING_MODULE_PATH TARGET "mdl::mdl_python" PROPERTY BINARY_DIR)

# Platform depended symbols and keywords
if(WINDOWS)
    set(ENV_SEP ";")
    set(ENV_LIB_PATH "PATH")
elseif(MACOSX)
    set(ENV_SEP ":")
    set(ENV_LIB_PATH "DYLD_LIBRARY_PATH")
else() # LINUX
    set(ENV_SEP ":")
    set(ENV_LIB_PATH "LD_LIBRARY_PATH")
endif()

# Depending on the product and it's distribution we need set paths and enviroment variables slightly different
if("MDL_BINARY_RELEASE" IN_LIST MDL_ADDITIONAL_COMPILER_DEFINES)
    if(MDL_INTERNAL_BUILD)
        set(_VS_CODE_FILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/cmake_templates/mdl_python_examples.examples_internal.code-workspace)
        set(_SETUP_ENV_FILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/cmake_templates/setup_env.examples_internal.sh)
    else()
        set(_VS_CODE_FILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/cmake_templates/mdl_python_examples.binary_release.code-workspace)
        set(_SETUP_ENV_FILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/cmake_templates/setup_env.binary_release.sh)
    endif()
elseif ("MDL_SOURCE_RELEASE" IN_LIST MDL_ADDITIONAL_COMPILER_DEFINES)
    get_property(MDL_SDK_PATH TARGET "mdl::mdl_sdk" PROPERTY BINARY_DIR)
    get_property(FREEIMAGE_PATH TARGET "mdl::nv_freeimage" PROPERTY BINARY_DIR)
    set(ENV_MDL_SDK_PATH ${MDL_SDK_PATH})
    set(ENV_FREEIMAGE_PATH ${FREEIMAGE_PATH})
    if(WINDOWS)
        # for running the shell scripts on windows (e.g. using git bash or mingw)
        # we need to adjust the strings that go into the PATH to use a unix-like format
        string(SUBSTRING ${MDL_SDK_PATH} 1 1 _CHAR_AT_1)
        if(_CHAR_AT_1 STREQUAL ":")
            string(SUBSTRING ${MDL_SDK_PATH} 0 1 _CHAR_AT_0)
            string(SUBSTRING ${MDL_SDK_PATH} 2 -1 ENV_MDL_SDK_PATH)
            set(ENV_MDL_SDK_PATH "/${_CHAR_AT_0}${ENV_MDL_SDK_PATH}")
        endif()
        string(SUBSTRING ${FREEIMAGE_PATH} 1 1 _CHAR_AT_1)
        if(_CHAR_AT_1 STREQUAL ":")
            string(SUBSTRING ${FREEIMAGE_PATH} 0 1 _CHAR_AT_0)
            string(SUBSTRING ${FREEIMAGE_PATH} 2 -1 ENV_FREEIMAGE_PATH)
            set(ENV_FREEIMAGE_PATH "/${_CHAR_AT_0}${ENV_FREEIMAGE_PATH}")
        endif()
    endif()
    set(_VS_CODE_FILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/cmake_templates/mdl_python_examples.open_source.code-workspace)
    set(_SETUP_ENV_FILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/cmake_templates/setup_env.open_source.sh)
endif()

# create the IDE or shell support files
get_property(_GENERATOR_IS_MULTI_CONFIG GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(_GENERATOR_IS_MULTI_CONFIG)
    foreach(_CONFIG ${CMAKE_CONFIGURATION_TYPES})
        set(_MI_OBJ ${MI_OBJ_${_CONFIG}})
        make_directory(${CMAKE_CURRENT_BINARY_DIR}/env/${_CONFIG})
        configure_file(${_SETUP_ENV_FILE_IN} ${CMAKE_CURRENT_BINARY_DIR}/env/${_CONFIG}/setup_env.sh @ONLY)
    endforeach()
else()
    set(_CONFIG ${CMAKE_BUILD_TYPE})
    set(_MI_OBJ ${MI_OBJ_${_CONFIG}})
    make_directory(${CMAKE_CURRENT_BINARY_DIR}/env/${_CONFIG})
    configure_file(${_SETUP_ENV_FILE_IN} ${CMAKE_CURRENT_BINARY_DIR}/env/${_CONFIG}/setup_env.sh @ONLY)
endif()
configure_file(${_VS_CODE_FILE_IN} ${CMAKE_BINARY_DIR}/mdl_python_examples.code-workspace @ONLY)
