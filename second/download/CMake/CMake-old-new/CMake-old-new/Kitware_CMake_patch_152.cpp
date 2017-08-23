@@ -43,24 +43,25 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv,
   // which signature were we called with ?
   this->SrcFileSignature = true;
 
-  cmState::TargetType targetType = cmState::EXECUTABLE;
+  cmStateEnums::TargetType targetType = cmStateEnums::EXECUTABLE;
   const char* tt =
     this->Makefile->GetDefinition("CMAKE_TRY_COMPILE_TARGET_TYPE");
   if (!isTryRun && tt && *tt) {
-    if (strcmp(tt, cmState::GetTargetTypeName(cmState::EXECUTABLE)) == 0) {
-      targetType = cmState::EXECUTABLE;
+    if (strcmp(tt, cmState::GetTargetTypeName(cmStateEnums::EXECUTABLE)) ==
+        0) {
+      targetType = cmStateEnums::EXECUTABLE;
     } else if (strcmp(tt, cmState::GetTargetTypeName(
-                            cmState::STATIC_LIBRARY)) == 0) {
-      targetType = cmState::STATIC_LIBRARY;
+                            cmStateEnums::STATIC_LIBRARY)) == 0) {
+      targetType = cmStateEnums::STATIC_LIBRARY;
     } else {
       this->Makefile->IssueMessage(
         cmake::FATAL_ERROR, std::string("Invalid value '") + tt +
           "' for "
           "CMAKE_TRY_COMPILE_TARGET_TYPE.  Only "
           "'" +
-          cmState::GetTargetTypeName(cmState::EXECUTABLE) + "' and "
-                                                            "'" +
-          cmState::GetTargetTypeName(cmState::STATIC_LIBRARY) +
+          cmState::GetTargetTypeName(cmStateEnums::EXECUTABLE) + "' and "
+                                                                 "'" +
+          cmState::GetTargetTypeName(cmStateEnums::STATIC_LIBRARY) +
           "' "
           "are allowed.");
       return -1;
@@ -122,12 +123,12 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv,
       libsToLink += "\"" + cmSystemTools::TrimWhitespace(argv[i]) + "\" ";
       if (cmTarget* tgt = this->Makefile->FindTargetToUse(argv[i])) {
         switch (tgt->GetType()) {
-          case cmState::SHARED_LIBRARY:
-          case cmState::STATIC_LIBRARY:
-          case cmState::INTERFACE_LIBRARY:
-          case cmState::UNKNOWN_LIBRARY:
+          case cmStateEnums::SHARED_LIBRARY:
+          case cmStateEnums::STATIC_LIBRARY:
+          case cmStateEnums::INTERFACE_LIBRARY:
+          case cmStateEnums::UNKNOWN_LIBRARY:
             break;
-          case cmState::EXECUTABLE:
+          case cmStateEnums::EXECUTABLE:
             if (tgt->IsExecutableWithExports()) {
               break;
             }
@@ -481,13 +482,13 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv,
               ? "NEW"
               : "OLD");
 
-    if (targetType == cmState::EXECUTABLE) {
+    if (targetType == cmStateEnums::EXECUTABLE) {
       /* Put the executable at a known location (for COPY_FILE).  */
       fprintf(fout, "set(CMAKE_RUNTIME_OUTPUT_DIRECTORY \"%s\")\n",
               this->BinaryDirectory.c_str());
       /* Create the actual executable.  */
       fprintf(fout, "add_executable(%s", targetName.c_str());
-    } else // if (targetType == cmState::STATIC_LIBRARY)
+    } else // if (targetType == cmStateEnums::STATIC_LIBRARY)
     {
       /* Put the static library at a known location (for COPY_FILE).  */
       fprintf(fout, "set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY \"%s\")\n",
@@ -627,16 +628,16 @@ void cmCoreTryCompile::CleanupFiles(const char* binDir)
 }
 
 void cmCoreTryCompile::FindOutputFile(const std::string& targetName,
-                                      cmState::TargetType targetType)
+                                      cmStateEnums::TargetType targetType)
 {
   this->FindErrorMessage = "";
   this->OutputFile = "";
   std::string tmpOutputFile = "/";
-  if (targetType == cmState::EXECUTABLE) {
+  if (targetType == cmStateEnums::EXECUTABLE) {
     tmpOutputFile += targetName;
     tmpOutputFile +=
       this->Makefile->GetSafeDefinition("CMAKE_EXECUTABLE_SUFFIX");
-  } else // if (targetType == cmState::STATIC_LIBRARY)
+  } else // if (targetType == cmStateEnums::STATIC_LIBRARY)
   {
     tmpOutputFile +=
       this->Makefile->GetSafeDefinition("CMAKE_STATIC_LIBRARY_PREFIX");