(define zero 0)

; Basic function,
; is item zero? e.g:
; (zero? 1)        ; #f
; (zero? 0)        ; #t
; (zero? "Hello!") ; #f
(define (zero? n)
    (if (= n 0) #t #f))

; Is number even?
; (even 5) ; #f
; (even 6) ; #t
(define (even? n)
    (if (integer? n)  
        (if (= (mod n 2) 0)
            #t
            #f)
        #f))

; Remove the first occurence
; of "a" in a list, e.g:
; (rember 'Hello '(As \
; I entered Hello, I blurted \
; out a Hello.)) == As I entered,
; I blurted out a Hello.
(define rember
  (lambda (a lat)
    (cond
      ((null? lat) '())
      ((eq? (car lat) a) (cdr lat))
      (else (cons (car lat)
                  (rember a (cdr lat)))))))

; Code to check if something
; is an atom, e.g not pair
; and not null either.
(define atom?
 (lambda (x)
    (and (not (pair? x)) (not (null? x)))))

; LAT - List of AToms
(define lat?
  (lambda (l)
    (cond
      ((null? l) #t)
      ((atom? (car l)) (lat? (cdr l)))
      (else #f))))

(define addtup
  (lambda (tup)
    (cond
      ((null? tup) 0)
      (else (o+ (car tup) (addtup (cdr tup)))))))

; Useful for doing print
; operations on booleans,
; e.g this:
; (define bool1 (zero? 0))
; (define bool2 (zero? 1))
; (write (bool_to_str bool1)) ; "True"
; (write (bool_to_str bool2)) ; "False"
(define (bool_to_str v)
    (if (boolean? v) ; Type(V) = bool? ... else "Null"
        (if (= v #t) ; V = #t? "True" else "False"
            "True"
            "False")
        "Null"))

(define (min a b)
    (if (< a b)
      a  ; A < B => A
      b)) ; A > B => B

; Do a reverse implementation,
; since min is just !max we can
; flip over min to be max, E.G:
; max(a, b) = !min(a, b)
(define (max a b)
    (if (= (min a b) b)
      a  ; MIN(A, B) == B? A
      b)) ; MIN(A, B) == A? B

; Here, we do a classic factorial
; implementation. Since ex. 5! ==
; 5 * 4!, we can recurse trough.
(define (facto n)
    (if (= n 1) ; We don't wanna recurse forever.
      1
      n * (facto n - 1)))
