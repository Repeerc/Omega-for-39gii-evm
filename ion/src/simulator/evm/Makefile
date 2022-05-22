
ion_src += $(addprefix ion/src/simulator/evm/, \
  head.c \
  main.cpp \
  callback.cpp \
  clipboard.cpp \
  display.cpp \
  framebuffer.cpp \
  telemetry_init.cpp \
  keyboard.cpp \
  events_keyboard.cpp \
  events.cpp \
  newlib_stub.c \
  sys_llapi.c \
)

ion_src += ion/src/shared/collect_registers.cpp

sdl_simu_needs_to_be_removed += $(addprefix ion/src/simulator/shared/, \
  timing.cpp \
  events_platform.cpp \
  framebuffer.cpp \
  keyboard.cpp \
  window.cpp \
  main.cpp \
  clipboard.cpp \
  display.cpp:-headless \
  events_keyboard.cpp:-headless \
  events.cpp \
  framebuffer_base.cpp \
  keyboard_sdl.cpp:-headless \
  main_sdl.cpp:-headless \
  layout.cpp:-headless \
  dummy/store_script.cpp \
)

# Remove the dummy diplay (re-implemented) and the SDL simulator stuff.
ion_src := $(filter-out $(sdl_simu_needs_to_be_removed),$(ion_src))

LDSCRIPT = ion/src/simulator/evm/sys_ld.script

