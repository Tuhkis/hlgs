call gcc -O1 -c impl.c -o impl.o -fPIC
call gcc -O1 -c hlgs.c -o hlgs.o -fPIC

call gcc -shared -o hlgs.hdll *.o libhl.dll -lwinmm -lgdi32 -lopengl32 -lkernel32 -luser32 -lshell32 -lAdvapi32 -Llibhl.lib

