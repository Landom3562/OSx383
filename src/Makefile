SOURCES=boot.o main.o monitor.o common.o descriptor_tables.o isr.o interrupt.o gdt.o kb.o clock.o shell.o timer.o task.o scheduler.o context_switch.o

CFLAGS=-nostdlib -nostdinc -fno-builtin -fno-stack-protector -m32 -O0 
LDFLAGS=-melf_i386 -Tlink.ld 
ASFLAGS=-felf32

all: $(SOURCES) link

clean:
	-rm *.o kernel

link:
	ld $(LDFLAGS) -o kernel $(SOURCES)

.s.o:
	nasm $(ASFLAGS) $<
