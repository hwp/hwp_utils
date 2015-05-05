# Author : Weipeng He <heweipeng@gmail.com>
# Copyright (c) 2015, All rights reserved.

add_executable(check_list list_test.c)
target_link_libraries(check_list container_lib test_lib)

add_test(NAME check_list COMMAND check_list)

