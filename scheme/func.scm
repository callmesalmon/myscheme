(define (even? n)
    (if (integer? n)  
        (if (= (mod n 2) 0)
            #t
            #f)
        #f))

(even? 4) ; #t
(even? 9) ; #f
