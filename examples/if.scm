(define (bool v)
    (if (boolean? v)
        (if (= v #t)
            "True"
            "False")))

(bool #t) ; "True"  (#t => "True")
(bool #f) ; "False" (#f => "False")
