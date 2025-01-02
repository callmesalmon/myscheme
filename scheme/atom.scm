(define (zero? n)
    (if (= n 0) #t #f))

(define atom?
 (lambda (x)
    (and (not (pair? x)) (not (null? x)))))

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

(atom? (car '(Harry had a heap of apples)))         ; true
(atom? (cdr '(Harry had a heap of apples)))         ; false
(atom? (cdr '(Harry)))                              ; false
(atom? (car (cdr '(swing low sweet cherry oat))))   ; true
(atom? (car (cdr '(swing (low sweet) cherry oat)))) ; false
