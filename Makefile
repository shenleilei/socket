KDIR = /usr/src/linux-headers-3.13.0-32-generic
PWD = $(shell pwd)
CC=gcc
obj-m := netlink_kernel.o
default:
	make -C $(KDIR) M=$(PWD) modules
clean:
	$(RM) *.o *.ko *.mod.c Module.symvers
