# Add the custom library for my_addition
add_library(my_addition STATIC my_addition.c)

# Link the Pico SDK libraries to my_addition
target_link_libraries(my_addition
  pico_stdlib
  pico_multicore
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
  )

# This is the main binary. List your C files here.
add_executable(myproject
    blink.c
    )

pico_set_program_name(myproject "blink")
pico_set_program_version(myproject "0.1")

# Modify the below lines to enable/disable output over UART/USB.
# These are mutually exclusive, only set one.
pico_enable_stdio_uart(myproject 0)
pico_enable_stdio_usb(myproject 1)

# Add the libraries to the build
target_link_libraries(myproject PRIVATE
  pico_stdlib
  pico_multicore
  pico_async_context_freertos
  FreeRTOS-Kernel-Heap4
  my_addition
)

# The CYW43 is the Wifi/Bluetooth module. If the board is set to pico_w, this
# variable will be set and the wireless libraries added.
if(PICO_CYW43_SUPPORTED)
    # For led support on pico_w
    target_link_libraries(myproject PRIVATE
      pico_cyw43_arch_none
    )
    target_link_libraries(my_addition
      pico_cyw43_arch_none
    )
endif()

# Another pico macro which generates the uf2 file in addition to the elf
pico_add_extra_outputs(myproject)
