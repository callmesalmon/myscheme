(load "scheme/std.scm")

(define computer_on_fire #f)
(define scheme_is_running #t)

(write (bool_to_str (computer_on_fire)))  ; "True" ($computer_on_fire == bool)
(write (bool_to_Str (scheme_is_running))) ; "True" ($scheme_is_running == bool)
