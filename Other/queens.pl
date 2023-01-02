:- use_module(library(clpfd)).

start(X) :-
	permutation([0,1,2,3,4,5,6,7],X).

nc(X,A,B) :- 
	nth0(A, X, AV),
	nth0(B, X, BV),
	D #= B - A,
	AV #\= BV + D,
	AV #\= BV - D.

pred1(_,A,B):-
	A #>= B.	%EXIT PREDICATE WHEN PRED1 IS DONE

pred1(L,A,B):-
	A #< B,
	nc(L,A,B),
	S is A + 1,
	pred1(L,S,B).

pred2(_,_,B):-
	B #>= 8.	%EXIT PREDICATE WHEN PRED2 IS DONE

pred2(L,A,B):-
	B #< 8,
	pred1(L,A,B),
	S is B + 1,
	pred2(L,A,S).
	

nc_all(X):-
	pred2(X,0,1).	%WE INSTANTIATE PRED2 WITH COLS 0 AND 1 TO START
	
