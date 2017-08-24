@@ -201,13 +201,13 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
   else
     {
     // only valid for srcfile signatures
-    if (compileDefs.size())
+    if (!compileDefs.empty())
       {
       this->Makefile->IssueMessage(cmake::FATAL_ERROR,
         "COMPILE_DEFINITIONS specified on a srcdir type TRY_COMPILE");
       return -1;
       }
-    if (copyFile.size())
+    if (!copyFile.empty())
       {
       this->Makefile->IssueMessage(cmake::FATAL_ERROR,
         "COPY_FILE specified on a srcdir type TRY_COMPILE");
@@ -371,7 +371,7 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
     fprintf(fout, "set(CMAKE_SUPPRESS_REGENERATION 1)\n");
     fprintf(fout, "link_directories(${LINK_DIRECTORIES})\n");
     // handle any compile flags we need to pass on
-    if (compileDefs.size())
+    if (!compileDefs.empty())
       {
       fprintf(fout, "add_definitions( ");
       for (size_t i = 0; i < compileDefs.size(); ++i)
@@ -547,7 +547,7 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
     std::string copyFileErrorMessage;
     this->FindOutputFile(targetName);
 
-    if ((res==0) && (copyFile.size()))
+    if ((res==0) && !copyFile.empty())
       {
       if(this->OutputFile.empty() ||
          !cmSystemTools::CopyFileAlways(this->OutputFile,