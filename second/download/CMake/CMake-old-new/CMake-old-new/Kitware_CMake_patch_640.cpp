@@ -23,6 +23,16 @@
 #include <stdio.h>
 #include <ctype.h>
 
+#if defined( _WIN32 ) || defined( APPLE ) || defined( __CYGWIN__ )
+  // On Windows and apple, no difference between lower and upper case
+  #define CM_GLOB_CASE_INDEPENDENT
+#endif
+
+#if defined( _WIN32 ) || defined( __CYGWIN__ )
+  // Handle network paths
+  #define CM_GLOB_SUPPORT_NETWORK_PATHS
+#endif
+
 class cmGlobInternal
 {
 public:
@@ -52,7 +62,7 @@ void cmGlob::Escape(int ch, char* buffer)
     }
   else
     {
-#if defined( _WIN32 ) || defined(APPLE)
+#if defined( CM_GLOB_CASE_INDEPENDENT )
     // On Windows and apple, no difference between lower and upper case
     sprintf(buffer, "%c", tolower(ch));
 #else
@@ -163,7 +173,7 @@ void cmGlob::RecurseDirectory(const std::string& dir, bool dir_only)
       continue;
       }
 
-#if defined( _WIN32 ) || defined( APPLE )
+#if defined( CM_GLOB_CASE_INDEPENDENT )
     // On Windows and apple, no difference between lower and upper case
     fname = cmsys::SystemTools::LowerCase(fname);
 #endif
@@ -209,7 +219,7 @@ void cmGlob::ProcessDirectory(std::string::size_type start,
       continue;
       }
 
-#if defined( _WIN32 ) || defined( APPLE )
+#if defined( CM_GLOB_CASE_INDEPENDENT )
     // On Windows and apple, no difference between lower and upper case
     fname = cmsys::SystemTools::LowerCase(fname);
 #endif
@@ -256,10 +266,36 @@ bool cmGlob::FindFiles(const std::string& inexpr)
     expr = cmsys::SystemTools::GetCurrentWorkingDirectory();
     expr += "/" + inexpr;
     }
+
+  int skip = 0;
+
+#if defined( CM_GLOB_SUPPORT_NETWORK_PATHS )
+  // Handle network paths
+  if ( expr[0] == '/' && expr[1] == '/' )
+    {
+    int cnt = 0;
+    for ( cc = 2; cc < expr.size(); cc ++ )
+      {
+      if ( expr[cc] == '/' )
+        {
+        cnt ++;
+        if ( cnt == 2 )
+          {
+          break;
+          }
+        }
+      }
+    skip = cc + 1;
+    expr = expr.substr(skip);
+    }
+  else
+#endif
+
   if ( expr[1] == ':' && expr[0] != '/' )
     {
     expr = expr.substr(2);
     }
+  cexpr = "";
   for ( cc = 0; cc < expr.size(); cc ++ )
     {
     int ch = expr[cc];
@@ -280,6 +316,17 @@ bool cmGlob::FindFiles(const std::string& inexpr)
     {
     this->AddExpression(cexpr.c_str());
     }
+
+#ifdef _WIN32
+  // Handle network paths
+  if ( skip > 0 )
+    {
+    this->ProcessDirectory(0, inexpr.substr(0, skip),
+      true);     
+    }
+  else
+#endif
+
   if ( inexpr[1] == ':' && inexpr[0] != '/' )
     {
     std::string startdir = "A:/";