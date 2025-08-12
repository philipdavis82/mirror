project('raylib', 'c')

# Platform detection
platform_c_args = []
platform_link_args = []
platform_deps = []

message(host_machine.system())
if host_machine.system() == 'linux' or host_machine.system() == 'undefined'
  # Try to find system dependencies, fallback gracefully
  gl_dep = dependency('gl', required: false)
  if not gl_dep.found()
    gl_dep = dependency('GL', required: false)
  endif
  if not gl_dep.found()
    # Fallback to manual linking
    platform_link_args += ['-lGL']
  else
    platform_deps += [gl_dep]
  endif
  
  # Other Linux dependencies
  threads_dep = dependency('threads', required: false)
  if threads_dep.found()
    platform_deps += [threads_dep]
  else
    platform_link_args += ['-lpthread']
  endif
  
  x11_dep = dependency('x11', required: false)
  if x11_dep.found()
    platform_deps += [x11_dep]
  else
    platform_link_args += ['-lX11']
  endif
  
  # Optional dependencies with fallbacks
  foreach dep_name : ['xrandr', 'xi', 'xinerama', 'xcursor']
    dep = dependency(dep_name, required: false)
    if dep.found()
      platform_deps += [dep]
    else
      platform_link_args += ['-l' + dep_name]
    endif
  endforeach
  
elif host_machine.system() == 'windows'
  platform_link_args += ['-lgdi32', '-lwinmm', '-lopengl32']
elif host_machine.system() == 'darwin'
  # Add macOS frameworks here if needed
endif

# Raylib source files
raylib_sources = files(
  'src/rcore.c',
  'src/raudio.c', 
  'src/rglfw.c',
  'src/rmodels.c',
  'src/rshapes.c',
  'src/rtext.c',
  'src/rtextures.c',
  'src/utils.c',
)

# Include directories
raylib_inc = include_directories('src', 'src/external/glfw/include')

# Raylib library
raylib_lib = static_library('raylib',
  raylib_sources,
  include_directories: raylib_inc,
  c_args: [
    '-DRAYLIB_IMPLEMENTATION',
    '-DPLATFORM_DESKTOP',
    '-D_GNU_SOURCE',
    '-DGRAPHICS_API_OPENGL_33',
    '-D_GLFW_X11',
    '-DSUPPORT_FILEFORMAT_PNG',
    '-DSUPPORT_FILEFORMAT_JPG', 
    '-DSUPPORT_FILEFORMAT_GIF',
    '-DSUPPORT_FILEFORMAT_WAV',
    '-DSUPPORT_FILEFORMAT_OGG',
    '-DSUPPORT_FILEFORMAT_MP3',
    '-DSUPPORT_CAMERA_SYSTEM',
    '-DSUPPORT_GESTURES_SYSTEM',
    '-DSUPPORT_MOUSE_GESTURES',
    '-DSUPPORT_TOUCH_AS_MOUSE',
    '-DSUPPORT_SSH_KEYBOARD_RPI',
    '-DSUPPORT_DEFAULT_FONT',
    '-DSUPPORT_STANDARD_FILEIO',
    '-DSUPPORT_TRACELOG',
  ] + platform_c_args,
  dependencies: platform_deps,
  link_args: platform_link_args,
)

# Create dependency object for the main project
raylib_dep = declare_dependency(
  link_with: raylib_lib,
  include_directories: raylib_inc,
  dependencies: platform_deps,
)
