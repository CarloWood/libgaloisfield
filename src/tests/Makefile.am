## Process this file with automake to generate Makefile.in

AUTOMAKE_OPTIONS = foreign

EXTRA_PROGRAMS = \
	polynomial_gcd \
	prime_generator

CLEANFILES = $(EXTRA_PROGRAMS)

LIBS= @LIBS@ @CWD_LIBS@
BUILT_SOURCES =

polynomial_gcd_SOURCES = polynomial_gcd.cc
polynomial_gcd_DEPENDENCIES = $(DEPENDENCIES)

prime_generator_SOURCES = prime_generator.cc
prime_generator_DEPENDENCIES = $(DEPENDENCIES)

#threads_CXXFLAGS = -D_REENTRANT -DLIBCWD_THREAD_SAFE @CXXFLAGS@
#threads_SOURCES = threads.cc
#threads_LDADD = ../libcwd_r.la

#noinst_HEADERS = sys.h debug.h sys.h syslog_debug.h threads_debug.h initbug_GlobalObject.h

LDADD = ../libgaloisfield.la
full_top_builddir := $(shell (cd $(top_builddir); pwd))
LDFLAGS = -Wl,-rpath -Wl,$(full_top_builddir)/.libs

CXXFLAGS = -g @CWD_FLAGS@
INCLUDES = -I. -I$(top_builddir)/src/include -I$(srcdir)/../include -I$(srcdir)/.. -I$(top_builddir)
DEFAULT_INCLUDES =

if USE_PCH
@Makefilein@PREVCXXDEPMODE := $(CXXDEPMODE)
@Makefilein@CXXDEPMODE = $(PREVCXXDEPMODE) havepch=yes
@Makefilein@ifeq (./$(DEPDIR)/pch.po, $(wildcard ./$(DEPDIR)/pch.po))
@Makefilein@@am__include@ ./$(DEPDIR)/pch.po
@Makefilein@endif
CXXFLAGS += @PCHFLAGS@

APPLICATIONSUM := $(shell echo "$(CXXFLAGS)" | md5sum | sed -e 's/ .*//')

BUILT_SOURCES += pch.h.gch/$(APPLICATIONSUM)

pch.h.gch/$(APPLICATIONSUM): $(srcdir)/../pch-source.h Makefile
	@rm -f $@
	@test -d pch.h.gch || mkdir pch.h.gch
	@test -d $(DEPDIR) || mkdir $(DEPDIR)
	@mkdir -p empty.pch.h
	@touch empty.pch.h/pch.h
	@if $(CXX) -Iempty.pch.h $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(CXXFLAGS) \
	  -UUSE_PCH -M -MT pch.h.gch -MF $(DEPDIR)/pch.TTpo $(srcdir)/../pch-source.h; then \
	  cat $(DEPDIR)/pch.TTpo | sed -e 's%^pch\.h\.gch:%pch.h.gch/$(APPLICATIONSUM):%' -e 's% empty\.pch\.h/pch\.h%%' > $(DEPDIR)/pch.Tpo; \
	  cmp -s $(DEPDIR)/pch.Tpo $(DEPDIR)/pch.po || mv $(DEPDIR)/pch.Tpo $(DEPDIR)/pch.po; \
	fi
	$(CXX) -Iempty.pch.h $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(CXXFLAGS) \
	  -c -o $@ $(srcdir)/../pch-source.h
	@rm empty.pch.h/pch.h
	@rmdir empty.pch.h

DEPENDENCIES = pch.h.gch/$(APPLICATIONSUM)

endif

all: $(EXTRA_PROGRAMS)

clean-local:
if USE_PCH
	rm -f pch.h.gch/* $(DEPDIR)/pch.*po
endif

MAINTAINERCLEANFILES = $(srcdir)/Makefile.in sys.h
