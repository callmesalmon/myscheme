(define (bool_to_str v)
    (if (boolean? v)
        (if (= v #t)
            "True"
            "False")
        "Null"))

(bool_to_str #t) ; "True"  (#t => "True")
(bool_to_str #f) ; "False" (#f => "False")
