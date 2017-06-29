obj-m += fluff.o

all:
	make -C /lib/modules/4.11.0/build M=$(PWD) modules

clean:
	make -C /lib/modules/4.11.0/build M=$(PWD) clean
