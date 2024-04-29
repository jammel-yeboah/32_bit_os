CC=i686-elf-gcc
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra
LFLAGS=-T linker.ld -ffreestanding -O2 -nostdlib -lgcc

myos.bin: kernel.o boot.o
	$(CC) $(LFLAGS) -o $@ $^

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.o: %.s
	i686-elf-as -o $@ $<

.PHONY: clean
clean:
	rm -f *.o myos.bin

.PHONY: check-multiboot
check-multiboot: myos.bin
		if grub-file --is-x86-multiboot $<; then \
			echo multiboot confirmed; \
		else \
			echo the file is not multiboot; \
		fi

myos.iso: myos.bin grub.cfg
	mkdir -p isodir/boot/grub
	cp myos.bin isodir/boot/myos.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o myos.iso isodir
