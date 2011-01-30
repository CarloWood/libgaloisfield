dnl Run autogen.sh to produce a configure script.

dnl CW_VERSION_MAJOR               : Increment when the whole library was rewritten; or some VERY MAJOR change was made.
dnl CW_VERSION_MINOR               : Increment when major changes have occured, like removing interfaces.
dnl CW_VERSION_REVISION            : Increment every public release; or set to 0 when CW_VERSION_MINOR was incremented.

define(CW_VERSION_MAJOR, 0)
define(CW_VERSION_MINOR, 0)
define(CW_VERSION_REVISION, 0)

dnl Version info, see http://www.gnu.org/software/libtool/manual.html#Updating-version-info
dnl
dnl CW_INTERFACE_VERSION           : Current interface version, increment whenever the interface is changed.
dnl CW_INTERFACE_VERSION_REVISION  : Revision, increment every public release; or set to 0 when the interface is changed.
dnl CW_INTERFACE_AGE               : Increment if interfaces have been added; or set to 0 when interfaces have been removed.

define(CW_INTERFACE_VERSION, 0)
define(CW_INTERFACE_VERSION_REVISION, 0)
define(CW_INTERFACE_AGE, 0)

define(CW_PACKAGE_NAME, [libgaloisfield])
define(CW_BUGREPORT, [carlo@alinoe.com])

dnl Package name and version
AC_INIT(CW_PACKAGE_NAME, CW_VERSION_MAJOR.CW_VERSION_MINOR.CW_VERSION_REVISION, CW_BUGREPORT)

dnl Put resulting configuration defines in this header file.
AC_CONFIG_HEADERS([config.h])

dnl Ensure that the directory specified with --srcdir was correct
dnl by demanding that it contains `libgaloisfield.pc.in'.
AC_CONFIG_SRCDIR([libgaloisfield.pc.in])

dnl Automake options.
AM_INIT_AUTOMAKE

dnl Include maintainer mode targets
AM_MAINTAINER_MODE

dnl Because we use cwautomacros.
CW_AUTOMACROS([20110128])

dnl We use doxygen for documentation.
CW_DOXYGEN

dnl Demand at least version 2.57 of autoconf.
AC_PREREQ(2.57)

dnl Check for compiler and preprocessor
AC_PROG_CC
AC_PROG_CXX
AC_PROG_CXXCPP

dnl Add --enable-debug (DEBUG, DOXYGEN_DEBUG), --enable-libcwd (CWDEBUG, DOXYGEN_CWDEBUG),
dnl --enable-optimise and --enable-profile options. Update USE_LIBCWD, CWD_LIBS and CXXFLAGS accordingly.
CW_OPG_FLAGS([-W -Wall -Woverloaded-virtual -Wundef -Wpointer-arith -Wwrite-strings -Winline])

dnl Add --enable-pch (USE_PCH (macro)) option.
dnl Update USE_PCH (automake conditional) and PCHFLAGS accordingly.
CW_PCHFLAGS

dnl Each Makefile.am should use DEFS = @DEFS@. Set DEFS here.
DEFS="-DHAVE_CONFIG_H"
AC_SUBST(DEFS)

dnl These CFLAGS are used in the .pc file.
PCCFLAGS=
AC_SUBST(PCCFLAGS)

dnl Checks for other programs.
AC_PROG_INSTALL
AC_PROG_LIBTOOL

dnl Libtool version info
VERSIONINFO="CW_INTERFACE_VERSION:CW_INTERFACE_VERSION_REVISION:CW_INTERFACE_AGE"
AC_SUBST(VERSIONINFO)

dnl Detect boost.
#CW_BOOST([$cw_enable_static], [no], [])

dnl Used in sys.h to force recompilation when the compiler version changes.
CW_PROG_CXX_FINGER_PRINTS
CC_FINGER_PRINT="$cw_prog_cc_finger_print"
AC_SUBST([CC_FINGER_PRINT])
CXX_FINGER_PRINT="$cw_prog_cxx_finger_print"
AC_SUBST([CXX_FINGER_PRINT])
CXXCPP_FINGER_PRINT="$cw_prog_cxxcpp_finger_print"
AC_SUBST([CXXCPP_FINGER_PRINT])

dnl Generate src/sys.h from src/sys.h.in
CW_CONFIG_FILE([src], [sys.h])

dnl Output the other configuration files.
AC_CONFIG_FILES(
        [Makefile]
        [src/Makefile]
	[src/include/Makefile]
	[src/include/libgaloisfield/Makefile]
	[libgaloisfield.pc]
        [doc/Makefile]
        [doc/doxygen.config]
	[doc/html.header]
	[doc/html.footer])

AC_OUTPUT
