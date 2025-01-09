; --- MyScheme std.scm ---
; This is the standard library for MyScheme.
; Or, atleast it *can* be. You can include it
; in your project like any other thing in the
; scheme/ directory, yet this is special.
; If you want the best experience with
; MyScheme, please Copy-Paste the
; following into your project:
;     
;     (load "scheme/std.scm")

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
      a   ; MIN(A, B) == B? A
      b)) ; MIN(A, B) == A? B

; Here, we do a classic factorial
; implementation. Since ex. 5! ==
; 5 * 4!, we can recurse trough.
(define (facto n)
    (if (= n 1) ; We don't wanna recurse forever.
      1         ; 1! = 1
      n * (facto n - 1)))

(define (caar x) (car (car x))) 
(define (cadr x) (car (cdr x))) 
(define (cddr x) (cdr (cdr x))) 
(define (cdar x) (cdr (car x))) 

(define (caaar x) (car (car (car x)))) 
(define (caadr x) (car (car (cdr x)))) 
(define (cadar x) (car (cdr (car x)))) 
(define (caddr x) (car (cdr (cdr x)))) 
(define (cdaar x) (cdr (car (car x)))) 
(define (cdadr x) (cdr (car (cdr x)))) 
(define (cddar x) (cdr (cdr (car x)))) 
(define (cdddr x) (cdr (cdr (cdr x)))) 

(define (caaaar x) (car (car (car (car x))))) 
(define (caaadr x) (car (car (car (cdr x))))) 
(define (caadar x) (car (car (cdr (car x))))) 
(define (caaddr x) (car (car (cdr (cdr x))))) 
(define (cadaar x) (car (cdr (car (car x))))) 
(define (cadadr x) (car (cdr (car (cdr x))))) 
(define (caddar x) (car (cdr (cdr (car x))))) 
(define (cadddr x) (car (cdr (cdr (cdr x))))) 
(define (cdaaar x) (cdr (car (car (car x))))) 
(define (cdaadr x) (cdr (car (car (cdr x))))) 
(define (cdadar x) (cdr (car (cdr (car x))))) 
(define (cdaddr x) (cdr (car (cdr (cdr x))))) 
(define (cddaar x) (cdr (cdr (car (car x))))) 
(define (cddadr x) (cdr (cdr (car (cdr x))))) 
(define (cdddar x) (cdr (cdr (cdr (car x))))) 
(define (cddddr x) (cdr (cdr (cdr (cdr x))))) 

; null
(define null '())

; python-esque null
(define None '())

; bool
(define true #t)
(define false #f)

; python-esque bool
(define True  #t)
(define False #f)

; write
(define (newline) (write ""))
(define print write)
(define (println obj) (write obj)(newline))

; math
(define (square x) (* x x))
(define (cube x)(* x x x))
(define (inc x) (+ x 1))
(define (dec x) (- x 1))
(define (abs x) (if (> x 0) x (- x)))

(define (expt b n)
  (define (expt-iter b counter product)
    (if (= counter 0)
        product
        (expt-iter b
                   (- counter 1)
                   (* b product))))
  (expt-iter b n 1))
 
(define (gcd a b) (if (= b 0) a (gcd b (remainder a b))))
 
; list
(define (assoc x y)
  (cond ((null? y) '())
        ((eq? x (caar y)) (car y))
        ((assoc x (cdr y)))))

(define (assv x y)
  (cond ((null? y) '())
        ((eqv? x (caar y)) (car y))
        ((assv x (cdr y)))))

(define (assq x y)
  (cond ((null? y) '())
        ((eq? x (caar y)) (car y))
        ((assq x (cdr y)))))



(define subst
  (lambda (new old slist)
    (if (null? slist)
      '()
       (cons
	     (subst-in-s-exp new old (car slist)) 
	     (subst new old (cdr slist))))))

(define subst-in-s-exp
  (lambda (new old sexp)
    (cond ((symbol? sexp)
          (if (eqv? sexp old) new sexp))
          ((pair? sexp) (subst new old sexp))
          (else sexp))))

; help function
(define (help)
    (print "MYSCHEME"                                         )
    (print "    MyScheme is a Scheme interpreter I hacked"    )
    (print "    together in an afternoon. It's... Functional.")
    (print "USAGE"                                            )
    (print "    myscm <args>"                                 )
    (print "FLAGS"                                            )
    (print "    -d: Enable debug mode."                       )
    (print "    -v: Print version and exit."                  )
    (print "BUILD CONFIGURATION FLAGS"                        )
    (print "    --repl: Only use repl"                        )
    (print "    --exclude <opt>: Exclude <opt> from build."   )
    (print "    --clang: Compile with Clang"                  )
    (print "    --cflags <flags>: Compile with <flags>"       )
    (print "TODO"                                             )
    (print "    - Add macro support."                         )
    (print "    - Add user input support."                    )
    (print "    - Add GUI support."                           ))