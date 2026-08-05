# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\crazypoppersapp_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\crazypoppersapp_autogen.dir\\ParseCache.txt"
  "crazypoppersapp_autogen"
  )
endif()
