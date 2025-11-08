# AKA-GOAT

Build Instructions

Follow these steps to build the AKA-GOAT App on Windows using MSYS2.

1️⃣ Install MSYS2

Download and install MSYS2: https://www.msys2.org/wiki/MSYS2-installation/

Ensure the following tools are installed and available in your MSYS2 MinGW64 shell:

pacman -Syu
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake

2️⃣ Clone the repository
git clone <repo-url>
cd AKA-GOAT

3️⃣ Pull all submodules
git submodule update --init --recursive


This ensures all submodules are updated

4️⃣ Install system dependencies

Use MSYS2 MinGW64 shell:

pacman -Syu   # Update packages
pacman -S mingw-w64-x86_64-curl mingw-w64-x86_64-openssl mingw-w64-x86_64-opencv mingw-w64-x86_64-toolchain mingw-w64-x86_64-zlib



5️⃣ Set up Python virtual environment
python -m venv venv
source venv/bin/activate
python -m pip install ninja numpy


6️⃣ Build the project

cd backend
mkdir build
cd build
cmake ..
cmake --build .


On first build, this will compile all dependencies and your executable.

The resulting executable will be located in:

backend/build/AKA_GOAT_App.exe

7️⃣ Rebuilding after changes

Once the build folder is configured:

cd backend/build
cmake --build .


8️⃣ Run the App
./AKA_GOAT_App.exe