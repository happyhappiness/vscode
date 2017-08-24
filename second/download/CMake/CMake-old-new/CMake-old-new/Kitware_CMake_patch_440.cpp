@@ -24,7 +24,6 @@
 #include <queue>
 #include <cstdio>
 
-using namespace std;
 
 #ifdef _WIN32
 #include <windows.h>
@@ -52,16 +51,16 @@ struct Subprocess {
 
   bool Done() const;
 
-  const string& GetOutput() const;
+  const std::string& GetOutput() const;
 
   int ExitCode() const { return exit_code_; }
 
  private:
   Subprocess();
-  bool Start(struct SubprocessSet* set, const string& command, const string& dir);
+  bool Start(struct SubprocessSet* set, const std::string& command, const std::string& dir);
   void OnPipeReady();
 
-  string buf_;
+  std::string buf_;
 
 #ifdef _WIN32
   /// Set up pipe_ as the parent-side pipe of the subprocess; return the
@@ -89,13 +88,13 @@ struct SubprocessSet {
   SubprocessSet();
   ~SubprocessSet();
 
-  Subprocess* Add(const string& command, const string& dir);
+  Subprocess* Add(const std::string& command, const std::string& dir);
   bool DoWork();
   Subprocess* NextFinished();
   void Clear();
 
-  vector<Subprocess*> running_;
-  queue<Subprocess*> finished_;
+  std::vector<Subprocess*> running_;
+  std::queue<Subprocess*> finished_;
 
 #ifdef _WIN32
   static BOOL WINAPI NotifyInterrupted(DWORD dwCtrlType);
@@ -137,7 +136,7 @@ static void Fatal(const char* msg, ...) {
 
 
 #ifdef _WIN32
-string GetLastErrorString() {
+std::string GetLastErrorString() {
   DWORD err = GetLastError();
 
   char* msg_buf;
@@ -151,7 +150,7 @@ string GetLastErrorString() {
         (char*)&msg_buf,
         0,
         NULL);
-  string msg = msg_buf;
+  std::string msg = msg_buf;
   LocalFree(msg_buf);
   return msg;
 }
@@ -244,8 +243,8 @@ HANDLE Subprocess::SetupPipe(HANDLE ioport) {
   return output_write_child;
 }
 
-bool Subprocess::Start(SubprocessSet* set, const string& command,
-                                           const string& dir) {
+bool Subprocess::Start(SubprocessSet* set, const std::string& command,
+                                           const std::string& dir) {
   HANDLE child_pipe = SetupPipe(set->ioport_);
 
   SECURITY_ATTRIBUTES security_attributes;
@@ -358,7 +357,7 @@ bool Subprocess::Done() const {
   return pipe_ == NULL;
 }
 
-const string& Subprocess::GetOutput() const {
+const std::string& Subprocess::GetOutput() const {
   return buf_;
 }
 
@@ -389,7 +388,7 @@ BOOL WINAPI SubprocessSet::NotifyInterrupted(DWORD dwCtrlType) {
   return FALSE;
 }
 
-Subprocess *SubprocessSet::Add(const string& command, const string& dir) {
+Subprocess *SubprocessSet::Add(const std::string& command, const std::string& dir) {
   Subprocess *subprocess = new Subprocess;
   if (!subprocess->Start(this, command, dir)) {
     delete subprocess;
@@ -420,7 +419,7 @@ bool SubprocessSet::DoWork() {
   subproc->OnPipeReady();
 
   if (subproc->Done()) {
-    vector<Subprocess*>::iterator end =
+    std::vector<Subprocess*>::iterator end =
         std::remove(running_.begin(), running_.end(), subproc);
     if (running_.end() != end) {
       finished_.push(subproc);
@@ -440,14 +439,14 @@ Subprocess* SubprocessSet::NextFinished() {
 }
 
 void SubprocessSet::Clear() {
-  for (vector<Subprocess*>::iterator i = running_.begin();
+  for (std::vector<Subprocess*>::iterator i = running_.begin();
        i != running_.end(); ++i) {
     if ((*i)->child_)
       if (!GenerateConsoleCtrlEvent(CTRL_BREAK_EVENT,
                                     GetProcessId((*i)->child_)))
         Win32Fatal("GenerateConsoleCtrlEvent");
   }
-  for (vector<Subprocess*>::iterator i = running_.begin();
+  for (std::vector<Subprocess*>::iterator i = running_.begin();
        i != running_.end(); ++i)
     delete *i;
   running_.clear();
@@ -498,25 +497,25 @@ static void usage(const char* msg) {
           "<rest of command ...>\n", msg);
 }
 
-static string trimLeadingSpace(const string& cmdline) {
+static std::string trimLeadingSpace(const std::string& cmdline) {
   int i = 0;
   for (; cmdline[i] == ' '; ++i)
     ;
   return cmdline.substr(i);
 }
 
-static void doEscape(string& str, const string& search, const string& repl) {
-  string::size_type pos = 0;
-  while ((pos = str.find(search, pos)) != string::npos) {
+static void doEscape(std::string& str, const std::string& search, const std::string& repl) {
+  std::string::size_type pos = 0;
+  while ((pos = str.find(search, pos)) != std::string::npos) {
     str.replace(pos, search.size(), repl);
     pos += repl.size();
   }
 }
 
 // Strips one argument from the cmdline and returns it. "surrounding quotes"
 // are removed from the argument if there were any.
-static string getArg(string& cmdline) {
-  string ret;
+static std::string getArg(std::string& cmdline) {
+  std::string ret;
   bool in_quoted = false;
   unsigned int i = 0;
 
@@ -539,15 +538,15 @@ static string getArg(string& cmdline) {
 }
 
 static void parseCommandLine(LPTSTR wincmdline,
-                             string& lang,
-                             string& srcfile,
-                             string& dfile,
-                             string& objfile,
-                             string& prefix,
-                             string& clpath,
-                             string& binpath,
-                             string& rest) {
-  string cmdline(wincmdline);
+                             std::string& lang,
+                             std::string& srcfile,
+                             std::string& dfile,
+                             std::string& objfile,
+                             std::string& prefix,
+                             std::string& clpath,
+                             std::string& binpath,
+                             std::string& rest) {
+  std::string cmdline(wincmdline);
   /* self */ getArg(cmdline);
   lang = getArg(cmdline);
   srcfile = getArg(cmdline);
@@ -559,8 +558,8 @@ static void parseCommandLine(LPTSTR wincmdline,
   rest = trimLeadingSpace(cmdline);
 }
 
-static void outputDepFile(const string& dfile, const string& objfile,
-        vector<string>& incs) {
+static void outputDepFile(const std::string& dfile, const std::string& objfile,
+        std::vector<std::string>& incs) {
 
   if (dfile.empty())
     return;
@@ -575,11 +574,11 @@ static void outputDepFile(const string& dfile, const string& objfile,
   if (!out)
     return;
 
-  string tmp = objfile;
+  std::string tmp = objfile;
   doEscape(tmp, " ", "\\ ");
   fprintf(out, "%s: \\\n", tmp.c_str());
 
-  for (vector<string>::iterator i(incs.begin()); i != incs.end(); ++i) {
+  for (std::vector<std::string>::iterator i(incs.begin()); i != incs.end(); ++i) {
     tmp = *i;
     doEscape(tmp, "\\", "/");
     doEscape(tmp, " ", "\\ ");
@@ -611,12 +610,12 @@ std::string replace(const std::string& str, const std::string& what,
 
 
 
-static int process( const string& srcfilename,
-                    const string& dfile,
-                    const string& objfile,
-                    const string& prefix,
-                    const string& cmd,
-                    const string& dir = "",
+static int process( const std::string& srcfilename,
+                    const std::string& dfile,
+                    const std::string& objfile,
+                    const std::string& prefix,
+                    const std::string& cmd,
+                    const std::string& dir = "",
                     bool quiet = false) {
 
   SubprocessSet subprocs;
@@ -632,17 +631,17 @@ static int process( const string& srcfilename,
   bool success = subproc->Finish() == ExitSuccess;
   int exit_code = subproc->ExitCode();
 
-  string output = subproc->GetOutput();
+  std::string output = subproc->GetOutput();
   delete subproc;
 
   // process the include directives and output everything else
-  stringstream ss(output);
-  string line;
-  vector<string> includes;
+  std::stringstream ss(output);
+  std::string line;
+  std::vector<std::string> includes;
   bool isFirstLine = true; // cl prints always first the source filename
   while (getline(ss, line)) {
     if (startsWith(line, prefix)) {
-      string inc = trimLeadingSpace(line.substr(prefix.size()).c_str());
+      std::string inc = trimLeadingSpace(line.substr(prefix.size()).c_str());
       if (inc[inc.size() - 1] == '\r') // blech, stupid \r\n
         inc = inc.substr(0, inc.size() - 1);
       includes.push_back(inc);
@@ -676,14 +675,14 @@ int main() {
   // subprocesses, so by avoiding argc/argv, the subprocess is called with
   // the same command line verbatim.
 
-  string lang, srcfile, dfile, objfile, prefix, cl, binpath, rest;
+  std::string lang, srcfile, dfile, objfile, prefix, cl, binpath, rest;
   parseCommandLine(GetCommandLine(), lang, srcfile, dfile, objfile,
                                      prefix, cl, binpath, rest);
 
   // needed to suppress filename output of msvc tools
-  string srcfilename;
+  std::string srcfilename;
   std::string::size_type pos = srcfile.rfind("\\");
-  if (pos != string::npos) {
+  if (pos != std::string::npos) {
     srcfilename = srcfile.substr(pos + 1);
   }
 
@@ -695,7 +694,7 @@ int main() {
   } else if (lang == "RC") {
     // "misuse" cl.exe to get headers from .rc files
 
-    string clrest = rest;
+    std::string clrest = rest;
     // rc: /fo x.dir\x.rc.res  ->  cl: /out:x.dir\x.rc.res.dep.obj
     clrest = replace(clrest, "/fo", "/out:");
     clrest = replace(clrest, objfile, objfile + ".dep.obj ");
@@ -705,9 +704,9 @@ int main() {
     cl = "\"" + cl + "\" /P /DRC_INVOKED ";
 
     // call cl in object dir so the .i is generated there
-    string objdir;
+    std::string objdir;
     std::string::size_type pos = objfile.rfind("\\");
-    if (pos != string::npos) {
+    if (pos != std::string::npos) {
       objdir = objfile.substr(0, pos);
     }
 