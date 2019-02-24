.pos 0x0
main:            ld   $sb, r5             # initialize stack pointer
                 inca r5                  # to the bottom of the stack
                 gpc  $0x6, r6            # set return address
                 j    0x300               # call main
                 halt                     
.pos 0x100
p:               .long 0x1000             # int* p = a
.pos 0x200
bar:             ld   0x0(r5), r0         # r0 = a
                 ld   0x4(r5), r1         # r1 = b
                 ld   $0x100, r2          # r2 = &p
                 ld   0x0(r2), r2         # r2 = p
                 ld   (r2, r1, 4), r3     # r3 = p[b]
                 add  r3, r0              # r0 = a + p[b]
                 st   r0, (r2, r1, 4)     # p[b] = a + p[b]
                 j    0x0(r6)             
.pos 0x300
foo:             ld   $0xfffffff4, r0     # r0 = -12
                 add  r0, r5              # allocate frame on the stack
                 st   r6, 0x8(r5)         # save return address
                 ld   $0x1, r0            # r0 = 1
                 st   r0, 0x0(r5)         # local a = 1
                 ld   $0x2, r0            # r0 = 2
                 st   r0, 0x4(r5)         # local b = 2
                 ld   $0xfffffff8, r0     # r0 = -8
                 add  r0, r5              # stack pointer - 8
                 ld   $0x3, r0            # r0 = 3
                 st   r0, 0x0(r5)         # parameter 3
                 ld   $0x4, r0            # r0 = 4
                 st   r0, 0x4(r5)         # parameter 4
                 gpc  $0x6, r6            # set return address
                 j    0x200               # call bar
                 ld   $0x8, r0            # r0 = 8
                 add  r0, r5              # deallocate parameters
                 ld   0x0(r5), r1         # r1 = a
                 ld   0x4(r5), r2         # r2 = b
                 ld   $0xfffffff8, r0     # r0 = -8
                 add  r0, r5              # stack pointer - 8
                 st   r1, 0x0(r5)         # parameter a
                 st   r2, 0x4(r5)         # parameter b
                 gpc  $0x6, r6            # set return address
                 j    0x200               # call bar(a,b)
                 ld   $0x8, r0            # r0 = 8
                 add  r0, r5              # deallocate parameters
                 ld   0x8(r5), r6         # update return address
                 ld   $0xc, r0            # r0 = 12
                 add  r0, r5              # deallocate frame
                 j    0x0(r6)             
.pos 0x1000
a:               .long 0x0
                 .long 0x0                
                 .long 0x0                
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
