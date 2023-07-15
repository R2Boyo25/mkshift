AC_INIT([mkshift],[0.1.0])
AM_INIT_AUTOMAKE([subdir-objects])

AC_PROG_CXX
AC_PROG_RANLIB

AC_SUBST([MKSHIFTLIBSLD], ["$(pkg-config xext x11 cairo-xlib-xrender --libs) $(pkg-config xrandr --libs --silence-errors) $(pkg-config xinerama --libs --silence-errors)"])
AC_CHECK_HEADERS([X11/extensions/Xrandr.h X11/extensions/Xinerama.h])

AC_CONFIG_FILES([link_flags])
AC_CONFIG_FILES([Makefile])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_SUBDIRS([libs/yoga])

AC_OUTPUT
