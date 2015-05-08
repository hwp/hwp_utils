# Author : Weipeng He <heweipeng@gmail.com>
# Copyright (c) 2015, All rights reserved.

set_source_files_properties(hashmap_test.c common_test.c
  PROPERTIES COMPILE_FLAGS -D_GNU_SOURCE)

add_executable(darray_test list_test.c darray_test.c)
target_link_libraries(darray_test container_lib test_lib)
add_test(NAME darray_test COMMAND darray_test)

add_executable(hashmap_test hashmap_test.c)
target_link_libraries(hashmap_test container_lib test_lib)
add_test(NAME hashmap_test COMMAND hashmap_test)

add_executable(common_test common_test.c)
target_link_libraries(common_test container_lib test_lib)
add_test(NAME common_test COMMAND common_test)

