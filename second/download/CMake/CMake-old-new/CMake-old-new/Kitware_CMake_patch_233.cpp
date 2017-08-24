@@ -19,13 +19,42 @@
 
 #include <assert.h>
 
-int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
+int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv,
+                                     bool isTryRun)
 {
   this->BinaryDirectory = argv[1].c_str();
   this->OutputFile = "";
   // which signature were we called with ?
   this->SrcFileSignature = true;
 
+  cmState::TargetType targetType = cmState::EXECUTABLE;
+  const char* tt =
+    this->Makefile->GetDefinition("CMAKE_TRY_COMPILE_TARGET_TYPE");
+  if (!isTryRun && tt && *tt)
+    {
+    if (strcmp(tt, cmState::GetTargetTypeName(cmState::EXECUTABLE)) == 0)
+      {
+      targetType = cmState::EXECUTABLE;
+      }
+    else if (strcmp(tt,
+                    cmState::GetTargetTypeName(cmState::STATIC_LIBRARY)) == 0)
+      {
+      targetType = cmState::STATIC_LIBRARY;
+      }
+    else
+      {
+      this->Makefile->IssueMessage(
+        cmake::FATAL_ERROR,
+        std::string("Invalid value '") + tt + "' for "
+        "CMAKE_TRY_COMPILE_TARGET_TYPE.  Only "
+        "'" + cmState::GetTargetTypeName(cmState::EXECUTABLE) + "' and "
+        "'" + cmState::GetTargetTypeName(cmState::STATIC_LIBRARY) + "' "
+        "are allowed."
+        );
+      return -1;
+      }
+    }
+
   const char* sourceDirectory = argv[2].c_str();
   const char* projectName = 0;
   std::string targetName;
@@ -486,11 +515,22 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
       fprintf(fout, "set(CMAKE_ENABLE_EXPORTS %s)\n", ee);
       }
 
-    /* Put the executable at a known location (for COPY_FILE).  */
-    fprintf(fout, "set(CMAKE_RUNTIME_OUTPUT_DIRECTORY \"%s\")\n",
-            this->BinaryDirectory.c_str());
-    /* Create the actual executable.  */
-    fprintf(fout, "add_executable(%s", targetName.c_str());
+    if (targetType == cmState::EXECUTABLE)
+      {
+      /* Put the executable at a known location (for COPY_FILE).  */
+      fprintf(fout, "set(CMAKE_RUNTIME_OUTPUT_DIRECTORY \"%s\")\n",
+              this->BinaryDirectory.c_str());
+      /* Create the actual executable.  */
+      fprintf(fout, "add_executable(%s", targetName.c_str());
+      }
+    else // if (targetType == cmState::STATIC_LIBRARY)
+      {
+      /* Put the static library at a known location (for COPY_FILE).  */
+      fprintf(fout, "set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY \"%s\")\n",
+              this->BinaryDirectory.c_str());
+      /* Create the actual static library.  */
+      fprintf(fout, "add_library(%s STATIC", targetName.c_str());
+      }
     for(std::vector<std::string>::iterator si = sources.begin();
         si != sources.end(); ++si)
       {
@@ -549,7 +589,7 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
   if (this->SrcFileSignature)
     {
     std::string copyFileErrorMessage;
-    this->FindOutputFile(targetName);
+    this->FindOutputFile(targetName, targetType);
 
     if ((res==0) && !copyFile.empty())
       {
@@ -651,13 +691,26 @@ void cmCoreTryCompile::CleanupFiles(const char* binDir)
     }
 }
 
-void cmCoreTryCompile::FindOutputFile(const std::string& targetName)
+void cmCoreTryCompile::FindOutputFile(const std::string& targetName,
+                                      cmState::TargetType targetType)
 {
   this->FindErrorMessage = "";
   this->OutputFile = "";
   std::string tmpOutputFile = "/";
-  tmpOutputFile += targetName;
-  tmpOutputFile +=this->Makefile->GetSafeDefinition("CMAKE_EXECUTABLE_SUFFIX");
+  if (targetType == cmState::EXECUTABLE)
+    {
+    tmpOutputFile += targetName;
+    tmpOutputFile +=
+      this->Makefile->GetSafeDefinition("CMAKE_EXECUTABLE_SUFFIX");
+    }
+  else // if (targetType == cmState::STATIC_LIBRARY)
+    {
+    tmpOutputFile +=
+      this->Makefile->GetSafeDefinition("CMAKE_STATIC_LIBRARY_PREFIX");
+    tmpOutputFile += targetName;
+    tmpOutputFile +=
+      this->Makefile->GetSafeDefinition("CMAKE_STATIC_LIBRARY_SUFFIX");
+    }
 
   // a list of directories where to search for the compilation result
   // at first directly in the binary dir