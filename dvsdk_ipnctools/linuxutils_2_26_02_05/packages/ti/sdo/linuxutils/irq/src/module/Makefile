#
#  Copyright 2011 by Texas Instruments Incorporated.
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; version 2 of the License.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>
#
#

ROOTDIR = ../..

# We conditionally include $(ROOTDIR)/Rules.make because when the
# kernel make system invokes us, it won't be found... but that's okay.
-include $(ROOTDIR)/Rules.make

TARGET = irqk.ko

obj-y += irqk.o

EXTRA_CFLAGS +=	-DUSE_UDEV=$(USE_UDEV) -ULSP_210

MAKE_ENV = ARCH=arm CROSS_COMPILE=$(MVTOOL_PREFIX)

INCLUDEDIR = $(ROOTDIR)/include
HEADERS = $(wildcard *.h)
TARGETHEADERS = $(addprefix $(INCLUDEDIR)/, $(HEADERS))

debug: EXTRA_CFLAGS += -D__DEBUG

.PHONY: clean debug release install default

default: release

docs:

release: $(TARGETHEADERS)
	make -C $(LINUXKERNEL_INSTALL_DIR) M=`pwd` $(MAKE_ENV) \
		EXTRA_CFLAGS="$(EXTRA_CFLAGS)" 

debug: $(TARGETHEADERS)
	make -C $(LINUXKERNEL_INSTALL_DIR) M=`pwd` $(MAKE_ENV) \
		EXTRA_CFLAGS="$(EXTRA_CFLAGS)" modules

$(TARGETHEADERS): $(HEADERS)
	@echo Installing headers...
	@install -d $(INCLUDEDIR)
	@install $< $@

install:
	install -d $(EXEC_DIR)

clean:
	-rm -rf *.o *mod* *.ko .irq* .tmp*
#
#  @(#) ti.sdo.linuxutils.irq; 1, 0, 0,85; 7-12-2011 11:02:28; /db/atree/library/trees/linuxutils/linuxutils-j05x/src/ xlibrary

#

