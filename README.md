# AKA-GOAT

# Build Instructions

1. Install MSYS2 https://www.msys2.org/wiki/MSYS2-installation/

ensure that you have both gcc and cmake

2. Clone the repo

3. Pull all submodules - git submodule update --init --recursive

4. install dependencies

pacman -Syu
pacman -S mingw-w64-x86_64-curl mingw-w64-x86_64-openssl

5. source a venv

run the following commands
python -m venv venv
source venv/bin/activate
python -m pip install -r requirements.txt

6. Build the project

cd backend
mkdir build
cd build
cmake .. -DCPR_USE_SYSTEM_CURL=OFF
cmake --build .

for any changes, only call "cmake --build ."