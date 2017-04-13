.name "Wall Razors"
.comment "Be careful of the corners, I hear they're 90 Degrees."


st r1, 6
init:
	live %1
	fork %:wallinit
	st r1, 6
	live %1
	fork %:init
	st r1, 6
	live %1
	fork %:evens

odds:
	st r1, 6
	live %1
	fork %:ohigh
	
	olow:
		st r1, 6
		live %1
		fork %:three
		
		one:
			ld %0, r1
			ld %-60, r2
			and %0, %0, r3
			zjmp %:launch
		
		three:
			ld %720, r1
			ld %-52, r2
			and %0, %0, r3
			zjmp %:launch

	ohigh:
		st r1, 6
		live %1
		fork %:seven
		
		five:
			ld %69, r4
			ld %-44, r2
			and %0, %0, r3
			zjmp %:launch
		
		seven:
			ld %101318606, r1
			ld %-36, r2
			and %0, %0, r3
			zjmp %:launch

evens:
	st r1, 6
	live %1
	fork %:ehigh
	
	elow:
		st r1, 6
		live %1
		fork %:four
	
		two:
			ld %0, r1
			ld %-56, r2
			and %0, %0, r3
			zjmp %:launch

		four:
			ld %393473, r1
			ld %-48, r2
			and %0, %0, r3
			zjmp %:launch

	ehigh:
		st r1, 6
		live %1
		fork %:eight
		
		six:
			ld %190054658, r1
			ld %-40, r2
			and %0, %0, r3
			zjmp %:launch
		
		eight:
			ld %0, r1
			ld %-32, r2
			and %0, %0, r3
			zjmp %:launch

launch:
	sti r1, r2, %:init
	zjmp %-388

wallinit:
	st r1, 6
	live %1
	fork %:negwall
	st r1, 6
	live %1
	fork %:poswall
	st r1, 6
	live %1
	fork %:init
	and %0, %0, r5
	zjmp %:wallinit

negwall:
	ld %3, r2
	ld %200, r3
	st r1, 6
	live %1
	and %0, %0, r5
	fork %:negwall
	zjmp %:bothwall

poswall:
	ld %4, r2
	ld %100, r3
	st r1, 6
	live %1
	and %0, %0, r5
	fork %:poswall
	zjmp %:bothwall

bothwall:
	st r1, 6
	live %1
	ld %589824, r4
	sti r4, r3, %0
	add r2, r3, r3
	and %0, %0, r5
	zjmp %:bothwall

