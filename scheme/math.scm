(define (square x)
    x * x) ; 2x = (square x)

(define (even? n)
    (if (integer? n)  
        (if (= (mod n 2) 0) ; n % 2 = 0?
            #t
            #f)
        #f))

(define (min a b)
    (if (< a b)
      a  ; A < B => A
      b) ; A > B => B

; Do a reverse implementation,
; since min is just !max we can
; flip over min to be max.
(define (max a b)
    (if (= (min a b) b)
      a  ; MIN(A, B) == B? A
      b) ; MIN(A, B) == A? B

; Here, we do a classic factorial
; implementation. Since ex. 5! ==
; 4!, we can recurse trough.
(define (factorial n)
    (if (= n 1)
      1
      n * (factorial n - 1)))
