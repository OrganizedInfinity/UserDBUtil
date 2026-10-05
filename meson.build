project(
  'gendb',
  'c',
  meson_version: '>= 1.3.0',
)


dependencies = [
  declare_dependency(
    link_args: [ '-ldb' ]
  ),
  dependency('libcrypt')
]

sources = [
  'main.c'
]

exe = executable(
  'gendb',
  sources,
  install: true,
  dependencies: dependencies,
)

test('basic', exe)
