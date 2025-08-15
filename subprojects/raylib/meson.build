project('raylib', 'c')

# Get build options
platform_option = get_option('platform')
graphics_api_option = get_option('graphics_api')

# Platform detection
platform_c_args = []
platform_link_args = []
platform_deps = []

message('Building raylib for platform: ' + platform_option)
message('Using graphics API: ' + graphics_api_option)

if host_machine.system() == 'linux' or host_machine.system() == 'undefined'
  if platform_option == 'desktop'
    # Desktop dependencies (X11/GLFW)
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
    
    # Other Linux desktop dependencies
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
    
  elif platform_option == 'drm'
    # DRM dependencies
    threads_dep = dependency('threads', required: false)
    if threads_dep.found()
      platform_deps += [threads_dep]
    else
      platform_link_args += ['-lpthread']
    endif
    
    # DRM specific libraries
    platform_link_args += ['-lGLESv2', '-lEGL', '-ldrm', '-lgbm', '-lrt', '-lm', '-ldl']
  endif
  
elif host_machine.system() == 'windows'
  platform_link_args += ['-lgdi32', '-lwinmm', '-lopengl32']
elif host_machine.system() == 'darwin'
  # Add macOS frameworks here if needed
endif

# Raylib source files - common sources
raylib_sources = files(
  'src/raudio.c',
  'src/rmodels.c',
  'src/rshapes.c',
  'src/rtext.c',
  'src/rtextures.c',
  'src/utils.c',
)

# Platform-specific sources
if platform_option == 'desktop'
  raylib_sources += files('src/rcore.c', 'src/rglfw.c')
elif platform_option == 'drm'
  raylib_sources += files('src/rcore.c')
endif

# Include directories
if platform_option == 'desktop'
  raylib_inc = include_directories('src', 'src/external/glfw/include')
elif platform_option == 'drm'
  raylib_inc = include_directories('src', '/usr/include/libdrm')
endif

# Platform and graphics API specific compilation flags
platform_c_args = ['-DRAYLIB_IMPLEMENTATION', '-D_GNU_SOURCE']

if platform_option == 'desktop'
  platform_c_args += ['-DPLATFORM_DESKTOP', '-D__linux__']
  if graphics_api_option == 'opengl33'
    platform_c_args += ['-DGRAPHICS_API_OPENGL_33']
  elif graphics_api_option == 'opengl_es2'
    platform_c_args += ['-DGRAPHICS_API_OPENGL_ES2']
  endif
  platform_c_args += ['-D_GLFW_X11']
elif platform_option == 'drm'
  platform_c_args += ['-DPLATFORM_DRM', '-DGRAPHICS_API_OPENGL_ES2', '-DEGL_NO_X11', '-D__linux__']
endif

# Common feature flags
common_c_args = [
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
]
# Raylib library
raylib_lib = static_library('raylib',
  raylib_sources,
  include_directories: raylib_inc,
  c_args: platform_c_args + common_c_args,
  dependencies: platform_deps,
  link_args: platform_link_args,
)

# Create dependency object for the main project
raylib_dep = declare_dependency(
  link_with: raylib_lib,
  include_directories: raylib_inc,
  dependencies: platform_deps,
)
