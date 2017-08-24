@@ -22,12 +22,12 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
   // which signature were we called with ?
   this->SrcFileSignature = false;
   unsigned int i;
-  
+
   const char* sourceDirectory = argv[2].c_str();
   const char* projectName = 0;
   const char* targetName = 0;
   int extraArgs = 0;
-  
+
   // look for CMAKE_FLAGS and store them
   std::vector<std::string> cmakeFlags;
   for (i = 3; i < argv.size(); ++i)
@@ -37,8 +37,8 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
      // CMAKE_FLAGS is the first argument because we need an argv[0] that
      // is not used, so it matches regular command line parsing which has
      // the program name as arg 0
-      for (; i < argv.size() && argv[i] != "COMPILE_DEFINITIONS" && 
-             argv[i] != "OUTPUT_VARIABLE"; 
+      for (; i < argv.size() && argv[i] != "COMPILE_DEFINITIONS" &&
+             argv[i] != "OUTPUT_VARIABLE";
            ++i)
         {
         extraArgs++;
@@ -73,8 +73,8 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
     if (argv[i] == "COMPILE_DEFINITIONS")
       {
       extraArgs++;
-      for (i = i + 1; i < argv.size() && argv[i] != "CMAKE_FLAGS" && 
-             argv[i] != "OUTPUT_VARIABLE"; 
+      for (i = i + 1; i < argv.size() && argv[i] != "CMAKE_FLAGS" &&
+             argv[i] != "OUTPUT_VARIABLE";
            ++i)
         {
         extraArgs++;
@@ -101,7 +101,7 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
       break;
       }
     }
-    
+
   // do we have a srcfile signature
   if (argv.size() - extraArgs == 3)
     {
@@ -133,7 +133,7 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
     }
   // make sure the binary directory exists
   cmSystemTools::MakeDirectory(this->BinaryDirectory.c_str());
-  
+
   // do not allow recursive try Compiles
   if (this->BinaryDirectory == this->Makefile->GetHomeOutputDirectory())
     {
@@ -143,15 +143,15 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
     this->Makefile->IssueMessage(cmake::FATAL_ERROR, e.str());
     return -1;
     }
-  
+
   std::string outFileName = this->BinaryDirectory + "/CMakeLists.txt";
   // which signature are we using? If we are using var srcfile bindir
   if (this->SrcFileSignature)
     {
     // remove any CMakeCache.txt files so we will have a clean test
     std::string ccFile = this->BinaryDirectory + "/CMakeCache.txt";
     cmSystemTools::RemoveFile(ccFile.c_str());
-    
+
     // we need to create a directory and CMakeList file etc...
     // first create the directories
     sourceDirectory = this->BinaryDirectory.c_str();
@@ -226,7 +226,7 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
     langFlags += "_FLAGS";
     fprintf(fout, "SET(CMAKE_VERBOSE_MAKEFILE 1)\n");
     fprintf(fout, "SET(CMAKE_%s_FLAGS \"", lang);
-    const char* flags = this->Makefile->GetDefinition(langFlags.c_str()); 
+    const char* flags = this->Makefile->GetDefinition(langFlags.c_str());
     if(flags)
       {
       fprintf(fout, " %s ", flags);
@@ -247,10 +247,10 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
       }
 
     /* for the TRY_COMPILEs we want to be able to specify the architecture.
-      So the user can set CMAKE_OSX_ARCHITECTURE to i386;ppc and then set 
+      So the user can set CMAKE_OSX_ARCHITECTURE to i386;ppc and then set
       CMAKE_TRY_COMPILE_OSX_ARCHITECTURE first to i386 and then to ppc to
-      have the tests run for each specific architecture. Since 
-      cmLocalGenerator doesn't allow building for "the other" 
+      have the tests run for each specific architecture. Since
+      cmLocalGenerator doesn't allow building for "the other"
       architecture only via CMAKE_OSX_ARCHITECTURES.
       */
     if(this->Makefile->GetDefinition("CMAKE_TRY_COMPILE_OSX_ARCHITECTURES")!=0)
@@ -286,45 +286,45 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
             this->BinaryDirectory.c_str());
     /* Create the actual executable.  */
     fprintf(fout, "ADD_EXECUTABLE(cmTryCompileExec \"%s\")\n",source.c_str());
-    fprintf(fout, 
+    fprintf(fout,
             "TARGET_LINK_LIBRARIES(cmTryCompileExec ${LINK_LIBRARIES})\n");
     fclose(fout);
     projectName = "CMAKE_TRY_COMPILE";
     targetName = "cmTryCompileExec";
-    // if the source is not in CMakeTmp 
+    // if the source is not in CMakeTmp
     if(source.find("CMakeTmp") == source.npos)
       {
       this->Makefile->AddCMakeDependFile(source.c_str());
       }
-    
+
     }
   // else the srcdir bindir project target signature
   else
     {
     projectName = argv[3].c_str();
-    
+
     if (argv.size() - extraArgs == 5)
       {
       targetName = argv[4].c_str();
       }
     }
-  
+
   bool erroroc = cmSystemTools::GetErrorOccuredFlag();
   cmSystemTools::ResetErrorOccuredFlag();
   std::string output;
   // actually do the try compile now that everything is setup
-  int res = this->Makefile->TryCompile(sourceDirectory, 
+  int res = this->Makefile->TryCompile(sourceDirectory,
                                        this->BinaryDirectory.c_str(),
-                                       projectName, 
-                                       targetName, 
+                                       projectName,
+                                       targetName,
                                        this->SrcFileSignature,
-                                       &cmakeFlags, 
+                                       &cmakeFlags,
                                        &output);
   if ( erroroc )
     {
     cmSystemTools::SetErrorOccured();
     }
-  
+
   // set the result var to the return value to indicate success or failure
   this->Makefile->AddCacheDefinition(argv[0].c_str(),
                                      (res == 0 ? "TRUE" : "FALSE"),
@@ -335,7 +335,7 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
     {
     this->Makefile->AddDefinition(outputVariable.c_str(), output.c_str());
     }
-  
+
   if (this->SrcFileSignature)
     {
     this->FindOutputFile(targetName);
@@ -369,7 +369,7 @@ void cmCoreTryCompile::CleanupFiles(const char* binDir)
     {
     return;
     }
-  
+
   std::string bdir = binDir;
   if(bdir.find("CMakeTmp") == std::string::npos)
     {
@@ -378,7 +378,7 @@ void cmCoreTryCompile::CleanupFiles(const char* binDir)
       "CMakeTmp:", binDir);
     return;
     }
-  
+
   cmsys::Directory dir;
   dir.Load(binDir);
   size_t fileNum;
@@ -388,8 +388,8 @@ void cmCoreTryCompile::CleanupFiles(const char* binDir)
     if (strcmp(dir.GetFile(static_cast<unsigned long>(fileNum)),".") &&
         strcmp(dir.GetFile(static_cast<unsigned long>(fileNum)),".."))
       {
-      
-      if(deletedFiles.find( dir.GetFile(static_cast<unsigned long>(fileNum))) 
+
+      if(deletedFiles.find( dir.GetFile(static_cast<unsigned long>(fileNum)))
          == deletedFiles.end())
         {
         deletedFiles.insert(dir.GetFile(static_cast<unsigned long>(fileNum)));