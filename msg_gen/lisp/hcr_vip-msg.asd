
(cl:in-package :asdf)

(defsystem "hcr_vip-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "sonar_vip" :depends-on ("_package_sonar_vip"))
    (:file "_package_sonar_vip" :depends-on ("_package"))
  ))