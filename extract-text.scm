#! /usr/bin/guile \
--no-auto-compile -s
!#

;; Copyright (C) 2012 Barry Schwartz
;; 
;; This program is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 3 of the License, or
;; (at your option) any later version.
;; 
;; This program is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.
;; 
;; You should have received a copy of the GNU General Public License
;; along with this program; if not, see <http://www.gnu.org/licenses/>.

(use-modules
 (ice-9 getopt-long)
 (ice-9 rdelim)
 (ice-9 regex)
 (ice-9 local-eval)
 )

(define (extract-from-line re substitute s)
  (let* ((matches (regexp-exec re s))
         (env (let ((: (lambda (n) (match:substring matches n))))
                (the-environment))))
    (if matches
        ;; Evaluate 'substitute' with '(: 0)', '(: 1)', ...,
        ;; representing regexp sub-matches.
        (with-input-from-string substitute
          (lambda () (local-eval (read) env)))
        '())
    )
  )

(define (extract-text re substitute)
  (let ((s (read-line)))
    (if (eof-object? s)
        '()
        (let ((subst (extract-from-line re substitute s)))
          (cond ((string? subst) (write-line subst)))
          (extract-text re substitute)))
    )
  )

(define (extract-text-from-file re substitute file)
  (with-input-from-file file (lambda () (extract-text re substitute))))

(define (extract-text-from-files re substitute files)
  (let ((extract-from-file (lambda (f)
                             (extract-text-from-file re substitute f))))
    (for-each extract-from-file files)))

(define (main args)
  (let* ((option-spec '((expression (single-char #\e) (value #t))
                        (substitute (single-char #\s) (value #t))))
         (options (getopt-long args option-spec))

         ;; These defaults copy text lines from input to output.
         (expression (option-ref options 'expression ".*"))
         (substitute (option-ref options 'substitute "(: 0)"))

         (files (option-ref options '() #f))

         (re (make-regexp expression)))
    (cond ((= (length files) 0) (extract-text re substitute))
          (else (extract-text-from-files re substitute files)))
    )
  )

(main (command-line))
