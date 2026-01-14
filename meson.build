project('fractal-project', 'c',
  version: '1.0.0',
  default_options: [
    'c_std=c11',
    'warning_level=3',
    'werror=true',
    'buildtype=debugoptimized'
  ]
)

add_project_arguments('-D_GNU_SOURCE', language: 'c')

cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required: true)

src = files(
  'src/main.c',
  'src/image.c',
  'src/fractal.c'
)

test_src = files(
  'src/test_main.c',
  'src/image.c',
  'src/fractal.c'
)

executable('fractal', src,
  dependencies: [m_dep],
  install: true
)

test_exe = executable('fractal_test', test_src,
  dependencies: [m_dep]
)

test('basic_test', test_exe)