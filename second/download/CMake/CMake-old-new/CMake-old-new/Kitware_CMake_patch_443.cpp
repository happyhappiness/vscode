@@ -604,7 +604,8 @@ bool contains(const std::string& str, const std::string& what) {
   return str.find(what) != std::string::npos;
 }
 
-std::string replace(const std::string& str, const std::string& what, const std::string& replacement) {
+std::string replace(const std::string& str, const std::string& what,
+                    const std::string& replacement) {
   size_t pos = str.find(what);
   if (pos == std::string::npos)
     return str;
@@ -614,12 +615,12 @@ std::string replace(const std::string& str, const std::string& what, const std::
 
 
 
-static int process(bool ignoreErrors,
-                    const string& srcfile,
+static int process( const string& srcfile,
                     const string& dfile,
                     const string& objfile,
                     const string& prefix,
-                    const string& cmd) {
+                    const string& cmd,
+                    bool quiet = false) {
 
   SubprocessSet subprocs;
   Subprocess* subproc = subprocs.Add(cmd);
@@ -652,8 +653,7 @@ static int process(bool ignoreErrors,
        }
     } else {
       if (!isFirstLine || !startsWith(line, srcfile)) {
-        if (!ignoreErrors) {
-          // suppress errors when cl is fed with a rc file
+        if (!quiet) {
           fprintf(stdout, "%s\n", line.c_str());
         }
       } else {
@@ -663,10 +663,6 @@ static int process(bool ignoreErrors,
   }
 
   if (!success) {
-    if (ignoreErrors) {
-      //printf("\n-- RC file %i dependencies in %s\n\n", includes.size(), dfile.c_str());
-      outputDepFile(dfile, objfile, includes);
-    }
     return exit_code;
   }
 
@@ -699,19 +695,19 @@ int main() {
 #endif
 
   if (lang != "RC") {
-    return process(false, srcfile, dfile, objfile, prefix, binpath + " /showIncludes " + rest);
+    return process(srcfile, dfile, objfile, prefix,
+                   binpath + " /showIncludes " + rest);
   } else {
     // "misuse" cl.exe to get headers from .rc files
     // rc: /fo  x\CMakeFiles\x.dir\x.rc.res              src\x\x.rc
     // cl: /out:x\CMakeFiles\x.dir\x.rc.res.dep.obj  /Tc src\x\x.rc
 
-    cl = "\"" + cl + "\" /showIncludes ";
-    string clRest = rest;
-    clRest = replace(clRest, "/fo" + objfile, "/out:" + objfile + ".dep.obj /Tc ");
+    cl = "\"" + cl + "\" /P /DRC_INVOKED /showIncludes " +
+         replace(rest, "/fo" + objfile, "/out:" + objfile + ".dep.obj /Tc ");
 
     int ret;
-    ret = process(true,  srcfile, dfile, objfile, prefix, cl + clRest);
-    ret = process(false, srcfile, ""   , objfile, prefix, binpath + " " + rest);
+    ret = process(srcfile, dfile, objfile, prefix, cl, true);
+    ret = process(srcfile, ""   , objfile, prefix, binpath + " " + rest);
     return ret;
   }
 