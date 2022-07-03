gcc -c -Wall -Werror -fpic wrapper.c -o neptune.o
gcc -shared -o export/libneptune.so neptune.o
