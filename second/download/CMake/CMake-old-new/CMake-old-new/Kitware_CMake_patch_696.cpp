@@ -21,6 +21,7 @@
 #include <cmsys/SystemTools.hxx>
 
 #include <stdio.h>
+#include <ctype.h>
 
 class cmGlobInternal
 {
@@ -51,7 +52,12 @@ void cmGlob::Escape(int ch, char* buffer)
     }
   else
     {
+#if defined( _WIN32 ) || defined(APPLE)
+    // On Windows and apple, no difference between lower and upper case
+    sprintf(buffer, "%c", tolower(ch));
+#else
     sprintf(buffer, "%c", ch);
+#endif
     }
 }
 
@@ -147,17 +153,25 @@ void cmGlob::RecurseDirectory(const std::string& dir, bool dir_only)
     }
   unsigned long cc;
   std::string fullname;
+  std::string fname;
   for ( cc = 0; cc < d.GetNumberOfFiles(); cc ++ )
     {
-    if ( strcmp(d.GetFile(cc), ".") == 0 ||
-      strcmp(d.GetFile(cc), "..") == 0  )
+    fname = d.GetFile(cc);
+    if ( strcmp(fname.c_str(), ".") == 0 ||
+      strcmp(fname.c_str(), "..") == 0  )
       {
       continue;
       }
-    fullname = dir + "/" + d.GetFile(cc);
+
+#if defined( _WIN32 ) || defined( APPLE )
+    // On Windows and apple, no difference between lower and upper case
+    fname = cmsys::SystemTools::LowerCase(fname);
+#endif
+
+    fullname = dir + "/" + fname;
     if ( !dir_only || !cmsys::SystemTools::FileIsDirectory(fullname.c_str()) )
       {
-      if ( m_Internals->Expressions[m_Internals->Expressions.size()-1].find(d.GetFile(cc)) )
+      if ( m_Internals->Expressions[m_Internals->Expressions.size()-1].find(fname.c_str()) )
         {
         m_Internals->Files.push_back(fullname);
         }
@@ -185,28 +199,36 @@ void cmGlob::ProcessDirectory(std::string::size_type start,
     }
   unsigned long cc;
   std::string fullname;
+  std::string fname;
   for ( cc = 0; cc < d.GetNumberOfFiles(); cc ++ )
     {
-    if ( strcmp(d.GetFile(cc), ".") == 0 ||
-     strcmp(d.GetFile(cc), "..") == 0  )
+    fname = d.GetFile(cc);
+    if ( strcmp(fname.c_str(), ".") == 0 ||
+      strcmp(fname.c_str(), "..") == 0  )
       {
       continue;
       }
+
+#if defined( _WIN32 ) || defined( APPLE )
+    // On Windows and apple, no difference between lower and upper case
+    fname = cmsys::SystemTools::LowerCase(fname);
+#endif
+
     if ( start == 0 )
       {
-      fullname = dir + d.GetFile(cc);
+      fullname = dir + fname;
       }
     else
       {
-      fullname = dir + "/" + d.GetFile(cc);
+      fullname = dir + "/" + fname;
       }
 
     if ( (!dir_only || !last) && !cmsys::SystemTools::FileIsDirectory(fullname.c_str()) )
       {
       continue;
       }
 
-    if ( m_Internals->Expressions[start].find(d.GetFile(cc)) )
+    if ( m_Internals->Expressions[start].find(fname.c_str()) )
       {
       if ( last )
         {