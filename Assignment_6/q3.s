.pos 0x100
#compute the average grade
average:
ld $n, r0       # r0 = &n
ld (r0), r0     # r0 = n
ld $s, r1       # r1 = &s
ld (r1), r1     # r1 = s
ld $24, r2      # r2 = sizeof(struct Student)

compute_loop:
beq r0, sort    # if n == 0 goto sort
ld 4(r1), r3    # r3 = s->grade[0] = sum of the grade
ld 8(r1), r4    # r4 = s->grade[1]
add r4, r3      # r3 = s->grade[0] + s->grade[1]
ld 12(r1), r4   # r4 = s->grade[2]
add r4, r3      # r3 = s->grade[0] + s->grade[1] + s->grade[2]
ld 16(r1), r4   # r4 = s->grade[3]
add r4, r3      # r3 = s->grade[0] + s->grade[1] + s->grade[2] + s->grade[3]
shr $2, r3      # r3 = sum_of_four_grades / 4
st r3, 20(r1)   # s->average = sum_of_four_grades / 4
add r2, r1      # *s++
dec r0          # n--
br compute_loop # goto compute_loop

#sort (bubble sort)
sort:
ld $n, r0       # r0 = &n
ld (r0), r0     # r0 = n
ld $s, r1       # r1 = &s
ld (r1), r1     # r1 = s

dec r0          # n--

outer_loop:
beq r0, median  # if n == 0 goto median
ld $1, r2       # r2 = 1 = j

inner_loop:
mov r0, r3      # r3 = n
not r3          # r3 = !n
inc r3          # r3 = -n
add r2, r3      # r3 = j - n
bgt r3, next_outer_loop     # if j > n goto next_outer_loop

# compare (if statement)
mov r2, r4      # r4 = j
mov r2, r5      # r5 = j
shl $4, r4      # r4 = 16j
shl $3, r5      # r5 = 8j
add r5, r4      # r4 = 24j
add r1, r4      # r4 = &s[j]
mov r4, r5      # r5 = &s[j]
ld $-24, r6     # r6 = -24 = - sizeof(struct Student)
add r6, r4      # r4 = &s[j - 1]
ld 20(r4), r6   # r6 = s[j - 1].average
ld 20(r5), r7   # r7 = s[j].average
not r6          # r6 = !s[j - 1].average
inc r6          # r6 = -s[j - 1].average
add r7, r6      # r6 = s[j].average - s[j - 1].average
bgt r6, next_inner_loop     # if s[j].average > s[j - 1].average goto next_inner_loop
beq r6, next_inner_loop     # if s[j].average == s[j - 1].average goto next_inner_loop

#swap if s[j].average < s[j - 1].average
ld $6, r3       # r3 = 6 = sizeof(struct Student) / 4 = k
swap_loop:  # swap every element in the struct
            # *a = &s[j - 1]
            # *b = &s[j]
beq r3, next_inner_loop     # if k == 0 goto next_inner_loop
ld (r4), r6     # r6 = *a
ld (r5), r7     # r7 = *b
st r7, (r4)     # *a = *b
st r6, (r5)     # *b = *a
inca r4         # a++
inca r5         # b++
dec r3          # k--
br swap_loop    # goto swap_loop

next_inner_loop:
inc r2          # j++
br inner_loop   # goto inner_loop

next_outer_loop:
dec r0          # n--
br outer_loop   # goto outer_loop

median:
ld $n, r0       # r0 = &n
ld (r0), r0     # r0 = n
shr $1, r0      # r0 = n / 2
mov r0, r1      # r1 = n / 2
shl $4, r0      # r0 = 16(n / 2)
shl $3, r1      # r1 = 8(n / 2)
add r1, r0      # r0 = 24(n / 2)
ld $s, r1       # r1 = &s
ld (r1), r1     # r1 = s
add r1, r0      # r0 = &s[n / 2]
ld (r0), r0     # r0 = s[n / 2].studentid
ld $m, r1       # r1 = &m
st r0, (r1)     # m  = s[n / 2].studentid
halt




.pos 0x2000
n:      .long 3         # just one student
m:      .long 0         # put the answer here
s:      .long base      # address of the array
base:   .long 1234      # student ID
        .long 80        # grade 0
        .long 60        # grade 1
        .long 78        # grade 2
        .long 90        # grade 3
        .long 0         # computed average

.long 2222      # student ID
.long 90
.long 90
.long 90
.long 90
.long 0

.long 3333
.long 100
.long 100
.long 100
.long 100
.long 0

