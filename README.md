# mylibelf

Prerequisite Packages installation:
sudo apt install libelf-dev
sudo apt-get install libbsd-dev


Build command:
gcc read_eh.c -o ehread.elf -lelf -lbsd
