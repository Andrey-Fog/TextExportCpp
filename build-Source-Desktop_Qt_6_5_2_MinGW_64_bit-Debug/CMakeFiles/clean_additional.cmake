# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\TextExportCpp_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\TextExportCpp_autogen.dir\\ParseCache.txt"
  "TextExportCpp_autogen"
  )
endif()
