
(cl:in-package :asdf)

(defsystem "mars-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils :std_msgs-msg
)
  :components ((:file "_package")
    (:file "IRStamped" :depends-on ("_package_IRStamped"))
    (:file "_package_IRStamped" :depends-on ("_package"))
  ))