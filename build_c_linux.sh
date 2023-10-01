#!/bin/sh

gcc -O1 -c impl.c -o impl.o -fPIC
gcc -O1 -c hlgs.c -o hlgs.o -fPIC

gcc -shared -o hlgs.hdll *.o

