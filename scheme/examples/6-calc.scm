(load "../extras.scm") ; this means you gotta be in the scheme/examples
                       ; directory to run this script
(meet-arg-req 4)

(define op (get-arg 1))

(define n1 (string->number (get-arg 2)))
(define n2 (string->number (get-arg 3)))

(define (evaluate op n1 n2)
  (cond
    ((eq? op "add") (+ n1 n2))
    ((eq? op "sub") (- n1 n2))
    ((eq? op "mul") (* n1 n2))
    ((eq? op "div") (/ n1 n2))
    (else "**Invalid operator name**")))

(writeln "Result: ")
(writeln (evaluate op n1 n2))