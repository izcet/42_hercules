.name "Mind Blocker"
.comment "I came out of the core because you need to stop."


st r1, 6
init:
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
			ld %0, r1
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
			ld %150994945, r1
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
	zjmp %-375
