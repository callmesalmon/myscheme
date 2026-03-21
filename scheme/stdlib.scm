; --- MyScheme file ---
; This is the standard library for MyScheme.

(define zero 0)

(define (zero? n)
    (if (= n 0) #t #f))

(define (even? n)
    (if (integer? n)
        (if (= (mod n 2) 0)
            #t
            #f)
        #f))

; My beloved!!!
(define rember
  (lambda (a lat)
    (cond
      ((null? lat) '())
      ((eq? (car lat) a) (cdr lat))
      (else (cons (car lat)
                  (rember a (cdr lat)))))))

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

(define (bool_to_str v)
    (if (boolean? v)
        (if (= v #t)
            "True"
            "False")
        "Null"))

(define (min a b)
    (if (< a b)
      a   ; A < B => A
      b)) ; A > B => B

; In this magical land, max is just -min!
(define (max a b)
    (if (= (min a b) b)
      a   ; MIN(A, B) == B? A
      b)) ; MIN(A, B) == A? B

(define (facto n)
    (if (= n 1)
      1
      (* n (facto (- n 1)))))

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

(define (length lst)
  (if (null? lst)
      0
      (+ 1 (length (cdr lst)))))

; A more imperative way of
; using lists. A bit counterinuitive,
; but I like it! :3
(define (element-at lst index)
  (if (zero? index)
      (car lst)
      (element-at (cdr lst) (- index 1))))

(define null '())

(define true #t)
(define false #f)

; concatenate all elements
; (has to be strings) in ``lst``
(define (concat lst)
  (if (= (length lst) 0)
    ""
    ; i. e lst[0] + concat(cdr(list)) in
    ; a more imperative language
    (string-append (element-at lst 0)
      (concat (cdr lst)))))

(define (writeln obj)
  (write obj)
  (write "\n"))

(define (invert x)
  (- 0 x))

(define (square x) (* x x))
(define (cube x)(* x x x))
(define (inc x) (+ x 1))
(define (dec x) (- x 1))
(define (abs x) (if (> x 0) x (invert x)))

; Exponents!
(define (expt b n)
  (define (expt-iter b counter product)
    (if (= counter 0)
        product
        (expt-iter b
                   (- counter 1)
                   (* b product))))
  (expt-iter b n 1))

(define (gcd a b)
  (if (= b 0) a
    (gcd b (remainder a b))))

; The following square-root functions are made
; with "great inspiration" from:
;   https://jaredkrinke.github.io/learn-scheme/1-1-7-examplesquarer.html
(define (average x y)
  (/ (+ x y) 2))

(define (improve-accuracy guess x)
  (average guess (/ x guess)))

(define (good-enough? guess x)
  (< (abs (- (square guess) x)) 1))

; Do not attempt to guess the square root
; of any number that can't be square-root:ed...
; YOU HAVE BEEN WARNED
(define (sqrt x)
  (define (sqrt-iter guess x)
    (if (good-enough? guess x)
      guess
      (sqrt-iter (improve-accuracy guess x)
        x)))
  (abs (sqrt-iter 1 x)))

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

; In my opinion it's a bit nicer to have this as a variable
; rather than a function.
(define argc (__builtin_argc))

; help function,
; run in repl using
; ``(help)``.
(define (help)
    (writeln "MYSCHEME")
    (writeln "\tMyScheme is a Scheme interpreter I hacked")
    (writeln "\ttogether in a month. It's functional enough.")
    (writeln "USAGE")
    (writeln "\tmyscm <args>")
    (writeln "FLAGS")
    (writeln "\t-d: Enable debug mode.")
    (writeln "\t-v: Print version and exit.")
    (writeln "\t-n: Do NOT use stdlib.")
    (writeln "TODO")
    (writeln "\t- Add user input support.")
    (writeln "\t- Add macro support.")
    (writeln "\t- Add GUI support."))
