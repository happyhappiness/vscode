@@ -137,6 +137,8 @@ BOOL CMakeSetupDialog::OnInitDialog()
   this->LoadFromRegistry();
   // try to load the cmake cache from disk
   this->LoadCacheFromDiskToGUI();
+  m_WhereBuildControl.LimitText(2048);
+  m_WhereSourceControl.LimitText(2048);
   // Set the version number
   char tmp[1024];
   sprintf(tmp,"Version %s", cmMakefile::GetVersion());
@@ -435,15 +437,6 @@ void CMakeSetupDialog::OnBuildProjects()
   CString makefileIn = m_WhereSource;
   makefileIn += "/CMakeLists.txt";
   makefile.ReadListFile(makefileIn); 
-  if(!cmCacheManager::GetInstance()->GetCacheValue("CMAKE_CXX"))
-    {
-    if(!makefile.GetDefinition("CMAKE_CXX"))
-      {
-      makefile.AddDefinition("CMAKE_CXX", "VC60");
-      }
-    cmCacheManager::GetInstance()->AddCacheEntry("CMAKE_CXX", "VC60",
-                                                 "Compiler used", cmCacheManager::STRING);
-    }
   // Generate the project files
   makefile.GenerateMakefile();
   // Save the cache