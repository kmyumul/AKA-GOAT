# AKA-GOAT

Build Instructions

Follow these steps to build the AKA-GOAT App on Windows using MSYS2.

1️⃣ Install MSYS2

Download and install MSYS2: https://www.msys2.org/wiki/MSYS2-installation/

Ensure the following tools are installed and available in your MSYS2 MinGW64 shell:

pacman -Syu          # Update the package database and core system packages
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-cmake

2️⃣ Clone the repository
git clone <repo-url>
cd AKA-GOAT

3️⃣ Pull all submodules
git submodule update --init --recursive


This ensures Crow, ASIO, CPR, and other submodules are downloaded.

4️⃣ Install system dependencies

Use MSYS2 MinGW64 shell:

pacman -Syu   # Update packages
pacman -S mingw-w64-x86_64-curl mingw-w64-x86_64-openssl
pacman -S mingw-w64-x86_64-opencv
pacman -S mingw-w64-x86_64-toolchain mingw-w64-x86_64-zlib


⚠️ This ensures CPR can link against system libcurl, avoiding issues with libpsl/meson.

5️⃣ Set up Python virtual environment (optional, for build tools)
python -m venv venv
source venv/bin/activate   # On Windows PowerShell: venv\Scripts\activate
python -m pip install -r requirements.txt


The requirements.txt should include build tools like:

ninja
numpy


These are only needed if you build CPR/libcurl from source with Meson.

6️⃣ Build the project

From the backend directory:

mkdir -p build
cd build
cmake .. -DCPR_USE_SYSTEM_CURL=OFF   # Use OFF if you want CPR to build its own libcurl
cmake --build .


On first build, this will compile all dependencies and your executable.

The resulting executable will be located in:

backend/build/Release/AKA_GOAT_App.exe  # MSVC
backend/build/AKA_GOAT_App.exe          # MinGW

7️⃣ Rebuilding after changes

Once the build folder is configured:

cd backend/build
cmake --build .


You do not need to rerun cmake .. unless you change CMake options or add new source files.

8️⃣ Run the App
./AKA_GOAT_App.exe


Open a browser and visit:

http://localhost:18080/