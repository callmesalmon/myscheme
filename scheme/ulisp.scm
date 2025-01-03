; This example was heavily inspired by Paul Graham blog 
; (http://paulgraham.com/lisp.html)
; 
; Minimal lisp can be implemented in scheme using only:
; `atom`, `car`, `cdr`, `cond`, `cons`, `eq` and `quote`

; Core functions:

(define (_null x) (eq? x '()))

(define atom?
 (lambda (x)
    (and (not (pair? x)) (not (null? x)))))

(define (_and x y)
  (cond (x (cond (y #t) (#t #f)))
        (#t #f)))

(define (_not x)
  (cond (x '#f)
        ('#t '#t)))

(define (_append x y)
  (cond ((_null x) y)
        (#t (cons (car x) (_append (cdr x) y)))))

(define (_list x y)
  (cons x (cons y '())))

(define (_pair x y)
  (cond ((_and (_null x) (_null y)) '())
        ((_and (_not (atom? x)) (_not (atom? y)))
         (cons (_list (car x) (car y))
               (_pair (cdr x) (cdr y))))))

(define (caar x)   (car (car x)))
(define (cadr x)   (car (cdr x)))
(define (cadar x)  (car (cdr (car x))))
(define (caddr x)  (car (cdr (cdr x))))
(define (caddar x) (car (cdr (cdr (car x)))))

(define (_assoc x y)
  (cond ((equal? (caar y) x) (cadar y))
        (#t (_assoc x (cdr y)))))

; Having `_eval` implemented, we can evaluate any S-expression

(define (_eval e a)
  (cond
    ((atom? e) (_assoc e a))
    ((atom? (car e))
     (cond
       ((equal? (car e) 'quote) (cadr e))
       ((equal? (car e) 'atom)  (atom?  (_eval (cadr e) a)))
       ((equal? (car e) 'eq)    (equal?    (_eval (cadr e)  a)
                                           (_eval (caddr e) a)))
       ((equal? (car e) 'car)   (car    (_eval (cadr e) a)))
       ((equal? (car e) 'cdr)   (cdr    (_eval (cadr e) a)))
       ((equal? (car e) 'cons)  (cons   (_eval (cadr e) a)
                                     (_eval (caddr e) a)))
       ((equal? (car e) 'cond)  (_evcon (cdr e) a))
       (#t (_eval (cons (_assoc (car e) a)
                        (cdr e))
                  a))))
    ((equal? (caar e) 'lambda)
     (_eval (caddar e)
            (_append (_pair (cadar e) (_evlis (cdr e) a))
                     a)))))

(define (_evcon c a)
  (cond ( (equal? (_eval (caar c) a) '()) (_evcon (cdr c)   a))
        ('t                               (_eval  (cadar c) a))))

(define (_evlis m a)
  (cond ((_null m) '())
        ('t (cons (_eval  (car m) a)
                  (_evlis (cdr m) a)))))

; Let's try something out.
; First, we should define a variable for keeping
; bindings as we will need it for lambdas.
(define env '())

; Now, core functions *should* work.
(_eval ''some-symbol env)
(_eval '(car '(a b c)) env)
(_eval '(cdr '(a b c)) env)
(_eval '(cons 'a '(b c)) env)

; Booleans kinda work, though
; true is `t` and false is `()`.
(_eval '(cond ('() 'false) ('t 'true) ) env)

; You may now use lambdas!
(_eval '((lambda (x) (cons 'a x)) '(b c)) env)

; We bootstrapped the language,
; hence MyScheme is Turing-complete!
