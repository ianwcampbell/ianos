
SRCS = $(wildcard *.c)
CROSSPATH=../../gcc-arm-8.3-2019.03-x86_64-aarch64-elf/bin/aarch64-elf-
CC=$(CROSSPATH)gcc
OBJCOPY=$(CROSSPATH)objcopy
LINKER=$(CROSSPATH)ld
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles

all: clean kernel8.img

start.o: start.S
	$(CC) $(CFLAGS) -c start.S -o start.o

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

kernel8.img: start.o $(OBJS)
	$(LINKER) -nostdlib -nostartfiles start.o $(OBJS) -T link.ld -o kernel8.elf
	$(OBJCOPY) -O binary kernel8.elf kernel8.img

clean:
	rm kernel8.elf *.o >/dev/null 2>/dev/null || true

run:
	qemu-system-aarch64 -M raspi3 -kernel kernel8.img -serial stdio
