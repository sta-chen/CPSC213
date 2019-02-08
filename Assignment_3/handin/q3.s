.pos 0x100
ld $3, r0 # a_t = r0 = 3
ld $a, r1 # r1 = &a
st r0, (r1) # a = 3
ld $p, r2 # r2 = &p (a ptr)
st r1, (r2) # p = &a
ld (r2), r3 # r3 = p
ld (r3), r4 # r4 = *p
mov r4, r0 # r0 = *p
dec r0 # r0 = *p - 1
st r0, (r3) # *p = *p - 1

ld $b, r0 # r0 = &b
st r0, (r2) # p = &b
ld (r2), r3 # r3 = p
mov r3, r4 # r4 = r3
inca r4 # r4 = p + 4
st r4, (r2) # p = p + 4
ld (r1), r1 # r1 = a
ld (r2), r3 # r2 = p
mov r1, r4 # r4 = r1
shl $2, r4 # a = 4 * a
add r4, r3 # p = p + a
ld (r0, r1, 4), r5 # r5 = b[a]
st r5, (r3) # p[a] = b[a]

ld (r0), r4 # r4 = b[0]
ld (r2), r1 # r1 = p[0]
st r4, 12(r1) # p[3] = b[0]


halt

.pos 0x2000
# initialization
a:  .long 0
p:  .long 0
b:  .long 1
    .long 2
    .long 3
    .long 4
    .long 5


# test 1 b[0]=1, b[1]=2, b[2]=3, b[3]=4, b[4]=5,
# a=2 *p=2
# b[0]=1, b[1]=2, b[2]=3, b[3]=3, b[4]=1,
