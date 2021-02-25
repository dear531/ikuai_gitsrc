MODULE_NAME :=test_netlink_kmodule
obj-m :=$(MODULE_NAME).o
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
all:
	$(MAKE) -C $(KERNELDIR) M=$(PWD)
	gcc -o user_sent user_sent.c
clean:
	$(MAKE) clean -C $(KERNELDIR) M=$(PWD)
	rm -rf user_sent
