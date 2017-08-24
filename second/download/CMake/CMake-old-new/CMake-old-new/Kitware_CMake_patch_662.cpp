@@ -48,13 +48,16 @@ cmCTestScriptHandler::cmCTestScriptHandler()
 {
   m_Verbose = false; 
   m_Backup = false; 
+  m_EmptyBinDir = false;
+  m_EmptyBinDirOnce = false;
   m_Makefile = 0;
   m_LocalGenerator = 0;
   m_CMake = 0;
   m_GlobalGenerator = 0;
   
   // the *60 is becuase the settings are in minutes but GetTime is seconds
   m_MinimumInterval = 30*60;
+  m_ContinuousDuration = -1;
 }
 
 
@@ -177,13 +180,46 @@ int cmCTestScriptHandler::ExtractVariables()
   // get some info that should be set
   m_Makefile = m_LocalGenerator->GetMakefile();
 
-  m_SourceDir = m_Makefile->GetSafeDefinition("CTEST_SOURCE_DIRECTORY");
-  m_BinaryDir = m_Makefile->GetSafeDefinition("CTEST_BINARY_DIRECTORY");
-  m_CTestCmd  = m_Makefile->GetSafeDefinition("CTEST_COMMAND");
-  m_Backup    = m_Makefile->IsOn("CTEST_BACKUP_AND_RESTORE");
+  // Temporary variables
+  const char* minInterval;
+  const char* contDuration;
 
-  // in order to backup and restore we also must have the cvs root
+  m_SourceDir   = m_Makefile->GetSafeDefinition("CTEST_SOURCE_DIRECTORY");
+  m_BinaryDir   = m_Makefile->GetSafeDefinition("CTEST_BINARY_DIRECTORY");
+  m_CTestCmd    = m_Makefile->GetSafeDefinition("CTEST_COMMAND");
   m_CVSCheckOut = m_Makefile->GetSafeDefinition("CTEST_CVS_CHECKOUT");
