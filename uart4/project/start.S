.global _start

_start:
    ldr pc, =_reset_handler
    ldr pc, =_undefined_handler
    ldr pc, =_svc_handler
    ldr pc, =_prefetch_handler
    ldr pc, =_data_abort_handler
    ldr pc, =_not_user_handler
    ldr pc, =_irq_handler
    ldr pc, =_fiq_handler  

_undefined_handler:
    ldr pc, =_undefined_handler

_svc_handler:
    ldr pc, =_svc_handler

_prefetch_handler:
    ldr pc, =_prefetch_handler

 _data_abort_handler:
    ldr pc, =_data_abort_handler   

_not_user_handler:
    ldr pc, =_not_user_handler

 _irq_handler:
    subs lr, lr, #4
    stmfd sp!, {r0-r12, lr}

    mrc p15, 4, r1, c15, c0, 0
    add r1, r1, #0x2000
    ldr r0, [r1, #0x0C]

    stmfd sp!, {r0, r1}

    cps #0x1F
    stmfd sp!, {lr}
    bl system_interrupt_handler
    ldmfd sp!, {lr}

    cps 0x12
    ldmfd sp!, {r0, r1}
    str r0, [r1, #0x10]

    ldmfd sp!, {r0-r12, pc}^

_fiq_handler:
    ldr pc, =_fiq_handler    

_reset_handler:
    cpsid i

    mrc p15, 0, r0, c1, c0, 0
    bic r0, r0, #(1 << 13)
    orr r0, r0, #(1 << 12)
    mcr p15, 0, r0, c1, c0, 0


    cps #0x12
    ldr sp, =0x82000000

    cps #0x1F//system
    ldr sp, =0x84000000
    cpsie i

    bl _init_bss
    b main
    b finished

_init_bss:
    ldr r0, = __bss_start
    ldr r1, =__bss_end
loop:
    mov r2, #0
    str r2, [r0]
    add r0, r0, #4
    cmp r0, r1
    blt loop
    bx lr




finished:
    b finished    