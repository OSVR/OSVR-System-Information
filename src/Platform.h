/** @file
    @brief Auto-configured header

    If this filename ends in `.h`, don't edit it: your edits will
    be lost next time this file is regenerated!

    Must be c-safe!

    @date 2016

    @author
    Sensics, Inc.
    <http://sensics.com/osvr>
*/

/*
// Copyright 2016 Sensics, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
*/

#ifndef INCLUDED_Platform_h_GUID_13406B0D_1932_4A36_A5F1_55C508E07198
#define INCLUDED_Platform_h_GUID_13406B0D_1932_4A36_A5F1_55C508E07198

/**
 * Platform-specific variables.
 *
 * Prefer testing for specific compiler or platform features instead of relying
 * on these variables.
 *
 */
//@{
//#cmakedefine OSVR_AIX
//#cmakedefine OSVR_ANDROID
//#cmakedefine OSVR_BSDOS
//#cmakedefine OSVR_FREEBSD
//#cmakedefine OSVR_HPUX
//#cmakedefine OSVR_IRIX
//#cmakedefine OSVR_LINUX
//#cmakedefine OSVR_KFREEBSD
//#cmakedefine OSVR_NETBSD
//#cmakedefine OSVR_OPENBSD
//#cmakedefine OSVR_OFS1
//#cmakedefine OSVR_SCO_SV
//#cmakedefine OSVR_UNIXWARE
//#cmakedefine OSVR_XENIX
//#cmakedefine OSVR_SUNOS
//#cmakedefine OSVR_TRU64
//#cmakedefine OSVR_ULTRIX
//#cmakedefine OSVR_CYGWIN
//#cmakedefine OSVR_MACOSX
//#cmakedefine OSVR_WINDOWS
//@}

/**
 * \name Operating system tests.
 *
 * Multiple OS defines may be enabled at the same time.
 */
//@{
#if defined(_AIX)
#define OSVR_AIX 1
#endif

#if defined(__ANDROID__)
#define OSVR_ANDROID 1
#endif

#if defined(__bsdi__)
#define OSVR_BSDOS 1
#endif

#if defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(BSD)
#define OSVR_FREEBSD 1
#endif

#if defined(hpux) || defined(_hpux) || defined(__hpux)
#define OSVR_HPUX 1
#endif

#if defined(sgi) || defined(__sgi)
#define OSVR_IRIX 1
#endif

#if defined(linux) || defined(__linux__)
#define OSVR_LINUX 1
#endif

#if defined(__FreeBSD_kernel__) && defined(__GLIBC__)
#define OSVR_KFREEBSD 1
#endif

#if defined(__NetBSD__)
#define OSVR_NETBSD 1
#endif

#if defined(__OpenBSD__)
#define OSVR_OPENBSD 1
#endif

#if defined(sco) && defined(_UNIXWARE7)
#define OSVR_UNIXWARE 1
#endif

#if defined(sun) || defined(__sun)
#if defined(__SVR4) || defined(__svr4__)
#define OSVR_SOLARIS 1
# else
#define OSVR_SUNOS 1
#endif
#endif

#if defined(__osf) || defined(__osf__)
#define OSVR_TRU64 1
#endif

#if defined(ultrix) || defined(__ultrix) || defined(__ultrix__) || (defined(unix) && defined(vax))
#define OSVR_ULTRIX 1
#endif

#if defined(__CYGWIN__)
#define OSVR_CYGWIN 1
#endif

#if (defined(__APPLE__) && defined(__MACH__))
#define OSVR_MACOSX 1
#endif

#if defined(_WIN32) || defined(WIN32) || defined(__NT__) || defined(__WIN32__)
#define OSVR_WINDOWS 1
#if defined(_WIN64)
#define OSVR_WIN64 1
#else
#define OSVR_WIN32 1
#endif // _WIN64
#endif // OSVR_WINDOWS

#if defined(_XBOX)
#define OSVR_XBOX 1
#endif
//@}

/** \name More general platforms. */
//@{
#if defined(unix) || defined(__unix__) || defined(__unix)
#define OSVR_UNIX 1
#endif

#if defined(OSVR_UNIX) || defined(OSVR_MACOSX)
#include <unistd.h>
#if defined(_POSIX_VERSION)
#define OSVR_POSIX 1
#endif
#endif
//@}

/**
 * \name Compiler tests.
 */
//@{
#if defined(__clang__)
#define OSVR_COMPILER_CLANG 1
#define OSVR_COMPILER_STRING "Clang"
#elif defined(__ICC) || defined(__INTEL_COMPILER)
#define OSVR_COMPILER_INTEL 1
#define OSVR_COMPILER_STRING "Intel"
#elif defined(__GNUC__) || defined(__GNUG__)
/* The GCC branch must be placed after Clang and Intel. */
#define OSVR_COMPILER_GCC 1
#define OSVR_COMPILER_STRING "GCC"
#elif defined(__HP_cc) || defined(__HP_aCC)
#define OSVR_COMPILER_HP 1
#define OSVR_COMPILER_STRING "HP"
#elif defined(__IBMC__) || defined(__IBMCPP__)
#define OSVR_COMPILER_IBM 1
#define OSVR_COMPILER_STRING "IBM"
#elif defined(_MSC_VER)
#define OSVR_COMPILER_MSVC 1
#define OSVR_COMPILER_STRING "Microsoft Visual C/C++"
#elif defined(__PGI)
#define OSVR_COMPILER_PORTLAND 1
#define OSVR_COMPILER_STRING "Portland"
#elif defined(__SUNPRO_C) || defined(__SUNPRO_CC)
#define OSVR_COMPILER_SOLARIS 1
#define OSVR_COMPILER_STRING "Solaris"
#endif
//@}

/**
 * \name Language tests.
 */
//@{
#if defined(__cplusplus)
#define OSVR_LANGUAGE_CPLUSPLUS 1
#else
#define OSVR_LANGUAGE_C 1
#endif
//@}

#endif // INCLUDED_Platform_h_GUID_13406B0D_1932_4A36_A5F1_55C508E07198

