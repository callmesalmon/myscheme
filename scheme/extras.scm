; --- MyScheme file ---
; Extra functions and variables for the lazy.

; Kills the program if args < n
;
; Great for if you don't want
; all of these fucking segfaults...
(define (meet-arg-req n)
  (cond
    ((< argc n) (exit 11))))

; Due to some problems with lists and therefore problems
; with concat, these are provided instead.
(define (strcomb3 s1 s2 s3)
  (string-append (string-append s1 s2) s3))

(define (strcomb4 s1 s2 s3 s4)
  (string-append (strcomb3 s1 s2 s3) s4))

(define (strcomb5 s1 s2 s3 s4 s5)
  (string-append (strcomb4 s1 s2 s3 s4) s5))
; ^ just make your own after this

; Join strings, separated by a space
(define (strjoinspc s1 s2)
  (strcomb3 s1 " " s2))