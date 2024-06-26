global context_switch
context_switch:
     cli;
     mov ecx, [esp+4]   ; EIP
     mov ebp, [esp+8]  ; EBP
     mov esp, [esp+12]  ; ESP
     mov eax, 0x12345   ; magic number to detect a task switch
     sti;
     jmp ecx
global save_context
global restore_context
save_context:
    pusha                   ;Push all general-purpose registers onto the stack
    mov [eax], esp        ;Save the stack pointer into the task structure
    ret

restore_context:
    mov esp, [eax]        ;Restore the stack pointer from the task structure
    popa                    ;Pop all general-purpose registers from the stack
    ret
global read_eip
read_eip:
    pop eax          ;Get the return address from the stack
    jmp eax         ;Jump to the return address