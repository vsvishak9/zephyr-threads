Setting up the zephyr rtos environment requires downloading and installation of zephyr toolchain and host tools.

detailed guide can be found on https://docs.zephyrproject.org/3.1.0/develop/getting_started/index.html

Then create a workspace folder "zephyrproject" and cd into it
exec following commands
    
    python3 -m venv .venv
    pip install west
    west init .
    west update
    
    west build -b native_posix samples/hello_world
    west build -t run
