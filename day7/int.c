#include <stdio.h>

#include "bootpack.h"
#include "fifo.h"
#include "graphic.h"
#include "int.h"
#include "io.h"
#include "keyboard.h"
#include "mouse.h"

void init_pic(void) {
  // 禁止所有中断
  io_out8(PIC0_IMR, 0xff);
  io_out8(PIC1_IMR, 0xff);

  io_out8(PIC0_ICW1, 0x11); // 边缘触发模式
  io_out8(PIC0_ICW2, 0x20); // IRQ0-7由INT20-27接收
  io_out8(PIC0_ICW3, 1 << 2); // PIC1由IRQ2连接
  io_out8(PIC0_ICW4, 0x01); // 无缓冲区模式

  io_out8(PIC1_ICW1, 0x11); // 边缘触发模式
  io_out8(PIC1_ICW2, 0x28); // IRQ8-15由INT28-2f接收
  io_out8(PIC1_ICW3, 2); // PIC1由IRQ2连接
  io_out8(PIC1_ICW4, 0x01); // 无缓冲区模式

  io_out8(PIC0_IMR, 0xfb); // PIC1以外中断全部禁止
  io_out8(PIC1_IMR, 0xff); // 禁止全部中断
}

void int_handler21(int *esp) {
  io_out8(PIC0_OCW2, 0x61); // 通知PIC IRQ-1（0x60+1）的受理已经完成
  unsigned char data = io_in8(PORT_KEYDAT);

  fifo8_put(&keyfifo, data);
}

void int_handler2c(int *esp) {
  io_out8(PIC1_OCW2, 0x64); // 通知PIC1 IRQ-12的受理已经完成
  io_out8(PIC0_OCW2, 0x62); // 通知PIC0 IRQ-02的受理已经完成
  unsigned char data = io_in8(PORT_KEYDAT);
  
  fifo8_put(&mousefifo, data);
}

void int_handler27(int *esp) {
	io_out8(PIC0_OCW2, 0x67);
}
