@@ -68,98 +68,98 @@ class cmCTestScriptFunctionBlocker : public cmFunctionBlocker
   //virtual bool ShouldRemove(const cmListFileFunction& lff, cmMakefile &mf);
   //virtual void ScopeEnded(cmMakefile &mf);
 
-  cmCTestScriptHandler* m_CTestScriptHandler;
+  cmCTestScriptHandler* CTestScriptHandler;
 };
 
 // simply update the time and don't block anything
 bool cmCTestScriptFunctionBlocker::
 IsFunctionBlocked(const cmListFileFunction& , cmMakefile &)
 {
-  m_CTestScriptHandler->UpdateElapsedTime();
+  this->CTestScriptHandler->UpdateElapsedTime();
   return false;
 }
 
 //----------------------------------------------------------------------
 cmCTestScriptHandler::cmCTestScriptHandler()
 {
-  m_Backup = false;
-  m_EmptyBinDir = false;
-  m_EmptyBinDirOnce = false;
-  m_Makefile = 0;
-  m_LocalGenerator = 0;
-  m_CMake = 0;
-  m_GlobalGenerator = 0;
+  this->Backup = false;
+  this->EmptyBinDir = false;
+  this->EmptyBinDirOnce = false;
+  this->Makefile = 0;
+  this->LocalGenerator = 0;
+  this->CMake = 0;
+  this->GlobalGenerator = 0;
 
-  m_ScriptStartTime = 0;
+  this->ScriptStartTime = 0;
 
   // the *60 is becuase the settings are in minutes but GetTime is seconds
-  m_MinimumInterval = 30*60;
-  m_ContinuousDuration = -1;
+  this->MinimumInterval = 30*60;
+  this->ContinuousDuration = -1;
 }
 
 //----------------------------------------------------------------------
 void cmCTestScriptHandler::Initialize()
 {
   this->Superclass::Initialize();
-  m_Backup = false;
-  m_EmptyBinDir = false;
-  m_EmptyBinDirOnce = false;
-
-  m_SourceDir = "";
-  m_BinaryDir = "";
-  m_BackupSourceDir = "";
-  m_BackupBinaryDir = "";
-  m_CTestRoot = "";
-  m_CVSCheckOut = "";
-  m_CTestCmd = "";
-  m_CVSCmd = "";
-  m_CTestEnv = "";
-  m_InitCache = "";
-  m_CMakeCmd = "";
-  m_CMOutFile = "";
-  m_ExtraUpdates.clear();
-
-  m_MinimumInterval = 20*60;
-  m_ContinuousDuration = -1;
+  this->Backup = false;
+  this->EmptyBinDir = false;
+  this->EmptyBinDirOnce = false;
+
+  this->SourceDir = "";
+  this->BinaryDir = "";
+  this->BackupSourceDir = "";
+  this->BackupBinaryDir = "";
+  this->CTestRoot = "";
+  this->CVSCheckOut = "";
+  this->CTestCmd = "";
+  this->CVSCmd = "";
+  this->CTestEnv = "";
+  this->InitCache = "";
+  this->CMakeCmd = "";
+  this->CMOutFile = "";
+  this->ExtraUpdates.clear();
+
+  this->MinimumInterval = 20*60;
+  this->ContinuousDuration = -1;
 
   // what time in seconds did this script start running
-  m_ScriptStartTime = 0;
+  this->ScriptStartTime = 0;
 
-  m_Makefile = 0;
-  if (m_LocalGenerator)
+  this->Makefile = 0;
+  if (this->LocalGenerator)
     {
-    delete m_LocalGenerator;
+    delete this->LocalGenerator;
     }
-  m_LocalGenerator = 0;
-  if (m_GlobalGenerator)
+  this->LocalGenerator = 0;
+  if (this->GlobalGenerator)
     {
-    delete m_GlobalGenerator;
+    delete this->GlobalGenerator;
     }
-  m_GlobalGenerator = 0;
-  if (m_CMake)
+  this->GlobalGenerator = 0;
+  if (this->CMake)
     {
-    delete m_CMake;
+    delete this->CMake;
     }
 }
 
 //----------------------------------------------------------------------
 cmCTestScriptHandler::~cmCTestScriptHandler()
 {
   // local generator owns the makefile
-  m_Makefile = 0;
-  if (m_LocalGenerator)
+  this->Makefile = 0;
+  if (this->LocalGenerator)
     {
-    delete m_LocalGenerator;
+    delete this->LocalGenerator;
     }
-  m_LocalGenerator = 0;
-  if (m_GlobalGenerator)
+  this->LocalGenerator = 0;
+  if (this->GlobalGenerator)
     {
-    delete m_GlobalGenerator;
+    delete this->GlobalGenerator;
     }
-  m_GlobalGenerator = 0;
-  if (m_CMake)
+  this->GlobalGenerator = 0;
+  if (this->CMake)
     {
-    delete m_CMake;
+    delete this->CMake;
     }
 }
 
