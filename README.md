Setting up the zephyr rtos environment requires downloading and installation of zephyr toolchain and host tools.

detailed guide can be found on https://docs.zephyrproject.org/3.1.0/develop/getting_started/index.html
For Arch linux i had to install the packages using below command
    
    sudo pacman -S git cmake ninja gperf ccache dfu-util dtc wget \
    python-pip python-setuptools python-wheel tk xz file make lib32-gcc-libs lib32-glibc
    
For setting up Zephyr SDK:
    
    wget https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.14.2/zephyr-sdk-0.14.2_linux-x86_64.tar.gz
    wget -O - https://github.com/zephyrproject-rtos/sdk-ng/releases/download/v0.14.2/sha256.sum | shasum --check --ignore-missing
    
Extract the Zephyr SDK bundle archive (make sure you extract in $HOME folder):

    cd <sdk download directory>
    tar xvf zephyr-sdk-0.14.2_linux-x86_64.tar.gz

Run the Zephyr SDK bundle setup script:

    cd zephyr-sdk-0.14.2
    ./setup.sh

Then create a workspace folder "zephyrproject" and cd into it
exec following commands
    
    python3 -m venv .venv
    #then source the venv activation script, i used vscode, it does it automatically.
    pip install west
    west init .
    west update
    
Now copy the folder in this repository in zephyr subfolder inside workspace.
Replace "name of project" with the folder name wich u have to compile.
    
    west build -p -b native_posix <name of project>
    west build -t run
