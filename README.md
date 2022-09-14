Setting up the zephyr rtos environment requires downloading and installation of zephyr toolchain and host tools.

detailed guide can be found on https://docs.zephyrproject.org/3.1.0/develop/getting_started/index.html

Then create a workspace folder "zephyrproject" and cd into it
exec following commands
    
    python3 -m venv .venv
    #then source the venv activation script, i used vscode, it does it automatically.
    pip install west
    west init .
    west update

replace <name of project> with the folder name wich u have to compile.
    
    west build -b native_posix <name of project>
    west build -t run
