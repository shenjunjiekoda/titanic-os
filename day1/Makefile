all:
	nasm titanicos.asm -o titanicos.img

clean:
	rm -rf titanicos.img

qemu:all
	qemu-system-x86_64 -fda titanicos.img

.PHONY:
	all