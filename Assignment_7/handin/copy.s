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
.long 0x2080
.long 0x2080
.long 0x2080
.long 0x2080
.long 0x2080
.long 0x2080
.long 0x2080
.long 0xff00ff00            # nop slide
.long 0xff00ff00            # nop slide
.long 0xff00ff00            # nop slide
.long 0xff00ff00            # nop slide
.long 0xff00ff00            # nop slide
.long 0xff00ff00            # nop slide
.long 0xff00ff00            # nop slide
.long 0xff00ff00            # nop slide
.long 0xff00ff00            # nop slide
.long 0xff00ff00            # nop slide
.long 0xff00ff00            # nop slide
.long 0xff00ff00            # nop slide
.long 0xff00ff00            # nop slide
.long 0xff00ff00            # nop slide
.long 0xff00ff00            # nop slide
.long 0xff00ff00            # nop slide
.long 0xff00ff00            # nop slide
.long 0xff00ff00            # nop slide
.long 0xff00ff00            # nop slide
.long 0xff00ff00            # nop slide
.long 0xff00ff00            # nop slide
.long 0xff00ff00            # nop slide
.long 0xff00ff00            # nop slide
.long 0xff00ff00            # nop slide
.long 0xff00ff00            # nop slide
.long 0xff00ff00            # nop slide
.long 0xff00ff00            # nop slide
.long 0xff00ff00            # nop slide
.long 0xff00ff00            # nop slide
.long 0xff00ff00            # nop slide
.long 0x0100ffff            # ld $-1, r1
.long 0xffffff00            # finished with nop
.long 0x0200ffff            # ld $-1, r2
.long 0xffffff00            # finished with nop
.long 0x0300ffff            # ld $-1, r3
.long 0xffffff00            # finished with nop
.long 0x0400ffff            # ld $-1, r4
.long 0xffffff00            # finished with nop
.long 0x0500ffff            # ld $-1, r5
.long 0xffffff00            # finished with nop
.long 0x0600ffff            # ld $-1, r6
.long 0xffffff00            # finished with nop
.long 0x0700ffff            # ld $-1, r7
.long 0xffffff00            # finished with nop
.long 0x0000ffff            # ld $-1, r0
.long 0xffffff00            # finished with nop
.long 0xff00f000            # nop then halt
.long 0


.pos 0x2000
.long 0
.long 0
stack_bottom:
.long 0
