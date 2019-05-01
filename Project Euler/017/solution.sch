(define (lookup n)
  ;; Find the spell for `n' in `fundamental-numbers'
  (define fundamental-numbers
    (list (cons 0 "zero")
          (cons 1 "one")
          (cons 2 "two")
          (cons 3 "three")
          (cons 4 "four")
          (cons 5 "five")
          (cons 6 "six")
          (cons 7 "seven")
          (cons 8 "eight")
          (cons 9 "nine")
          (cons 10 "ten")
          (cons 11 "eleven")
          (cons 12 "twelve")
          (cons 13 "thirteen")
          (cons 14 "fourteen")
          (cons 15 "fifteen")
          (cons 16 "sixteen")
          (cons 17 "seventeen")
          (cons 18 "eighteen")
          (cons 19 "nineteen")
          (cons 20 "twenty")
          (cons 30 "thirty")
          (cons 40 "forty")
          (cons 50 "fifty")
          (cons 60 "sixty")
          (cons 70 "seventy")
          (cons 80 "eighty")
          (cons 90 "ninety")))

  (define (lookup-iter n list-of-pairs)
    ;; Find the spell for `n' in `list-of-pairs'
    (if (eq? list-of-pairs (list))
        #f
        (let ((current-pair (car list-of-pairs)))
          (if (= n (car current-pair))
              (cdr current-pair)
              (lookup-iter n (cdr list-of-pairs))))))
  (lookup-iter n fundamental-numbers))

(define (power x n)
  ;; Return x^n, in which `n' is an positive integer.
  (cond ((= n 0) 1)
        ((= n 1) x)
        ((even? n)
         (let ((half-power (power x (/ n 2))))
           (* half-power half-power)))
        (else                           ; `n' is odd
         (let ((half-power (power x (/ (- n 1) 2))))
           (* half-power (* half-power x))))))

(define (digit m nth)
  ;; Returns the `nth' least significant decimal digit of `m'.
  (modulo (floor (/ m (power 10 (- nth 1)))) 10))

;; (define (spell n)
;;   (if (or (< n 0) (>= n 10000))
;;       "Not implemented..."
;;       (cond
;;        ((<= n 20) (lookup n))
;;        ((and (>= n 21) (< n 100))
;;         (if (= (modulo n 10) 0)
;;             (lookup n)
;;             (string-append (lookup (* (digit n 2) 10))
;;                            " "
;;                            (lookup (digit n 1)))))
;;        ((and (>= n 100) (< n 1000))
;;         (if (= (modulo n 100) 0)
;;             (string-append (lookup (digit n 3))
;;                            " hundred")
;;             (string-append (lookup (digit n 3))
;;                            " hundred and "
;;                            (spell (modulo n 100)))))
;;        ((>= n 1000)
;;         (if (= (modulo n 1000) 0)
;;             (string-append (lookup (digit n 4))
;;                            " thousand")
;;             (string-append (lookup (digit n 4))
;;                            " thousand "
;;                            (spell (modulo n 1000))))))))
                           
(define (spell n)
  (if (or (< n 0) (>= n 10000))
      "Not implemented..."
      (cond
       ((<= n 20) (lookup n))
       ((and (>= n 21) (< n 100))
        (if (= (modulo n 10) 0)
            (lookup n)
            (string-append (lookup (* (digit n 2) 10))
                           (lookup (digit n 1)))))
       ((and (>= n 100) (< n 1000))
        (if (= (modulo n 100) 0)
            (string-append (lookup (digit n 3))
                           "hundred")
            (string-append (lookup (digit n 3))
                           "hundredand"
                           (spell (modulo n 100)))))
       ((>= n 1000)
        (if (= (modulo n 1000) 0)
            (string-append (lookup (digit n 4))
                           "thousand")
            (string-append (lookup (digit n 4))
                           "thousand"
                           (spell (modulo n 1000))))))))

(define (reduce p seq initial)
  (if (eq? (cdr seq) (list))
      (p (car seq) initial)
      (p (car seq) (reduce p (cdr seq) initial))))

(define (sum seq)
  (reduce + seq 0))

(define (range start end)
  (if (= start (- end 1))
      (list start)
      (cons start (range (+ start 1) end))))

;; (map (lambda (n) (display (spell n)) (display "\n")) (range 1 1001))
(display (sum (map (lambda (n)
            (string-length (spell n)))
          (range 1 1001))))
(newline)
