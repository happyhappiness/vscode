@@ -28,7 +28,7 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
 
   const char* sourceDirectory = argv[2].c_str();
   const char* projectName = 0;
-  const char* targetName = 0;
+  std::string targetName;
   std::vector<std::string> cmakeFlags;
   std::vector<std::string> compileDefs;
   std::string outputVariable;
@@ -249,7 +249,8 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
         si != sources.end(); ++si)
       {
       std::string ext = cmSystemTools::GetFilenameLastExtension(*si);
-      if(const char* lang = gg->GetLanguageFromExtension(ext.c_str()))
+      std::string lang = gg->GetLanguageFromExtension(ext.c_str());
+      if(!lang.empty())
         {
         testLangs.insert(lang);
         }
@@ -283,7 +284,7 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
       {
       cmOStringStream e;
       e << "Failed to open\n"
-        << "  " << outFileName.c_str() << "\n"
+        << "  " << outFileName << "\n"
         << cmSystemTools::GetLastSystemError();
       this->Makefile->IssueMessage(cmake::FATAL_ERROR, e.str());
       return -1;
@@ -306,13 +307,13 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
       std::string rulesOverrideBase = "CMAKE_USER_MAKE_RULES_OVERRIDE";
       std::string rulesOverrideLang = rulesOverrideBase + "_" + *li;
       if(const char* rulesOverridePath =
-         this->Makefile->GetDefinition(rulesOverrideLang.c_str()))
+         this->Makefile->GetDefinition(rulesOverrideLang))
         {
         fprintf(fout, "set(%s \"%s\")\n",
                 rulesOverrideLang.c_str(), rulesOverridePath);
         }
       else if(const char* rulesOverridePath2 =
-              this->Makefile->GetDefinition(rulesOverrideBase.c_str()))
+              this->Makefile->GetDefinition(rulesOverrideBase))
         {
         fprintf(fout, "set(%s \"%s\")\n",
                 rulesOverrideBase.c_str(), rulesOverridePath2);
@@ -324,7 +325,7 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
         li != testLangs.end(); ++li)
       {
       std::string langFlags = "CMAKE_" + *li + "_FLAGS";
-      const char* flags = this->Makefile->GetDefinition(langFlags.c_str());
+      const char* flags = this->Makefile->GetDefinition(langFlags);
       fprintf(fout, "set(CMAKE_%s_FLAGS %s)\n", li->c_str(),
               lg->EscapeForCMake(flags?flags:"").c_str());
       fprintf(fout, "set(CMAKE_%s_FLAGS \"${CMAKE_%s_FLAGS}"
@@ -356,7 +357,7 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
       cmExportTryCompileFileGenerator tcfg;
       tcfg.SetExportFile((this->BinaryDirectory + fname).c_str());
       tcfg.SetExports(targets);
-      tcfg.SetConfig(this->Makefile->GetDefinition(
+      tcfg.SetConfig(this->Makefile->GetSafeDefinition(
                                           "CMAKE_TRY_COMPILE_CONFIGURATION"));
 
       if(!tcfg.GenerateImportFile())
@@ -449,7 +450,7 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
     fprintf(fout, "set(CMAKE_RUNTIME_OUTPUT_DIRECTORY \"%s\")\n",
             this->BinaryDirectory.c_str());
     /* Create the actual executable.  */
-    fprintf(fout, "add_executable(%s", targetName);
+    fprintf(fout, "add_executable(%s", targetName.c_str());
     for(std::vector<std::string>::iterator si = sources.begin();
         si != sources.end(); ++si)
       {
@@ -465,12 +466,13 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
     if (useOldLinkLibs)
       {
       fprintf(fout,
-              "target_link_libraries(%s ${LINK_LIBRARIES})\n",targetName);
+              "target_link_libraries(%s ${LINK_LIBRARIES})\n",
+              targetName.c_str());
       }
     else
       {
       fprintf(fout, "target_link_libraries(%s %s)\n",
-              targetName,
+              targetName.c_str(),
               libsToLink.c_str());
       }
     fclose(fout);
@@ -482,7 +484,7 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
   std::string output;
   // actually do the try compile now that everything is setup
   int res = this->Makefile->TryCompile(sourceDirectory,
-                                       this->BinaryDirectory.c_str(),
+                                       this->BinaryDirectory,
                                        projectName,
                                        targetName,
                                        this->SrcFileSignature,
@@ -494,14 +496,14 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
     }
 
   // set the result var to the return value to indicate success or failure
-  this->Makefile->AddCacheDefinition(argv[0].c_str(),
+  this->Makefile->AddCacheDefinition(argv[0],
                                      (res == 0 ? "TRUE" : "FALSE"),
                                      "Result of TRY_COMPILE",
                                      cmCacheManager::INTERNAL);
 
   if ( outputVariable.size() > 0 )
     {
-    this->Makefile->AddDefinition(outputVariable.c_str(), output.c_str());
+    this->Makefile->AddDefinition(outputVariable, output.c_str());
     }
 
   if (this->SrcFileSignature)
@@ -517,9 +519,9 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
         {
         cmOStringStream emsg;
         emsg << "Cannot copy output executable\n"
-             << "  '" << this->OutputFile.c_str() << "'\n"
+             << "  '" << this->OutputFile << "'\n"
              << "to destination specified by COPY_FILE:\n"
-             << "  '" << copyFile.c_str() << "'\n";
+             << "  '" << copyFile << "'\n";
         if(!this->FindErrorMessage.empty())
           {
           emsg << this->FindErrorMessage.c_str();
@@ -538,7 +540,7 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
 
     if(!copyFileError.empty())
       {
-      this->Makefile->AddDefinition(copyFileError.c_str(),
+      this->Makefile->AddDefinition(copyFileError,
                                     copyFileErrorMessage.c_str());
       }
     }
@@ -564,7 +566,7 @@ void cmCoreTryCompile::CleanupFiles(const char* binDir)
   cmsys::Directory dir;
   dir.Load(binDir);
   size_t fileNum;
-  std::set<cmStdString> deletedFiles;
+  std::set<std::string> deletedFiles;
   for (fileNum = 0; fileNum <  dir.GetNumberOfFiles(); ++fileNum)
     {
     if (strcmp(dir.GetFile(static_cast<unsigned long>(fileNum)),".") &&
@@ -609,7 +611,7 @@ void cmCoreTryCompile::CleanupFiles(const char* binDir)
     }
 }
 
-void cmCoreTryCompile::FindOutputFile(const char* targetName)
+void cmCoreTryCompile::FindOutputFile(const std::string& targetName)
 {
   this->FindErrorMessage = "";
   this->OutputFile = "";