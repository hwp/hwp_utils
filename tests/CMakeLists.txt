# Author : Weipeng He <heweipeng@gmail.com>
# Copyright (c) 2015, All rights reserved.

set_source_files_properties(hashmap_test.c common_test.c
  PROPERTIES COMPILE_FLAGS -D_GNU_SOURCE)

add_executable(common_test common_test.c)
target_link_libraries(common_test ${PACKAGE})
add_test(NAME common_test COMMAND common_test)

add_executable(darray_test list_test.c darray_test.c)
target_link_libraries(darray_test ${PACKAGE})
add_test(NAME darray_test COMMAND darray_test)

add_executable(hashmap_test hashmap_test.c)
target_link_libraries(hashmap_test ${PACKAGE})
add_test(NAME hashmap_test COMMAND hashmap_test)

add_executable(pqueue_test pqueue_test.c)
target_link_libraries(pqueue_test ${PACKAGE})
add_test(NAME pqueue_test COMMAND pqueue_test)

