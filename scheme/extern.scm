; Oh and btw, you can load extern libraries,
; let's try one! "scheme/std.scm", the stdlib
; (even though it's preinstalled).
(load "scheme/std.scm")

; Now, we can run an external function
; like ``writeln``!
(writeln "Hello World!")

; Or maybe ``zero?``?
(writeln (bool_to_str (zero? 0)))
(writeln (bool_to_str (zero? 1)))

; Or possibly even ``even``! See
; what I did there? Clever, right?
(writeln (bool_to_str (even? 777)))
(writeln (bool_to_str (even? 778)))