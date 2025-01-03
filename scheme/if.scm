; Why does this script exist?
; Well, it exits to be able to
; print boolean values. Include
; it in your project if you wish.

(define (bool_to_str v)
    (if (boolean? v)
        (if (= v #t)
            "True"
            "False")
        "Null"))

(write (bool_to_str #t)) ; "True"  (#t => "True")
(write (bool_to_str #f)) ; "False" (#f => "False")
