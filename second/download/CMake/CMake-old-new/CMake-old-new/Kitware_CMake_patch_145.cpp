@@ -1,14 +1,5 @@
-/*============================================================================
-  KWSys - Kitware System Library
-  Copyright 2000-2009 Kitware, Inc., Insight Software Consortium
-
-  Distributed under the OSI-approved BSD License (the "License");
-  see accompanying file Copyright.txt for details.
-
-  This software is distributed WITHOUT ANY WARRANTY; without even the
-  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
-  See the License for more information.
-============================================================================*/
+/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
+   file Copyright.txt or https://cmake.org/licensing#kwsys for details.  */
 #include "kwsysPrivate.h"
 #include KWSYS_HEADER(Directory.hxx)
 
@@ -19,16 +10,15 @@
 // Work-around CMake dependency scanning limitation.  This must
 // duplicate the above list of headers.
 #if 0
-# include "Directory.hxx.in"
-# include "Configure.hxx.in"
-# include "Encoding.hxx.in"
+#include "Configure.hxx.in"
+#include "Directory.hxx.in"
+#include "Encoding.hxx.in"
 #endif
 
 #include <string>
 #include <vector>
 
-namespace KWSYS_NAMESPACE
-{
+namespace KWSYS_NAMESPACE {
 
 //----------------------------------------------------------------------------
 class DirectoryInternals
@@ -62,10 +52,9 @@ unsigned long Directory::GetNumberOfFiles() const
 //----------------------------------------------------------------------------
 const char* Directory::GetFile(unsigned long dindex) const
 {
-  if ( dindex >= this->Internal->Files.size() )
-    {
+  if (dindex >= this->Internal->Files.size()) {
     return 0;
-    }
+  }
   return this->Internal->Files[dindex].c_str();
 }
 
@@ -88,9 +77,10 @@ void Directory::Clear()
 
 #if defined(_WIN32) && !defined(__CYGWIN__)
 #include <windows.h>
-#include <io.h>
+
 #include <ctype.h>
 #include <fcntl.h>
+#include <io.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
@@ -99,15 +89,14 @@ void Directory::Clear()
 
 // Wide function names can vary depending on compiler:
 #ifdef __BORLANDC__
-# define _wfindfirst_func __wfindfirst
-# define _wfindnext_func __wfindnext
+#define _wfindfirst_func __wfindfirst
+#define _wfindnext_func __wfindnext
 #else
-# define _wfindfirst_func _wfindfirst
-# define _wfindnext_func _wfindnext
+#define _wfindfirst_func _wfindfirst
+#define _wfindnext_func _wfindnext
 #endif
 
-namespace KWSYS_NAMESPACE
-{
+namespace KWSYS_NAMESPACE {
 
 bool Directory::Load(const std::string& name)
 {
@@ -120,42 +109,34 @@ bool Directory::Load(const std::string& name)
 #endif
   char* buf;
   size_t n = name.size();
-  if ( *name.rbegin() == '/' || *name.rbegin() == '\\' )
-    {
+  if (*name.rbegin() == '/' || *name.rbegin() == '\\') {
     buf = new char[n + 1 + 1];
     sprintf(buf, "%s*", name.c_str());
-    }
-  else
-    {
+  } else {
     // Make sure the slashes in the wildcard suffix are consistent with the
     // rest of the path
     buf = new char[n + 2 + 1];
-    if ( name.find('\\') != name.npos )
-      {
+    if (name.find('\\') != name.npos) {
       sprintf(buf, "%s\\*", name.c_str());
-      }
-    else
-      {
+    } else {
       sprintf(buf, "%s/*", name.c_str());
-      }
     }
-  struct _wfinddata_t data;      // data of current file
+  }
+  struct _wfinddata_t data; // data of current file
 
   // Now put them into the file array
-  srchHandle = _wfindfirst_func((wchar_t*)Encoding::ToWide(buf).c_str(), &data);
-  delete [] buf;
+  srchHandle =
+    _wfindfirst_func((wchar_t*)Encoding::ToWide(buf).c_str(), &data);
+  delete[] buf;
 
-  if ( srchHandle == -1 )
-    {
+  if (srchHandle == -1) {
     return 0;
-    }
+  }
 
   // Loop through names
-  do
-    {
+  do {
     this->Internal->Files.push_back(Encoding::ToNarrow(data.name));
-    }
-  while ( _wfindnext_func(srchHandle, &data) != -1 );
+  } while (_wfindnext_func(srchHandle, &data) != -1);
   this->Internal->Path = name;
   return _findclose(srchHandle) != -1;
 }
@@ -170,34 +151,29 @@ unsigned long Directory::GetNumberOfFilesInDirectory(const std::string& name)
 #endif
   char* buf;
   size_t n = name.size();
-  if ( *name.rbegin() == '/' )
-    {
+  if (*name.rbegin() == '/') {
     buf = new char[n + 1 + 1];
     sprintf(buf, "%s*", name.c_str());
-    }
-  else
-    {
+  } else {
     buf = new char[n + 2 + 1];
     sprintf(buf, "%s/*", name.c_str());
-    }
-  struct _wfinddata_t data;      // data of current file
+  }
+  struct _wfinddata_t data; // data of current file
 
   // Now put them into the file array
-  srchHandle = _wfindfirst_func((wchar_t*)Encoding::ToWide(buf).c_str(), &data);
-  delete [] buf;
+  srchHandle =
+    _wfindfirst_func((wchar_t*)Encoding::ToWide(buf).c_str(), &data);
+  delete[] buf;
 
-  if ( srchHandle == -1 )
-    {
+  if (srchHandle == -1) {
     return 0;
-    }
+  }
 
   // Loop through names
   unsigned long count = 0;
-  do
-    {
+  do {
     count++;
-    }
-  while ( _wfindnext_func(srchHandle, &data) != -1 );
+  } while (_wfindnext_func(srchHandle, &data) != -1);
   _findclose(srchHandle);
   return count;
 }
@@ -209,40 +185,38 @@ unsigned long Directory::GetNumberOfFilesInDirectory(const std::string& name)
 // Now the POSIX style directory access
 
 #include <sys/types.h>
+
 #include <dirent.h>
 
 // PGI with glibc has trouble with dirent and large file support:
 //  http://www.pgroup.com/userforum/viewtopic.php?
 //  p=1992&sid=f16167f51964f1a68fe5041b8eb213b6
 // Work around the problem by mapping dirent the same way as readdir.
 #if defined(__PGI) && defined(__GLIBC__)
-# define kwsys_dirent_readdir dirent
-# define kwsys_dirent_readdir64 dirent64
-# define kwsys_dirent kwsys_dirent_lookup(readdir)
-# define kwsys_dirent_lookup(x) kwsys_dirent_lookup_delay(x)
-# define kwsys_dirent_lookup_delay(x) kwsys_dirent_##x
+#define kwsys_dirent_readdir dirent
+#define kwsys_dirent_readdir64 dirent64
+#define kwsys_dirent kwsys_dirent_lookup(readdir)
+#define kwsys_dirent_lookup(x) kwsys_dirent_lookup_delay(x)
+#define kwsys_dirent_lookup_delay(x) kwsys_dirent_##x
 #else
-# define kwsys_dirent dirent
+#define kwsys_dirent dirent
 #endif
 
-namespace KWSYS_NAMESPACE
-{
+namespace KWSYS_NAMESPACE {
 
 bool Directory::Load(const std::string& name)
 {
   this->Clear();
-   
+
   DIR* dir = opendir(name.c_str());
 
-  if (!dir)
-    {
+  if (!dir) {
     return 0;
-    }
+  }
 
-  for (kwsys_dirent* d = readdir(dir); d; d = readdir(dir) )
-    {
+  for (kwsys_dirent* d = readdir(dir); d; d = readdir(dir)) {
     this->Internal->Files.push_back(d->d_name);
-    }
+  }
   this->Internal->Path = name;
   closedir(dir);
   return 1;
@@ -252,16 +226,14 @@ unsigned long Directory::GetNumberOfFilesInDirectory(const std::string& name)
 {
   DIR* dir = opendir(name.c_str());
 
-  if (!dir)
-    {
+  if (!dir) {
     return 0;
-    }
+  }
 
   unsigned long count = 0;
-  for (kwsys_dirent* d = readdir(dir); d; d = readdir(dir) )
-    {
+  for (kwsys_dirent* d = readdir(dir); d; d = readdir(dir)) {
     count++;
-    }
+  }
   closedir(dir);
   return count;
 }