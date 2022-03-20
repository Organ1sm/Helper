add_executable(TupleExample TupleExample.cpp)
target_compile_options(
  TupleExample
  PUBLIC -std=c++17
  PUBLIC -Werror
)

add_executable(Curry Currying.cpp)
target_compile_options(
  Curry
  PUBLIC -std=c++17
  PUBLIC -Werror
)
target_link_options(Curry PUBLIC -fuse-ld=lld)

