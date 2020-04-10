;; for plugin/global gtags
(global-set-key (kbd "M-,") 'gtags-find-tag)
(global-set-key (kbd "M-.") 'gtags-find-rtag)

(global-set-key (kbd "C-t") 'gtags-pop-stack)
(global-set-key (kbd "C-f") 'find-file-other-window)

;(global-set-key (kbd "M-g M-f") 'gtags-find-file)
;(global-set-key (kbd "M-g M-s") 'gtags-find-symbeol)
;(global-set-key (kbd "M-g M-u") 'gtags-update)

;(global-set-key (kbd "C-M-g") 'goto-line)
(define-key global-map "\C-c\C-g" 'goto-line)
(define-key global-map "\C-x\C-x" 'other-window)


(define-prefix-command 'window-sense-map)
(global-set-key (kbd "C-q") 'window-sense-map)
(define-key window-sense-map (kbd "C-f") 'find-file-other-window)
(define-key window-sense-map (kbd "C-c") 'delete-window)
