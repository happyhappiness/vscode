@@ -40,20 +40,20 @@ namespace KWSYS_NAMESPACE
 {
 #if defined( _WIN32 ) || defined( APPLE ) || defined( __CYGWIN__ )
   // On Windows and apple, no difference between lower and upper case
-  #define CM_GLOB_CASE_INDEPENDENT
+  #define KWSYS_GLOB_CASE_INDEPENDENT
 #endif
 
 #if defined( _WIN32 ) || defined( __CYGWIN__ )
   // Handle network paths
-  #define CM_GLOB_SUPPORT_NETWORK_PATHS
+  #define KWSYS_GLOB_SUPPORT_NETWORK_PATHS
 #endif
 
 //----------------------------------------------------------------------------
 class GlobInternals
 {
 public:
   std::vector<std::string> Files;
-  std::vector<cmsys::RegularExpression> Expressions;
+  std::vector<kwsys::RegularExpression> Expressions;
   std::vector<std::string> TextExpressions;
 };
 
@@ -82,7 +82,7 @@ void Glob::Escape(int ch, char* buffer)
     }
   else
     {
-#if defined( CM_GLOB_CASE_INDEPENDENT )
+#if defined( KWSYS_GLOB_CASE_INDEPENDENT )
     // On Windows and apple, no difference between lower and upper case
     sprintf(buffer, "%c", tolower(ch));
 #else
@@ -180,7 +180,7 @@ std::string Glob::ConvertExpression(const std::string& expr)
 void Glob::RecurseDirectory(std::string::size_type start,
   const std::string& dir, bool dir_only)
 {
-  cmsys::Directory d;
+  kwsys::Directory d;
   if ( !d.Load(dir.c_str()) )
     {
     return;
@@ -207,9 +207,9 @@ void Glob::RecurseDirectory(std::string::size_type start,
       realname = dir + "/" + fname;
       }
 
-#if defined( CM_GLOB_CASE_INDEPENDENT )
+#if defined( KWSYS_GLOB_CASE_INDEPENDENT )
     // On Windows and apple, no difference between lower and upper case
-    fname = cmsys::SystemTools::LowerCase(fname);
+    fname = kwsys::SystemTools::LowerCase(fname);
 #endif
 
     if ( start == 0 )
@@ -221,14 +221,14 @@ void Glob::RecurseDirectory(std::string::size_type start,
       fullname = dir + "/" + fname;
       }
 
-    if ( !dir_only || !cmsys::SystemTools::FileIsDirectory(realname.c_str()) )
+    if ( !dir_only || !kwsys::SystemTools::FileIsDirectory(realname.c_str()) )
       {
       if ( m_Internals->Expressions[m_Internals->Expressions.size()-1].find(fname.c_str()) )
         {
         m_Internals->Files.push_back(realname);
         }
       }
-    if ( cmsys::SystemTools::FileIsDirectory(realname.c_str()) )
+    if ( kwsys::SystemTools::FileIsDirectory(realname.c_str()) )
       {
       this->RecurseDirectory(start+1, realname, dir_only);
       }
@@ -246,7 +246,7 @@ void Glob::ProcessDirectory(std::string::size_type start,
     this->RecurseDirectory(start, dir, dir_only);
     return;
     }
-  cmsys::Directory d;
+  kwsys::Directory d;
   if ( !d.Load(dir.c_str()) )
     {
     return;
@@ -273,9 +273,9 @@ void Glob::ProcessDirectory(std::string::size_type start,
       realname = dir + "/" + fname;
       }
 
-#if defined( CM_GLOB_CASE_INDEPENDENT )
+#if defined( KWSYS_GLOB_CASE_INDEPENDENT )
     // On Windows and apple, no difference between lower and upper case
-    fname = cmsys::SystemTools::LowerCase(fname);
+    fname = kwsys::SystemTools::LowerCase(fname);
 #endif
 
     if ( start == 0 )
@@ -291,7 +291,7 @@ void Glob::ProcessDirectory(std::string::size_type start,
     //std::cout << "Match: " << m_Internals->TextExpressions[start].c_str() << std::endl;
     //std::cout << "Full name: " << fullname << std::endl;
 
-    if ( (!dir_only || !last) && !cmsys::SystemTools::FileIsDirectory(realname.c_str()) )
+    if ( (!dir_only || !last) && !kwsys::SystemTools::FileIsDirectory(realname.c_str()) )
       {
       continue;
       }
@@ -320,9 +320,9 @@ bool Glob::FindFiles(const std::string& inexpr)
   m_Internals->Expressions.clear();
   m_Internals->Files.clear();
 
-  if ( !cmsys::SystemTools::FileIsFullPath(expr.c_str()) )
+  if ( !kwsys::SystemTools::FileIsFullPath(expr.c_str()) )
     {
-    expr = cmsys::SystemTools::GetCurrentWorkingDirectory();
+    expr = kwsys::SystemTools::GetCurrentWorkingDirectory();
     expr += "/" + inexpr;
     }
   std::string fexpr = expr;
@@ -349,7 +349,7 @@ bool Glob::FindFiles(const std::string& inexpr)
     }
   if ( skip == 0 )
     {
-#if defined( CM_GLOB_SUPPORT_NETWORK_PATHS )
+#if defined( KWSYS_GLOB_SUPPORT_NETWORK_PATHS )
     // Handle network paths
     if ( expr[0] == '/' && expr[1] == '/' )
       {
@@ -419,7 +419,7 @@ bool Glob::FindFiles(const std::string& inexpr)
 void Glob::AddExpression(const char* expr)
 {
   m_Internals->Expressions.push_back(
-    cmsys::RegularExpression(
+    kwsys::RegularExpression(
       this->ConvertExpression(expr).c_str()));
   m_Internals->TextExpressions.push_back(this->ConvertExpression(expr));
 }