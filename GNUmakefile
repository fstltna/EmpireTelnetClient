#
#   Empire - A multi-player, client/server Internet based war game.
#   Copyright (C) 1986-2017, Dave Pare, Jeff Bailey, Thomas Ruschak,
#                 Ken Stevens, Steve McClure, Markus Armbruster
#
#   Empire is free software: you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation, either version 3 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#   ---
#
#   See files README, COPYING and CREDITS in the root of the source
#   tree for related information and legal notices.  It is expected
#   that future projects/authors will amend these files as needed.
#
#   ---
#
#   GNUmakefile.  Generated from GNUmakefile.in by configure.
#   GNUmakefile.in: Makefile template for configure
#
#   Known contributors to this file:
#      Markus Armbruster, 2005-2009
#

# The real meat is in Make.mk, which see.

TARNAME := empire

CC := gcc
CFLAGS := -g -O2 -Wall -Wextra -Wdeclaration-after-statement -Wformat-security -Winit-self -Wlogical-op -Wmissing-prototypes -Wnested-externs -Wold-style-definition -Wpacked -Wpointer-arith -Wredundant-decls -Wstrict-prototypes -Wundef -Wno-unused-parameter -fno-builtin-carg -fno-common -fno-strict-aliasing -fno-strict-overflow
CPPFLAGS :=  -DHAVE_CONFIG_H
LDFLAGS :=  -fstack-protector-strong
LIBOBJS := 
LDLIBS := -lm
empthread := LWP
ifeq ($(empthread),POSIX)
CC := gcc
CFLAGS := $(CFLAGS) -pthread
LDFLAGS := $(LDFLAGS) -pthread
LDLIBS :=  $(LDLIBS)
endif
ifeq ($(empthread),Windows)
CFLAGS := $(CFLAGS) -mthreads
endif
LIBS_client := -ltermcap -lreadline   $(LDLIBS)
LIBS_server :=   $(LDLIBS)
LDLIBS :=  $(LDLIBS)
CCDEPMODE := depmode=gcc3
how_to_dep := fast
#how_to_dep := depcomp
EXEEXT := 
ifneq (o,o)
$(error This makefile can't cope with your compiler's object file names)
endif

AWK := mawk
INSTALL := /usr/bin/install -c
INSTALL_DATA := ${INSTALL} -m 644
INSTALL_PROGRAM := ${INSTALL}
NROFF := GROFF_NO_SGR= groff -Tascii -U
RANLIB := ranlib

prefix := /usr/local
exec_prefix := ${prefix}
bindir := ${exec_prefix}/bin
sbindir := ${exec_prefix}/sbin
datarootdir := ${prefix}/share
datadir := ${datarootdir}
localstatedir := ${prefix}/var
mandir := ${datarootdir}/man
sysconfdir := ${prefix}/etc

srcdir := .
VPATH := .

revctrl := 

EMPIREHOST := 127.0.0.1
EMPIREPORT := 6665

include $(srcdir)/Make.mk
