.pos 0x100
start:           ld   $sb, r5             # initialize the stack pointer
                 inca r5                  # move to the bottom of the stack
                 gpc  $0x6, r6            # set return address
                 j    main                # call main()
                 halt                     
f:               deca r5                  # allocate stack frame
                 ld   $0x0, r0            # r0 = j = 0
                 ld   0x4(r5), r1         # r1 = i = 0
                 ld   $0x80000000, r2     # r2 = 0x80000000
f_loop:          beq  r1, f_end           # if i == 0 goto f_end
                 mov  r1, r3              # r3 = i
                 and  r2, r3              # r3 = i & 0x80000000
                 beq  r3, f_if1           # if i & 0x80000000 == 0 goto f_if1
                 inc  r0                  # j++
f_if1:           shl  $1, r1              # i = i  << 1
                 br   f_loop              # goto f_loop
f_end:           inca r5                  # deallocate stack frame
                 j    0x0(r6)             # return
main:            deca r5                  # allocate stack frame
                 deca r5                  # allocate stack frame
                 st   r6, 0x4(r5)         # save return address
                 ld   $0x8, r4            # r4 = i = 8
main_loop:       beq  r4, main_end        # if i == 0 goto main_end
                 dec  r4                  # i--
                 ld   $x, r0              # r0 = &x
                 ld   (r0, r4, 4), r0     # r0 = x[i]
                 deca r5                  # allocate  one int parameter
                 st   r0, 0x0(r5)         # parameter x[i]
                 gpc  $0x6, r6            # set return address
                 j    f                   # call f(x[i])
                 inca r5                  # deallocate parameter
                 ld   $y, r1              # r1 = &y
                 st   r0, (r1, r4, 4)     # y[i] = f(x[i])
                 br   main_loop           # goto main_loop
main_end:        ld   0x4(r5), r6         # update return address
                 inca r5                  # deallocate frame
                 inca r5                  # deallocate frame
                 j    0x0(r6)             
.pos 0x2000
x:               .long 0x1                
                 .long 0x2                
                 .long 0x3                
                 .long 0xffffffff         
                 .long 0xfffffffe         
                 .long 0x0                
                 .long 0xb8               
                 .long 0x1444dbe2         
y:               .long 0x0                
                 .long 0x0                
                 .long 0x0                
                 .long 0x0                
                 .long 0x0                
                 .long 0x0                
                 .long 0x0                
                 .long 0x0                
.pos 0x8000
                 .long 0x0                # These are here so you can see (some of) the stack contents.
                 .long 0x0                
                 .long 0x0                
                 .long 0x0                
                 .long 0x0                
                 .long 0x0                
                 .long 0x0                
                 .long 0x0                
                 .long 0x0                
                 .long 0x0                
                 .long 0x0                
                 .long 0x0                
                 .long 0x0                
                 .long 0x0                
                 .long 0x0                
                 .long 0x0                
                 .long 0x0                
                 .long 0x0                
                 .long 0x0                
                 .long 0x0                
                 .long 0x0                
                 .long 0x0                
                 .long 0x0                
sb:              .long 0x0                
