@@ -12,7 +12,7 @@
 #if defined(_MSC_VER) && _MSC_VER < 1300
 # define _WIN32_WINNT 0x0400 /* for wincrypt.h */
 #endif
-#include "cmSystemTools.h"   
+#include "cmSystemTools.h"
 #include <ctype.h>
 #include <errno.h>
 #include <time.h>
@@ -126,7 +126,7 @@ const char* cmSystemTools::GetWindows9xComspecSubstitute()
   return cmSystemTools::s_Windows9xComspecSubstitute.c_str();
 }
 
-void (*cmSystemTools::s_ErrorCallback)(const char*, const char*, 
+void (*cmSystemTools::s_ErrorCallback)(const char*, const char*,
                                        bool&, void*);
 void (*cmSystemTools::s_StdoutCallback)(const char*, int len, void*);
 void* cmSystemTools::s_ErrorCallbackClientData = 0;
@@ -144,7 +144,7 @@ void cmSystemTools::ExpandRegistryValues(std::string& source, KeyWOW64 view)
   // a close square-bracket.  The ']' character must be the first in the
   // list of characters inside the [^...] block of the expression.
   cmsys::RegularExpression regEntry("\\[(HKEY[^]]*)\\]");
-  
+
   // check for black line or comment
   while (regEntry.find(source))
     {
@@ -237,7 +237,7 @@ void cmSystemTools::Stdout(const char* s)
 {
   if(s_StdoutCallback)
     {
-    (*s_StdoutCallback)(s, static_cast<int>(strlen(s)), 
+    (*s_StdoutCallback)(s, static_cast<int>(strlen(s)),
                         s_StdoutCallbackClientData);
     }
   else
@@ -268,15 +268,15 @@ void cmSystemTools::Message(const char* m1, const char *title)
     }
   if(s_ErrorCallback)
     {
-    (*s_ErrorCallback)(m1, title, s_DisableMessages, 
+    (*s_ErrorCallback)(m1, title, s_DisableMessages,
                        s_ErrorCallbackClientData);
     return;
     }
   else
     {
     std::cerr << m1 << std::endl << std::flush;
     }
-  
+
 }
 
 
@@ -311,7 +311,7 @@ bool cmSystemTools::IsOn(const char* val)
     return false;
     }
   std::basic_string<char> v = val;
-  
+
   for(std::basic_string<char>::iterator c = v.begin();
       c != v.end(); c++)
     {
@@ -344,13 +344,13 @@ bool cmSystemTools::IsOff(const char* val)
     return true;
     }
   std::basic_string<char> v = val;
-  
+
   for(std::basic_string<char>::iterator c = v.begin();
       c != v.end(); c++)
     {
     *c = static_cast<char>(toupper(*c));
     }
-  return (v == "OFF" || v == "0" || v == "NO" || v == "FALSE" || 
+  return (v == "OFF" || v == "0" || v == "NO" || v == "FALSE" ||
           v == "N" || cmSystemTools::IsNOTFOUND(v.c_str()) || v == "IGNORE");
 }
 
@@ -569,14 +569,14 @@ std::vector<cmStdString> cmSystemTools::ParseArguments(const char* command)
       args.push_back(arg);
       }
     }
-  
+
   return args;
 }
 
 
 bool cmSystemTools::RunSingleCommand(std::vector<cmStdString>const& command,
                                      std::string* output ,
-                                     int* retVal , const char* dir , 
+                                     int* retVal , const char* dir ,
                                      bool verbose ,
                                      double timeout )
 {
@@ -601,7 +601,7 @@ bool cmSystemTools::RunSingleCommand(std::vector<cmStdString>const& command,
     }
   cmsysProcess_SetTimeout(cp, timeout);
   cmsysProcess_Execute(cp);
-  
+
   std::vector<char> tempOutput;
   char* data;
   int length;
@@ -632,13 +632,13 @@ bool cmSystemTools::RunSingleCommand(std::vector<cmStdString>const& command,
       }
     }
     }