@@ -168,7 +168,7 @@ cmCTestScriptHandler::~cmCTestScriptHandler()
 // just adds an argument to the vector
 void cmCTestScriptHandler::AddConfigurationScript(const char *script)
 {
-  m_ConfigurationScripts.push_back(script);
+  this->ConfigurationScripts.push_back(script);
 }
 
 
@@ -179,8 +179,8 @@ int cmCTestScriptHandler::ProcessHandler()
 {
   int res = 0;
   std::vector<cmStdString>::iterator it;
-  for ( it = m_ConfigurationScripts.begin();
-        it != m_ConfigurationScripts.end();
+  for ( it = this->ConfigurationScripts.begin();
+        it != this->ConfigurationScripts.end();
         it ++ )
     {
     // for each script run it
@@ -196,14 +196,14 @@ int cmCTestScriptHandler::ProcessHandler()
 
 void cmCTestScriptHandler::UpdateElapsedTime()
 {
-  if (m_LocalGenerator)
+  if (this->LocalGenerator)
     {
     // set the current elapsed time
     char timeString[20];
     int itime = static_cast<unsigned int>(cmSystemTools::GetTime()
-                                          - m_ScriptStartTime);
+                                          - this->ScriptStartTime);
     sprintf(timeString,"%i",itime);
-    m_LocalGenerator->GetMakefile()->AddDefinition("CTEST_ELAPSED_TIME",
+    this->LocalGenerator->GetMakefile()->AddDefinition("CTEST_ELAPSED_TIME",
                                                    timeString);
     }
 }
@@ -212,9 +212,9 @@ void cmCTestScriptHandler::UpdateElapsedTime()
 void cmCTestScriptHandler::AddCTestCommand(cmCTestCommand* command)
 {
   cmCTestCommand* newCom = command;
-  newCom->m_CTest = m_CTest;
-  newCom->m_CTestScriptHandler = this;
-  m_CMake->AddCommand(newCom);
+  newCom->CTest = this->CTest;
+  newCom->CTestScriptHandler = this;
+  this->CMake->AddCommand(newCom);
 }
 
 //----------------------------------------------------------------------
@@ -242,31 +242,31 @@ int cmCTestScriptHandler::ReadInScript(const std::string& total_script_arg)
 
   // create a cmake instance to read the configuration script
   // read in the list file to fill the cache
-  if (m_CMake)
+  if (this->CMake)
     {
-    delete m_CMake;
-    delete m_GlobalGenerator;
-    delete m_LocalGenerator;
+    delete this->CMake;
+    delete this->GlobalGenerator;
+    delete this->LocalGenerator;
     }
-  m_CMake = new cmake;
-  m_CMake->AddCMakePaths(m_CTest->GetCTestExecutable());
-  m_GlobalGenerator = new cmGlobalGenerator;
-  m_GlobalGenerator->SetCMakeInstance(m_CMake);
+  this->CMake = new cmake;
+  this->CMake->AddCMakePaths(this->CTest->GetCTestExecutable());
+  this->GlobalGenerator = new cmGlobalGenerator;
+  this->GlobalGenerator->SetCMakeInstance(this->CMake);
 
-  m_LocalGenerator = m_GlobalGenerator->CreateLocalGenerator();
-  m_LocalGenerator->SetGlobalGenerator(m_GlobalGenerator);
-  m_Makefile = m_LocalGenerator->GetMakefile();
+  this->LocalGenerator = this->GlobalGenerator->CreateLocalGenerator();
+  this->LocalGenerator->SetGlobalGenerator(this->GlobalGenerator);
+  this->Makefile = this->LocalGenerator->GetMakefile();
 
   // set a variable with the path to the current script
-  m_Makefile->AddDefinition("CTEST_SCRIPT_DIRECTORY",
+  this->Makefile->AddDefinition("CTEST_SCRIPT_DIRECTORY",
                             cmSystemTools::GetFilenamePath(script).c_str());
-  m_Makefile->AddDefinition("CTEST_SCRIPT_NAME",
+  this->Makefile->AddDefinition("CTEST_SCRIPT_NAME",
                             cmSystemTools::GetFilenameName(script).c_str());
-  m_Makefile->AddDefinition("CTEST_EXECUTABLE_NAME",
-                            m_CTest->GetCTestExecutable());
-  m_Makefile->AddDefinition("CMAKE_EXECUTABLE_NAME",
-                            m_CTest->GetCMakeExecutable());
-  m_Makefile->AddDefinition("CTEST_RUN_CURRENT_SCRIPT", true);
+  this->Makefile->AddDefinition("CTEST_EXECUTABLE_NAME",
+                            this->CTest->GetCTestExecutable());
+  this->Makefile->AddDefinition("CMAKE_EXECUTABLE_NAME",
+                            this->CTest->GetCMakeExecutable());
+  this->Makefile->AddDefinition("CTEST_RUN_CURRENT_SCRIPT", true);
   this->UpdateElapsedTime();
 
   // add any ctest specific commands, probably should have common superclass
@@ -287,16 +287,16 @@ int cmCTestScriptHandler::ReadInScript(const std::string& total_script_arg)
   // add the script arg if defined
   if (script_arg.size())
     {
-    m_Makefile->AddDefinition("CTEST_SCRIPT_ARG", script_arg.c_str());
+    this->Makefile->AddDefinition("CTEST_SCRIPT_ARG", script_arg.c_str());
     }
 
   // always add a function blocker to update the elapsed time
   cmCTestScriptFunctionBlocker *f = new cmCTestScriptFunctionBlocker();
-  f->m_CTestScriptHandler = this;
-  m_Makefile->AddFunctionBlocker(f);
+  f->CTestScriptHandler = this;
+  this->Makefile->AddFunctionBlocker(f);
 
   // finally read in the script
-  if (!m_Makefile->ReadListFile(0, script.c_str()))
+  if (!this->Makefile->ReadListFile(0, script.c_str()))
     {
     return 2;
     }
@@ -313,85 +313,97 @@ int cmCTestScriptHandler::ExtractVariables()
   const char* minInterval;
   const char* contDuration;
 
-  m_SourceDir   = m_Makefile->GetSafeDefinition("CTEST_SOURCE_DIRECTORY");
-  m_BinaryDir   = m_Makefile->GetSafeDefinition("CTEST_BINARY_DIRECTORY");
-  m_CTestCmd    = m_Makefile->GetSafeDefinition("CTEST_COMMAND");
-  m_CVSCheckOut = m_Makefile->GetSafeDefinition("CTEST_CVS_CHECKOUT");
-  m_CTestRoot   = m_Makefile->GetSafeDefinition("CTEST_DASHBOARD_ROOT");
-  m_CVSCmd      = m_Makefile->GetSafeDefinition("CTEST_CVS_COMMAND");
-  m_CTestEnv    = m_Makefile->GetSafeDefinition("CTEST_ENVIRONMENT");
-  m_InitCache   = m_Makefile->GetSafeDefinition("CTEST_INITIAL_CACHE");
-  m_CMakeCmd    = m_Makefile->GetSafeDefinition("CTEST_CMAKE_COMMAND");
-  m_CMOutFile
-    = m_Makefile->GetSafeDefinition("CTEST_CMAKE_OUTPUT_FILE_NAME");
-
-  m_Backup      = m_Makefile->IsOn("CTEST_BACKUP_AND_RESTORE");
-  m_EmptyBinDir = m_Makefile->IsOn("CTEST_START_WITH_EMPTY_BINARY_DIRECTORY");
-  m_EmptyBinDirOnce
-    = m_Makefile->IsOn("CTEST_START_WITH_EMPTY_BINARY_DIRECTORY_ONCE");
+  this->SourceDir
+    = this->Makefile->GetSafeDefinition("CTEST_SOURCE_DIRECTORY");
+  this->BinaryDir
+    = this->Makefile->GetSafeDefinition("CTEST_BINARY_DIRECTORY");
+  this->CTestCmd
+    = this->Makefile->GetSafeDefinition("CTEST_COMMAND");
+  this->CVSCheckOut
+    = this->Makefile->GetSafeDefinition("CTEST_CVS_CHECKOUT");
+  this->CTestRoot
+    = this->Makefile->GetSafeDefinition("CTEST_DASHBOARD_ROOT");
+  this->CVSCmd
+    = this->Makefile->GetSafeDefinition("CTEST_CVS_COMMAND");
+  this->CTestEnv
+    = this->Makefile->GetSafeDefinition("CTEST_ENVIRONMENT");
+  this->InitCache
+    = this->Makefile->GetSafeDefinition("CTEST_INITIAL_CACHE");
+  this->CMakeCmd
+    = this->Makefile->GetSafeDefinition("CTEST_CMAKE_COMMAND");
+  this->CMOutFile
+    = this->Makefile->GetSafeDefinition("CTEST_CMAKE_OUTPUT_FILE_NAME");
+
+  this->Backup
+    = this->Makefile->IsOn("CTEST_BACKUP_AND_RESTORE");
+  this->EmptyBinDir
+    = this->Makefile->IsOn("CTEST_START_WITH_EMPTY_BINARY_DIRECTORY");
+  this->EmptyBinDirOnce
+    = this->Makefile->IsOn("CTEST_START_WITH_EMPTY_BINARY_DIRECTORY_ONCE");
 
   minInterval
-    = m_Makefile->GetDefinition("CTEST_CONTINUOUS_MINIMUM_INTERVAL");
-  contDuration  = m_Makefile->GetDefinition("CTEST_CONTINUOUS_DURATION");
+    = this->Makefile->GetDefinition("CTEST_CONTINUOUS_MINIMUM_INTERVAL");
+  contDuration
+    = this->Makefile->GetDefinition("CTEST_CONTINUOUS_DURATION");
 
   char updateVar[40];
   int i;
   for (i = 1; i < 10; ++i)
     {
     sprintf(updateVar,"CTEST_EXTRA_UPDATES_%i",i);
-    const char *updateVal = m_Makefile->GetDefinition(updateVar);
+    const char *updateVal = this->Makefile->GetDefinition(updateVar);
     if ( updateVal )
       {
-      if ( m_CVSCmd.empty() )
+      if ( this->CVSCmd.empty() )
         {
         cmSystemTools::Error(updateVar,
           " specified without specifying CTEST_CVS_COMMAND.");
         return 12;
         }
-      m_ExtraUpdates.push_back(updateVal);
+      this->ExtraUpdates.push_back(updateVal);
       }
     }
 
   // in order to backup and restore we also must have the cvs root
-  if (m_Backup && m_CVSCheckOut.empty())
+  if (this->Backup && this->CVSCheckOut.empty())
     {
     cmSystemTools::Error(
       "Backup was requested without specifying CTEST_CVS_CHECKOUT.");
     return 3;
     }
 
   // make sure the required info is here
-  if (this->m_SourceDir.empty() ||
-      this->m_BinaryDir.empty() ||
-      this->m_CTestCmd.empty())
-    {
-    std::string message = "CTEST_SOURCE_DIRECTORY = ";
-    message += (!m_SourceDir.empty()) ? m_SourceDir.c_str() : "(Null)";
-    message += "\nCTEST_BINARY_DIRECTORY = ";
-    message += (!m_BinaryDir.empty()) ? m_BinaryDir.c_str() : "(Null)";
-    message += "\nCTEST_COMMAND = ";
-    message += (!m_CTestCmd.empty()) ? m_CTestCmd.c_str() : "(Null)";
+  if (this->SourceDir.empty() ||
+      this->BinaryDir.empty() ||
+      this->CTestCmd.empty())
+    {
+    std::string msg = "CTEST_SOURCE_DIRECTORY = ";
+    msg += (!this->SourceDir.empty()) ? this->SourceDir.c_str() : "(Null)";
+    msg += "\nCTEST_BINARY_DIRECTORY = ";
+    msg += (!this->BinaryDir.empty()) ? this->BinaryDir.c_str() : "(Null)";
+    msg += "\nCTEST_COMMAND = ";
+    msg += (!this->CTestCmd.empty()) ? this->CTestCmd.c_str() : "(Null)";
     cmSystemTools::Error(
       "Some required settings in the configuration file were missing:\n",
-      message.c_str());
+      msg.c_str());
     return 4;
     }
 
   // if the dashboard root isn't specified then we can compute it from the
-  // m_SourceDir
-  if (m_CTestRoot.empty() )
+  // this->SourceDir
+  if (this->CTestRoot.empty() )
     {
-    m_CTestRoot = cmSystemTools::GetFilenamePath(m_SourceDir).c_str();
+    this->CTestRoot = cmSystemTools::GetFilenamePath(this->SourceDir).c_str();
     }
 
   // the script may override the minimum continuous interval
   if (minInterval)
     {
-    m_MinimumInterval = 60 * atof(minInterval);
+    this->MinimumInterval = 60 * atof(minInterval);
     }
   if (contDuration)
     {
-    m_ContinuousDuration = 60.0 * atof(contDuration);
+    this->ContinuousDuration = 60.0 * atof(contDuration);
     }
 
 
@@ -417,7 +429,7 @@ int cmCTestScriptHandler::RunConfigurationScript(
 {
   int result;
 
-  m_ScriptStartTime =
+  this->ScriptStartTime =
     cmSystemTools::GetTime();
 
   // read in the script
@@ -428,7 +440,7 @@ int cmCTestScriptHandler::RunConfigurationScript(
     }
 
   // only run the curent script if we should
-  if (m_Makefile && m_Makefile->IsOn("CTEST_RUN_CURRENT_SCRIPT"))
+  if (this->Makefile && this->Makefile->IsOn("CTEST_RUN_CURRENT_SCRIPT"))
     {
     return this->RunCurrentScript();
     }
@@ -441,7 +453,7 @@ int cmCTestScriptHandler::RunCurrentScript()
   int result;
 
   // do not run twice
-  m_Makefile->AddDefinition("CTEST_RUN_CURRENT_SCRIPT", false);
+  this->Makefile->AddDefinition("CTEST_RUN_CURRENT_SCRIPT", false);
 
   // no popup widows
   cmSystemTools::SetRunCommandHideConsole(true);
@@ -454,10 +466,10 @@ int cmCTestScriptHandler::RunCurrentScript()
     }
 
   // set any environment variables
-  if (!m_CTestEnv.empty())
+  if (!this->CTestEnv.empty())
     {
     std::vector<std::string> envArgs;
-    cmSystemTools::ExpandListArgument(m_CTestEnv.c_str(),envArgs);
+    cmSystemTools::ExpandListArgument(this->CTestEnv.c_str(),envArgs);
     // for each variable/argument do a putenv
     for (unsigned i = 0; i < envArgs.size(); ++i)
       {
@@ -468,27 +480,27 @@ int cmCTestScriptHandler::RunCurrentScript()
   // now that we have done most of the error checking finally run the
   // dashboard, we may be asked to repeatedly run this dashboard, such as
   // for a continuous, do we ned to run it more than once?
-  if ( m_ContinuousDuration >= 0 )
+  if ( this->ContinuousDuration >= 0 )
     {
     this->UpdateElapsedTime();
-    double ending_time  = cmSystemTools::GetTime() + m_ContinuousDuration;
-    if (m_EmptyBinDirOnce)
+    double ending_time  = cmSystemTools::GetTime() + this->ContinuousDuration;
+    if (this->EmptyBinDirOnce)
       {
-      m_EmptyBinDir = true;
+      this->EmptyBinDir = true;
       }
     do
       {
       double interval = cmSystemTools::GetTime();
       result = this->RunConfigurationDashboard();
       interval = cmSystemTools::GetTime() - interval;
-      if (interval < m_MinimumInterval)
+      if (interval < this->MinimumInterval)
         {
         this->SleepInSeconds(
-          static_cast<unsigned int>(m_MinimumInterval - interval));
+          static_cast<unsigned int>(this->MinimumInterval - interval));
         }
-      if (m_EmptyBinDirOnce)
+      if (this->EmptyBinDirOnce)
         {
-        m_EmptyBinDir = false;
+        this->EmptyBinDir = false;
         }
       }
     while (cmSystemTools::GetTime() < ending_time);
@@ -510,16 +522,16 @@ int cmCTestScriptHandler::CheckOutSourceDir()
   int retVal;
   bool res;
 
-  if (!cmSystemTools::FileExists(m_SourceDir.c_str()) &&
-      !m_CVSCheckOut.empty())
+  if (!cmSystemTools::FileExists(this->SourceDir.c_str()) &&
+      !this->CVSCheckOut.empty())
     {
     // we must now checkout the src dir
     output = "";
-    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Run cvs: " << m_CVSCheckOut
-      << std::endl);
-    res = cmSystemTools::RunSingleCommand(m_CVSCheckOut.c_str(), &output,
-                                          &retVal, m_CTestRoot.c_str(),
-                                          m_HandlerVerbose, 0 /*m_TimeOut*/);
+    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+      "Run cvs: " << this->CVSCheckOut << std::endl);
+    res = cmSystemTools::RunSingleCommand(this->CVSCheckOut.c_str(), &output,
+      &retVal, this->CTestRoot.c_str(), this->HandlerVerbose,
+      0 /*this->TimeOut*/);
     if (!res || retVal != 0)
       {
       cmSystemTools::Error("Unable to perform cvs checkout:\n",
@@ -536,27 +548,27 @@ int cmCTestScriptHandler::BackupDirectories()
   int retVal;
 
   // compute the backup names
-  m_BackupSourceDir = m_SourceDir;
-  m_BackupSourceDir += "_CMakeBackup";
-  m_BackupBinaryDir = m_BinaryDir;
-  m_BackupBinaryDir += "_CMakeBackup";
+  this->BackupSourceDir = this->SourceDir;
+  this->BackupSourceDir += "_CMakeBackup";
+  this->BackupBinaryDir = this->BinaryDir;
+  this->BackupBinaryDir += "_CMakeBackup";
 
   // backup the binary and src directories if requested
-  if (m_Backup)
+  if (this->Backup)
     {
     // if for some reason those directories exist then first delete them
-    if (cmSystemTools::FileExists(m_BackupSourceDir.c_str()))
+    if (cmSystemTools::FileExists(this->BackupSourceDir.c_str()))
       {
-      cmSystemTools::RemoveADirectory(m_BackupSourceDir.c_str());
+      cmSystemTools::RemoveADirectory(this->BackupSourceDir.c_str());
       }
-    if (cmSystemTools::FileExists(m_BackupBinaryDir.c_str()))
+    if (cmSystemTools::FileExists(this->BackupBinaryDir.c_str()))
       {
-      cmSystemTools::RemoveADirectory(m_BackupBinaryDir.c_str());
+      cmSystemTools::RemoveADirectory(this->BackupBinaryDir.c_str());
       }
 
     // first rename the src and binary directories
-    rename(m_SourceDir.c_str(), m_BackupSourceDir.c_str());
-    rename(m_BinaryDir.c_str(), m_BackupBinaryDir.c_str());
+    rename(this->SourceDir.c_str(), this->BackupSourceDir.c_str());
+    rename(this->BinaryDir.c_str(), this->BackupBinaryDir.c_str());
 
     // we must now checkout the src dir
     retVal = this->CheckOutSourceDir();
@@ -580,9 +592,11 @@ int cmCTestScriptHandler::PerformExtraUpdates()
   bool res;
 
   // do an initial cvs update as required
-  command = m_CVSCmd;
+  command = this->CVSCmd;
   std::vector<cmStdString>::iterator it;
-  for (it = m_ExtraUpdates.begin(); it != m_ExtraUpdates.end(); ++ it )
+  for (it = this->ExtraUpdates.begin();
+    it != this->ExtraUpdates.end();
+    ++ it )
     {
     std::vector<std::string> cvsArgs;
     cmSystemTools::ExpandListArgument(it->c_str(),cvsArgs);
@@ -593,11 +607,11 @@ int cmCTestScriptHandler::PerformExtraUpdates()
       fullCommand += cvsArgs[1];
       output = "";
       retVal = 0;
-      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Run CVS: "
+      cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Run CVS: "
         << fullCommand.c_str() << std::endl);
       res = cmSystemTools::RunSingleCommand(fullCommand.c_str(), &output,
         &retVal, cvsArgs[0].c_str(),
-        m_HandlerVerbose, 0 /*m_TimeOut*/);
+        this->HandlerVerbose, 0 /*this->TimeOut*/);
       if (!res || retVal != 0)
         {
         cmSystemTools::Error("Unable to perform extra cvs updates:\n",
@@ -636,23 +650,24 @@ int cmCTestScriptHandler::RunConfigurationDashboard()
     }
 
   // clear the binary directory?
-  if (m_EmptyBinDir)
+  if (this->EmptyBinDir)
     {
-    if ( !cmCTestScriptHandler::EmptyBinaryDirectory(m_BinaryDir.c_str()) )
+    if ( !cmCTestScriptHandler::EmptyBinaryDirectory(
+        this->BinaryDir.c_str()) )
       {
-      cmCTestLog(m_CTest, ERROR_MESSAGE,
+      cmCTestLog(this->CTest, ERROR_MESSAGE,
         "Problem removing the binary directory" << std::endl);
       }
     }
 
   // make sure the binary directory exists if it isn't the srcdir
-  if (!cmSystemTools::FileExists(m_BinaryDir.c_str()) &&
-      m_SourceDir != m_BinaryDir)
+  if (!cmSystemTools::FileExists(this->BinaryDir.c_str()) &&
+      this->SourceDir != this->BinaryDir)
     {
-    if (!cmSystemTools::MakeDirectory(m_BinaryDir.c_str()))
+    if (!cmSystemTools::MakeDirectory(this->BinaryDir.c_str()))
       {
       cmSystemTools::Error("Unable to create the binary directory:\n",
-                           m_BinaryDir.c_str());
+                           this->BinaryDir.c_str());
       this->RestoreBackupDirectories();
       return 7;
       }
@@ -661,10 +676,10 @@ int cmCTestScriptHandler::RunConfigurationDashboard()
   // if the binary directory and the source directory are the same,
   // and we are starting with an empty binary directory, then that means
   // we must check out the source tree
-  if (m_EmptyBinDir && m_SourceDir == m_BinaryDir)
+  if (this->EmptyBinDir && this->SourceDir == this->BinaryDir)
     {
     // make sure we have the required info
-    if (m_CVSCheckOut.empty())
+    if (this->CVSCheckOut.empty())
       {
       cmSystemTools::Error("You have specified the source and binary "
         "directories to be the same (an in source build). You have also "
@@ -691,9 +706,9 @@ int cmCTestScriptHandler::RunConfigurationDashboard()
     }
 
   // put the initial cache into the bin dir
-  if (!m_InitCache.empty())
+  if (!this->InitCache.empty())
     {
-    std::string cacheFile = m_BinaryDir;
+    std::string cacheFile = this->BinaryDir;
     cacheFile += "/CMakeCache.txt";
     cmGeneratedFileStream fout(cacheFile.c_str());
     if(!fout)
@@ -702,7 +717,7 @@ int cmCTestScriptHandler::RunConfigurationDashboard()
       return 9;
       }
 
-    fout.write(m_InitCache.c_str(), m_InitCache.size());
+    fout.write(this->InitCache.c_str(), this->InitCache.size());
 
     // Make sure the operating system has finished writing the file
     // before closing it.  This will ensure the file is finished before
@@ -714,29 +729,29 @@ int cmCTestScriptHandler::RunConfigurationDashboard()
   // do an initial cmake to setup the DartConfig file
   int cmakeFailed = 0;
   std::string cmakeFailedOuput;
-  if (!m_CMakeCmd.empty())
+  if (!this->CMakeCmd.empty())
     {
-    command = m_CMakeCmd;
+    command = this->CMakeCmd;
     command += " \"";
-    command += m_SourceDir;
+    command += this->SourceDir;
     output = "";
     command += "\"";
     retVal = 0;
-    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Run cmake command: "
+    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Run cmake command: "
       << command.c_str() << std::endl);
     res = cmSystemTools::RunSingleCommand(command.c_str(), &output,
-      &retVal, m_BinaryDir.c_str(),
-      m_HandlerVerbose, 0 /*m_TimeOut*/);
+      &retVal, this->BinaryDir.c_str(),
+      this->HandlerVerbose, 0 /*this->TimeOut*/);
 
-    if ( !m_CMOutFile.empty() )
+    if ( !this->CMOutFile.empty() )
       {
-      std::string cmakeOutputFile = m_CMOutFile;
+      std::string cmakeOutputFile = this->CMOutFile;
       if ( !cmSystemTools::FileIsFullPath(cmakeOutputFile.c_str()) )
         {
-        cmakeOutputFile = m_BinaryDir + "/" + cmakeOutputFile;
+        cmakeOutputFile = this->BinaryDir + "/" + cmakeOutputFile;
         }
 
-      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT,
+      cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
         "Write CMake output to file: " << cmakeOutputFile.c_str()
         << std::endl);
       cmGeneratedFileStream fout(cmakeOutputFile.c_str());
@@ -746,7 +761,8 @@ int cmCTestScriptHandler::RunConfigurationDashboard()
         }
       else
         {
-        cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot open CMake output file: "
+        cmCTestLog(this->CTest, ERROR_MESSAGE,
+          "Cannot open CMake output file: "
           << cmakeOutputFile.c_str() << " for writing" << std::endl);
         }
       }
@@ -760,18 +776,18 @@ int cmCTestScriptHandler::RunConfigurationDashboard()
 
   // run ctest, it may be more than one command in here
   std::vector<std::string> ctestCommands;
-  cmSystemTools::ExpandListArgument(m_CTestCmd,ctestCommands);
+  cmSystemTools::ExpandListArgument(this->CTestCmd,ctestCommands);
   // for each variable/argument do a putenv
   for (unsigned i = 0; i < ctestCommands.size(); ++i)
     {
     command = ctestCommands[i];
     output = "";
     retVal = 0;
-    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Run ctest command: "
+    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Run ctest command: "
       << command.c_str() << std::endl);
     res = cmSystemTools::RunSingleCommand(command.c_str(), &output,
-                                          &retVal, m_BinaryDir.c_str(),
-                                          m_HandlerVerbose, 0 /*m_TimeOut*/);
+      &retVal, this->BinaryDir.c_str(), this->HandlerVerbose,
+      0 /*this->TimeOut*/);
 
     // did something critical fail in ctest
     if (!res || cmakeFailed ||
@@ -780,11 +796,13 @@ int cmCTestScriptHandler::RunConfigurationDashboard()
       this->RestoreBackupDirectories();
       if (cmakeFailed)
         {
-        cmCTestLog(m_CTest, ERROR_MESSAGE, "Unable to run cmake:" << std::endl
+        cmCTestLog(this->CTest, ERROR_MESSAGE,
+          "Unable to run cmake:" << std::endl
           << cmakeFailedOuput.c_str() << std::endl);
         return 10;
         }
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "Unable to run ctest:" << std::endl
+      cmCTestLog(this->CTest, ERROR_MESSAGE,
+        "Unable to run ctest:" << std::endl
         << output.c_str() << std::endl);
       if (!res)
         {
@@ -795,10 +813,10 @@ int cmCTestScriptHandler::RunConfigurationDashboard()
     }
 
   // if all was succesful, delete the backup dirs to free up disk space
-  if (m_Backup)
+  if (this->Backup)
     {
-    cmSystemTools::RemoveADirectory(m_BackupSourceDir.c_str());
-    cmSystemTools::RemoveADirectory(m_BackupBinaryDir.c_str());
+    cmSystemTools::RemoveADirectory(this->BackupSourceDir.c_str());
+    cmSystemTools::RemoveADirectory(this->BackupBinaryDir.c_str());
     }
 
   return 0;
@@ -810,20 +828,20 @@ void cmCTestScriptHandler::RestoreBackupDirectories()
 {
   // if we backed up the dirs and the build failed, then restore
   // the backed up dirs
-  if (m_Backup)
+  if (this->Backup)
     {
     // if for some reason those directories exist then first delete them
-    if (cmSystemTools::FileExists(m_SourceDir.c_str()))
+    if (cmSystemTools::FileExists(this->SourceDir.c_str()))
       {
-      cmSystemTools::RemoveADirectory(m_SourceDir.c_str());
+      cmSystemTools::RemoveADirectory(this->SourceDir.c_str());
       }
-    if (cmSystemTools::FileExists(m_BinaryDir.c_str()))
+    if (cmSystemTools::FileExists(this->BinaryDir.c_str()))
       {
-      cmSystemTools::RemoveADirectory(m_BinaryDir.c_str());
+      cmSystemTools::RemoveADirectory(this->BinaryDir.c_str());
       }
     // rename the src and binary directories
-    rename(m_BackupSourceDir.c_str(), m_SourceDir.c_str());
-    rename(m_BackupBinaryDir.c_str(), m_BinaryDir.c_str());
+    rename(this->BackupSourceDir.c_str(), this->SourceDir.c_str());
+    rename(this->BackupBinaryDir.c_str(), this->BinaryDir.c_str());
     }
 }
 