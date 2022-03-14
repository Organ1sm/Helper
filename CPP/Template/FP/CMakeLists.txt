add_executable(Curry Currying.cpp)
target_compile_options(
  Curry
  PUBLIC -std=c++17
  PUBLIC -Werror
)
target_link_options(Curry PUBLIC -fuse-ld=lld)
