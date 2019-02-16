.pos 0x100
            ld $0, r0           # r0 = 0 = i'
            ld $n, r1           # r1 = &n
            ld (r1), r1         # r1 = n
            not r1              # r1 = !n
            inc r1              # r1 = -n
            ld $0, r2           # r2 = 0 = c'
            ld $a, r3           # r3 = &a
            ld $b, r4           # r4 = &b
loop:       mov r0, r5          # r4 = i'
            add r1, r5          # r4 = i' - n
            beq r5, end_loop    # if i' = n goto end_loop
            ld (r3, r0, 4), r6  # r6 = a[i']
            ld (r4, r0, 4), r7  # r7 = b[i']
            not r7              # r7 = !b[i']
            inc r7              # r7 = -b[i']
            add r6, r7          # r7 = a[i'] - b[i']
            bgt r7, if          # if a[i'] > b[i'] goto if
            inc r0              # i'++
            br loop             # goto loop
if:         inc r2              # c'++
            inc r0              # i'++
            br loop             # goto loop
end_loop:   ld $c, r3           # r3 = &c
            st r2, (r3)         # c = c'
            ld $i, r4           # r4 = &i
            st r0, (r4)         # i = i'
            halt


.pos 0x1000
i:  .long 0xffffffff    # i
n:  .long 5     # n
a:  .long 10    # a[0]
    .long 20    # a[1]
    .long 30    # a[2]
    .long 40    # a[3]
    .long 50    # a[4]
b:  .long 11    # b[0]
    .long 20    # b[1]
    .long 28    # b[2]
    .long 44    # b[3]
    .long 48    # b[4]
c:  .long 0
