.name "Test Hero"
.comment "Please ignore"

init:
sti r1, %:staging, %2
sti r1, %:staging, %8
ld %, r16

staging:
ld %0, r1
live %0
fork %-12
#sti r2, r20, r2
#sti r2, r20, r2
#sti r3, r20, r2
#sti r4, r20, r2
#sti r5, r20, r2
#sti r6, r20, r2

#st r7, -16
#st r8, -15


loading:
ld %0, r2 				# 00 00 00 00
ld -22, r3 				# 02 90 xx xx
ld -23, r4 				# xx xx 01 01 
ld -24, r5				# xx xx xx xx
ld -25, r6				# 0c ff f4 ??

firing:
sti r2, r16, r2
sti r2, r16, r2
sti r3, r16, r2
sti r4, r16, r2
sti r5, r16, r2
sti r6, r16, r2
