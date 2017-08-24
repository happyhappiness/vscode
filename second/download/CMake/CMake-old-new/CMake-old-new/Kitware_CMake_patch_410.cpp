@@ -62,15 +62,19 @@ static std::string trimLeadingSpace(const std::string& cmdline) {
   return cmdline.substr(i);
 }
 
-static void doEscape(std::string& str, const std::string& search,
-                                       const std::string& repl) {
+static void replaceAll(std::string& str, const std::string& search,
+                                         const std::string& repl) {
   std::string::size_type pos = 0;
   while ((pos = str.find(search, pos)) != std::string::npos) {
     str.replace(pos, search.size(), repl);
     pos += repl.size();
   }
 }
 
+bool startsWith(const std::string& str, const std::string& what) {
+  return str.compare(0, what.size(), what) == 0;
+}
+
 // Strips one argument from the cmdline and returns it. "surrounding quotes"
 // are removed from the argument if there were any.
 static std::string getArg(std::string& cmdline) {
@@ -117,6 +121,13 @@ static void parseCommandLine(LPTSTR wincmdline,
   rest = trimLeadingSpace(cmdline);
 }
 
+// Not all backslashes need to be escaped in a depfile, but it's easier that
+// way.  See the re2c grammar in ninja's source code for more info.
+static void escapePath(std::string &path) {
+  replaceAll(path, "\\", "\\\\");
+  replaceAll(path, " ", "\\ ");
+}
+
 static void outputDepFile(const std::string& dfile, const std::string& objfile,
         std::vector<std::string>& incs) {
 
@@ -132,16 +143,24 @@ static void outputDepFile(const std::string& dfile, const std::string& objfile,
   // FIXME should this be fatal or not? delete obj? delete d?
   if (!out)
     return;
+  std::string cwd = cmSystemTools::GetCurrentWorkingDirectory();
+  replaceAll(cwd, "/", "\\");
+  cwd += "\\";
 
   std::string tmp = objfile;
-  doEscape(tmp, " ", "\\ ");
+  escapePath(tmp);
   fprintf(out, "%s: \\\n", tmp.c_str());
 
   std::vector<std::string>::iterator it = incs.begin();
   for (; it != incs.end(); ++it) {
     tmp = *it;
-    doEscape(tmp, "\\", "/");
-    doEscape(tmp, " ", "\\ ");
+    // The paths need to match the ones used to identify build artifacts in the
+    // build.ninja file.  Therefore we need to canonicalize the path to use
+    // backward slashes and relativize the path to the build directory.
+    replaceAll(tmp, "/", "\\");
+    if (startsWith(tmp, cwd))
+      tmp = tmp.substr(cwd.size());
+    escapePath(tmp);
     fprintf(out, "%s \\\n", tmp.c_str());
   }
 
@@ -150,10 +169,6 @@ static void outputDepFile(const std::string& dfile, const std::string& objfile,
 }
 
 
-bool startsWith(const std::string& str, const std::string& what) {
-  return str.compare(0, what.size(), what) == 0;
-}
-
 bool contains(const std::string& str, const std::string& what) {
   return str.find(what) != std::string::npos;
 }