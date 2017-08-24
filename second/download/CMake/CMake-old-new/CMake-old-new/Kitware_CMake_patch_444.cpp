@@ -535,14 +535,17 @@ static string getArg(string& cmdline) {
 }
 
 static void parseCommandLine(LPTSTR wincmdline,
+                             string& lang,
                              string& srcfile,
                              string& dfile,
                              string& objfile,
                              string& prefix,
                              string& clpath,
+                             string& binpath,
                              string& rest) {
   string cmdline(wincmdline);
   /* self */ getArg(cmdline);
+  lang = getArg(cmdline);
   srcfile = getArg(cmdline);
   std::string::size_type pos = srcfile.rfind("\\");
   if (pos != string::npos) {
@@ -554,12 +557,16 @@ static void parseCommandLine(LPTSTR wincmdline,
   objfile = getArg(cmdline);
   prefix = getArg(cmdline);
   clpath = getArg(cmdline);
+  binpath = getArg(cmdline);
   rest = trimLeadingSpace(cmdline);
 }
 
 static void outputDepFile(const string& dfile, const string& objfile,
         vector<string>& incs) {
 
+  if (dfile.empty())
+    return;
+
   // strip duplicates
   sort(incs.begin(), incs.end());
   incs.erase(unique(incs.begin(), incs.end()), incs.end());
@@ -581,6 +588,7 @@ static void outputDepFile(const string& dfile, const string& objfile,
     //doEscape(tmp, "(", "\\("); // TODO ninja can't read ( and )
     //doEscape(tmp, ")", "\\)");
     fprintf(out, "%s \\\n", tmp.c_str());
+    //printf("include: %s \n", tmp.c_str());
   }
 
   fprintf(out, "\n");
@@ -596,29 +604,26 @@ bool contains(const std::string& str, const std::string& what) {
   return str.find(what) != std::string::npos;
 }
 
-int main() {
+std::string replace(const std::string& str, const std::string& what, const std::string& replacement) {
+  size_t pos = str.find(what);
+  if (pos == std::string::npos)
+    return str;
+  std::string replaced = str;
+  return replaced.replace(pos, what.size(), replacement);
+}
 
-  // Use the Win32 api instead of argc/argv so we can avoid interpreting the
-  // rest of command line after the .d and .obj. Custom parsing seemed
-  // preferable to the ugliness you get into in trying to re-escape quotes for
-  // subprocesses, so by avoiding argc/argv, the subprocess is called with
-  // the same command line verbatim.
 
-  string srcfile, dfile, objfile, prefix, clpath, rest;
-  parseCommandLine(GetCommandLine(), srcfile, dfile, objfile,
-                                     prefix, clpath, rest);
 
-#if 0
-  fprintf(stderr, "\n\ncmcldebug:\n");
-  fprintf(stderr, ".d  : %s\n", dfile.c_str());
-  fprintf(stderr, "OBJ : %s\n", objfile.c_str());
-  fprintf(stderr, "CL  : %s\n", clpath.c_str());
-  fprintf(stderr, "REST: %s\n", rest.c_str());
-  fprintf(stderr, "\n\n");
-#endif
+static int process(bool ignoreErrors,
+                    const string& srcfile,
+                    const string& dfile,
+                    const string& objfile,
+                    const string& prefix,
+                    const string& cmd) {
 
   SubprocessSet subprocs;
-  Subprocess* subproc = subprocs.Add(clpath + " /showIncludes " + rest);
+  Subprocess* subproc = subprocs.Add(cmd);
+
   if(!subproc)
     return 2;
 
@@ -647,18 +652,67 @@ int main() {
        }
     } else {
       if (!isFirstLine || !startsWith(line, srcfile)) {
-        fprintf(stdout, "%s\n", line.c_str());
+        if (!ignoreErrors) {
+          // suppress errors when cl is fed with a rc file
+          fprintf(stdout, "%s\n", line.c_str());
+        }
       } else {
         isFirstLine = false;
       }
     }
   }
 
-  if (!success)
+  if (!success) {
+    if (ignoreErrors) {
+      //printf("\n-- RC file %i dependencies in %s\n\n", includes.size(), dfile.c_str());
+      outputDepFile(dfile, objfile, includes);
+    }
     return exit_code;
+  }
 
   // don't update .d until/unless we succeed compilation
   outputDepFile(dfile, objfile, includes);
 
   return 0;
 }
+
+
+int main() {
+
+  // Use the Win32 api instead of argc/argv so we can avoid interpreting the
+  // rest of command line after the .d and .obj. Custom parsing seemed
+  // preferable to the ugliness you get into in trying to re-escape quotes for
+  // subprocesses, so by avoiding argc/argv, the subprocess is called with
+  // the same command line verbatim.
+
+  string lang, srcfile, dfile, objfile, prefix, cl, binpath, rest;
+  parseCommandLine(GetCommandLine(), lang, srcfile, dfile, objfile,
+                                     prefix, cl, binpath, rest);
+
+#if 0
+  fprintf(stderr, "\n\ncmcldebug:\n");
+  fprintf(stderr, ".d  : %s\n", dfile.c_str());
+  fprintf(stderr, "OBJ : %s\n", objfile.c_str());
+  fprintf(stderr, "CL  : %s\n", clpath.c_str());
+  fprintf(stderr, "REST: %s\n", rest.c_str());
+  fprintf(stderr, "\n\n");
+#endif
+
+  if (lang != "RC") {
+    return process(false, srcfile, dfile, objfile, prefix, binpath + " /showIncludes " + rest);
+  } else {
+    // "misuse" cl.exe to get headers from .rc files
+    // rc: /fo  x\CMakeFiles\x.dir\x.rc.res              src\x\x.rc
+    // cl: /out:x\CMakeFiles\x.dir\x.rc.res.dep.obj  /Tc src\x\x.rc
+
+    cl = "\"" + cl + "\" /showIncludes ";
+    string clRest = rest;
+    clRest = replace(clRest, "/fo" + objfile, "/out:" + objfile + ".dep.obj /Tc ");
+
+    int ret;
+    ret = process(true,  srcfile, dfile, objfile, prefix, cl + clRest);
+    ret = process(false, srcfile, ""   , objfile, prefix, binpath + " " + rest);
+    return ret;
+  }
+
+}