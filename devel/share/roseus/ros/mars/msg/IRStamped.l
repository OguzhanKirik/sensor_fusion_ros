;; Auto-generated. Do not edit!


(when (boundp 'mars::IRStamped)
  (if (not (find-package "MARS"))
    (make-package "MARS"))
  (shadow 'IRStamped (find-package "MARS")))
(unless (find-package "MARS::IRSTAMPED")
  (make-package "MARS::IRSTAMPED"))

(in-package "ROS")
;;//! \htmlinclude IRStamped.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass mars::IRStamped
  :super ros::object
  :slots (_header _beam_index ))

(defmethod mars::IRStamped
  (:init
   (&key
    ((:header __header) (instance std_msgs::Header :init))
    ((:beam_index __beam_index) 0)
    )
   (send-super :init)
   (setq _header __header)
   (setq _beam_index (round __beam_index))
   self)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:beam_index
   (&optional __beam_index)
   (if __beam_index (setq _beam_index __beam_index)) _beam_index)
  (:serialization-length
   ()
   (+
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ;; int32 _beam_index
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;; int32 _beam_index
       (write-long _beam_index s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;; int32 _beam_index
     (setq _beam_index (sys::peek buf ptr- :integer)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get mars::IRStamped :md5sum-) "2833188b873a5f2c26a8d59d0288053a")
(setf (get mars::IRStamped :datatype-) "mars/IRStamped")
(setf (get mars::IRStamped :definition-)
      "Header header
int32 beam_index

================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

")



(provide :mars/IRStamped "2833188b873a5f2c26a8d59d0288053a")


