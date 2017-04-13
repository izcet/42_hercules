	    .name "Master_Shredder"
	    .comment "You speak my name, but you do not know me. I am Ch'rell, Oroku Saki, Duke Acureds, the one TRUE Shredder! I am a destroyer of worlds, and I fear no one!"

	st  r1, 6
	live %1
	ld %589824, r10
	ld %655260, r11
	st r10, -32
	st r11, -33
	sti r1, %:forks, %1
    sti r1, %:shield, %1
    and r2, %0, r2
    fork %:shield
	fork %:second

	first:
	    live %1
	    fork %:third
	    ld %150994945 ,r1
	    ld %0, r2
	    ld %-56, r4
	    ld %00, r3
	    zjmp %:forks

	second:
	    live %2
	    fork %:fourth
	    ld -17, r7
	    ld %4, r2
	    ld %-52, r4
	    ld %00, r3
	    zjmp %:forks

	third:
	    ld %190054660, r1
	    ld %8, r2
	    ld %-48, r4
	    ld %00, r3
	    zjmp %:forks

	fourth:
	    ld %50986950, r1
	    ld %12, r2
	    ld %-44, r4
	    ld %00, r3
	    zjmp %:forks

forks:
	live %5
    and r7, %0, r7
	sti r1, r2, %:fourth
	fork %:forks
    zjmp %-50

shield:
    live %6
    st r10, 100
    st r10, 100
    st r10, 100
    st r10, 100
    st r10, 100
    st r10, 100
    st r10, 100
    st r10, 100
    st r10, 100
    st r10, 100
    st r10, 100
	st r10, 100
	st r10, 100
	st r10, 100
	st r10, 100
    st r10, 100
	st r10, 100
	st r10, 100
	st r10, 100
    zjmp %:shield
