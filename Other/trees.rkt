#lang racket

(struct bst-node (value left right count) #:mutable #:transparent)

(define n1 (bst-node 5 empty empty 1))
(define n2 (bst-node 10 empty empty 1))
(define n3 (bst-node 15 empty empty 1))

;extra node definitions for n2 for testing functions
(define n4 (bst-node 7 empty empty 1))
(define n5 (bst-node 20 empty empty 1))
(define n6 (bst-node 1 empty empty 1))
(define n7 (bst-node 14 empty empty 1))

(set-bst-node-left! n2 n1)
(set-bst-node-right! n2 n3)

;adding extra nodes to n2 as in BST for testing fuctions
(set-bst-node-right! n1 n4)
(set-bst-node-left! n1 n6)
(set-bst-node-right! n3 n5)
(set-bst-node-left! n3 n7)

;VISUAL TREE ON HOW N2 LOOKS LIKE

;              10
;             /  \
;            5    15
;           / \   / \
;          1   7 14 20


(define (add-value-to-bst tree v)
  (add-value-to-bst-subtree tree tree v))


(define (add-value-to-bst-subtree tree subtree v)
  (cond
    ((and (< v (bst-node-value tree))(null? (bst-node-left tree)))
     (set-bst-node-left! subtree (bst-node v empty empty 1)))   

     
    ((and (< v (bst-node-value tree))(not (null? (bst-node-left tree))))
     (add-value-to-bst (bst-node-left subtree) v))

     
    ((and (> v (bst-node-value tree))(null? (bst-node-right tree)))
     (set-bst-node-right! subtree (bst-node v empty empty 1)))  

     
    ((and (> v (bst-node-value tree))(not (null? (bst-node-right tree))))
     (add-value-to-bst (bst-node-right subtree) v))

    (else (set-bst-node-count! subtree (+ (bst-node-count subtree) 1))
     
    )))

(define (traverse n)
  (cond
    ;If   n   is empty, value is the empty list
    ((null? n) '())
    ;If   left and right of n are both empty, value is value of n as a list
    ((and (null? (bst-node-left n))(null? (bst-node-right n))
          (list(bst-node-value n))))
    ;If only left field is empty, value is value of n cons’ed to recursive call to right
    ((and (null? (bst-node-left n))(not (null? (bst-node-right n)))
          (cons (bst-node-value n)(traverse (bst-node-right n)))))
    ;If only right field is empty, value is value of n cons’ed to recursive call to left
    ((and (not (null? (bst-node-left n)))(null? (bst-node-right n))
          (cons (traverse (bst-node-right n))(bst-node-value n))))
    ;If neither is empty, value is recursive call to left, appended to value of n as list, appended to recursive call to right
    (else (append (traverse(bst-node-left n))(list(bst-node-value n))(traverse(bst-node-right n))))
    ))


(define (get-random-in-range rng)
  (inexact->exact (remainder (floor (* (random) (expt 2 31))) rng))  )

;ADDED AN EXTRA PARAMETER OF 'l' WHICH EXPECTS AN EMPTY LIST THAT WILL GET FILLED OUT ONCE THE FUNCTION ENDS
(define (get-random-list-in-range rng count l)
  (cond
    ((= count 0) l)
    (else (get-random-list-in-range rng (- count 1) (append l (list(get-random-in-range rng)))))
   ))

(define (contains? x n)
  (cond
    ((empty? x) #f)
    ((= (car x) n) #t)
    (else (contains? (cdr x) n))
    ))

(define (contains-duplicates? x)
  (cond
    ((or (empty? x)(= (length x) 1)) #f)
    ((contains? (cdr x)(car x)) #t) 
    (else (contains-duplicates? (cdr x)))
  ))

(define (add-random-to-list-unique x rng)
  (add-random-to-list-unique-1 x (cons (get-random-in-range rng) x) rng))

(define (add-random-to-list-unique-1 x y rng)
  (cond
    ((not (contains-duplicates? y)) y)
    (else (add-random-to-list-unique-1 x (cons (get-random-in-range rng) (cdr y)) rng))
  ))

(define (get-random-list-in-range-unique rng count)
  (cond
     ((= count 1) (add-random-to-list-unique empty rng))
     (else (append (add-random-to-list-unique (get-random-list-in-range-unique rng (- count 1)) rng)))
  ))

(define (is-sorted? x)
  (cond
    ((or (empty? x)(= (length x) 1)) #t)
    (else (and (< (car x)(car (cdr x)))(is-sorted? (cdr x))))
    ))

(define (find-path v n)
  (find-path-1 v n empty))

(define (find-path-1 v n p)
  (cond
    ((empty? n) p)
    ((= v (bst-node-value n))(cons n p))
    ;cons n onto value of recursive call with n   replaced by left of n
    ((< v (bst-node-value n))(cons n (find-path v (bst-node-left n))))
    ;cons n onto value of recursive call with n   replaced by right of n 
    ;((> v (bst-node-value n))(cons (find-path v (bst-node-right n))(p)))
    ((> v (bst-node-value n))(cons n (find-path v (bst-node-right n))))
  ))

;Useful example to call the function below: (get-path-values (find-path 5 n2))
(define (get-path-values p)
  (cond
    ((null? p) empty)
    (else (cons (bst-node-value (car p)) (get-path-values (cdr p))))
   ))

(define (get-child-count n)
  (cond
    ((and (empty? (bst-node-left n))(empty? (bst-node-right n))) 0)
    ((and (not (empty? (bst-node-left n)))(empty? (bst-node-right n))) 1)
    ((and (empty? (bst-node-left n))(not (empty? (bst-node-right n)))) 1)
    (else 2) 
  )) 


(define (find-inorder-prev n)
  (cond
    ((null? (bst-node-right (bst-node-left n))) (list (bst-node-left n) n))
    (else (find-path-inorder-prev (bst-node-right (bst-node-left n)) (list(bst-node-left n) n)))
    ))


(define (find-path-inorder-prev n p)
  (if (empty? (bst-node-right n)) (cons n p) (find-path-inorder-prev (bst-node-right n) (append p (list n)) ))
  )
