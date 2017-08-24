@@ -128,7 +128,7 @@ class SystemToolsHack
 #include <io.h>
 #include <direct.h>
 #define _unlink unlink
-#endif 
+#endif
 
 /* The maximum length of a file name.  */
 #if defined(PATH_MAX)
@@ -168,9 +168,9 @@ static inline char *realpath(const char *path, char *resolved_path)
   snprintf(resolved_path, maxlen, "%s", path);
   BPath normalized(resolved_path, NULL, true);
   const char *resolved = normalized.Path();
-  if (resolved != NULL)   // NULL == No such file. 
+  if (resolved != NULL)   // NULL == No such file.
     {
-    if (snprintf(resolved_path, maxlen, "%s", resolved) < maxlen) 
+    if (snprintf(resolved_path, maxlen, "%s", resolved) < maxlen)
       {
       return resolved_path;
       }
@@ -179,7 +179,7 @@ static inline char *realpath(const char *path, char *resolved_path)
 }
 #endif
 
-#if defined(_WIN32) && (defined(_MSC_VER) || defined(__WATCOMC__) || defined(__BORLANDC__) || defined(__MINGW32__)) 
+#if defined(_WIN32) && (defined(_MSC_VER) || defined(__WATCOMC__) || defined(__BORLANDC__) || defined(__MINGW32__))
 inline int Mkdir(const char* dir)
 {
   return _mkdir(dir);
@@ -300,7 +300,7 @@ double SystemTools::GetTime(void)
 #endif
 }
 
-class SystemToolsTranslationMap : 
+class SystemToolsTranslationMap :
     public kwsys_stl::map<kwsys_stl::string,kwsys_stl::string>
 {
 };
@@ -392,7 +392,7 @@ kwsysDeletingCharVector::~kwsysDeletingCharVector()
 #endif
 }
 bool SystemTools::PutEnv(const char* value)
