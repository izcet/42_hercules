.name "Brutadon"
.comment "I got this!"

enter:
sti r1, %:liveloop, %1
sti r1, %:init, %1
sti r1, %:inject, %1
ld %65793, r2
ld %2, r3
ld %-100, r4
ld %-20, r5

inject:
live %4
sti r3, r4, %0
sti r2, r4, %1
sti r1, r4, %-8
sti r1, r4, %-8
add r4, r5, r4
init:
live %4 
fork %:inject
fork %:init
fork %:init
fork %:init
fork %:init

liveloop:
live %4
zjmp %:liveloop
fork %:inject

zjmp %4000 
end:
