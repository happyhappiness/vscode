@@ -169,8 +169,9 @@ int cmCoreTryCompile::TryCompileCode(std::vector<std::string> const& argv)
     const char* lang =(this->Makefile->GetCMakeInstance()->GetGlobalGenerator()
                         ->GetLanguageFromExtension(ext.c_str()));
     const char* def = this->Makefile->GetDefinition("CMAKE_MODULE_PATH");
-    fprintf(fout, "cmake_minimum_required(VERSION %u.%u)\n",
-            cmVersion::GetMajorVersion(), cmVersion::GetMinorVersion());
+    fprintf(fout, "cmake_minimum_required(VERSION %u.%u.%u.%u)\n",
+            cmVersion::GetMajorVersion(), cmVersion::GetMinorVersion(),
+            cmVersion::GetPatchVersion(), cmVersion::GetTweakVersion());
     if(def)
       {
       fprintf(fout, "SET(CMAKE_MODULE_PATH %s)\n", def);
@@ -394,28 +395,18 @@ void cmCoreTryCompile::CleanupFiles(const char* binDir)
           }
         else
           {
-          if(!cmSystemTools::RemoveFile(fullPath.c_str()))
+          // Sometimes anti-virus software hangs on to new files so we
+          // cannot delete them immediately.  Try a few times.
+          int tries = 5;
+          while(!cmSystemTools::RemoveFile(fullPath.c_str()) &&
+                --tries && cmSystemTools::FileExists(fullPath.c_str()))
             {
-            bool removed = false;
-            int numAttempts = 0;
-            // sometimes anti-virus software hangs on to
-            // new files and we can not delete them, so try
-            // 5 times with .5 second delay between tries.
-            while(!removed && numAttempts < 5)
-              {
-              cmSystemTools::Delay(500);
-              if(cmSystemTools::RemoveFile(fullPath.c_str()))
-                {
-                removed = true;
-                }
-              numAttempts++;
-              }
-            if(!removed)
-              {
-              std::string m = "Remove failed on file: ";
-              m += fullPath;
-              cmSystemTools::ReportLastSystemError(m.c_str());
-              }
+            cmSystemTools::Delay(500);
+            }
+          if(tries == 0)
+            {
+            std::string m = "Remove failed on file: " + fullPath;
+            cmSystemTools::ReportLastSystemError(m.c_str());
             }
           }
         }