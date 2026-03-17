(define var "Hello World!")
(writeln var)

(define (func)
  (writeln "Hello, World!"))

(define (func2 param)
  (write "Hello, ")
  (write param)
  (write (newline)))

(func)
(func2 "Scheme enjoyer")