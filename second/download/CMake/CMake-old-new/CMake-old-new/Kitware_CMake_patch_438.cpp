@@ -206,7 +206,7 @@ static int process( const std::string& srcfilename,
       includes.push_back(inc);
     } else {
       if (!isFirstLine || !startsWith(line, srcfilename)) {
-        if (!quiet) {
+        if (!quiet || exit_code != 0) {
           fprintf(stdout, "%s\n", line.c_str());
         }
       } else {
@@ -267,8 +267,11 @@ int main() {
     }
 
     // extract dependencies with cl.exe
-    process(srcfilename, dfile, objfile,
-                  prefix, cl + nol + show + clrest, objdir, true);
+    int exit_code = process(srcfilename, dfile, objfile,
+                            prefix, cl + nol + show + clrest, objdir, true);
+
+    if (exit_code != 0)
+      return exit_code;
 
     // compile rc file with rc.exe
     return process(srcfilename, "" , objfile, prefix, binpath + " " + rest);