-{ 
+{
   static kwsysDeletingCharVector localEnvironment;
   char* envVar = new char[strlen(value)+1];
   strcpy(envVar, value);
@@ -414,7 +414,7 @@ const char* SystemTools::GetExecutableExtension()
   return ".exe";
 #else
   return "";
-#endif  
+#endif
 }
 
 
@@ -482,7 +482,7 @@ void SystemTools::ReplaceString(kwsys_stl::string& source,
 {
   const char *src = source.c_str();
   char *searchPos = const_cast<char *>(strstr(src,replace));
-  
+
   // get out quick if string is not found
   if (!searchPos)
     {
@@ -499,7 +499,7 @@ void SystemTools::ReplaceString(kwsys_stl::string& source,
   char *orig = strdup(src);
   char *currentPos = orig;
   searchPos = searchPos - src + orig;
-  
+
   // initialize the result
   source.erase(source.begin(),source.end());
   do
@@ -551,7 +551,7 @@ static DWORD SystemToolsMakeRegistryMode(DWORD mode,
 #endif
 
 // Read a registry value.
-// Example : 
+// Example :
 //      HKEY_LOCAL_MACHINE\SOFTWARE\Python\PythonCore\2.1\InstallPath
 //      =>  will return the data of the "default" value of the key
 //      HKEY_LOCAL_MACHINE\SOFTWARE\Scriptics\Tcl\8.4;Root
@@ -580,7 +580,7 @@ bool SystemTools::ReadRegistryValue(const char *key, kwsys_stl::string &value,
 
   second = primary.substr(start+1, valuenamepos-start-1);
   primary = primary.substr(0, start);
-  
+
   HKEY primaryKey = HKEY_CURRENT_USER;
   if (primary == "HKEY_CURRENT_USER")
     {
@@ -602,11 +602,11 @@ bool SystemTools::ReadRegistryValue(const char *key, kwsys_stl::string &value,
     {
     primaryKey = HKEY_USERS;
     }
-  
+
   HKEY hKey;
-  if(RegOpenKeyEx(primaryKey, 
-                  second.c_str(), 
-                  0, 
+  if(RegOpenKeyEx(primaryKey,
+                  second.c_str(),
+                  0,
                   SystemToolsMakeRegistryMode(KEY_READ, view),
                   &hKey) != ERROR_SUCCESS)
     {
@@ -617,11 +617,11 @@ bool SystemTools::ReadRegistryValue(const char *key, kwsys_stl::string &value,
     DWORD dwType, dwSize;
     dwSize = 1023;
     char data[1024];
-    if(RegQueryValueEx(hKey, 
-                       (LPTSTR)valuename.c_str(), 
-                       NULL, 
-                       &dwType, 
-                       (BYTE *)data, 
+    if(RegQueryValueEx(hKey,
+                       (LPTSTR)valuename.c_str(),
+                       NULL,
+                       &dwType,
+                       (BYTE *)data,
                        &dwSize) == ERROR_SUCCESS)
       {
       if (dwType == REG_SZ)
@@ -656,7 +656,7 @@ bool SystemTools::ReadRegistryValue(const char *, kwsys_stl::string &,
 
 
 // Write a registry value.
-// Example : 
+// Example :
 //      HKEY_LOCAL_MACHINE\SOFTWARE\Python\PythonCore\2.1\InstallPath
 //      =>  will set the data of the "default" value of the key
 //      HKEY_LOCAL_MACHINE\SOFTWARE\Scriptics\Tcl\8.4;Root
@@ -669,7 +669,7 @@ bool SystemTools::WriteRegistryValue(const char *key, const char *value,
   kwsys_stl::string primary = key;
   kwsys_stl::string second;
   kwsys_stl::string valuename;
- 
+
   size_t start = primary.find("\\");
   if (start == kwsys_stl::string::npos)
     {
@@ -684,7 +684,7 @@ bool SystemTools::WriteRegistryValue(const char *key, const char *value,
 
   second = primary.substr(start+1, valuenamepos-start-1);
   primary = primary.substr(0, start);
-  
+
   HKEY primaryKey = HKEY_CURRENT_USER;
   if (primary == "HKEY_CURRENT_USER")
     {
@@ -706,13 +706,13 @@ bool SystemTools::WriteRegistryValue(const char *key, const char *value,
     {
     primaryKey = HKEY_USERS;
     }
-  
+
   HKEY hKey;
   DWORD dwDummy;
   char lpClass[] = "";
-  if(RegCreateKeyEx(primaryKey, 
-                    second.c_str(), 
-                    0, 
+  if(RegCreateKeyEx(primaryKey,
+                    second.c_str(),
+                    0,
                     lpClass,
                     REG_OPTION_NON_VOLATILE,
                     SystemToolsMakeRegistryMode(KEY_WRITE, view),
@@ -723,11 +723,11 @@ bool SystemTools::WriteRegistryValue(const char *key, const char *value,
     return false;
     }
 
-  if(RegSetValueEx(hKey, 
-                   (LPTSTR)valuename.c_str(), 
-                   0, 
-                   REG_SZ, 
-                   (CONST BYTE *)value, 
+  if(RegSetValueEx(hKey,
+                   (LPTSTR)valuename.c_str(),
+                   0,
+                   REG_SZ,
+                   (CONST BYTE *)value,
                    (DWORD)(strlen(value) + 1)) == ERROR_SUCCESS)
     {
     return true;
@@ -742,7 +742,7 @@ bool SystemTools::WriteRegistryValue(const char *, const char *, KeyWOW64)
 #endif
 
 // Delete a registry value.
-// Example : 
+// Example :
 //      HKEY_LOCAL_MACHINE\SOFTWARE\Python\PythonCore\2.1\InstallPath
 //      =>  will delete the data of the "default" value of the key
 //      HKEY_LOCAL_MACHINE\SOFTWARE\Scriptics\Tcl\8.4;Root
@@ -754,7 +754,7 @@ bool SystemTools::DeleteRegistryValue(const char *key, KeyWOW64 view)
   kwsys_stl::string primary = key;
   kwsys_stl::string second;
   kwsys_stl::string valuename;
- 
+
   size_t start = primary.find("\\");
   if (start == kwsys_stl::string::npos)
     {
@@ -769,7 +769,7 @@ bool SystemTools::DeleteRegistryValue(const char *key, KeyWOW64 view)
 
   second = primary.substr(start+1, valuenamepos-start-1);
   primary = primary.substr(0, start);
-  
+
   HKEY primaryKey = HKEY_CURRENT_USER;
   if (primary == "HKEY_CURRENT_USER")
     {
@@ -791,19 +791,19 @@ bool SystemTools::DeleteRegistryValue(const char *key, KeyWOW64 view)
     {
     primaryKey = HKEY_USERS;
     }
-  
+
   HKEY hKey;
-  if(RegOpenKeyEx(primaryKey, 
-                  second.c_str(), 
-                  0, 
+  if(RegOpenKeyEx(primaryKey,
+                  second.c_str(),
+                  0,
                   SystemToolsMakeRegistryMode(KEY_WRITE, view),
                   &hKey) != ERROR_SUCCESS)
     {
     return false;
     }
   else
     {
-    if(RegDeleteValue(hKey, 
+    if(RegDeleteValue(hKey,
                       (LPTSTR)valuename.c_str()) == ERROR_SUCCESS)
       {
       RegCloseKey(hKey);
@@ -824,17 +824,17 @@ bool SystemTools::SameFile(const char* file1, const char* file2)
 #ifdef _WIN32
   HANDLE hFile1, hFile2;
 
-  hFile1 = CreateFile( file1, 
-                      GENERIC_READ, 
+  hFile1 = CreateFile( file1,
+                      GENERIC_READ,
                       FILE_SHARE_READ ,
                       NULL,
                       OPEN_EXISTING,
                       FILE_FLAG_BACKUP_SEMANTICS,
                       NULL
     );
-  hFile2 = CreateFile( file2, 
-                      GENERIC_READ, 
-                      FILE_SHARE_READ, 
+  hFile2 = CreateFile( file2,
+                      GENERIC_READ,
+                      FILE_SHARE_READ,
                       NULL,
                       OPEN_EXISTING,
                       FILE_FLAG_BACKUP_SEMANTICS,
@@ -868,10 +868,10 @@ bool SystemTools::SameFile(const char* file1, const char* file2)
     {
     // see if the files are the same file
     // check the device inode and size
-    if(memcmp(&fileStat2.st_dev, &fileStat1.st_dev, sizeof(fileStat1.st_dev)) == 0 && 
+    if(memcmp(&fileStat2.st_dev, &fileStat1.st_dev, sizeof(fileStat1.st_dev)) == 0 &&
        memcmp(&fileStat2.st_ino, &fileStat1.st_ino, sizeof(fileStat1.st_ino)) == 0 &&
-       fileStat2.st_size == fileStat1.st_size 
-      ) 
+       fileStat2.st_size == fileStat1.st_size
+      )
       {
       return true;
       }
@@ -1068,11 +1068,11 @@ kwsys_stl::string SystemTools::CapitalizedWords(const kwsys_stl::string& s)
 #if defined(_MSC_VER) && defined (_MT) && defined (_DEBUG)
     // MS has an assert that will fail if s[i] < 0; setting
     // LC_CTYPE using setlocale() does *not* help. Painful.
-    if ((int)s[i] >= 0 && isalpha(s[i]) && 
+    if ((int)s[i] >= 0 && isalpha(s[i]) &&
         (i == 0 || ((int)s[i - 1] >= 0 && isspace(s[i - 1]))))
 #else
     if (isalpha(s[i]) && (i == 0 || isspace(s[i - 1])))
-#endif        
+#endif
       {
       n[i] = static_cast<kwsys_stl::string::value_type>(toupper(s[i]));
       }
@@ -1089,11 +1089,11 @@ kwsys_stl::string SystemTools::UnCapitalizedWords(const kwsys_stl::string& s)
 #if defined(_MSC_VER) && defined (_MT) && defined (_DEBUG)
     // MS has an assert that will fail if s[i] < 0; setting
     // LC_CTYPE using setlocale() does *not* help. Painful.
-    if ((int)s[i] >= 0 && isalpha(s[i]) && 
+    if ((int)s[i] >= 0 && isalpha(s[i]) &&
         (i == 0 || ((int)s[i - 1] >= 0 && isspace(s[i - 1]))))
 #else
     if (isalpha(s[i]) && (i == 0 || isspace(s[i - 1])))
-#endif        
+#endif
       {
       n[i] = static_cast<kwsys_stl::string::value_type>(tolower(s[i]));
       }
@@ -1171,7 +1171,7 @@ char* SystemTools::AppendStrings(
   return newstr;
 }
 
-// Return a lower case string 
+// Return a lower case string
 kwsys_stl::string SystemTools::LowerCase(const kwsys_stl::string& s)
 {
   kwsys_stl::string n;
@@ -1183,7 +1183,7 @@ kwsys_stl::string SystemTools::LowerCase(const kwsys_stl::string& s)
   return n;
 }
 
-// Return a lower case string 
+// Return a lower case string
 kwsys_stl::string SystemTools::UpperCase(const kwsys_stl::string& s)
 {
   kwsys_stl::string n;
@@ -1313,7 +1313,7 @@ const char* SystemTools::FindLastString(const char* str1, const char* str2)
     {
     return NULL;
     }
-  
+
   size_t len1 = strlen(str1), len2 = strlen(str2);
   if (len1 >= len2)
     {
@@ -1341,8 +1341,8 @@ char* SystemTools::DuplicateString(const char* str)
   return NULL;
 }
 
-// Return a cropped string 
-kwsys_stl::string SystemTools::CropString(const kwsys_stl::string& s, 
+// Return a cropped string
+kwsys_stl::string SystemTools::CropString(const kwsys_stl::string& s,
                                           size_t max_len)
 {
   if (!s.size() || max_len == 0 || max_len >= s.size())
@@ -1386,7 +1386,7 @@ kwsys_stl::vector<kwsys::String> SystemTools::SplitString(const char* p, char se
   if(isPath && path[0] == '/')
     {
     path.erase(path.begin());
-    paths.push_back("/"); 
+    paths.push_back("/");
     }
   kwsys_stl::string::size_type pos1 = 0;
   kwsys_stl::string::size_type pos2 = path.find(sep, pos1+1);
@@ -1395,9 +1395,9 @@ kwsys_stl::vector<kwsys::String> SystemTools::SplitString(const char* p, char se
     paths.push_back(path.substr(pos1, pos2-pos1));
     pos1 = pos2+1;
     pos2 = path.find(sep, pos1+1);
-    } 
+    }
   paths.push_back(path.substr(pos1, pos2-pos1));
-  
+
   return paths;
 }
 
@@ -1411,11 +1411,11 @@ int SystemTools::EstimateFormatLength(const char *format, va_list ap)
 
   // Quick-hack attempt at estimating the length of the string.
   // Should never under-estimate.
-  
+
   // Start with the length of the format string itself.
 
   size_t length = strlen(format);
-  
+
   // Increase the length for every argument in the format.
 
   const char* cur = format;
@@ -1447,32 +1447,32 @@ int SystemTools::EstimateFormatLength(const char *format, va_list ap)
           {
           // Assume the argument contributes no more than 64 characters.
           length += 64;
-            
+
           // Eat the argument.
           static_cast<void>(va_arg(ap, double));
           } break;
           default:
           {
           // Assume the argument contributes no more than 64 characters.
           length += 64;
-            
+
           // Eat the argument.
           static_cast<void>(va_arg(ap, int));
           } break;
           }
         }
-      
+
       // Move past the characters just tested.
       ++cur;
       }
     }
-  
+
   return static_cast<int>(length);
 }
 
 kwsys_stl::string SystemTools::EscapeChars(
-  const char *str, 
-  const char *chars_to_escape, 
+  const char *str,
+  const char *chars_to_escape,
   char escape_char)
 {
   kwsys_stl::string n;
@@ -1529,7 +1529,7 @@ static void ConvertVMSToUnix(kwsys_stl::string& path)
 }
 #endif
 
-// convert windows slashes to unix slashes 
+// convert windows slashes to unix slashes
 void SystemTools::ConvertToUnixSlashes(kwsys_stl::string& path)
 {
   const char* pathCString = path.c_str();
@@ -1596,7 +1596,7 @@ void SystemTools::ConvertToUnixSlashes(kwsys_stl::string& path)
         }
       }
 #endif
-    // remove trailing slash if the path is more than 
+    // remove trailing slash if the path is more than
     // a single /
     pathCString = path.c_str();
     if(path.size() > 1 && *(pathCString+(path.size()-1)) == '/')
@@ -1614,7 +1614,7 @@ void SystemTools::ConvertToUnixSlashes(kwsys_stl::string& path)
 kwsys_stl::string SystemTools::ConvertToUnixOutputPath(const char* path)
 {
   kwsys_stl::string ret = path;
-  
+
   // remove // except at the beginning might be a cygwin drive
   kwsys_stl::string::size_type pos=1;
   while((pos = ret.find("//", pos)) != kwsys_stl::string::npos)
@@ -1652,7 +1652,7 @@ kwsys_stl::string SystemTools::ConvertToOutputPath(const char* path)
 
 // remove double slashes not at the start
 kwsys_stl::string SystemTools::ConvertToWindowsOutputPath(const char* path)
-{  
+{
   kwsys_stl::string ret;
   // make it big enough for all of path and double quotes
   ret.reserve(strlen(path)+3);
@@ -1738,13 +1738,13 @@ bool SystemTools::FilesDiffer(const char* source,
                               const char* destination)
 {
   struct stat statSource;
-  if (stat(source, &statSource) != 0) 
+  if (stat(source, &statSource) != 0)
     {
     return true;
     }
 
   struct stat statDestination;
-  if (stat(destination, &statDestination) != 0) 
+  if (stat(destination, &statDestination) != 0)
     {
     return true;
     }
@@ -1790,7 +1790,7 @@ bool SystemTools::FilesDiffer(const char* source,
       {
       return true;
       }
-    
+
     // If this block differs the file differs.
     if(memcmp(static_cast<const void*>(source_buf),
               static_cast<const void*>(dest_buf),
@@ -1849,7 +1849,7 @@ bool SystemTools::CopyFileAlways(const char* source, const char* destination)
   // Open files
 
 #if defined(_WIN32) || defined(__CYGWIN__)
-  kwsys_ios::ifstream fin(source, 
+  kwsys_ios::ifstream fin(source,
                     kwsys_ios::ios::binary | kwsys_ios::ios::in);
 #else
   kwsys_ios::ifstream fin(source);
@@ -1858,25 +1858,25 @@ bool SystemTools::CopyFileAlways(const char* source, const char* destination)
     {
     return false;
     }
- 
+
   // try and remove the destination file so that read only destination files
   // can be written to.
   // If the remove fails continue so that files in read only directories
   // that do not allow file removal can be modified.
   SystemTools::RemoveFile(destination);
 
 #if defined(_WIN32) || defined(__CYGWIN__)
-  kwsys_ios::ofstream fout(destination, 
+  kwsys_ios::ofstream fout(destination,
                      kwsys_ios::ios::binary | kwsys_ios::ios::out | kwsys_ios::ios::trunc);
 #else
-  kwsys_ios::ofstream fout(destination, 
+  kwsys_ios::ofstream fout(destination,
                      kwsys_ios::ios::out | kwsys_ios::ios::trunc);
 #endif
   if(!fout)
     {
     return false;
     }
-  
+
   // This copy loop is very sensitive on certain platforms with
   // slightly broken stream libraries (like HPUX).  Normally, it is
   // incorrect to not check the error condition on the fin.read()
@@ -1890,12 +1890,12 @@ bool SystemTools::CopyFileAlways(const char* source, const char* destination)
       fout.write(buffer, fin.gcount());
       }
     }
-  
+
   // Make sure the operating system has finished writing the file
   // before closing it.  This will ensure the file is finished before
   // the check below.
   fout.flush();
-  
+
   fin.close();
   fout.close();
 
@@ -1979,7 +1979,7 @@ bool SystemTools::CopyADirectory(const char* source, const char* destination,
 unsigned long SystemTools::FileLength(const char* filename)
 {
   struct stat fs;
-  if (stat(filename, &fs) != 0) 
+  if (stat(filename, &fs) != 0)
     {
       return 0;
     }
@@ -2225,7 +2225,7 @@ ::FindName(const char* name,
 {
   // Add the system search path to our path first
   kwsys_stl::vector<kwsys_stl::string> path;
-  if (!no_system_path) 
+  if (!no_system_path)
     {
     SystemTools::GetPath(path, "CMAKE_FILE_PATH");
     SystemTools::GetPath(path);
@@ -2340,7 +2340,7 @@ kwsys_stl::string SystemTools::FindProgram(
   // first try with extensions if the os supports them
   if(extensions.size())
     {
-    for(kwsys_stl::vector<kwsys_stl::string>::iterator i = 
+    for(kwsys_stl::vector<kwsys_stl::string>::iterator i =
           extensions.begin(); i != extensions.end(); ++i)
       {
       tryPath = name;
@@ -2368,7 +2368,7 @@ kwsys_stl::string SystemTools::FindProgram(
     }
   // now add the additional paths
   {
-  for(kwsys_stl::vector<kwsys_stl::string>::const_iterator i = 
+  for(kwsys_stl::vector<kwsys_stl::string>::const_iterator i =
         userPaths.begin();  i != userPaths.end(); ++i)
     {
     path.push_back(*i);
@@ -2397,7 +2397,7 @@ kwsys_stl::string SystemTools::FindProgram(
     // first try with extensions
     if(extensions.size())
       {
-      for(kwsys_stl::vector<kwsys_stl::string>::iterator ext 
+      for(kwsys_stl::vector<kwsys_stl::string>::iterator ext
             = extensions.begin(); ext != extensions.end(); ++ext)
         {
         tryPath = *p;
@@ -2962,7 +2962,7 @@ kwsys_stl::string SystemTools::RelativePath(const char* local, const char* remot
     }
 
   // split up both paths into arrays of strings using / as a separator
-  kwsys_stl::vector<kwsys::String> localSplit = SystemTools::SplitString(local, '/', true); 
+  kwsys_stl::vector<kwsys::String> localSplit = SystemTools::SplitString(local, '/', true);
   kwsys_stl::vector<kwsys::String> remoteSplit = SystemTools::SplitString(remote, '/', true);
   kwsys_stl::vector<kwsys::String> commonPath; // store shared parts of path in this array
   kwsys_stl::vector<kwsys::String> finalPath;  // store the final relative path here
@@ -3019,7 +3019,7 @@ kwsys_stl::string SystemTools::RelativePath(const char* local, const char* remot
       }
     }
   kwsys_stl::string relativePath;     // result string
-  // now turn the array of directories into a unix path by puttint / 
+  // now turn the array of directories into a unix path by puttint /
   // between each entry that does not already have one
   for(kwsys_stl::vector<String>::iterator vit1 = finalPath.begin();
       vit1 != finalPath.end(); ++vit1)
@@ -3396,7 +3396,7 @@ kwsys_stl::string SystemTools::GetFilenamePath(const kwsys_stl::string& filename
 {
   kwsys_stl::string fn = filename;
   SystemTools::ConvertToUnixSlashes(fn);
-  
+
   kwsys_stl::string::size_type slash_pos = fn.rfind("/");
   if(slash_pos != kwsys_stl::string::npos)
     {
@@ -3515,7 +3515,7 @@ SystemTools::GetFilenameWithoutLastExtension(const kwsys_stl::string& filename)
 }
 
 bool SystemTools::FileHasSignature(const char *filename,
-                                   const char *signature, 
+                                   const char *signature,
                                    long offset)
 {
   if (!filename || !signature)
@@ -3547,9 +3547,9 @@ bool SystemTools::FileHasSignature(const char *filename,
   return res;
 }
 
-SystemTools::FileTypeEnum 
+SystemTools::FileTypeEnum
 SystemTools::DetectFileType(const char *filename,
-                            unsigned long length, 
+                            unsigned long length,
                             double percent_bin)
 {
   if (!filename || percent_bin < 0)
@@ -3577,13 +3577,13 @@ SystemTools::DetectFileType(const char *filename,
   // Loop over contents and count
 
   size_t text_count = 0;
- 
+
   const unsigned char *ptr = buffer;
   const unsigned char *buffer_end = buffer + read_length;
 
   while (ptr != buffer_end)
     {
-    if ((*ptr >= 0x20 && *ptr <= 0x7F) || 
+    if ((*ptr >= 0x20 && *ptr <= 0x7F) ||
         *ptr == '\n' ||
         *ptr == '\r' ||
         *ptr == '\t')
@@ -3595,7 +3595,7 @@ SystemTools::DetectFileType(const char *filename,
 
   delete [] buffer;
 
-  double current_percent_bin =  
+  double current_percent_bin =
     (static_cast<double>(read_length - text_count) /
      static_cast<double>(read_length));
 
@@ -3607,8 +3607,8 @@ SystemTools::DetectFileType(const char *filename,
   return SystemTools::FileTypeText;
 }
 
-bool SystemTools::LocateFileInDir(const char *filename, 
-                                  const char *dir, 
+bool SystemTools::LocateFileInDir(const char *filename,
+                                  const char *dir,
                                   kwsys_stl::string& filename_found,
                                   int try_filename_dirs)
 {
@@ -3621,7 +3621,7 @@ bool SystemTools::LocateFileInDir(const char *filename,
 
   kwsys_stl::string filename_base = SystemTools::GetFilenameName(filename);
 
-  // Check if 'dir' is really a directory 
+  // Check if 'dir' is really a directory
   // If win32 and matches something like C:, accept it as a dir
 
   kwsys_stl::string real_dir;
@@ -3645,7 +3645,7 @@ bool SystemTools::LocateFileInDir(const char *filename,
   if (filename_base.size() && dir)
     {
     size_t dir_len = strlen(dir);
-    int need_slash = 
+    int need_slash =
       (dir_len && dir[dir_len - 1] != '/' && dir[dir_len - 1] != '\\');
 
     kwsys_stl::string temp = dir;
@@ -3676,7 +3676,7 @@ bool SystemTools::LocateFileInDir(const char *filename,
         filename_dir = SystemTools::GetFilenamePath(filename_dir);
         filename_dir_base = SystemTools::GetFilenameName(filename_dir);
 #if defined( _WIN32 )
-        if (!filename_dir_base.size() || 
+        if (!filename_dir_base.size() ||
             filename_dir_base[filename_dir_base.size() - 1] == ':')
 #else
         if (!filename_dir_base.size())
@@ -3700,7 +3700,7 @@ bool SystemTools::LocateFileInDir(const char *filename,
         } while (!res && filename_dir_base.size());
       }
     }
-    
+
   return res;
 }
 
@@ -3746,12 +3746,12 @@ bool SystemTools::FileIsFullPath(const char* in_name)
 
 bool SystemTools::GetShortPath(const char* path, kwsys_stl::string& shortPath)
 {
-#if defined(WIN32) && !defined(__CYGWIN__)  
+#if defined(WIN32) && !defined(__CYGWIN__)
   const int size = int(strlen(path)) +1; // size of return
   char *buffer = new char[size];  // create a buffer
   char *tempPath = new char[size];  // create a buffer
   int ret;
-  
+
   // if the path passed in has quotes around it, first remove the quotes
   if (path[0] == '"' && path[strlen(path)-1] == '"')
     {
@@ -3762,7 +3762,7 @@ bool SystemTools::GetShortPath(const char* path, kwsys_stl::string& shortPath)
     {
     strcpy(tempPath,path);
     }
-  
+
   buffer[0] = 0;
   ret = GetShortPathName(tempPath, buffer, size);
 
@@ -3785,7 +3785,7 @@ bool SystemTools::GetShortPath(const char* path, kwsys_stl::string& shortPath)
 #endif
 }
 
-void SystemTools::SplitProgramFromArgs(const char* path, 
+void SystemTools::SplitProgramFromArgs(const char* path,
                                        kwsys_stl::string& program, kwsys_stl::string& args)
 {
   // see if this is a full path to a program
@@ -3797,7 +3797,7 @@ void SystemTools::SplitProgramFromArgs(const char* path,
     return;
     }
   // Try to find the program in the path, note the program
-  // may have spaces in its name so we have to look for it 
+  // may have spaces in its name so we have to look for it
   kwsys_stl::vector<kwsys_stl::string> e;
   kwsys_stl::string findProg = SystemTools::FindProgram(path, e);
   if(findProg.size())
@@ -3828,7 +3828,7 @@ void SystemTools::SplitProgramFromArgs(const char* path,
       args = dir.substr(spacePos, dir.size()-spacePos);
       return;
       }
-    // Now try and find the the program in the path 
+    // Now try and find the the program in the path
     findProg = SystemTools::FindProgram(tryProg.c_str(), e);
     if(findProg.size())
       {
@@ -4203,23 +4203,23 @@ kwsys_stl::string SystemTools::GetOperatingSystemNameAndVersion()
   if (!bOsVersionInfoEx)
     {
     osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
-    if (!GetVersionEx((OSVERSIONINFO *)&osvi)) 
+    if (!GetVersionEx((OSVERSIONINFO *)&osvi))
       {
       return 0;
       }
     }
-  
+
   switch (osvi.dwPlatformId)
     {
     // Test for the Windows NT product family.
 
     case VER_PLATFORM_WIN32_NT:
-      
+
       // Test for the specific product family.
 
       if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 0)
         {
-#if (_MSC_VER >= 1300) 
+#if (_MSC_VER >= 1300)
         if (osvi.wProductType == VER_NT_WORKSTATION)
           {
           res += "Microsoft Windows Vista";
@@ -4259,7 +4259,7 @@ kwsys_stl::string SystemTools::GetOperatingSystemNameAndVersion()
         {
         // Test for the workstation type.
 
-#if (_MSC_VER >= 1300) 
+#if (_MSC_VER >= 1300)
         if (osvi.wProductType == VER_NT_WORKSTATION)
           {
           if (osvi.dwMajorVersion == 4)
@@ -4278,7 +4278,7 @@ kwsys_stl::string SystemTools::GetOperatingSystemNameAndVersion()
               }
             }
           }
-            
+
         // Test for the server type.
 
         else if (osvi.wProductType == VER_NT_SERVER)
@@ -4302,7 +4302,7 @@ kwsys_stl::string SystemTools::GetOperatingSystemNameAndVersion()
               res += " Standard Edition";
               }
             }
-          
+
           else if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0)
             {
             if (osvi.wSuiteMask & VER_SUITE_DATACENTER)
@@ -4319,7 +4319,7 @@ kwsys_stl::string SystemTools::GetOperatingSystemNameAndVersion()
               }
             }
 
-          else if (osvi.dwMajorVersion <= 4)  // Windows NT 4.0 
+          else if (osvi.dwMajorVersion <= 4)  // Windows NT 4.0
             {
             if (osvi.wSuiteMask & VER_SUITE_ENTERPRISE)
               {
@@ -4336,7 +4336,7 @@ kwsys_stl::string SystemTools::GetOperatingSystemNameAndVersion()
 
       // Test for specific product on Windows NT 4.0 SP5 and earlier
 
-      else  
+      else
         {
         HKEY hKey;
         #define BUFSIZE 80
@@ -4386,7 +4386,7 @@ kwsys_stl::string SystemTools::GetOperatingSystemNameAndVersion()
 
       // Display service pack (if any) and build number.
 
-      if (osvi.dwMajorVersion == 4 && 
+      if (osvi.dwMajorVersion == 4 &&
           lstrcmpi(osvi.szCSDVersion, "Service Pack 6") == 0)
         {
         HKEY hKey;
@@ -4415,7 +4415,7 @@ kwsys_stl::string SystemTools::GetOperatingSystemNameAndVersion()
           res += buffer;
           res += ")";
           }
-        
+
         RegCloseKey(hKey);
         }
       else // Windows NT 3.51 and earlier or Windows 2000 and later
@@ -4455,11 +4455,11 @@ kwsys_stl::string SystemTools::GetOperatingSystemNameAndVersion()
       if (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion == 90)
         {
         res += "Microsoft Windows Millennium Edition";
-        } 
+        }
       break;
 
     case VER_PLATFORM_WIN32s:
-      
+
       res +=  "Microsoft Win32s";
       break;
     }
@@ -4469,7 +4469,7 @@ kwsys_stl::string SystemTools::GetOperatingSystemNameAndVersion()
 }
 
 // ----------------------------------------------------------------------
-bool SystemTools::ParseURLProtocol( const kwsys_stl::string& URL, 
+bool SystemTools::ParseURLProtocol( const kwsys_stl::string& URL,
                                     kwsys_stl::string& protocol,
                                     kwsys_stl::string& dataglom )
 {
@@ -4487,12 +4487,12 @@ bool SystemTools::ParseURLProtocol( const kwsys_stl::string& URL,
 }
 
 // ----------------------------------------------------------------------
-bool SystemTools::ParseURL( const kwsys_stl::string& URL, 
+bool SystemTools::ParseURL( const kwsys_stl::string& URL,
                             kwsys_stl::string& protocol,
-                            kwsys_stl::string& username, 
-                            kwsys_stl::string& password, 
-                            kwsys_stl::string& hostname, 
-                            kwsys_stl::string& dataport, 
+                            kwsys_stl::string& username,
+                            kwsys_stl::string& password,
+                            kwsys_stl::string& hostname,
+                            kwsys_stl::string& dataport,
                             kwsys_stl::string& database )
 {
   kwsys::RegularExpression urlRe( VTK_URL_REGEX );
@@ -4515,7 +4515,7 @@ bool SystemTools::ParseURL( const kwsys_stl::string& URL,
   hostname = urlRe.match( 6 );
   dataport = urlRe.match( 8 );
   database = urlRe.match( 9 );
-  
+
   return true;
 }
 