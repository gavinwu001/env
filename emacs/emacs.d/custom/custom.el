(let ((default-directory "~/repos/env/emacs/emacs.d"))
  (normal-top-level-add-subdirs-to-load-path))

;; for key_mapping
(load "key_mapping.el")
;;  for plugin/global gtags
(load "gtags.el")

;; for google-c-style
(load "google-c-style.el")
;;(add-hook 'c-mode-common-hook 'google-set-c-style)
(add-hook 'c-mode-common-hook 'google-make-newline-indent)

(setq-default make-backup-files nil)
;;
(autoload 'gtags-mode "gtags" "" t)

;; set tab space
(setq-default indent-tabs-mode nil)

;;set auto offset 4
(setq default-tab-width 4)

;;(setq-default indent-tabs-mode nil)

(setq c-default-style "linux")

(setq c-basic-offset 4)

;; for desktop save, open the file , the cursor will appear where it closed before
;;(desktop-save-mode 1)

;;(let ((autosave-path "~/.emacs.d/auto-save-list")) (dolist (autosave-file (directory-files autosave-path nil "^#")) (rename-file (concat autosave-path "/" autosave-file) (concat "/tmp/" autosave-file))))

(setq auto-save-default nil)

;; show whitespace/tab
(setq whitespace-style
'(face indentation::tab indentation::space tabs tab-mark trailing))
(whitespace-mode 1)

(add-hook 'before-save-hook 'delete-trailing-whitespace)
(show-paren-mode 1)
(setq column-number-mode t)
