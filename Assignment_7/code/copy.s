.pos 0x100
main:   ld $stack_bottom, r5
        inca r5                 # allocate frame
        gpc $6, r6              # update RA and store in r6
        j copy                  # call copy
        halt
.pos 0x200
copy:   ld $-12, r0
        add r0, r5              # allocate frame
        st r6, 8(r5)            # store RA on stack
        ld $0, r2               # r2 = i = 0
L0:     ld $src, r0             # r0 = &src
        ld (r0, r2, 4), r0      # r0 = src[i]
        beq r0, end             # if src[i] == 0 goto end
        st r0, (r5, r2, 4)      # dst[i] = src[i]
        inc r2                  # i++
        br L0                   # goto L0
end:    ld $0, r0               # r0 = 0
        st r0, (r5, r2, 4)      # dst[i] = 0
        ld 8(r5), r6            # load RA from stack in r6
        ld $12, r0
        add r0, r5              # deallocate stack
        j (r6)                  # return


#data
.pos 0x1000
src:
.long 1                  # src[0]
.long 2                  # src[1]
.long 0x25C              # src[2]
.long 0x0000FFFF         # src[3]
.long 0xFFFF6001         # src[4]
.long 0x60026003         # src[5]
.long 0x60046005         # src[6]
.long 0x60066007         # src[7]
.long 0xF0000000         # src[8]
.long 0                  # src[9]


.pos 0x2000
.long 0
.long 0
stack_bottom:
.long 0
