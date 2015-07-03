# Author : Weipeng He <heweipeng@gmail.com>
# Copyright (c) 2014, All rights reserved.

add_library(${PACKAGE} SHARED
  common.c list.c map.c queue.c test.c debug.c)

install(TARGETS ${PACKAGE}
  LIBRARY DESTINATION lib)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
  DESTINATION include/${PACKAGE} FILES_MATCHING PATTERN "*.h")

