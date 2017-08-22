@@ -14,6 +14,8 @@
 
 #include KWSYS_HEADER(Configure.hxx)
 
+#include KWSYS_HEADER(Encoding.hxx)
+
 #include KWSYS_HEADER(stl/string)
 #include KWSYS_HEADER(stl/vector)
 
@@ -22,6 +24,7 @@
 #if 0
 # include "Directory.hxx.in"
 # include "Configure.hxx.in"
+# include "Encoding.hxx.in"
 # include "kwsys_stl.hxx.in"
 # include "kwsys_stl_string.hxx.in"
 # include "kwsys_stl_vector.hxx.in"
@@ -120,10 +123,10 @@ bool Directory::Load(const char* name)
     buf = new char[n + 2 + 1];
     sprintf(buf, "%s/*", name);
     }
-  struct _finddata_t data;      // data of current file
+  struct _wfinddata_t data;      // data of current file
 
   // Now put them into the file array
-  srchHandle = _findfirst(buf, &data);
+  srchHandle = _wfindfirst((wchar_t*)Encoding::ToWide(buf).c_str(), &data);
   delete [] buf;
 
   if ( srchHandle == -1 )
@@ -134,9 +137,9 @@ bool Directory::Load(const char* name)
   // Loop through names
   do
     {
-    this->Internal->Files.push_back(data.name);
+    this->Internal->Files.push_back(Encoding::ToNarrow(data.name));
     }
-  while ( _findnext(srchHandle, &data) != -1 );
+  while ( _wfindnext(srchHandle, &data) != -1 );
   this->Internal->Path = name;
   return _findclose(srchHandle) != -1;
 }
@@ -160,10 +163,10 @@ unsigned long Directory::GetNumberOfFilesInDirectory(const char* name)
     buf = new char[n + 2 + 1];
     sprintf(buf, "%s/*", name);
     }
-  struct _finddata_t data;      // data of current file
+  struct _wfinddata_t data;      // data of current file
 
   // Now put them into the file array
-  srchHandle = _findfirst(buf, &data);
+  srchHandle = _wfindfirst((wchar_t*)Encoding::ToWide(buf).c_str(), &data);
   delete [] buf;
 
   if ( srchHandle == -1 )
@@ -177,7 +180,7 @@ unsigned long Directory::GetNumberOfFilesInDirectory(const char* name)
     {
     count++;
     }
-  while ( _findnext(srchHandle, &data) != -1 );
+  while ( _wfindnext(srchHandle, &data) != -1 );
   _findclose(srchHandle);
   return count;
 }