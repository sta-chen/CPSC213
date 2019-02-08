.pos 0x100
#   i = a[3]
ld $i, r0 # r0 = &i
ld $a, r1 # r1 = &a
ld 12(r1), r2 # r2 = a[3]
st r2, (r0) # i = a[3]

#   i = a[i]
ld (r0), r2 # r2 = i
ld (r1, r2, 4), r2 # r2 = a[i]
st r2, (r0) # i = a[i]

# p = &j
ld $j, r0 # r0 = &j
ld $p, r2 # r2 = &p
st r0, (r2) # p = &j

# *p = 4
ld $4, r3 # r3 = 4
st r3, (r0) # *p (i.e. m[&j]) = 4

# p = &a[a[2]]
ld 8(r1), r0 # r0 = a[2]
shl $2, r0 # r0 = 4 * a[2]
mov r1, r3 # r3 = r1
add r0, r3 # r3 = &a + 4 * a[2]
st r3, (r2) # p = &a[a[2]]

# *p = *p + a[4]

ld 16(r1), r0 # r0 = a[4]
ld (r2), r3 # r3 = p
ld (r3), r4 # r4 = *p
add r4, r0 # r0 = a[4] + *p
st r0, (r3) # *p = a[4] + *p

halt

.pos 0x2000
# initialization
i:  .long 0             # i
j:  .long 0             # j
p:  .long 0             # p
a:  .long 1             # a[0]
    .long 2             # a[1]
    .long 3             # a[2]
    .long 4             # a[3]
    .long 5             # a[4]
    .long 6             # a[5]
    .long 7             # a[6]
    .long 8             # a[7]
    .long 9             # a[8]
    .long 10            # a[9]

# test 1 i=5 j=4 a={1, 2, 3, 9, 5, 6, 7, 8, 9, 10}
