@@ -103,7 +103,7 @@ void Directory::Clear()
 namespace KWSYS_NAMESPACE
 {
 
-bool Directory::Load(const char* name)
+bool Directory::Load(const kwsys_stl::string& name)
 {
   this->Clear();
 #if _MSC_VER < 1300
@@ -112,24 +112,24 @@ bool Directory::Load(const char* name)
   intptr_t srchHandle;
 #endif
   char* buf;
-  size_t n = strlen(name);
-  if ( name[n - 1] == '/' || name[n - 1] == '\\' )
+  size_t n = name.size();
+  if ( *name.rbegin() == '/' || *name.rbegin() == '\\' )
     {
     buf = new char[n + 1 + 1];
-    sprintf(buf, "%s*", name);
+    sprintf(buf, "%s*", name.c_str());
     }
   else
     {
     // Make sure the slashes in the wildcard suffix are consistent with the
     // rest of the path
     buf = new char[n + 2 + 1];
-    if ( strchr(name, '\\') )
+    if ( name.find('\\') != name.npos )
       {
-      sprintf(buf, "%s\\*", name);
+      sprintf(buf, "%s\\*", name.c_str());
       }
     else
       {
-      sprintf(buf, "%s/*", name);
+      sprintf(buf, "%s/*", name.c_str());
       }
     }
   struct _wfinddata_t data;      // data of current file
@@ -153,24 +153,24 @@ bool Directory::Load(const char* name)
   return _findclose(srchHandle) != -1;
 }
 
-unsigned long Directory::GetNumberOfFilesInDirectory(const char* name)
+unsigned long Directory::GetNumberOfFilesInDirectory(const kwsys_stl::string& name)
 {
 #if _MSC_VER < 1300
   long srchHandle;
 #else
   intptr_t srchHandle;
 #endif
   char* buf;
-  size_t n = strlen(name);
-  if ( name[n - 1] == '/' )
+  size_t n = name.size();
+  if ( *name.rbegin() == '/' )
     {
     buf = new char[n + 1 + 1];
-    sprintf(buf, "%s*", name);
+    sprintf(buf, "%s*", name.c_str());
     }
   else
     {
     buf = new char[n + 2 + 1];
-    sprintf(buf, "%s/*", name);
+    sprintf(buf, "%s/*", name.c_str());
     }
   struct _wfinddata_t data;      // data of current file
 
@@ -215,15 +215,11 @@ p=1992&sid=f16167f51964f1a68fe5041b8eb213b6
 namespace KWSYS_NAMESPACE
 {
 
-bool Directory::Load(const char* name)
+bool Directory::Load(const kwsys_stl::string& name)
 {
   this->Clear();
    
-  if (!name)
-    {
-    return 0;
-    }
-  DIR* dir = opendir(name);
+  DIR* dir = opendir(name.c_str());
 
   if (!dir)
     {
@@ -239,14 +235,9 @@ bool Directory::Load(const char* name)
   return 1;
 }
 
-unsigned long Directory::GetNumberOfFilesInDirectory(const char* name)
+unsigned long Directory::GetNumberOfFilesInDirectory(const kwsys_stl::string& name)
 {
-  DIR* dir = opendir(name);
-
-  if (!dir)
-    {
-    return 0;
-    }
+  DIR* dir = opendir(name.c_str());
 
   unsigned long count = 0;
   for (dirent* d = readdir(dir); d; d = readdir(dir) )