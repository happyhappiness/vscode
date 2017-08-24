@@ -16,9 +16,6 @@
 =========================================================================*/
 #include <SystemTools.hxx>
 
-#include <RegularExpression.hxx>
-#include <Directory.hxx>
-
 #include <std/iostream>
 #include <std/fstream>
 
@@ -525,60 +522,6 @@ bool SystemTools::DeleteRegistryValue(const char *)
 }
 #endif
 
-// replace replace with with as many times as it shows up in source.
-// write the result into source.
-#if defined(_WIN32) && !defined(__CYGWIN__)
-void SystemTools::ExpandRegistryValues(kwsys_std::string& source)
-{
-  // Regular expression to match anything inside [...] that begins in HKEY.
-  // Note that there is a special rule for regular expressions to match a
-  // close square-bracket inside a list delimited by square brackets.
-  // The "[^]]" part of this expression will match any character except
-  // a close square-bracket.  The ']' character must be the first in the
-  // list of characters inside the [^...] block of the expression.
-  RegularExpression regEntry("\\[(HKEY[^]]*)\\]");
-  
-  // check for black line or comment
-  while (regEntry.find(source))
-    {
-    // the arguments are the second match
-    kwsys_std::string key = regEntry.match(1);
-    kwsys_std::string val;
-    if (ReadRegistryValue(key.c_str(), val))
-      {
-      kwsys_std::string reg = "[";
-      reg += key + "]";
-      SystemTools::ReplaceString(source, reg.c_str(), val.c_str());
-      }
-    else
-      {
-      kwsys_std::string reg = "[";
-      reg += key + "]";
-      SystemTools::ReplaceString(source, reg.c_str(), "/registry");
-      }
-    }
-}
-#else
-void SystemTools::ExpandRegistryValues(kwsys_std::string&)
-{
-}
-#endif  
-
-
-kwsys_std::string SystemTools::EscapeQuotes(const char* str)
-{
-  kwsys_std::string result = "";
-  for(const char* ch = str; *ch != '\0'; ++ch)
-    {
-    if(*ch == '"')
-      {
-      result += '\\';
-      }
-    result += *ch;
-    }
-  return result;
-}
-
 bool SystemTools::SameFile(const char* file1, const char* file2)
 {
 #ifdef _WIN32
@@ -741,7 +684,6 @@ void SystemTools::ConvertToUnixSlashes(kwsys_std::string& path)
     }
 }
 
-
 // change // to /, and escape any spaces in the path
 kwsys_std::string SystemTools::ConvertToUnixOutputPath(const char* path)
 {
@@ -773,38 +715,6 @@ kwsys_std::string SystemTools::ConvertToUnixOutputPath(const char* path)
   return ret;
 }
 
-
-
-kwsys_std::string SystemTools::EscapeSpaces(const char* str)
-{
-#if defined(_WIN32) && !defined(__CYGWIN__)
-  kwsys_std::string result;
-  
-  // if there are spaces
-  kwsys_std::string temp = str;
-  if (temp.find(" ") != kwsys_std::string::npos && 
-      temp.find("\"")==kwsys_std::string::npos)
-    {
-    result = "\"";
-    result += str;
-    result += "\"";
-    return result;
-    }
-  return str;
-#else
-  kwsys_std::string result = "";
-  for(const char* ch = str; *ch != '\0'; ++ch)
-    {
-    if(*ch == ' ')
-      {
-      result += '\\';
-      }
-    result += *ch;
-    }
-  return result;
-#endif
-}
-
 kwsys_std::string SystemTools::ConvertToOutputPath(const char* path)
 {
 #if defined(_WIN32) && !defined(__CYGWIN__)
@@ -814,7 +724,6 @@ kwsys_std::string SystemTools::ConvertToOutputPath(const char* path)
 #endif
 }
 
-
 // remove double slashes not at the start
 kwsys_std::string SystemTools::ConvertToWindowsOutputPath(const char* path)
 {  
@@ -1482,6 +1391,23 @@ kwsys_std::string SystemTools::GetFilenameExtension(const kwsys_std::string& fil
     }
 }
 
