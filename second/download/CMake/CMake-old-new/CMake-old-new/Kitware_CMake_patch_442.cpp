@@ -482,15 +482,16 @@ void SubprocessSet::Clear() {
 // See http://msdn.microsoft.com/en-us/library/zay8tzh6(v=vs.85).aspx
 void _setargv() {}
 
-
 static void usage(const char* msg) {
-  Fatal("%s\n\nusage:\n"
-          "  cldeps "
-          "<source file> "
-          "<output path for *.d file> "
-          "<output path for *.obj file> "
-          "<prefix of /showIncludes> "
-          "<path to cl> "
+  Fatal("%s\n\nusage:\n    "
+          "cmcldeps "
+          "<language C, CXX or RC>  "
+          "<source file path>  "
+          "<output path for *.d file>  "
+          "<output path for *.obj file>  "
+          "<prefix of /showIncludes>  "
+          "<path to cl.exe>  "
+          "<path to tool (cl or rc)>  "
           "<rest of command ...>\n", msg);
 }
 
@@ -547,12 +548,6 @@ static void parseCommandLine(LPTSTR wincmdline,
   /* self */ getArg(cmdline);
   lang = getArg(cmdline);
   srcfile = getArg(cmdline);
-  std::string::size_type pos = srcfile.rfind("\\");
-  if (pos != string::npos) {
-    srcfile = srcfile.substr(pos + 1);
-  } else {
-    srcfile = "";
-  }
   dfile = getArg(cmdline);
   objfile = getArg(cmdline);
   prefix = getArg(cmdline);
@@ -615,7 +610,7 @@ std::string replace(const std::string& str, const std::string& what,
 
 
 
-static int process( const string& srcfile,
+static int process( const string& srcfilename,
                     const string& dfile,
                     const string& objfile,
                     const string& prefix,
@@ -652,7 +647,7 @@ static int process( const string& srcfile,
         includes.push_back(inc);
        }
     } else {
-      if (!isFirstLine || !startsWith(line, srcfile)) {
+      if (!isFirstLine || !startsWith(line, srcfilename)) {
         if (!quiet) {
           fprintf(stdout, "%s\n", line.c_str());
         }
@@ -685,32 +680,38 @@ int main() {
   parseCommandLine(GetCommandLine(), lang, srcfile, dfile, objfile,
                                      prefix, cl, binpath, rest);
 
-#if 0
-  fprintf(stderr, "\n\ncmcldebug:\n");
-  fprintf(stderr, ".d  : %s\n", dfile.c_str());
-  fprintf(stderr, "OBJ : %s\n", objfile.c_str());
-  fprintf(stderr, "CL  : %s\n", clpath.c_str());
-  fprintf(stderr, "REST: %s\n", rest.c_str());
-  fprintf(stderr, "\n\n");
-#endif
+  // needed to suppress filename output of msvc tools
+  string srcfilename;
+  std::string::size_type pos = srcfile.rfind("\\");
+  if (pos != string::npos) {
+    srcfilename = srcfile.substr(pos + 1);
+  }
 
-  std::string showflag = " /showIncludes /nologo ";
-  if (lang != "RC") {
-    return process(srcfile, dfile, objfile, prefix,
-                   binpath + showflag + rest);
-  } else {
+  std::string nol = " /nologo ";
+  std::string show = " /showIncludes ";
+  if (lang == "C" || lang == "CXX") {
+    return process(srcfilename, dfile, objfile, prefix,
+                   binpath + nol + show + rest);
+  } else if (lang == "RC") {
     // "misuse" cl.exe to get headers from .rc files
-    // rc: /fo  x\CMakeFiles\x.dir\x.rc.res              src\x\x.rc
-    // cl: /out:x\CMakeFiles\x.dir\x.rc.res.dep.obj  /Tc src\x\x.rc
 
-    cl = "\"" + cl + "\" /P /DRC_INVOKED " + showflag +
-         replace(rest, "/fo" + objfile, "/out:" + objfile + ".dep.obj /Tc ");
+    string clrest = rest;
+    // rc: /fo x.dir\x.rc.res  ->  cl: /out:x.dir\x.rc.res.dep.obj
+    clrest = replace(clrest, "/fo", "/out:");
+    clrest = replace(clrest, objfile, objfile + ".dep.obj ");
+    // rc: src\x\x.rc  ->  cl: /Tc src\x\x.rc
+    clrest = replace(clrest, srcfile, "/Tc " + srcfile);
+
+    cl = "\"" + cl + "\" /P /DRC_INVOKED ";
+
+    // extract dependencies with cl.exe
+    process(srcfilename, dfile, objfile,
+                  prefix, cl + nol + show + clrest, true);
 
-    int ret;
-    ret = process(srcfile, dfile, objfile, prefix, cl, true);
-    ret = process(srcfile, ""   , objfile, prefix,
-                  binpath + " /nologo "  + rest);
-    return ret;
+    // compile rc file with rc.exe
+    return process(srcfilename, "" , objfile, prefix, binpath + nol + rest);
   }
 
+  usage("Invalid language specified.");
+  return 1;
 }