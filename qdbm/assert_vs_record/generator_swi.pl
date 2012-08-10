:- dynamic(bla/1).

test1(NoFacts):-
	get_time(T0),
	gen1(1,NoFacts),
	get_time(T1),
	DT is T1-T0,
	nl,write('asserta: '),write(DT),nl,
	!.

gen1(X,NoFacts):-
	X =< NoFacts,
	asserta(bla(X)),
	bla(X),
	X1 is X+1,
	gen1(X1,NoFacts).
gen1(NoFacts,NoFacts).

%%%%%
test2(NoFacts):-
	get_time(T0),
	gen2(1,NoFacts),
	get_time(T1),
	DT is T1-T0,
	nl,write('recorda: '),write(DT),nl,
	!.

gen2(X,NoFacts):-
	X =< NoFacts,
	recorda(bla(X),bla(X),_),
	recorded(bla(X),_,_),
	X1 is X+1,
	gen2(X1,NoFacts).
gen2(NoFacts,NoFacts).

%%%%%
test3(NoFacts):-
	get_time(T0),
	gen3(1,NoFacts),
	get_time(T1),
	DT is T1-T0,
	nl,write('assertz: '),write(DT),nl,
	!.

gen3(X,NoFacts):-
	X =< NoFacts,
	assertz(bla(X)),
	bla(X),
	X1 is X+1,
	gen3(X1,NoFacts).
gen3(NoFacts,NoFacts).

%%%%%
test4(NoFacts):-
	get_time(T0),
	gen4(1,NoFacts),
	get_time(T1),
	DT is T1-T0,
	nl,write('recordz: '),write(DT),nl,
	!.

gen4(X,NoFacts):-
	X =< NoFacts,
	recordz(bla(X),bla(X),_),
	recorded(bla(X),_,_),
	X1 is X+1,
	gen4(X1,NoFacts).
gen4(NoFacts,NoFacts).

%%%%%%

