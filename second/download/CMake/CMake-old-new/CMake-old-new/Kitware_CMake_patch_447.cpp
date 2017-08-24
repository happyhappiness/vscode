@@ -517,7 +517,7 @@ static string getArg(string& cmdline) {
     if (i >= cmdline.size())
       usage("Couldn't parse arguments.");
     if (!in_quoted && cmdline[i] == ' ')
-      break;
+      break; // "a b" "x y"
     if (cmdline[i] == '"')
       in_quoted = !in_quoted;
   }
@@ -560,9 +560,12 @@ static void outputDepFile(const string& dfile, const string& objfile,
   if (!out)
     return;
 
-  fprintf(out, "%s: \\\n", objfile.c_str());
+  string tmp = objfile;
+  doEscape(tmp, " ", "\\ ");
+  fprintf(out, "%s: \\\n", tmp.c_str());
+
   for (vector<string>::iterator i(incs.begin()); i != incs.end(); ++i) {
-    string tmp = *i;
+    tmp = *i;
     doEscape(tmp, "\\", "\\\\");
     doEscape(tmp, " ", "\\ ");
     //doEscape(tmp, "(", "("); // TODO ninja cant read ( and )
@@ -594,10 +597,14 @@ int main() {
   string srcfile, dfile, objfile, prefix, clpath, rest;
   parseCommandLine(GetCommandLine(), srcfile, dfile, objfile, prefix, clpath, rest);
 
-  //fprintf(stderr, "D: %s\n", dfile.c_str());
-  //fprintf(stderr, "OBJ: %s\n", objfile.c_str());
-  //fprintf(stderr, "CL: %s\n", clpath.c_str());
-  //fprintf(stderr, "REST: %s\n", rest.c_str());
+#if 0
+  fprintf(stderr, "\n\ncmcldebug:\n");
+  fprintf(stderr, ".d  : %s\n", dfile.c_str());
+  fprintf(stderr, "OBJ : %s\n", objfile.c_str());
+  fprintf(stderr, "CL  : %s\n", clpath.c_str());
+  fprintf(stderr, "REST: %s\n", rest.c_str());
+  fprintf(stderr, "\n\n");
+#endif
 
   SubprocessSet subprocs;
   Subprocess* subproc = subprocs.Add(clpath + " /showIncludes " + rest);