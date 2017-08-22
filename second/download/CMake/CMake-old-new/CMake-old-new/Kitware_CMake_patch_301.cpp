@@ -28,7 +28,7 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
 
   const char* sourceDirectory = argv[2].c_str();
   const char* projectName = 0;
-  const char* targetName = 0;
+  std::string targetName;
   std::vector<std::string> cmakeFlags;
   std::vector<std::string> compileDefs;
   std::string outputVariable;
@@ -450,7 +450,7 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
     fprintf(fout, "set(CMAKE_RUNTIME_OUTPUT_DIRECTORY \"%s\")\n",
             this->BinaryDirectory.c_str());
     /* Create the actual executable.  */
-    fprintf(fout, "add_executable(%s", targetName);
+    fprintf(fout, "add_executable(%s", targetName.c_str());
     for(std::vector<std::string>::iterator si = sources.begin();
         si != sources.end(); ++si)
       {
@@ -466,12 +466,13 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
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
@@ -610,7 +611,7 @@ void cmCoreTryCompile::CleanupFiles(const char* binDir)
     }
 }
 
-void cmCoreTryCompile::FindOutputFile(const char* targetName)
+void cmCoreTryCompile::FindOutputFile(const std::string& targetName)
 {
   this->FindErrorMessage = "";
   this->OutputFile = "";