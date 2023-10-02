#!/bin/sh

if [ ! -f impl.o ]; then
  echo "[BUIILD] Building impl.c."
  gcc -O3 -pipe -c impl.c -o impl.o -fPIC
fi
echo "[BUIILD] Building hlgs.c."
gcc -O3 -pipe -c hlgs.c -o hlgs.o -fPIC

echo "[BUIILD] Linking hlgs.hdll."
gcc -shared -o hlgs.hdll *.o

