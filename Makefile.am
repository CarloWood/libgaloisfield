## Process this file with automake to generate Makefile.in

AUTOMAKE_OPTIONS = foreign
ACLOCAL_AMFLAGS = @ACLOCAL_CWFLAGS@

SUBDIRS = src . doc

EXTRA_DIST = COPYING INSTALL README NEWS
DISTCLEANFILES = stamp-h.in

DEFS = @DEFS@
CXXFLAGS = @CXXFLAGS@ @CWD_FLAGS@
LIBS = @CWD_LIBS@

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = libgaloisfield.pc

# --------------- Maintainer's Section

distclean-local:
	rm -rf $(srcdir)/autom4te.cache *~

MAINTAINERCLEANFILES = $(srcdir)/aclocal.m4 $(srcdir)/config.h.in $(srcdir)/configure $(srcdir)/Makefile.in \
	$(srcdir)/install-sh $(srcdir)/missing $(srcdir)/mkinstalldirs $(srcdir)/config.guess $(srcdir)/config.sub \
	$(srcdir)/ltmain.sh $(srcdir)/stamp-h.in $(srcdir)/ChangeLog $(srcdir)/depcomp troep*
