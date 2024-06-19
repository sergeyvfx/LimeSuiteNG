# Makefile for kernel module
KERNEL_VERSION:=$(shell uname -r)
KERNEL_PATH?=/lib/modules/$(KERNEL_VERSION)/build
ARCH?=$(shell uname -m)

# ARCH might be 'aarch64', but the linux lib directories might be named 'arm64'
ARCH?=$(shell if [ "$(shell uname -m)" = "aarch64" ] && [ ! -d $(KERNEL_PATH)/arch/$(shell uname -m) ]; then echo "arm64"; else echo $(shell uname -m); fi)

obj-m = litepcie.o
# litepcie-objs = litepcie.o

all: litepcie.ko

export EXTRA_CFLAGS := -std=gnu11 -Wno-declaration-after-statement -I$(PWD)/bsp

litepcie.ko: litepcie.c
	make -C $(KERNEL_PATH) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) M=$(PWD) modules

litepcie.ko: boards.h litepcie.h bsp/config.h bsp/csr.h bsp/flags.h bsp/mem.h bsp/soc.h

clean:
	make -C $(KERNEL_PATH) ARCH=$(ARCH) CROSS_COMPILE=$(CROSS_COMPILE) M=$(PWD) clean
	rm -f *~
