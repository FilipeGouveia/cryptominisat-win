/*
 * CryptoMiniSat
 *
 * Copyright (c) 2009-2014, Mate Soos. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation
 * version 2.0 of the License.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301  USA
*/

#include "src/GitSHA1.h"
const char* get_version_sha1()
{
    static const char myversion_sha1[] = "@GIT_SHA1@";
    return myversion_sha1;
}

const char* get_version_tag()
{
    static const char myversion_tag[] = "@PROJECT_VERSION@";
    return myversion_tag;
}

const char* get_compilation_env()
{
    static const char compilation_env[] =
    "CMAKE_CXX_COMPILER = @CMAKE_CXX_COMPILER@ | "
    "CMAKE_CXX_FLAGS = @CMAKE_CXX_FLAGS@ | "
    "COMPILE_DEFINES = @COMPILE_DEFINES@ | "
    "STATICCOMPILE = @STATICCOMPILE@ | "
    "ONLY_SIMPLE = @ONLY_SIMPLE@ | "
    "Boost_FOUND = @Boost_FOUND@ | "
    "TBB_FOUND = @TBB_FOUND@ | "
    "STATS = @STATS@ | "
    "MYSQL_FOUND = @MYSQL_FOUND@ | "
    "SQLITE3_FOUND = @SQLITE3_FOUND@ | "
    "ZLIB_FOUND = @ZLIB_FOUND@ | "
    "VALGRIND_FOUND = @VALGRIND_FOUND@ | "
    "ENABLE_TESTING = @ENABLE_TESTING@ | "
    "M4RI_FOUND = @M4RI_FOUND@ | "
    "SLOW_DEBUG = @SLOW_DEBUG@ | "
    "ENABLE_ASSERTIONS = @ENABLE_ASSERTIONS@ | "
    "PYTHON_EXECUTABLE = @PYTHON_EXECUTABLE@ | "
    "PYTHON_LIBRARY = @PYTHON_LIBRARY@ | "
    "PYTHON_INCLUDE_DIRS = @PYTHON_INCLUDE_DIRS@ | "
    "MY_TARGETS = @MY_TARGETS@ | "
    "compilation date time = " __DATE__ " " __TIME__
    ""
    ;
    return compilation_env;
}
