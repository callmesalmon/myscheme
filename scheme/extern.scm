; Oh and btw, you can load extern libraries,
; let's try one! "scheme/std.scm", the stdlib.
(load "scheme/std.scm")

; Now, we can run an external function
; like ``print``!
(print "Hello World!")

; Or maybe ``zero?``?
(print (bool_to_str (zero? 0)))
(print (bool_to_str (zero? 1)))

; Or possibly even ``even``! See
; what I did there? Clever, right?
(print (bool_to_str (even? 777)))
(print (bool_to_str (even? 778)))
