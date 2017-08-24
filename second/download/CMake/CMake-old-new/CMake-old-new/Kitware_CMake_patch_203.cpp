@@ -583,7 +583,7 @@ bool cmSystemTools::RunSingleCommand(std::vector<std::string> const& command,
        a != command.end(); ++a) {
     argv.push_back(a->c_str());
   }
-  argv.push_back(0);
+  argv.push_back(CM_NULLPTR);
 
   cmsysProcess* cp = cmsysProcess_New();
   cmsysProcess_SetCommand(cp, &*argv.begin());
@@ -595,12 +595,12 @@ bool cmSystemTools::RunSingleCommand(std::vector<std::string> const& command,
   if (outputflag == OUTPUT_PASSTHROUGH) {
     cmsysProcess_SetPipeShared(cp, cmsysProcess_Pipe_STDOUT, 1);
     cmsysProcess_SetPipeShared(cp, cmsysProcess_Pipe_STDERR, 1);
-    captureStdOut = 0;
-    captureStdErr = 0;
+    captureStdOut = CM_NULLPTR;
+    captureStdErr = CM_NULLPTR;
   } else if (outputflag == OUTPUT_MERGE ||
              (captureStdErr && captureStdErr == captureStdOut)) {
     cmsysProcess_SetOption(cp, cmsysProcess_Option_MergeOutput, 1);
-    captureStdErr = 0;
+    captureStdErr = CM_NULLPTR;
   }
   assert(!captureStdErr || captureStdErr != captureStdOut);
 
@@ -614,7 +614,8 @@ bool cmSystemTools::RunSingleCommand(std::vector<std::string> const& command,
   int pipe;
   if (outputflag != OUTPUT_PASSTHROUGH &&
       (captureStdOut || captureStdErr || outputflag != OUTPUT_NONE)) {
-    while ((pipe = cmsysProcess_WaitForData(cp, &data, &length, 0)) > 0) {
+    while ((pipe = cmsysProcess_WaitForData(cp, &data, &length, CM_NULLPTR)) >
+           0) {
       // Translate NULL characters in the output into valid text.
       // Visual Studio 7 puts these characters in the output of its
       // build process.
@@ -642,7 +643,7 @@ bool cmSystemTools::RunSingleCommand(std::vector<std::string> const& command,
     }
   }
 
-  cmsysProcess_WaitForExit(cp, 0);
+  cmsysProcess_WaitForExit(cp, CM_NULLPTR);
   if (captureStdOut) {
     captureStdOut->assign(tempStdOut.begin(), tempStdOut.end());
   }
@@ -1432,7 +1433,7 @@ void list_item_verbose(FILE* out, struct archive_entry* entry)
 
   /* Use uname if it's present, else uid. */
   p = archive_entry_uname(entry);
-  if ((p == NULL) || (*p == '\0')) {
+  if ((p == CM_NULLPTR) || (*p == '\0')) {
     sprintf(tmp, "%lu ", (unsigned long)archive_entry_uid(entry));
     p = tmp;
   }
@@ -1443,7 +1444,7 @@ void list_item_verbose(FILE* out, struct archive_entry* entry)
   fprintf(out, "%-*s ", (int)u_width, p);
   /* Use gname if it's present, else gid. */
   p = archive_entry_gname(entry);
-  if (p != NULL && p[0] != '\0') {
+  if (p != CM_NULLPTR && p[0] != '\0') {
     fprintf(out, "%s", p);
     w = strlen(p);
   } else {
@@ -1875,7 +1876,7 @@ unsigned int cmSystemTools::RandomSeed()
 
   // Try using a real random source.
   cmsys::ifstream fin;
-  fin.rdbuf()->pubsetbuf(0, 0); // Unbuffered read.
+  fin.rdbuf()->pubsetbuf(CM_NULLPTR, 0); // Unbuffered read.
   fin.open("/dev/urandom");
   if (fin.good() && fin.read(seed.bytes, sizeof(seed)) &&
       fin.gcount() == sizeof(seed)) {
@@ -1884,7 +1885,7 @@ unsigned int cmSystemTools::RandomSeed()
 
   // Fall back to the time and pid.
   struct timeval t;
-  gettimeofday(&t, 0);
+  gettimeofday(&t, CM_NULLPTR);
   unsigned int pid = static_cast<unsigned int>(getpid());
   unsigned int tv_sec = static_cast<unsigned int>(t.tv_sec);
   unsigned int tv_usec = static_cast<unsigned int>(t.tv_usec);
@@ -2199,8 +2200,8 @@ bool cmSystemTools::ChangeRPath(std::string const& file,
 
     // Get the RPATH and RUNPATH entries from it.
     int se_count = 0;
-    cmELF::StringEntry const* se[2] = { 0, 0 };
-    const char* se_name[2] = { 0, 0 };
+    cmELF::StringEntry const* se[2] = { CM_NULLPTR, CM_NULLPTR };
+    const char* se_name[2] = { CM_NULLPTR, CM_NULLPTR };
     if (cmELF::StringEntry const* se_rpath = elf.GetRPath()) {
       se[se_count] = se_rpath;
       se_name[se_count] = "RPATH";
@@ -2430,7 +2431,7 @@ bool cmSystemTools::RemoveRPath(std::string const& file, std::string* emsg,
     // Get the RPATH and RUNPATH entries from it and sort them by index
     // in the dynamic section header.
     int se_count = 0;
-    cmELF::StringEntry const* se[2] = { 0, 0 };
+    cmELF::StringEntry const* se[2] = { CM_NULLPTR, CM_NULLPTR };
     if (cmELF::StringEntry const* se_rpath = elf.GetRPath()) {
       se[se_count++] = se_rpath;
     }