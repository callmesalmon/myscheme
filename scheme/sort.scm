(define (merge-lists l1 l2)
  (cond [(null? l1) l2]
        [(null? l2) l1]
        [(< (car l1) (car l2))
         (cons (car l1) (merge-lists (cdr l1) l2))]
        [else
         (cons (car l2) (merge-lists (cdr l2) l1))]))

(define (even-numbers l)
  (cond [(null? l) '()]
        [(null? (cdr l)) '()]
        [else
         (cons (car (cdr l)) (even-numbers (cdr (cdr l))))]))

(define (odd-numbers l)
  (cond [(null? l) '()]
        [(null? (cdr l)) (list (car l))]
        [else
         (cons (car l) (odd-numbers (cdr (cdr l))))]))

(define (merge-sort l)
  (cond [(null? l) l]
        [(null? (cdr l)) l]
        [else
         (merge-lists
          (merge-sort (odd-numbers l))
          (merge-sort (even-numbers l)))]))
