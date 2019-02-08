.pos 0x100
ld $a, r0 #r0 = &a
ld $b, r1 #r1 = &b
ld (r1), r2 #r2 = b
inc r2 # r2 = r2 + 1
inca r2 # r2 = r2 + 4
shr $1, r2 # r2 = r2 / 2
ld (r1), r1 # r1 = b
and r1, r2 #r2 = r1 & r2
shl $2, r2 #r2 = r2 << 2
st r2, (r0)
halt

.pos 0x1000
a: .long 0xffffffff # a = -1

.pos 0x2000
b: .long 0x00000012 # b = 18


