@@ -61,22 +61,23 @@ class GlobInternals
 //----------------------------------------------------------------------------
 Glob::Glob()
 {
-  m_Internals = new GlobInternals;
-  m_Recurse = false;
+  this->Internals = new GlobInternals;
+  this->Recurse = false;
+  this->Relative = "";
 }
 
 //----------------------------------------------------------------------------
 Glob::~Glob()
 {
-  delete m_Internals;
+  delete this->Internals;
 }
 
 //----------------------------------------------------------------------------
 void Glob::Escape(int ch, char* buffer)
 {
   if (! (
-      'a' <= ch && ch <= 'z' || 
-      'A' <= ch && ch <= 'Z' || 
+      'a' <= ch && ch <= 'z' ||
+      'A' <= ch && ch <= 'Z' ||
       '0' <= ch && ch <= '9') )
     {
     sprintf(buffer, "\\%c", ch);
@@ -95,13 +96,13 @@ void Glob::Escape(int ch, char* buffer)
 //----------------------------------------------------------------------------
 kwsys_stl::vector<kwsys_stl::string>& Glob::GetFiles()
 {
-  return m_Internals->Files;
+  return this->Internals->Files;
 }
 
 //----------------------------------------------------------------------------
 kwsys_stl::string Glob::ConvertExpression(const kwsys_stl::string& expr)
 {
-  
+
   kwsys_stl::string::size_type i = 0;
   kwsys_stl::string::size_type n = expr.size();
 
@@ -130,7 +131,7 @@ kwsys_stl::string Glob::ConvertExpression(const kwsys_stl::string& expr)
       if ( j < n && expr[j] == ']' )
         {
         j = j+1;
-        } 
+        }
       while ( j < n && expr[j] != ']' )
         {
         j = j+1;
@@ -224,9 +225,10 @@ void Glob::RecurseDirectory(kwsys_stl::string::size_type start,
 
     if ( !dir_only || !kwsys::SystemTools::FileIsDirectory(realname.c_str()) )
       {
-      if ( m_Internals->Expressions[m_Internals->Expressions.size()-1].find(fname.c_str()) )
+      if ( this->Internals->Expressions[
+        this->Internals->Expressions.size()-1].find(fname.c_str()) )
         {
-        m_Internals->Files.push_back(realname);
+        this->AddFile(this->Internals->Files, realname.c_str());
         }
       }
     if ( kwsys::SystemTools::FileIsDirectory(realname.c_str()) )
@@ -237,12 +239,12 @@ void Glob::RecurseDirectory(kwsys_stl::string::size_type start,
 }
 
 //----------------------------------------------------------------------------
-void Glob::ProcessDirectory(kwsys_stl::string::size_type start, 
+void Glob::ProcessDirectory(kwsys_stl::string::size_type start,
   const kwsys_stl::string& dir, bool dir_only)
 {
   //kwsys_ios::cout << "ProcessDirectory: " << dir << kwsys_ios::endl;
-  bool last = ( start == m_Internals->Expressions.size()-1 );
-  if ( last && m_Recurse )
+  bool last = ( start == this->Internals->Expressions.size()-1 );
+  if ( last && this->Recurse )
     {
     this->RecurseDirectory(start, dir, dir_only);
     return;
@@ -289,19 +291,21 @@ void Glob::ProcessDirectory(kwsys_stl::string::size_type start,
       }
 
     //kwsys_ios::cout << "Look at file: " << fname << kwsys_ios::endl;
-    //kwsys_ios::cout << "Match: " << m_Internals->TextExpressions[start].c_str() << kwsys_ios::endl;
+    //kwsys_ios::cout << "Match: "
+    // << this->Internals->TextExpressions[start].c_str() << kwsys_ios::endl;
     //kwsys_ios::cout << "Full name: " << fullname << kwsys_ios::endl;
 
-    if ( (!dir_only || !last) && !kwsys::SystemTools::FileIsDirectory(realname.c_str()) )
+    if ( (!dir_only || !last) &&
+      !kwsys::SystemTools::FileIsDirectory(realname.c_str()) )
       {
       continue;
       }
 
-    if ( m_Internals->Expressions[start].find(fname.c_str()) )
+    if ( this->Internals->Expressions[start].find(fname.c_str()) )
       {
       if ( last )
         {
-        m_Internals->Files.push_back(realname);
+        this->AddFile(this->Internals->Files, realname.c_str());
         }
       else
         {
@@ -318,8 +322,8 @@ bool Glob::FindFiles(const kwsys_stl::string& inexpr)
   kwsys_stl::string::size_type cc;
   kwsys_stl::string expr = inexpr;
 
-  m_Internals->Expressions.clear();
-  m_Internals->Files.clear();
+  this->Internals->Expressions.clear();
+  this->Internals->Files.clear();
 
   if ( !kwsys::SystemTools::FileIsFullPath(expr.c_str()) )
     {
@@ -336,7 +340,7 @@ bool Glob::FindFiles(const kwsys_stl::string& inexpr)
       {
       last_slash = cc;
       }
-    if ( cc > 0 && 
+    if ( cc > 0 &&
       (expr[cc] == '[' || expr[cc] == '?' || expr[cc] == '*') &&
       expr[cc-1] != '\\' )
       {
@@ -345,7 +349,8 @@ bool Glob::FindFiles(const kwsys_stl::string& inexpr)
     }
   if ( last_slash > 0 )
     {
-    //kwsys_ios::cout << "I can skip: " << fexpr.substr(0, last_slash) << kwsys_ios::endl;
+    //kwsys_ios::cout << "I can skip: " << fexpr.substr(0, last_slash)
+    //<< kwsys_ios::endl;
     skip = last_slash;
     }
   if ( skip == 0 )
@@ -408,7 +413,7 @@ bool Glob::FindFiles(const kwsys_stl::string& inexpr)
   if ( skip > 0 )
     {
     this->ProcessDirectory(0, fexpr.substr(0, skip) + "/",
-      true);     
+      true);
     }
   else
     {
@@ -417,12 +422,47 @@ bool Glob::FindFiles(const kwsys_stl::string& inexpr)
   return true;
 }
 
+//----------------------------------------------------------------------------
 void Glob::AddExpression(const char* expr)
 {
-  m_Internals->Expressions.push_back(
+  this->Internals->Expressions.push_back(
     kwsys::RegularExpression(
       this->ConvertExpression(expr).c_str()));
-  m_Internals->TextExpressions.push_back(this->ConvertExpression(expr));
+  this->Internals->TextExpressions.push_back(this->ConvertExpression(expr));
+}
+
+//----------------------------------------------------------------------------
+void Glob::SetRelative(const char* dir)
+{
+  if ( !dir )
+    {
+    this->Relative = "";
+    return;
+    }
+  this->Relative = dir;
+}
+
+//----------------------------------------------------------------------------
+const char* Glob::GetRelative()
+{
+  if ( this->Relative.empty() )
+    {
+    return 0;
+    }
+  return this->Relative.c_str();
+}
+
+//----------------------------------------------------------------------------
+void Glob::AddFile(kwsys_stl::vector<kwsys_stl::string>& files, const char* file)
+{
+  if ( !this->Relative.empty() )
+    {
+    files.push_back(kwsys::SystemTools::RelativePath(this->Relative.c_str(), file));
+    }
+  else
+    {
+    files.push_back(file);
+    }
 }
 
 } // namespace KWSYS_NAMESPACE