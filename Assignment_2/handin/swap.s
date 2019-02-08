.pos 0x100
        ld $t, r0                    # r0 = &t
        ld $array, r1                # r1 = &array
        ld (r1), r2                  # r2 = array[0]
        ld 4(r1), r3                 # r3 = array[1]
        st r2, (r0)                  # t = array[0]
        st r3, (r1)                  # array[0] = array[1]
        ld (r0), r0                  # r0 = t
        st r0, 4(r1)                 # array[1] = t
        halt

.pos 0x1000
t:      .long 0xffffffff # -1
.pos 0x2000
array:  .long 0x00000001 # array[0] = 1
        .long 0x00000008 # array[1] = 8


