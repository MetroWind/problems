#!/usr/bin/env gsi
;; For Gambit

(define (digits n base)
  ;; Returns a list of digits of integer `n' in base `base', from
  ;; small place to big.
  (if (< n base)
      (list n)
      (cons (modulo n base)
            (digits (floor (/ n base)) base))))

(define (power x n)
  ;; Return x^n, in which `n' is an positive integer.
  (if (= n 1)
      x
      (if (even? n)
          ;; `n' is even
          (let ((half-power (power x (/ n 2))))
            (* half-power half-power))
          ;; `n' is odd
          (let ((half-power (power x (/ (- n 1) 2))))
            (* half-power (* half-power x))))))

(define (reduce p seq initial)
  (if (eq? (cdr seq) (list))
      (p (car seq) initial)
      (p (car seq) (reduce p (cdr seq) initial))))

(define (sum seq)
  (reduce + seq 0))

(display "Sum of digits of 2^1000 is ")
(display (sum (digits (power 2 1000) 10)))
(display ".")
(newline)
