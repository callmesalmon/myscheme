; While you can write
; your own type casting
; functions, the builtins
; offer a variety out of
; the box!!!

; int => str
(writeln (number->string 999)) ; "999"

; str => int
(define var_str (string->number "999")) ; var_str = (str->num "999") = 999, e.g var_str = 999
(writeln (number->string var_str))

; sym => str
(writeln (symbol->string sym)) ; "unbound variable"

; str => sym
(define var_sym (string->symbol "sym")) ; var_sym = (str->sym "sym") = sym, e.g var_sym = sym
(writeln (symbol->string var_sym))           ; "sym" (it's weird ik)