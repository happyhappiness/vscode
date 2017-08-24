@@ -192,7 +192,8 @@ void Win32Fatal(const char* function) {
 
 }  // anonymous namespace
 
-Subprocess::Subprocess() : child_(NULL) , overlapped_(), is_reading_(false), exit_code_(1) {
+Subprocess::Subprocess() : child_(NULL) , overlapped_(), is_reading_(false),
+                           exit_code_(1) {
 }
 
 Subprocess::~Subprocess() {
@@ -273,14 +274,17 @@ bool Subprocess::Start(SubprocessSet* set, const string& command) {
                       NULL, NULL,
                       &startup_info, &process_info)) {
     DWORD error = GetLastError();
-    if (error == ERROR_FILE_NOT_FOUND) { // file (program) not found error is treated as a normal build action failure
+    if (error == ERROR_FILE_NOT_FOUND) {
+      // file (program) not found error is treated
+      // as a normal build action failure
       if (child_pipe)
         CloseHandle(child_pipe);
       CloseHandle(pipe_);
       CloseHandle(nul);
       pipe_ = NULL;
       // child_ is already NULL;
-      buf_ = "CreateProcess failed: The system cannot find the file specified.\n";
+      buf_ =
+       "CreateProcess failed: The system cannot find the file specified.\n";
       return true;
     } else {
       Win32Fatal("CreateProcess");    // pass all other errors to Win32Fatal
@@ -436,7 +440,8 @@ void SubprocessSet::Clear() {
   for (vector<Subprocess*>::iterator i = running_.begin();
        i != running_.end(); ++i) {
     if ((*i)->child_)
-      if (!GenerateConsoleCtrlEvent(CTRL_BREAK_EVENT, GetProcessId((*i)->child_)))
+      if (!GenerateConsoleCtrlEvent(CTRL_BREAK_EVENT,
+                                    GetProcessId((*i)->child_)))
         Win32Fatal("GenerateConsoleCtrlEvent");
   }
   for (vector<Subprocess*>::iterator i = running_.begin();
@@ -530,7 +535,12 @@ static string getArg(string& cmdline) {
 }
 
 static void parseCommandLine(LPTSTR wincmdline,
-        string& srcfile, string& dfile, string& objfile, string& prefix, string& clpath, string& rest) {
+                             string& srcfile,
+                             string& dfile,
+                             string& objfile,
+                             string& prefix,
+                             string& clpath,
+                             string& rest) {
   string cmdline(wincmdline);
   /* self */ getArg(cmdline);
   srcfile = getArg(cmdline);
@@ -595,7 +605,8 @@ int main() {
   // the same command line verbatim.
 
   string srcfile, dfile, objfile, prefix, clpath, rest;
-  parseCommandLine(GetCommandLine(), srcfile, dfile, objfile, prefix, clpath, rest);
+  parseCommandLine(GetCommandLine(), srcfile, dfile, objfile,
+                                     prefix, clpath, rest);
 
 #if 0
   fprintf(stderr, "\n\ncmcldebug:\n");
@@ -630,7 +641,8 @@ int main() {
   std::string sysHeadersLower = "program files (x86)\\microsoft ";
   while (getline(ss, line)) {
     if (startsWith(line, prefix)) {
-       if (!contains(line, sysHeadersCamel) && !contains(line, sysHeadersLower)) {
+       if (!contains(line, sysHeadersCamel)
+           && !contains(line, sysHeadersLower)) {
         string inc = trimLeadingSpace(line.substr(prefix.size()).c_str());
         if (inc[inc.size() - 1] == '\r') // blech, stupid \r\n
           inc = inc.substr(0, inc.size() - 1);