@@ -1,8 +1,9 @@
-#include <cstdio>
 #include <cstdlib>
 #include <cstring>
 #include <ctype.h>
 
+#include <iostream>
+
 #if defined(_WIN32) && (defined(_MSC_VER) || defined(__WATCOMC__) || defined(__BORLANDC__) || defined(__MINGW32__))
 
 #include <io.h>
@@ -18,7 +19,7 @@ inline const char* Getcwd(char* buf, unsigned int len)
   const char* ret = _getcwd(buf, len);
   if(!ret)
     {
-    fprintf(stderr, "No current working directory.\n");
+    std::cerr << "No current working directory." << std::endl;
     abort();
     }
   // make sure the drive letter is capital
@@ -46,7 +47,7 @@ inline const char* Getcwd(char* buf, unsigned int len)
   const char* ret = getcwd(buf, len);
   if(!ret)
     {
-    fprintf(stderr, "No current working directory\n");
+    std::cerr << "No current working directory" << std::endl;
     abort();
     }
   return ret;
@@ -59,7 +60,7 @@ int main(int argc, char *argv[])
   char buf[2048];
   const char *cwd = Getcwd(buf, sizeof(buf));
 
-  fprintf(stdout, "Working directory: -->%s<--", cwd);
+  std::cout << "Working directory: -->" << cwd << "<--";
 
   return 0;
 }