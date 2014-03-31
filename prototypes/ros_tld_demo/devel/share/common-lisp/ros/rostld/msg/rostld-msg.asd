
(cl:in-package :asdf)

(defsystem "rostld-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "Image" :depends-on ("_package_Image"))
    (:file "_package_Image" :depends-on ("_package"))
  ))