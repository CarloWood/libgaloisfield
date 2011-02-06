## Process this file with automake to generate Makefile.in

AUTOMAKE_OPTIONS = foreign

SUBDIRS = . include tests

EXTRA_DIST = pch-source.h ${BUILT_SOURCES}

lib_LTLIBRARIES = libgaloisfield.la
VERSIONINFO = @VERSIONINFO@
INCLUDES = -I$(top_builddir)/include -I$(srcdir)/include
BUILT_SOURCES = irreducible_bits.cc factorized.cc
DEFS = @DEFS@
CXXFLAGS =

libgaloisfield_la_SOURCES = \
	GFElement.cc \
	GaloisField.cc \
	Prime.cc \
	debug_ostream_operators.h \
	debug_ostream_operators.cc \
	debug.h \
	debug.cc \
	${BUILT_SOURCES}

libgaloisfield_la_CXXFLAGS = @CXXFLAGS@ @CWD_FLAGS@
libgaloisfield_la_LIBADD = @LIBS@ @CWD_LIBS@
libgaloisfield_la_LDFLAGS = -version-info $(VERSIONINFO) -no-undefined

if MAINTAINER_MODE
bin_PROGRAMS = generate_irreducible_bits generate_factorized

generate_irreducible_bits_SOURCES = generate_irreducible_bits.cc
generate_factorized_SOURCES = generate_factorized.cc Prime.cc
generate_irreducible_bits_CXXFLAGS = @CXXFLAGS@
generate_factorized_CXXFLAGS = @CXXFLAGS@
endif

if USE_PCH
@Makefilein@PREVCXXDEPMODE := $(CXXDEPMODE)
@Makefilein@CXXDEPMODE = $(PREVCXXDEPMODE) havepch=yes
@Makefilein@ifeq (./$(DEPDIR)/pch.po, $(wildcard ./$(DEPDIR)/pch.po))
@Makefilein@@am__include@ ./$(DEPDIR)/pch.po
@Makefilein@endif
PIC_FLAGS := $(shell egrep '^pic_flag=.*-f(PIC|pic)' $(top_builddir)/libtool | head -n 1 | sed -r -e 's/pic_flag=//' -e 's/^ *"//' -e 's/" *$$//')
libgaloisfield_la_CXXFLAGS += @PCHFLAGS@

APPLICATIONSUM := $(shell echo "$(CXXFLAGS)" | md5sum | sed -e 's/ .*//')
APPLICATIONSUM_PIC := $(shell echo "$(CXXFLAGS) $(PICFLAGS)" | md5sum | sed -e 's/ .*//')

BUILT_SOURCES += pch.h.gch/$(APPLICATIONSUM)
BUILT_SOURCES += pch.h.gch/$(APPLICATIONSUM_PIC)

pch.h.gch/$(APPLICATIONSUM): $(srcdir)/pch-source.h Makefile
	@rm -f $@
	@test -d pch.h.gch || mkdir pch.h.gch
	@test -d $(DEPDIR) || mkdir $(DEPDIR)
	@mkdir -p empty.pch.h
	@touch empty.pch.h/pch.h
	@if $(CXX) -Iempty.pch.h $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(libgaloisfield_la_CXXFLAGS) \
	  -UUSE_PCH -M -MT pch.h.gch -MF $(DEPDIR)/pch.TTpo $(srcdir)/pch-source.h; then \
	  cat $(DEPDIR)/pch.TTpo | sed -e 's%^pch\.h\.gch:%pch.h.gch/$(APPLICATIONSUM):%' -e 's% empty\.pch\.h/pch\.h%%' > $(DEPDIR)/pch.Tpo; \
	  cmp -s $(DEPDIR)/pch.Tpo $(DEPDIR)/pch.po || mv $(DEPDIR)/pch.Tpo $(DEPDIR)/pch.po; \
	fi
	$(CXX) -Iempty.pch.h $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(libgaloisfield_la_CXXFLAGS) \
	  -c -o $@ $(srcdir)/pch-source.h
	@rm empty.pch.h/pch.h
	@rmdir empty.pch.h

pch.h.gch/$(APPLICATIONSUM_PIC): $(srcdir)/pch-source.h Makefile
	@rm -f $@
	@test -d pch.h.gch || mkdir pch.h.gch
	@test -d $(DEPDIR) || mkdir $(DEPDIR)
	@mkdir -p empty.pch.h
	@touch empty.pch.h/pch.h
	$(CXX) -Iempty.pch.h $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(libgaloisfield_la_CXXFLAGS) $(PIC_FLAGS) \
	  -c -o $@ $(srcdir)/pch-source.h
	@rm empty.pch.h/pch.h
	@rmdir empty.pch.h
endif

# --------------- Maintainer's Section

#dist-hook:

all-local:
	@if test -e $(top_srcdir)/../.libcwdrc-src -a ! -e .libcwdrc; then \
	  echo "ln -s $(top_srcdir)/../.libcwdrc-src .libcwdrc"; \
	  ln -s $(top_srcdir)/../.libcwdrc-src .libcwdrc; \
	fi
	@if test -e $(top_srcdir)/../.gdbinit-src -a ! -e .gdbinit; then \
	  echo "ln -s $(top_srcdir)/../.gdbinit-src .gdbinit"; \
	  ln -s $(top_srcdir)/../.gdbinit-src .gdbinit; \
	fi

distclean-local:
	rm -rf $(srcdir)/autom4te.cache
	@MAINTAINER_MODE_TRUE@rm -f .all_sources *.s *.ii

clean-local:
	rm -f core
if USE_PCH
	rm -f pch.h.gch/* $(DEPDIR)/pch.*po
endif

MAINTAINERCLEANFILES = $(srcdir)/Makefile.in sys.h $(srcdir)/irreducible_bits.cc $(srcdir)/factorized.cc tags troep* *.cgd

if MAINTAINER_MODE
$(srcdir)/irreducible_bits.cc: generate_irreducible_bits
	./generate_irreducible_bits ~/projects/libecc/libecc > $(srcdir)/irreducible_bits.cc

$(srcdir)/factorized.cc: generate_factorized
	./generate_factorized > $(srcdir)/factorized.cc

# Usage: You have to set the CTAGS_ROOT_SRCDIRS environment variable yourself,
# for example: export CTAGS_ROOT_SRCDIRS="/usr/src/gtk/glib-current /usr/src/gtk/gtk+-current"
# Then run 'vim -u /some/path/.vimrc' where the .vimrc is the normal .vimrc, but with the
# additional lines: set tags=/full/path/to/top_builddir/tags
#                   nmap <C-N> :tnext<CR>
ctags:
	rm -f .all_sources
	touch .all_sources
	for d in $(CTAGS_ROOT_SRCDIRS) $(top_srcdir); do \
	  find $$d -follow -type f -name '*.h' -o -name '*.hpp' -o -name '*.c' -o -name '*.cc' -o -name '*.cpp' -o -name '*.cxx' -o -name '*.C' -o -name '*.inl' >> .all_sources; \
	done
	ctags `cat .all_sources`
endif
