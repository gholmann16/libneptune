gcc -c -Wall -Werror -fpic wrapper.c -o neptune.o
gcc -c -Wall -Werror -fpic lib/localupdate.cpp -o update.o
gcc -shared -o export/libneptune.so neptune.o update.o