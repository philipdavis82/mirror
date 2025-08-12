project('mmirror', 'c', 'cpp')

cc  = meson.get_compiler('c')
cxx = meson.get_compiler('cpp')

c_args = []
cpp_args = []
link_args = []
name_suffix = []
dependencies = []

# Project files
inc_dir = include_directories(
  'src',
)

sources = files(
  'src/main.cpp',
)

executable('magic',
  sources,
  c_args: c_args,
  cpp_args: cpp_args,
  dependencies: dependencies,
  include_directories: inc_dir,
  link_args: link_args,
  name_suffix: name_suffix,
)