+  m_CTestRoot   = m_Makefile->GetSafeDefinition("CTEST_DASHBOARD_ROOT");
+  m_CVSCmd      = m_Makefile->GetSafeDefinition("CTEST_CVS_COMMAND");
+  m_CTestEnv    = m_Makefile->GetSafeDefinition("CTEST_ENVIRONMENT");
+  m_InitCache   = m_Makefile->GetSafeDefinition("CTEST_INITIAL_CACHE");
+  m_CMakeCmd    = m_Makefile->GetSafeDefinition("CTEST_CMAKE_COMMAND");
+  m_CMOutFile   = m_Makefile->GetSafeDefinition("CTEST_CMAKE_OUTPUT_FILE_NAME");
+
+  m_Backup      = m_Makefile->IsOn("CTEST_BACKUP_AND_RESTORE");
+  m_EmptyBinDir = m_Makefile->IsOn("CTEST_START_WITH_EMPTY_BINARY_DIRECTORY");
+  m_EmptyBinDirOnce = m_Makefile->IsOn("CTEST_START_WITH_EMPTY_BINARY_DIRECTORY_ONCE");
+
+  minInterval   = m_Makefile->GetDefinition("CTEST_CONTINUOUS_MINIMUM_INTERVAL");
+  contDuration  = m_Makefile->GetDefinition("CTEST_CONTINUOUS_DURATION");
+
+  char updateVar[40];
+  int i;
+  for (i = 1; i < 10; ++i)
+    {
+    sprintf(updateVar,"CTEST_EXTRA_UPDATES_%i",i);
+    const char *updateVal = m_Makefile->GetDefinition(updateVar);
+    if ( updateVal )
+      {
+      if ( m_CVSCmd.empty() )
+        {
+        cmSystemTools::Error(updateVar, " specified without specifying CTEST_CVS_COMMAND.");
+        return 12;
+        }
+      m_ExtraUpdates.push_back(updateVal);
+      }
+    }
+
+  // in order to backup and restore we also must have the cvs root
   if (m_Backup && m_CVSCheckOut.empty())
     {
     cmSystemTools::Error(
@@ -210,23 +246,21 @@ int cmCTestScriptHandler::ExtractVariables()
   
   // if the dashboard root isn't specified then we can compute it from the
   // m_SourceDir
-  if (m_Makefile->GetDefinition("CTEST_DASHBOARD_ROOT"))
-    {
-    m_CTestRoot = m_Makefile->GetDefinition("CTEST_DASHBOARD_ROOT");
-    }
-  else
+  if (m_CTestRoot.empty() )
     {
     m_CTestRoot = cmSystemTools::GetFilenamePath(m_SourceDir).c_str();
     }
 
   // the script may override the minimum continuous interval
-  if (m_Makefile->GetDefinition("CTEST_CONTINUOUS_MINIMUM_INTERVAL"))
+  if (minInterval)
     {
-    m_MinimumInterval = 60*
-      atof(m_Makefile->GetDefinition("CTEST_CONTINUOUS_MINIMUM_INTERVAL"));
+    m_MinimumInterval = 60 * atof(minInterval);
+    }
+  if (contDuration)
+    {
+    m_ContinuousDuration = 60.0 * atof(contDuration);
     }
   
-  m_CVSCmd = m_Makefile->GetSafeDefinition("CTEST_CVS_COMMAND");
   
   return 0;
 }
@@ -266,11 +300,10 @@ int cmCTestScriptHandler::RunConfigurationScript(
     }
   
   // set any environment variables
-  const char *ctestEnv = m_Makefile->GetDefinition("CTEST_ENVIRONMENT");
-  if (ctestEnv)
+  if (!m_CTestEnv.empty())
     {
     std::vector<std::string> envArgs;
-    cmSystemTools::ExpandListArgument(ctestEnv,envArgs);
+    cmSystemTools::ExpandListArgument(m_CTestEnv.c_str(),envArgs);
     // for each variable/argument do a putenv
     for (unsigned i = 0; i < envArgs.size(); ++i)
       {
@@ -281,13 +314,12 @@ int cmCTestScriptHandler::RunConfigurationScript(
   // now that we have done most of the error checking finally run the
   // dashboard, we may be asked to repeatedly run this dashboard, such as
   // for a continuous, do we ned to run it more than once?
-  if (m_Makefile->GetDefinition("CTEST_CONTINUOUS_DURATION"))
+  if ( m_ContinuousDuration >= 0 )
     {
-    double ending_time  = cmSystemTools::GetTime() + 
-      60.0*atof(m_Makefile->GetDefinition("CTEST_CONTINUOUS_DURATION"));
-    if (m_Makefile->IsOn("CTEST_START_WITH_EMPTY_BINARY_DIRECTORY_ONCE"))
+    double ending_time  = cmSystemTools::GetTime() + m_ContinuousDuration;
+    if (m_EmptyBinDirOnce)
       {
-      m_Makefile->AddDefinition("CTEST_START_WITH_EMPTY_BINARY_DIRECTORY","1");
+      m_EmptyBinDir = true;
       }
     do
       {
@@ -299,10 +331,9 @@ int cmCTestScriptHandler::RunConfigurationScript(
         this->LocalSleep(
           static_cast<unsigned int>(m_MinimumInterval - interval));
         }
-      if (m_Makefile->IsOn("CTEST_START_WITH_EMPTY_BINARY_DIRECTORY_ONCE"))
+      if (m_EmptyBinDirOnce)
         {
-        m_Makefile->AddDefinition("CTEST_START_WITH_EMPTY_BINARY_DIRECTORY",
-                                  "0");
+        m_EmptyBinDir = false;
         }
       }
     while (cmSystemTools::GetTime() < ending_time);
@@ -397,43 +428,31 @@ int cmCTestScriptHandler::PerformExtraUpdates()
 
   // do an initial cvs update as required
   command = m_CVSCmd;
-  char updateVar[40];
-  int i;
-  for (i = 1; i < 10; ++i)
+  std::vector<cmStdString>::iterator it;
+  for (it = m_ExtraUpdates.begin(); it != m_ExtraUpdates.end(); ++ it )
     {
-    sprintf(updateVar,"CTEST_EXTRA_UPDATES_%i",i);
-    const char *updateVal = m_Makefile->GetDefinition(updateVar);
-    if (updateVal)
+    std::vector<std::string> cvsArgs;
+    cmSystemTools::ExpandListArgument(it->c_str(),cvsArgs);
+    if (cvsArgs.size() == 2)
       {
-      if (m_CVSCmd.empty())
+      std::string fullCommand = command;
+      fullCommand += " update ";
+      fullCommand += cvsArgs[1];
+      output = "";
+      retVal = 0;
+      if ( m_Verbose )
         {
-        cmSystemTools::Error(updateVar, " specified without specifying CTEST_CVS_COMMAND.");
-        this->RestoreBackupDirectories();
-        return 12;
+        std::cerr << "Run CVS: " << fullCommand.c_str() << std::endl;
         }
-      std::vector<std::string> cvsArgs;
-      cmSystemTools::ExpandListArgument(updateVal,cvsArgs);
-      if (cvsArgs.size() == 2)
+      res = cmSystemTools::RunSingleCommand(fullCommand.c_str(), &output, 
+        &retVal, cvsArgs[0].c_str(),
+        m_Verbose, 0 /*m_TimeOut*/);
+      if (!res || retVal != 0)
         {
-        std::string fullCommand = command;
-        fullCommand += " update ";
-        fullCommand += cvsArgs[1];
-        output = "";
-        retVal = 0;
-        if ( m_Verbose )
-          {
-          std::cerr << "Run CVS: " << fullCommand.c_str() << std::endl;
-          }
-        res = cmSystemTools::RunSingleCommand(fullCommand.c_str(), &output, 
-          &retVal, cvsArgs[0].c_str(),
-          m_Verbose, 0 /*m_TimeOut*/);
-        if (!res || retVal != 0)
-          {
-          cmSystemTools::Error("Unable to perform extra cvs updates:\n", 
-            output.c_str());
-          this->RestoreBackupDirectories();
-          return 8;
-          }
+        cmSystemTools::Error("Unable to perform extra cvs updates:\n", 
+          output.c_str());
+        this->RestoreBackupDirectories();
+        return 8;
         }
       }
     }
@@ -467,7 +486,7 @@ int cmCTestScriptHandler::RunConfigurationDashboard()
     }
   
   // clear the binary directory?
-  if (m_Makefile->IsOn("CTEST_START_WITH_EMPTY_BINARY_DIRECTORY"))
+  if (m_EmptyBinDir)
     {
     // try to avoid deleting directories that we shouldn't
     std::string check = m_BinaryDir;
@@ -494,8 +513,7 @@ int cmCTestScriptHandler::RunConfigurationDashboard()
   // if the binary directory and the source directory are the same,
   // and we are starting with an empty binary directory, then that means
   // we must check out the source tree
-  if (m_Makefile->IsOn("CTEST_START_WITH_EMPTY_BINARY_DIRECTORY") &&
-      m_SourceDir == m_BinaryDir)
+  if (m_EmptyBinDir && m_SourceDir == m_BinaryDir)
     {
     // make sure we have the required info
     if (m_CVSCheckOut.empty())
@@ -521,9 +539,8 @@ int cmCTestScriptHandler::RunConfigurationDashboard()
     }
 
   // put the initial cache into the bin dir
-  if (m_Makefile->GetDefinition("CTEST_INITIAL_CACHE"))
+  if (!m_InitCache.empty())
     {
-    const char *initCache = m_Makefile->GetDefinition("CTEST_INITIAL_CACHE");
     std::string cacheFile = m_BinaryDir;
     cacheFile += "/CMakeCache.txt";
     std::ofstream fout(cacheFile.c_str());
@@ -533,7 +550,7 @@ int cmCTestScriptHandler::RunConfigurationDashboard()
       return 9;
       }
 
-    fout.write(initCache, strlen(initCache));
+    fout.write(m_InitCache.c_str(), m_InitCache.size());
 
     // Make sure the operating system has finished writing the file
     // before closing it.  This will ensure the file is finished before
@@ -543,12 +560,11 @@ int cmCTestScriptHandler::RunConfigurationDashboard()
     }
 
   // do an initial cmake to setup the DartConfig file
-  const char *cmakeCmd = m_Makefile->GetDefinition("CTEST_CMAKE_COMMAND");
   int cmakeFailed = 0;
   std::string cmakeFailedOuput;
-  if (cmakeCmd)
+  if (!m_CMakeCmd.empty())
     {
-    command = cmakeCmd;
+    command = m_CMakeCmd;
     command += " \"";
     command += m_SourceDir;
     output = "";
@@ -562,11 +578,9 @@ int cmCTestScriptHandler::RunConfigurationDashboard()
       &retVal, m_BinaryDir.c_str(),
       m_Verbose, 0 /*m_TimeOut*/);
 
-    const char* cmakeOutputFileName =
-      m_Makefile->GetDefinition("CTEST_CMAKE_OUTPUT_FILE_NAME");
-    if ( cmakeOutputFileName )
+    if ( !m_CMOutFile.empty() )
       {
-      std::string cmakeOutputFile = cmakeOutputFileName;
+      std::string cmakeOutputFile = m_CMOutFile;
       if ( !cmSystemTools::FileIsFullPath(cmakeOutputFile.c_str()) )
         {
         cmakeOutputFile = m_BinaryDir + "/" + cmakeOutputFile;