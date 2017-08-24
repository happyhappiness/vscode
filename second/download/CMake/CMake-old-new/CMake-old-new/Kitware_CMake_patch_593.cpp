@@ -290,7 +290,8 @@ void cmSystemTools::Message(const char* m1, const char *title)
     }
   if(s_ErrorCallback)
     {
-    (*s_ErrorCallback)(m1, title, s_DisableMessages, s_ErrorCallbackClientData);
+    (*s_ErrorCallback)(m1, title, s_DisableMessages, 
+                       s_ErrorCallbackClientData);
     return;
     }
   else
@@ -368,8 +369,10 @@ std::vector<cmStdString> cmSystemTools::ParseArguments(const char* command)
   bool win_path = false;
 
   if ( command[0] != '/' && command[1] == ':' && command[2] == '\\' ||
-       command[0] == '\"' && command[1] != '/' && command[2] == ':' && command[3] == '\\' || 
-       command[0] == '\'' && command[1] != '/' && command[2] == ':' && command[3] == '\\' || 
+       command[0] == '\"' && command[1] != '/' && command[2] == ':' 
+       && command[3] == '\\' || 
+       command[0] == '\'' && command[1] != '/' && command[2] == ':' 
+       && command[3] == '\\' || 
        command[0] == '\\' && command[1] == '\\')
     {
     win_path = true;
@@ -599,10 +602,12 @@ bool RunCommandViaWin32(const char* command,
                         int timeout)
 {
 #if defined(__BORLANDC__)
-  return cmWin32ProcessExecution::BorlandRunCommand(command, dir, output, 
-                                                    retVal, 
-                                                    verbose, timeout, 
-                                                    cmSystemTools::GetRunCommandHideConsole());
+  return 
+    cmWin32ProcessExecution::
+    BorlandRunCommand(command, dir, output, 
+                      retVal, 
+                      verbose, timeout, 
+                      cmSystemTools::GetRunCommandHideConsole());
 #else // Visual studio
   ::SetLastError(ERROR_SUCCESS);
   if ( ! command )
@@ -1137,7 +1142,8 @@ cmSystemTools::FileFormat cmSystemTools::GetFileFormat(const char* cext)
     ext == "for" || ext == ".for" ||
     ext == "f95" || ext == ".f95" 
     ) { return cmSystemTools::FORTRAN_FILE_FORMAT; }
-  if ( ext == "java" || ext == ".java" ) { return cmSystemTools::JAVA_FILE_FORMAT; }
+  if ( ext == "java" || ext == ".java" )
+    { return cmSystemTools::JAVA_FILE_FORMAT; }
   if ( 
     ext == "H" || ext == ".H" || 
     ext == "h" || ext == ".h" || 
@@ -1148,12 +1154,16 @@ cmSystemTools::FileFormat cmSystemTools::GetFileFormat(const char* cext)
     ext == "in" || ext == ".in" ||
     ext == "txx" || ext == ".txx"
     ) { return cmSystemTools::HEADER_FILE_FORMAT; }
-  if ( ext == "rc" || ext == ".rc" ) { return cmSystemTools::RESOURCE_FILE_FORMAT; }
-  if ( ext == "def" || ext == ".def" ) { return cmSystemTools::DEFINITION_FILE_FORMAT; }
+  if ( ext == "rc" || ext == ".rc" )
+    { return cmSystemTools::RESOURCE_FILE_FORMAT; }
+  if ( ext == "def" || ext == ".def" )
+    { return cmSystemTools::DEFINITION_FILE_FORMAT; }
   if ( ext == "lib" || ext == ".lib" ||
-       ext == "a" || ext == ".a") { return cmSystemTools::STATIC_LIBRARY_FILE_FORMAT; }
+       ext == "a" || ext == ".a")
+    { return cmSystemTools::STATIC_LIBRARY_FILE_FORMAT; }
   if ( ext == "o" || ext == ".o" ||
-       ext == "obj" || ext == ".obj") { return cmSystemTools::OBJECT_FILE_FORMAT; }
+       ext == "obj" || ext == ".obj") 
+    { return cmSystemTools::OBJECT_FILE_FORMAT; }
 #ifdef __APPLE__
   if ( ext == "dylib" || ext == ".dylib" ) 
     { return cmSystemTools::SHARED_LIBRARY_FILE_FORMAT; }
@@ -1231,11 +1241,13 @@ std::string cmSystemTools::RelativePath(const char* local, const char* remote)
 {
   if(!cmSystemTools::FileIsFullPath(local))
     {
-    cmSystemTools::Error("RelativePath must be passed a full path to local: ", local);
+    cmSystemTools::Error("RelativePath must be passed a full path to local: ",
+                         local);
     }
   if(!cmSystemTools::FileIsFullPath(remote))
     {
-    cmSystemTools::Error("RelativePath must be passed a full path to remote: ", remote);
+    cmSystemTools::Error("RelativePath must be passed a full path to remote: ",
+                         remote);
     }
   return cmsys::SystemTools::RelativePath(local, remote);
 }
