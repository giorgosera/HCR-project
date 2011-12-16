FILE(REMOVE_RECURSE
  "../src/hcr_vip/msg"
  "../msg_gen"
  "../msg_gen"
  "CMakeFiles/ROSBUILD_genmsg_lisp"
  "../msg_gen/lisp/location_msg.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_location_msg.lisp"
  "../msg_gen/lisp/laser_vip.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_laser_vip.lisp"
  "../msg_gen/lisp/sonar_vip.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_sonar_vip.lisp"
  "../msg_gen/lisp/sensorMsg.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_sensorMsg.lisp"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_lisp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
