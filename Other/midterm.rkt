#lang racket

;PROBLEM 1

(define (count a b)
  (cond
    ((= a b) displayln b)
    (else (and(displayln a)(count (+ a 1) b)))
    ))

;PROBLEM 2

(define (replace-list x a b)
  (cond
    ((empty? x) x)
    ((equal? a (car x))(cons b (cdr x)))
    (else (cons (car x)(replace-list (cdr x) a b)))
    ))

;PROBLEM 3

(define (min-value-h x v)
  (cond
    ((empty? x) v)
    ((< (car x) v) (min-value-h (cdr x)(car x)))
    (else (min-value-h (cdr x) v))
    ))

;MAIN CALLING FUNCTION
(define (min-value x)
  (min-value-h (cdr x)(car x)))

;PROBLEM 4

(define (smaller-num n1 n2)
  (cond
    ((< n1 n2) n1)
    (else n2)
    ))

;MAIN CALLING FUNCTION
(define (list-min-values list1 list2)
  (map (lambda (number1 number2)
         (smaller-num number1 number2))
       list1
       list2
       ))
  