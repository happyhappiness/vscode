@@ -1,15 +1,15 @@
 #include <stdio.h>
 #include "DumpInformation.h"
 
-int main(int, char*[])
+int DumpFile(char* filename, char* comment)
 {
-  FILE* file = fopen(CMAKE_DUMP_FILE, "r");
+  FILE* file = fopen(filename, "r");
   if(!file)
     {
-    printf("Error, could not open file %s\n", CMAKE_DUMP_FILE);
-    return -1;
+    printf("Error, could not open file %s\n", filename);
+    return 1;
     }
-  printf("#CMake System Variables are:");
+  printf("%s", comment);
   while(!feof(file))
     {
     int ch = fgetc(file);
@@ -37,3 +37,13 @@ int main(int, char*[])
   fclose(file);
   return 0;
 }
+
+
+int main(int, char*[])
+{
+  int res = 0;
+  res += DumpFile(CMAKE_DUMP_FILE, "#CMake System Variables are:");
+  res += DumpFile(CMAKE_CACHE_FILE, "#CMake Cache is:");
+  res += DumpFile(CMAKE_ALL_VARIABLES, "#CMake Variables are:");
+  return res;
+}