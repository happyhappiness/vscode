@@ -119,8 +119,9 @@ int cmTryCompileCommand::CoreTryCompileCode(
   // do not allow recursive try Compiles
   if (!strcmp(binaryDirectory,mf->GetHomeOutputDirectory()))
     {
-    cmSystemTools::Error("Attempt at a recursive or nested TRY_COMPILE in directory ",
-                         binaryDirectory);
+    cmSystemTools::Error(
+      "Attempt at a recursive or nested TRY_COMPILE in directory ",
+      binaryDirectory);
     return -1;
     }
   
@@ -201,7 +202,8 @@ int cmTryCompileCommand::CoreTryCompileCode(
       }
     
     fprintf(fout, "ADD_EXECUTABLE(cmTryCompileExec \"%s\")\n",source.c_str());
-    fprintf(fout, "TARGET_LINK_LIBRARIES(cmTryCompileExec ${LINK_LIBRARIES})\n");
+    fprintf(fout, 
+            "TARGET_LINK_LIBRARIES(cmTryCompileExec ${LINK_LIBRARIES})\n");
     fclose(fout);
     projectName = "CMAKE_TRY_COMPILE";
     targetName = "cmTryCompileExec";
@@ -279,7 +281,9 @@ void cmTryCompileCommand::CleanupFiles(const char* binDir)
   std::string bdir = binDir;
   if(bdir.find("CMakeTmp") == std::string::npos)
     {
-    cmSystemTools::Error("TRY_COMPILE attempt to remove -rf directory that does not contain CMakeTmp:", binDir);
+    cmSystemTools::Error(
+      "TRY_COMPILE attempt to remove -rf directory that does not contain "
+      "CMakeTmp:", binDir);
     return;
     }
   