-  
+
   cmsysProcess_WaitForExit(cp, 0);
   if ( output && tempOutput.begin() != tempOutput.end())
     {
     output->append(&*tempOutput.begin(), tempOutput.size());
     }
-  
+
   bool result = true;
   if(cmsysProcess_GetState(cp) == cmsysProcess_State_Exited)
     {
@@ -693,15 +693,15 @@ bool cmSystemTools::RunSingleCommand(std::vector<cmStdString>const& command,
       }
     result = false;
     }
-  
+
   cmsysProcess_Delete(cp);
   return result;
 }
 
 bool cmSystemTools::RunSingleCommand(
-  const char* command, 
+  const char* command,
   std::string* output,
-  int *retVal, 
+  int *retVal,
   const char* dir,
   bool verbose,
   double timeout)
@@ -717,17 +717,17 @@ bool cmSystemTools::RunSingleCommand(
     {
     return false;
     }
-  return cmSystemTools::RunSingleCommand(args, output,retVal, 
+  return cmSystemTools::RunSingleCommand(args, output,retVal,
                                          dir, verbose, timeout);
 }
-bool cmSystemTools::RunCommand(const char* command, 
+bool cmSystemTools::RunCommand(const char* command,
                                std::string& output,
                                const char* dir,
                                bool verbose,
                                int timeout)
 {
   int dummy;
-  return cmSystemTools::RunCommand(command, output, dummy, 
+  return cmSystemTools::RunCommand(command, output, dummy,
                                    dir, verbose, timeout);
 }
 
@@ -742,11 +742,11 @@ bool RunCommandViaWin32(const char* command,
                         int timeout)
 {
 #if defined(__BORLANDC__)
-  return 
+  return
     cmWin32ProcessExecution::
-    BorlandRunCommand(command, dir, output, 
-                      retVal, 
-                      verbose, timeout, 
+    BorlandRunCommand(command, dir, output,
+                      retVal,
+                      verbose, timeout,
                       cmSystemTools::GetRunCommandHideConsole());
 #else // Visual studio
   ::SetLastError(ERROR_SUCCESS);
@@ -760,7 +760,7 @@ bool RunCommandViaWin32(const char* command,
     {
     resProc.SetHideWindows(true);
     }
-  
+
   if ( cmSystemTools::GetWindows9xComspecSubstitute() )
     {
     resProc.SetConsoleSpawn(cmSystemTools::GetWindows9xComspecSubstitute() );
@@ -787,7 +787,7 @@ bool RunCommandViaSystem(const char* command,
                          std::string& output,
                          int& retVal,
                          bool verbose)
-{  
+{
   std::cout << "@@ " << command << std::endl;
 
   std::string commandInDir;
@@ -987,9 +987,9 @@ bool RunCommandViaPopen(const char* command,
 
 // run a command unix uses popen (easy)
 // windows uses system and ShortPath
-bool cmSystemTools::RunCommand(const char* command, 
+bool cmSystemTools::RunCommand(const char* command,
                                std::string& output,
-                               int &retVal, 
+                               int &retVal,
                                const char* dir,
                                bool verbose,
                                int timeout)
@@ -998,7 +998,7 @@ bool cmSystemTools::RunCommand(const char* command,
     {
     verbose = false;
     }
-  
+
 #if defined(WIN32) && !defined(__CYGWIN__)
   // if the command does not start with a quote, then
   // try to find the program, and if the program can not be
@@ -1017,9 +1017,9 @@ bool cmSystemTools::RunCommand(const char* command,
           {
           break;
           }
-        }      
+        }
       }
-    // if there are more than two double quotes use 
+    // if there are more than two double quotes use
     // GetShortPathName, the cmd.exe program in windows which
     // is used by system fails to execute if there are more than
     // one set of quotes in the arguments
@@ -1043,16 +1043,16 @@ bool cmSystemTools::RunCommand(const char* command,
         shortCmd += " ";
         shortCmd += args;
 
-        //return RunCommandViaSystem(shortCmd.c_str(), dir, 
+        //return RunCommandViaSystem(shortCmd.c_str(), dir,
         //                           output, retVal, verbose);
-        //return WindowsRunCommand(shortCmd.c_str(), dir, 
+        //return WindowsRunCommand(shortCmd.c_str(), dir,
         //output, retVal, verbose);
-        return RunCommandViaWin32(shortCmd.c_str(), dir, 
+        return RunCommandViaWin32(shortCmd.c_str(), dir,
                                   output, retVal, verbose, timeout);
         }
       else
         {
-        cmSystemTools::Error("Could not parse command line with quotes ", 
+        cmSystemTools::Error("Could not parse command line with quotes ",
                              command);
         }
       }
@@ -1116,7 +1116,7 @@ bool cmSystemTools::cmCopyFile(const char* source, const char* destination)
   return Superclass::CopyFileAlways(source, destination);
 }
 
-bool cmSystemTools::CopyFileIfDifferent(const char* source, 
+bool cmSystemTools::CopyFileIfDifferent(const char* source,
   const char* destination)
 {
   return Superclass::CopyFileIfDifferent(source, destination);
@@ -1247,7 +1247,7 @@ void cmSystemTools::Glob(const char *directory, const char *regexp,
 {
   cmsys::Directory d;
   cmsys::RegularExpression reg(regexp);
-  
+
   if (d.Load(directory))
     {
     size_t numf;
@@ -1300,7 +1300,7 @@ void cmSystemTools::GlobDirs(const char *fullPath,
 }
 
 
-void cmSystemTools::ExpandList(std::vector<std::string> const& arguments, 
+void cmSystemTools::ExpandList(std::vector<std::string> const& arguments,
                                std::vector<std::string>& newargs)
 {
   std::vector<std::string>::const_iterator i;
@@ -1399,8 +1399,8 @@ void cmSystemTools::ExpandListArgument(const std::string& arg,
     }
 }
 
-bool cmSystemTools::SimpleGlob(const cmStdString& glob, 
-                               std::vector<cmStdString>& files, 
+bool cmSystemTools::SimpleGlob(const cmStdString& glob,
+                               std::vector<cmStdString>& files,
                                int type /* = 0 */)
 {
   files.clear();
@@ -1440,8 +1440,8 @@ bool cmSystemTools::SimpleGlob(const cmStdString& glob,
           {
           continue;
           }
-        if ( sfname.size() >= ppath.size() && 
-             sfname.substr(0, ppath.size()) == 
+        if ( sfname.size() >= ppath.size() &&
+             sfname.substr(0, ppath.size()) ==
              ppath )
           {
           files.push_back(fname);
@@ -1461,10 +1461,10 @@ cmSystemTools::FileFormat cmSystemTools::GetFileFormat(const char* cext)
     }
   //std::string ext = cmSystemTools::LowerCase(cext);
   std::string ext = cext;
-  if ( ext == "c" || ext == ".c" || 
-       ext == "m" || ext == ".m" 
+  if ( ext == "c" || ext == ".c" ||
+       ext == "m" || ext == ".m"
     ) { return cmSystemTools::C_FILE_FORMAT; }
-  if ( 
+  if (
     ext == "C" || ext == ".C" ||
     ext == "M" || ext == ".M" ||
     ext == "c++" || ext == ".c++" ||
@@ -1473,22 +1473,22 @@ cmSystemTools::FileFormat cmSystemTools::GetFileFormat(const char* cext)
     ext == "cxx" || ext == ".cxx" ||
     ext == "mm" || ext == ".mm"
     ) { return cmSystemTools::CXX_FILE_FORMAT; }
-  if ( 
+  if (
     ext == "f" || ext == ".f" ||
     ext == "F" || ext == ".F" ||
     ext == "f77" || ext == ".f77" ||
     ext == "f90" || ext == ".f90" ||
     ext == "for" || ext == ".for" ||
-    ext == "f95" || ext == ".f95" 
+    ext == "f95" || ext == ".f95"
     ) { return cmSystemTools::FORTRAN_FILE_FORMAT; }
   if ( ext == "java" || ext == ".java" )
     { return cmSystemTools::JAVA_FILE_FORMAT; }
-  if ( 
-    ext == "H" || ext == ".H" || 
-    ext == "h" || ext == ".h" || 
+  if (
+    ext == "H" || ext == ".H" ||
+    ext == "h" || ext == ".h" ||
     ext == "h++" || ext == ".h++" ||
-    ext == "hm" || ext == ".hm" || 
-    ext == "hpp" || ext == ".hpp" || 
+    ext == "hm" || ext == ".hm" ||
+    ext == "hpp" || ext == ".hpp" ||
     ext == "hxx" || ext == ".hxx" ||
     ext == "in" || ext == ".in" ||
     ext == "txx" || ext == ".txx"
@@ -1501,18 +1501,18 @@ cmSystemTools::FileFormat cmSystemTools::GetFileFormat(const char* cext)
        ext == "a" || ext == ".a")
     { return cmSystemTools::STATIC_LIBRARY_FILE_FORMAT; }
   if ( ext == "o" || ext == ".o" ||
-       ext == "obj" || ext == ".obj") 
+       ext == "obj" || ext == ".obj")
     { return cmSystemTools::OBJECT_FILE_FORMAT; }
 #ifdef __APPLE__
-  if ( ext == "dylib" || ext == ".dylib" ) 
+  if ( ext == "dylib" || ext == ".dylib" )
     { return cmSystemTools::SHARED_LIBRARY_FILE_FORMAT; }
-  if ( ext == "so" || ext == ".so" || 
-       ext == "bundle" || ext == ".bundle" ) 
-    { return cmSystemTools::MODULE_FILE_FORMAT; } 
+  if ( ext == "so" || ext == ".so" ||
+       ext == "bundle" || ext == ".bundle" )
+    { return cmSystemTools::MODULE_FILE_FORMAT; }
 #else // __APPLE__
-  if ( ext == "so" || ext == ".so" || 
-       ext == "sl" || ext == ".sl" || 
-       ext == "dll" || ext == ".dll" ) 
+  if ( ext == "so" || ext == ".so" ||
+       ext == "sl" || ext == ".sl" ||
+       ext == "dll" || ext == ".dll" )
     { return cmSystemTools::SHARED_LIBRARY_FILE_FORMAT; }
 #endif // __APPLE__
   return cmSystemTools::UNKNOWN_FILE_FORMAT;
@@ -1708,7 +1708,7 @@ bool cmSystemTools::IsPathToFramework(const char* path)
   return false;
 }
 
-bool cmSystemTools::CreateTar(const char* outFileName, 
+bool cmSystemTools::CreateTar(const char* outFileName,
                               const std::vector<cmStdString>& files,
                               bool gzip, bool bzip2, bool verbose)
 {
@@ -1773,7 +1773,7 @@ namespace{
   static time_t          now;
   size_t u_width = 6;
   size_t gs_width = 13;
-  
+
   /*
    * We avoid collecting the entire list in memory at once by
    * listing things as we see them.  However, that also means we can't
@@ -1788,7 +1788,7 @@ namespace{
   fprintf(out, "%s %d ",
           archive_entry_strmode(entry),
           archive_entry_nlink(entry));
-  
+
   /* Use uname if it's present, else uid. */
   p = archive_entry_uname(entry);
   if ((p == NULL) || (*p == '\0'))
@@ -1809,28 +1809,28 @@ namespace{
     {
     fprintf(out, "%s", p);
     w = strlen(p);
-    } 
+    }
   else
     {
     sprintf(tmp, "%lu",
             (unsigned long)archive_entry_gid(entry));
     w = strlen(tmp);
     fprintf(out, "%s", tmp);
     }
-  
+
   /*
    * Print device number or file size, right-aligned so as to make
    * total width of group and devnum/filesize fields be gs_width.
    * If gs_width is too small, grow it.
    */
   if (archive_entry_filetype(entry) == AE_IFCHR
-      || archive_entry_filetype(entry) == AE_IFBLK) 
+      || archive_entry_filetype(entry) == AE_IFBLK)
     {
     sprintf(tmp, "%lu,%lu",
             (unsigned long)archive_entry_rdevmajor(entry),
             (unsigned long)archive_entry_rdevminor(entry));
     }
-  else 
+  else
     {
     /*
      * Note the use of platform-dependent macros to format
@@ -1851,7 +1851,7 @@ namespace{
 #define HALF_YEAR (time_t)365 * 86400 / 2
 #if defined(_WIN32) && !defined(__CYGWIN__)
   /* Windows' strftime function does not support %e format. */
-#define DAY_FMT  "%d"  
+#define DAY_FMT  "%d"
 #else
 #define DAY_FMT  "%e"  /* Day number without leading zeros */
 #endif
@@ -1881,15 +1881,15 @@ namespace{
 #ifdef __BORLANDC__
 # pragma warn -8066 /* unreachable code */
 #endif
-  
+
 long copy_data(struct archive *ar, struct archive *aw)
 {
   long r;
   const void *buff;
   size_t size;
   off_t offset;
-  
-  for (;;) 
+
+  for (;;)
     {
     r = archive_read_data_block(ar, &buff, &size, &offset);
     if (r == ARCHIVE_EOF)
@@ -1901,7 +1901,7 @@ long copy_data(struct archive *ar, struct archive *aw)
       return (r);
       }
     r = archive_write_data_block(aw, buff, size, offset);
-    if (r != ARCHIVE_OK) 
+    if (r != ARCHIVE_OK)
       {
       cmSystemTools::Message("archive_write_data_block()",
                              archive_error_string(aw));
@@ -1911,7 +1911,7 @@ long copy_data(struct archive *ar, struct archive *aw)
   return r;
 }
 
-bool extract_tar(const char* outFileName, bool verbose, 
+bool extract_tar(const char* outFileName, bool verbose,
                  bool extract)
 {
   struct archive* a = archive_read_new();
@@ -1921,12 +1921,12 @@ bool extract_tar(const char* outFileName, bool verbose,
   struct archive_entry *entry;
   int r = archive_read_open_file(a, outFileName, 10240);
   if(r)
-    { 
+    {
     cmSystemTools::Error("Problem with archive_read_open_file(): ",
                          archive_error_string(a));
     return false;
     }
-  for (;;) 
+  for (;;)
     {
     r = archive_read_next_header(a, &entry);
     if (r == ARCHIVE_EOF)
@@ -1969,7 +1969,7 @@ bool extract_tar(const char* outFileName, bool verbose,
         cmSystemTools::Error("Current file:",
                              archive_entry_pathname(entry));
         }
-      else 
+      else
         {
         copy_data(a, ext);
         r = archive_write_finish_entry(ext);
@@ -1991,9 +1991,9 @@ bool extract_tar(const char* outFileName, bool verbose,
 
 }
 }
-#endif 
+#endif
 
-bool cmSystemTools::ExtractTar(const char* outFileName, 
+bool cmSystemTools::ExtractTar(const char* outFileName,
                                bool , bool verbose)
 {
 #if defined(CMAKE_BUILD_WITH_CMAKE)
@@ -2005,7 +2005,7 @@ bool cmSystemTools::ExtractTar(const char* outFileName,
 #endif
 }
 
-bool cmSystemTools::ListTar(const char* outFileName, 
+bool cmSystemTools::ListTar(const char* outFileName,
                             bool ,
                             bool verbose)
 {
@@ -2121,8 +2121,8 @@ int cmSystemTools::WaitForLine(cmsysProcess* process, std::string& line,
 }
 
 void cmSystemTools::DoNotInheritStdPipes()
-{   
-#ifdef _WIN32  
+{
+#ifdef _WIN32
   // Check to see if we are attached to a console
   // if so, then do not stop the inherited pipes
   // or stdout and stderr will not show up in dos