+/**
+ * Return file extension of a full filename (dot included).
+ * Warning: this is the shortest extension (for example: .tar.gz)
+ */
+kwsys_std::string SystemTools::GetFilenameLastExtension(const kwsys_std::string& filename)
+{
+  kwsys_std::string name = SystemTools::GetFilenameName(filename);
+  kwsys_std::string::size_type dot_pos = name.rfind(".");
+  if(dot_pos != std::string::npos)
+    {
+    return name.substr(dot_pos);
+    }
+  else
+    {
+    return "";
+    }
+}
 
 /**
  * Return file name without extension of a full filename (i.e. without path).
@@ -1556,63 +1482,6 @@ bool SystemTools::FileIsFullPath(const char* in_name)
   return false;
 }
 
-void SystemTools::Glob(const char *directory, const char *regexp,
-                         kwsys_std::vector<kwsys_std::string>& files)
-{
-  Directory d;
-  RegularExpression reg(regexp);
-  
-  if (d.Load(directory))
-    {
-    size_t numf;
-        unsigned int i;
-    numf = d.GetNumberOfFiles();
-    for (i = 0; i < numf; i++)
-      {
-      kwsys_std::string fname = d.GetFile(i);
-      if (reg.find(fname))
-        {
-        files.push_back(fname);
-        }
-      }
-    }
-}
-
-
-void SystemTools::GlobDirs(const char *fullPath,
-                             kwsys_std::vector<kwsys_std::string>& files)
-{
-  kwsys_std::string path = fullPath;
-  kwsys_std::string::size_type pos = path.find("/*");
-  if(pos == kwsys_std::string::npos)
-    {
-    files.push_back(fullPath);
-    return;
-    }
-  kwsys_std::string startPath = path.substr(0, pos);
-  kwsys_std::string finishPath = path.substr(pos+2);
-
-  Directory d;
-  if (d.Load(startPath.c_str()))
-    {
-    for (unsigned int i = 0; i < d.GetNumberOfFiles(); ++i)
-      {
-      if(!(kwsys_std::string(d.GetFile(i)) == ".")
-         && !(kwsys_std::string(d.GetFile(i)) == ".."))
-        {
-        kwsys_std::string fname = startPath;
-        fname +="/";
-        fname += d.GetFile(i);
-        if(SystemTools::FileIsDirectory(fname.c_str()))
-          {
-          fname += finishPath;
-          SystemTools::GlobDirs(fname.c_str(), files);
-          }
-        }
-      }
-    }
-}
-
 bool SystemTools::GetShortPath(const char* path, kwsys_std::string& shortPath)
 {
 #if defined(WIN32) && !defined(__CYGWIN__)  
@@ -1654,61 +1523,6 @@ bool SystemTools::GetShortPath(const char* path, kwsys_std::string& shortPath)
 #endif
 }
 
-bool SystemTools::SimpleGlob(const kwsys_std::string& glob, 
-                               kwsys_std::vector<kwsys_std::string>& files, 
-                               int type /* = 0 */)
-{
-  files.clear();
-  if ( glob[glob.size()-1] != '*' )
-    {
-    return false;
-    }
-  kwsys_std::string path = SystemTools::GetFilenamePath(glob);
-  kwsys_std::string ppath = SystemTools::GetFilenameName(glob);
-  ppath = ppath.substr(0, ppath.size()-1);
-  if ( path.size() == 0 )
-    {
-    path = "/";
-    }
-
-  bool res = false;
-  Directory d;
-  if (d.Load(path.c_str()))
-    {
-    for (unsigned int i = 0; i < d.GetNumberOfFiles(); ++i)
-      {
-      if(!(kwsys_std::string(d.GetFile(i)) == ".")
-         && !(kwsys_std::string(d.GetFile(i)) == ".."))
-        {
-        kwsys_std::string fname = path;
-        if ( path[path.size()-1] != '/' )
-          {
-          fname +="/";
-          }
-        fname += d.GetFile(i);
-        kwsys_std::string sfname = d.GetFile(i);
-        if ( type > 0 && SystemTools::FileIsDirectory(fname.c_str()) )
-          {
-          continue;
-          }
-        if ( type < 0 && !SystemTools::FileIsDirectory(fname.c_str()) )
-          {
-          continue;
-          }
-        if ( sfname.size() >= ppath.size() && 
-             sfname.substr(0, ppath.size()) == 
-             ppath )
-          {
-          files.push_back(fname);
-          res = true;
-          }
-        }
-      }
-    }
-  return res;
-}
-
-
 void SystemTools::SplitProgramFromArgs(const char* path, 
                                          kwsys_std::string& program, kwsys_std::string& args)
 {
@@ -1816,10 +1630,15 @@ bool SystemTools::GetLineFromStream(kwsys_std::istream& is, kwsys_std::string& l
   return haveData;
 }
 
+} // namespace KWSYS_NAMESPACE
+
 #if defined(_MSC_VER) && defined(_DEBUG)
 # include <crtdbg.h>
 # include <stdio.h>
 # include <stdlib.h>
+namespace KWSYS_NAMESPACE
+{
+
 static int SystemToolsDebugReport(int, char* message, int*)
 {
   fprintf(stderr, message);
@@ -1833,10 +1652,11 @@ void SystemTools::EnableMSVCDebugHook()
     _CrtSetReportHook(SystemToolsDebugReport);
     }
 }
+
+} // namespace KWSYS_NAMESPACE
 #else
-void SystemTools::EnableMSVCDebugHook()
+namespace KWSYS_NAMESPACE
 {
-}
-#endif
-
+void SystemTools::EnableMSVCDebugHook() {}
 } // namespace KWSYS_NAMESPACE
+#endif