@@ -1288,7 +1300,8 @@ std::string cmSystemTools::MakeXMLSafe(const char* str)
   for ( ;*pos; ++pos)
     {
     char ch = *pos;
-    if ( (ch > 126 || ch < 32) && ch != 9  && ch != 10 && ch != 13 && ch != '\r' )
+    if ( (ch > 126 || ch < 32) && ch != 9  && ch != 10 && ch != 13 
+         && ch != '\r' )
       {
       char buffer[33];
       sprintf(buffer, "&lt;%d&gt;", (int)ch);
@@ -1349,13 +1362,16 @@ struct cmSystemToolsGZStruct
 };
 
 extern "C" {
-  int cmSystemToolsGZStructOpen(void* call_data, const char *pathname, int oflags, mode_t mode);
+  int cmSystemToolsGZStructOpen(void* call_data, const char *pathname, 
+                                int oflags, mode_t mode);
   int cmSystemToolsGZStructClose(void* call_data);
   ssize_t cmSystemToolsGZStructRead(void* call_data, void* buf, size_t count);
-  ssize_t cmSystemToolsGZStructWrite(void* call_data, const void* buf, size_t count);
+  ssize_t cmSystemToolsGZStructWrite(void* call_data, const void* buf, 
+                                     size_t count);
 }
 
-int cmSystemToolsGZStructOpen(void* call_data, const char *pathname, int oflags, mode_t mode)
+int cmSystemToolsGZStructOpen(void* call_data, const char *pathname, 
+                              int oflags, mode_t mode)
 {
   const char *gzoflags;
   int fd;
@@ -1411,15 +1427,18 @@ ssize_t cmSystemToolsGZStructRead(void* call_data, void* buf, size_t count)
   return cm_zlib_gzread(gzf->GZFile, buf, count);
 }
 
-ssize_t cmSystemToolsGZStructWrite(void* call_data, const void* buf, size_t count)
+ssize_t cmSystemToolsGZStructWrite(void* call_data, const void* buf,
+                                   size_t count)
 {
   cmSystemToolsGZStruct* gzf = static_cast<cmSystemToolsGZStruct*>(call_data);
   return cm_zlib_gzwrite(gzf->GZFile, (void*)buf, count);
 }
 
 #endif
 
-bool cmSystemTools::CreateTar(const char* outFileName, const std::vector<cmStdString>& files, bool gzip, bool verbose)
+bool cmSystemTools::CreateTar(const char* outFileName, 
+                              const std::vector<cmStdString>& files,
+                              bool gzip, bool verbose)
 {
 #if defined(CMAKE_BUILD_WITH_CMAKE)
   TAR *t;
@@ -1459,7 +1478,8 @@ bool cmSystemTools::CreateTar(const char* outFileName, const std::vector<cmStdSt
     if (tar_append_tree(t, buf, pathname) != 0)
       {
       cmOStringStream ostr;
-      ostr << "Problem with tar_append_tree(\"" << buf << "\", \"" << pathname << "\"): "
+      ostr << "Problem with tar_append_tree(\"" << buf << "\", \"" 
+           << pathname << "\"): "
         << strerror(errno);
       cmSystemTools::Error(ostr.str().c_str());
       tar_close(t);
@@ -1485,7 +1505,9 @@ bool cmSystemTools::CreateTar(const char* outFileName, const std::vector<cmStdSt
 #endif
 }
 
-bool cmSystemTools::ExtractTar(const char* outFileName, const std::vector<cmStdString>& files, bool gzip, bool verbose)
+bool cmSystemTools::ExtractTar(const char* outFileName, 
+                               const std::vector<cmStdString>& files, 
+                               bool gzip, bool verbose)
 {
   (void)files;
 #if defined(CMAKE_BUILD_WITH_CMAKE)
@@ -1535,7 +1557,9 @@ bool cmSystemTools::ExtractTar(const char* outFileName, const std::vector<cmStdS
 #endif
 }
 
-bool cmSystemTools::ListTar(const char* outFileName, std::vector<cmStdString>& files, bool gzip, bool verbose)
+bool cmSystemTools::ListTar(const char* outFileName, 
+                            std::vector<cmStdString>& files, bool gzip,
+                            bool verbose)
 {
 #if defined(CMAKE_BUILD_WITH_CMAKE)
   TAR *t;
@@ -1586,7 +1610,8 @@ bool cmSystemTools::ListTar(const char* outFileName, std::vector<cmStdString>& f
 #endif
     if (TH_ISREG(t) && tar_skip_regfile(t) != 0)
       {
-      cmSystemTools::Error("Problem with tar_skip_regfile(): ", strerror(errno));
+      cmSystemTools::Error("Problem with tar_skip_regfile(): ", 
+                           strerror(errno));
       return false;
       }
   }