MODULE_NAME = g13_driver

KDIR := /lib/modules/$(shell uname -r)/build

SRCS = src/g13_driver.c

OBJS = $(SRCS:.c=.o)

obj-m += $(MODULE_NAME).o
$(MODULE_NAME)-y = $(OBJS)

all:
	    make -C $(KDIR) M=$(PWD) modules

clean:
	    make -C $(KDIR) M=$(PWD) clean
