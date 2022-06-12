all:
	nasm titanicos.asm -o titanicos.bin
	dd if=/dev/zero of=titanicos.img bs=512 count=2880
	dd if=titanicos.bin of=titanicos.img bs=512 count=1 conv=notrunc

clean:
	rm -rf titanicos.bin titanicos.img

qemu:all
	#qemu-system-aarch64 -machine virt -cpu cortex-a53  -drive file=titanicos.img
	qemu-system-i386 -fda titanicos.img

.PHONY: all
