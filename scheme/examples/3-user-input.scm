(define (greet name)
  (write "Hello, ")
  (write name)
  (write "!\n"))

(write "What's your name? ")
(define name (read)) ; A little interesting syntax but it works
(greet name)