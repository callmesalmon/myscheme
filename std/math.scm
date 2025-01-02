(define zero 0)

(define (zero? n)
    (if (= n 0) #t #f))



(define (even? n)
    (if (integer? n)  
        (if (= (mod n 2) 0)
            #t
            #f)
        #f))
