@@ -124,7 +124,7 @@ std::string cmCTest::CurrentTime()
   struct tm* t = localtime(&currenttime);
   //return ::CleanString(ctime(&currenttime));
   char current_time[1024];
-  if ( m_ShortDateFormat )
+  if ( this->ShortDateFormat )
     {
     strftime(current_time, 1000, "%b %d %H:%M %Z", t);
     }
@@ -218,46 +218,46 @@ std::string cmCTest::MakeURLSafe(const std::string& str)
 //----------------------------------------------------------------------
 cmCTest::cmCTest()
 {
-  m_SubmitIndex            = 0;
-  m_ForceNewCTestProcess   = false;
-  m_TomorrowTag            = false;
-  m_Verbose                = false;
-  m_Debug                  = false;
-  m_ShowLineNumbers        = false;
-  m_Quiet                  = false;
-  m_ExtraVerbose           = false;
-  m_ProduceXML             = false;
-  m_ShowOnly               = false;
-  m_RunConfigurationScript = false;
-  m_TestModel              = cmCTest::EXPERIMENTAL;
-  m_InteractiveDebugMode   = true;
-  m_TimeOut                = 0;
-  m_CompressXMLFiles       = false;
-  m_CTestConfigFile        = "";
-  m_OutputLogFile          = 0;
-  m_OutputLogFileLastTag   = -1;
-  m_SuppressUpdatingCTestConfiguration = false;
-  m_DartVersion            = 1;
+  this->SubmitIndex            = 0;
+  this->ForceNewCTestProcess   = false;
+  this->TomorrowTag            = false;
+  this->Verbose                = false;
+  this->Debug                  = false;
+  this->ShowLineNumbers        = false;
+  this->Quiet                  = false;
+  this->ExtraVerbose           = false;
+  this->ProduceXML             = false;
+  this->ShowOnly               = false;
+  this->RunConfigurationScript = false;
+  this->TestModel              = cmCTest::EXPERIMENTAL;
+  this->InteractiveDebugMode   = true;
+  this->TimeOut                = 0;
+  this->CompressXMLFiles       = false;
+  this->CTestConfigFile        = "";
+  this->OutputLogFile          = 0;
+  this->OutputLogFileLastTag   = -1;
+  this->SuppressUpdatingCTestConfiguration = false;
+  this->DartVersion            = 1;
 
   int cc;
   for ( cc=0; cc < cmCTest::LAST_TEST; cc ++ )
     {
-    m_Tests[cc] = 0;
+    this->Tests[cc] = 0;
     }
-  m_ShortDateFormat        = true;
+  this->ShortDateFormat        = true;
 
-  m_TestingHandlers["build"]     = new cmCTestBuildHandler;
-  m_TestingHandlers["buildtest"] = new cmCTestBuildAndTestHandler;
-  m_TestingHandlers["coverage"]  = new cmCTestCoverageHandler;
-  m_TestingHandlers["script"]    = new cmCTestScriptHandler;
-  m_TestingHandlers["test"]      = new cmCTestTestHandler;
-  m_TestingHandlers["update"]    = new cmCTestUpdateHandler;
-  m_TestingHandlers["configure"] = new cmCTestConfigureHandler;
-  m_TestingHandlers["memcheck"]  = new cmCTestMemCheckHandler;
-  m_TestingHandlers["submit"]    = new cmCTestSubmitHandler;
+  this->TestingHandlers["build"]     = new cmCTestBuildHandler;
+  this->TestingHandlers["buildtest"] = new cmCTestBuildAndTestHandler;
+  this->TestingHandlers["coverage"]  = new cmCTestCoverageHandler;
+  this->TestingHandlers["script"]    = new cmCTestScriptHandler;
+  this->TestingHandlers["test"]      = new cmCTestTestHandler;
+  this->TestingHandlers["update"]    = new cmCTestUpdateHandler;
+  this->TestingHandlers["configure"] = new cmCTestConfigureHandler;
+  this->TestingHandlers["memcheck"]  = new cmCTestMemCheckHandler;
+  this->TestingHandlers["submit"]    = new cmCTestSubmitHandler;
 
   cmCTest::t_TestingHandlers::iterator it;
-  for ( it = m_TestingHandlers.begin(); it != m_TestingHandlers.end(); ++ it )
+  for ( it = this->TestingHandlers.begin(); it != this->TestingHandlers.end(); ++ it )
     {
     it->second->SetCTestInstance(this);
     }
@@ -270,7 +270,7 @@ cmCTest::cmCTest()
 cmCTest::~cmCTest()
 {
   cmCTest::t_TestingHandlers::iterator it;
-  for ( it = m_TestingHandlers.begin(); it != m_TestingHandlers.end(); ++ it )
+  for ( it = this->TestingHandlers.begin(); it != this->TestingHandlers.end(); ++ it )
     {
     delete it->second;
     it->second = 0;
@@ -283,18 +283,18 @@ int cmCTest::Initialize(const char* binary_dir, bool new_tag,
   bool verbose_tag)
 {
   cmCTestLog(this, DEBUG, "Here: " << __LINE__ << std::endl);
-  if(!m_InteractiveDebugMode)
+  if(!this->InteractiveDebugMode)
     {
     this->BlockTestErrorDiagnostics();
     }
 
-  m_BinaryDir = binary_dir;
-  cmSystemTools::ConvertToUnixSlashes(m_BinaryDir);
+  this->BinaryDir = binary_dir;
+  cmSystemTools::ConvertToUnixSlashes(this->BinaryDir);
 
   this->UpdateCTestConfiguration();
 
   cmCTestLog(this, DEBUG, "Here: " << __LINE__ << std::endl);
-  if ( m_ProduceXML )
+  if ( this->ProduceXML )
     {
   cmCTestLog(this, DEBUG, "Here: " << __LINE__ << std::endl);
     cmCTestLog(this, OUTPUT,
@@ -310,16 +310,16 @@ int cmCTest::Initialize(const char* binary_dir, bool new_tag,
       }
     }
 
-  if ( !this->ReadCustomConfigurationFileTree(m_BinaryDir.c_str()) )
+  if ( !this->ReadCustomConfigurationFileTree(this->BinaryDir.c_str()) )
     {
     cmCTestLog(this, DEBUG, "Cannot find custom configuration file tree"
       << std::endl);
     return 0;
     }
 
-  if ( m_ProduceXML )
+  if ( this->ProduceXML )
     {
-    std::string testingDir = m_BinaryDir + "/Testing";
+    std::string testingDir = this->BinaryDir + "/Testing";
     if ( cmSystemTools::FileExists(testingDir.c_str()) )
       {
       if ( !cmSystemTools::FileIsDirectory(testingDir.c_str()) )
@@ -342,7 +342,7 @@ int cmCTest::Initialize(const char* binary_dir, bool new_tag,
     std::ifstream tfin(tagfile.c_str());
     std::string tag;
     time_t tctime = time(0);
-    if ( m_TomorrowTag )
+    if ( this->TomorrowTag )
       {
       tctime += ( 24 * 60 * 60 );
       }
@@ -365,24 +365,24 @@ int cmCTest::Initialize(const char* binary_dir, bool new_tag,
       std::string tagmode;
       if ( cmSystemTools::GetLineFromStream(tfin, tagmode) )
         {
-        if ( tagmode.size() > 4 && !( m_Tests[cmCTest::START_TEST] ||
-            m_Tests[ALL_TEST] ))
+        if ( tagmode.size() > 4 && !( this->Tests[cmCTest::START_TEST] ||
+            this->Tests[ALL_TEST] ))
           {
-          m_TestModel = cmCTest::GetTestModelFromString(tagmode.c_str());
+          this->TestModel = cmCTest::GetTestModelFromString(tagmode.c_str());
           }
         }
       tfin.close();
       }
-    if ( tag.size() == 0 || new_tag || m_Tests[cmCTest::START_TEST] ||
-      m_Tests[ALL_TEST])
+    if ( tag.size() == 0 || new_tag || this->Tests[cmCTest::START_TEST] ||
+      this->Tests[ALL_TEST])
       {
       cmCTestLog(this, DEBUG, "TestModel: " << this->GetTestModelString()
         << std::endl);
-      cmCTestLog(this, DEBUG, "TestModel: " << m_TestModel << std::endl);
-      if ( m_TestModel == cmCTest::NIGHTLY )
+      cmCTestLog(this, DEBUG, "TestModel: " << this->TestModel << std::endl);
+      if ( this->TestModel == cmCTest::NIGHTLY )
         {
         lctime = this->GetNightlyTime(
-          this->GetCTestConfiguration("NightlyStartTime"), m_TomorrowTag);
+          this->GetCTestConfiguration("NightlyStartTime"), this->TomorrowTag);
         }
       char datestring[100];
       sprintf(datestring, "%04d%02d%02d-%02d%02d",
@@ -405,24 +405,24 @@ int cmCTest::Initialize(const char* binary_dir, bool new_tag,
           << this->GetTestModelString() << std::endl);
         }
       }
-    m_CurrentTag = tag;
+    this->CurrentTag = tag;
     }
   return 1;
 }
 
 //----------------------------------------------------------------------
 bool cmCTest::InitializeFromCommand(cmCTestCommand* command, bool first)
 {
-  if ( !first && !m_CurrentTag.empty() )
+  if ( !first && !this->CurrentTag.empty() )
     {
     return true;
     }
 
   std::string src_dir
     = this->GetCTestConfiguration("SourceDirectory").c_str();
   std::string bld_dir = this->GetCTestConfiguration("BuildDirectory").c_str();
-  m_DartVersion = 1;
-  m_SubmitFiles.clear();
+  this->DartVersion = 1;
+  this->SubmitFiles.clear();
 
   cmMakefile* mf = command->GetMakefile();
   std::string fname = src_dir;
@@ -462,8 +462,8 @@ bool cmCTest::InitializeFromCommand(cmCTestCommand* command, bool first)
   const char* dartVersion = mf->GetDefinition("CTEST_DART_SERVER_VERSION");
   if ( dartVersion )
     {
-    m_DartVersion = atoi(dartVersion);
-    if ( m_DartVersion < 0 )
+    this->DartVersion = atoi(dartVersion);
+    if ( this->DartVersion < 0 )
       {
       cmCTestLog(this, ERROR_MESSAGE, "Invalid Dart server version: "
         << dartVersion << ". Please specify the version number."
@@ -489,23 +489,23 @@ bool cmCTest::InitializeFromCommand(cmCTestCommand* command, bool first)
 //----------------------------------------------------------------------
 bool cmCTest::UpdateCTestConfiguration()
 {
-  if ( m_SuppressUpdatingCTestConfiguration )
+  if ( this->SuppressUpdatingCTestConfiguration )
     {
     return true;
     }
-  std::string fileName = m_CTestConfigFile;
+  std::string fileName = this->CTestConfigFile;
   if ( fileName.empty() )
     {
-    fileName = m_BinaryDir + "/DartConfiguration.tcl";
+    fileName = this->BinaryDir + "/DartConfiguration.tcl";
     if ( !cmSystemTools::FileExists(fileName.c_str()) )
       {
-      fileName = m_BinaryDir + "/CTestConfiguration.ini";
+      fileName = this->BinaryDir + "/CTestConfiguration.ini";
       }
     }
   if ( !cmSystemTools::FileExists(fileName.c_str()) )
     {
     // No need to exit if we are not producing XML
-    if ( m_ProduceXML )
+    if ( this->ProduceXML )
       {
       cmCTestLog(this, ERROR_MESSAGE, "Cannot find file: " << fileName.c_str()
         << std::endl);
@@ -552,14 +552,14 @@ bool cmCTest::UpdateCTestConfiguration()
       std::string key = line.substr(0, cpos);
       std::string value
         = cmCTest::CleanString(line.substr(cpos+1, line.npos));
-      m_CTestConfiguration[key] = value;
+      this->CTestConfiguration[key] = value;
       }
     fin.close();
     }
-  m_TimeOut = atoi(this->GetCTestConfiguration("TimeOut").c_str());
-  if ( m_ProduceXML )
+  this->TimeOut = atoi(this->GetCTestConfiguration("TimeOut").c_str());
+  if ( this->ProduceXML )
     {
-    m_CompressXMLFiles = cmSystemTools::IsOn(
+    this->CompressXMLFiles = cmSystemTools::IsOn(
       this->GetCTestConfiguration("CompressSubmission").c_str());
     }
   return true;
@@ -578,52 +578,52 @@ void cmCTest::BlockTestErrorDiagnostics()
 //----------------------------------------------------------------------
 void cmCTest::SetTestModel(int mode)
 {
-  m_InteractiveDebugMode = false;
-  m_TestModel = mode;
+  this->InteractiveDebugMode = false;
+  this->TestModel = mode;
 }
 
 //----------------------------------------------------------------------
 bool cmCTest::SetTest(const char* ttype, bool report)
 {
   if ( cmSystemTools::LowerCase(ttype) == "all" )
     {
-    m_Tests[cmCTest::ALL_TEST] = 1;
+    this->Tests[cmCTest::ALL_TEST] = 1;
     }
   else if ( cmSystemTools::LowerCase(ttype) == "start" )
     {
-    m_Tests[cmCTest::START_TEST] = 1;
+    this->Tests[cmCTest::START_TEST] = 1;
     }
   else if ( cmSystemTools::LowerCase(ttype) == "update" )
     {
-    m_Tests[cmCTest::UPDATE_TEST] = 1;
+    this->Tests[cmCTest::UPDATE_TEST] = 1;
     }
   else if ( cmSystemTools::LowerCase(ttype) == "configure" )
     {
-    m_Tests[cmCTest::CONFIGURE_TEST] = 1;
+    this->Tests[cmCTest::CONFIGURE_TEST] = 1;
     }
   else if ( cmSystemTools::LowerCase(ttype) == "build" )
     {
-    m_Tests[cmCTest::BUILD_TEST] = 1;
+    this->Tests[cmCTest::BUILD_TEST] = 1;
     }
   else if ( cmSystemTools::LowerCase(ttype) == "test" )
     {
-    m_Tests[cmCTest::TEST_TEST] = 1;
+    this->Tests[cmCTest::TEST_TEST] = 1;
     }
   else if ( cmSystemTools::LowerCase(ttype) == "coverage" )
     {
-    m_Tests[cmCTest::COVERAGE_TEST] = 1;
+    this->Tests[cmCTest::COVERAGE_TEST] = 1;
     }
   else if ( cmSystemTools::LowerCase(ttype) == "memcheck" )
     {
-    m_Tests[cmCTest::MEMCHECK_TEST] = 1;
+    this->Tests[cmCTest::MEMCHECK_TEST] = 1;
     }
   else if ( cmSystemTools::LowerCase(ttype) == "notes" )
     {
-    m_Tests[cmCTest::NOTES_TEST] = 1;
+    this->Tests[cmCTest::NOTES_TEST] = 1;
     }
   else if ( cmSystemTools::LowerCase(ttype) == "submit" )
     {
-    m_Tests[cmCTest::SUBMIT_TEST] = 1;
+    this->Tests[cmCTest::SUBMIT_TEST] = 1;
     }
   else
     {
@@ -647,7 +647,7 @@ bool cmCTest::OpenOutputFile(const std::string& path,
                      const std::string& name, cmGeneratedFileStream& stream,
                      bool compress)
 {
-  std::string testingDir = m_BinaryDir + "/Testing";
+  std::string testingDir = this->BinaryDir + "/Testing";
   if ( path.size() > 0 )
     {
     testingDir += "/" + path;
@@ -681,7 +681,7 @@ bool cmCTest::OpenOutputFile(const std::string& path,
     }
   if ( compress )
     {
-    if ( m_CompressXMLFiles )
+    if ( this->CompressXMLFiles )
       {
       stream.SetCompression(true);
       }
@@ -715,16 +715,16 @@ bool cmCTest::AddIfExists(SetOfStrings& files, const char* file)
 //----------------------------------------------------------------------
 bool cmCTest::CTestFileExists(const std::string& filename)
 {
-  std::string testingDir = m_BinaryDir + "/Testing/" + m_CurrentTag + "/" +
+  std::string testingDir = this->BinaryDir + "/Testing/" + this->CurrentTag + "/" +
     filename;
   return cmSystemTools::FileExists(testingDir.c_str());
 }
 
 //----------------------------------------------------------------------
 cmCTestGenericHandler* cmCTest::GetInitializedHandler(const char* handler)
 {
-  cmCTest::t_TestingHandlers::iterator it = m_TestingHandlers.find(handler);
-  if ( it == m_TestingHandlers.end() )
+  cmCTest::t_TestingHandlers::iterator it = this->TestingHandlers.find(handler);
+  if ( it == this->TestingHandlers.end() )
     {
     return 0;
     }
@@ -735,8 +735,8 @@ cmCTestGenericHandler* cmCTest::GetInitializedHandler(const char* handler)
 //----------------------------------------------------------------------
 cmCTestGenericHandler* cmCTest::GetHandler(const char* handler)
 {
-  cmCTest::t_TestingHandlers::iterator it = m_TestingHandlers.find(handler);
-  if ( it == m_TestingHandlers.end() )
+  cmCTest::t_TestingHandlers::iterator it = this->TestingHandlers.find(handler);
+  if ( it == this->TestingHandlers.end() )
     {
     return 0;
     }
@@ -767,13 +767,13 @@ int cmCTest::ProcessTests()
 
   for ( cc = 0; cc < LAST_TEST; cc ++ )
     {
-    if ( m_Tests[cc] )
+    if ( this->Tests[cc] )
       {
       notest = false;
       break;
       }
     }
-  if ( m_Tests[UPDATE_TEST] || m_Tests[ALL_TEST] )
+  if ( this->Tests[UPDATE_TEST] || this->Tests[ALL_TEST] )
     {
     cmCTestGenericHandler* uphandler = this->GetHandler("update");
     uphandler->SetOption("SourceDirectory",
@@ -784,42 +784,42 @@ int cmCTest::ProcessTests()
       res |= cmCTest::UPDATE_ERRORS;
       }
     }
-  if ( m_TestModel == cmCTest::CONTINUOUS && !update_count )
+  if ( this->TestModel == cmCTest::CONTINUOUS && !update_count )
     {
     return 0;
     }
-  if ( m_Tests[CONFIGURE_TEST] || m_Tests[ALL_TEST] )
+  if ( this->Tests[CONFIGURE_TEST] || this->Tests[ALL_TEST] )
     {
     if (this->GetHandler("configure")->ProcessHandler() < 0)
       {
       res |= cmCTest::CONFIGURE_ERRORS;
       }
     }
-  if ( m_Tests[BUILD_TEST] || m_Tests[ALL_TEST] )
+  if ( this->Tests[BUILD_TEST] || this->Tests[ALL_TEST] )
     {
     this->UpdateCTestConfiguration();
     if (this->GetHandler("build")->ProcessHandler() < 0)
       {
       res |= cmCTest::BUILD_ERRORS;
       }
     }
-  if ( m_Tests[TEST_TEST] || m_Tests[ALL_TEST] || notest )
+  if ( this->Tests[TEST_TEST] || this->Tests[ALL_TEST] || notest )
     {
     this->UpdateCTestConfiguration();
     if (this->GetHandler("test")->ProcessHandler() < 0)
       {
       res |= cmCTest::TEST_ERRORS;
       }
     }
-  if ( m_Tests[COVERAGE_TEST] || m_Tests[ALL_TEST] )
+  if ( this->Tests[COVERAGE_TEST] || this->Tests[ALL_TEST] )
     {
     this->UpdateCTestConfiguration();
     if (this->GetHandler("coverage")->ProcessHandler() < 0)
       {
       res |= cmCTest::COVERAGE_ERRORS;
       }
     }
-  if ( m_Tests[MEMCHECK_TEST] || m_Tests[ALL_TEST] )
+  if ( this->Tests[MEMCHECK_TEST] || this->Tests[ALL_TEST] )
     {
     this->UpdateCTestConfiguration();
     if (this->GetHandler("memcheck")->ProcessHandler() < 0)
@@ -829,7 +829,7 @@ int cmCTest::ProcessTests()
     }
   if ( !notest )
     {
-    std::string notes_dir = m_BinaryDir + "/Testing/Notes";
+    std::string notes_dir = this->BinaryDir + "/Testing/Notes";
     if ( cmSystemTools::FileIsDirectory(notes_dir.c_str()) )
       {
       cmsys::Directory d;
@@ -842,25 +842,25 @@ int cmCTest::ProcessTests()
         if ( cmSystemTools::FileExists(fullname.c_str()) &&
           !cmSystemTools::FileIsDirectory(fullname.c_str()) )
           {
-          if ( m_NotesFiles.size() > 0 )
+          if ( this->NotesFiles.size() > 0 )
             {
-            m_NotesFiles += ";";
+            this->NotesFiles += ";";
             }
-          m_NotesFiles += fullname;
-          m_Tests[NOTES_TEST] = 1;
+          this->NotesFiles += fullname;
+          this->Tests[NOTES_TEST] = 1;
           }
         }
       }
     }
-  if ( m_Tests[NOTES_TEST] || m_Tests[ALL_TEST] )
+  if ( this->Tests[NOTES_TEST] || this->Tests[ALL_TEST] )
     {
     this->UpdateCTestConfiguration();
-    if ( m_NotesFiles.size() )
+    if ( this->NotesFiles.size() )
       {
-      this->GenerateNotesFile(m_NotesFiles.c_str());
+      this->GenerateNotesFile(this->NotesFiles.c_str());
       }
     }
-  if ( m_Tests[SUBMIT_TEST] || m_Tests[ALL_TEST] )
+  if ( this->Tests[SUBMIT_TEST] || this->Tests[ALL_TEST] )
     {
     this->UpdateCTestConfiguration();
     if (this->GetHandler("submit")->ProcessHandler() < 0)
@@ -879,7 +879,7 @@ int cmCTest::ProcessTests()
 //----------------------------------------------------------------------
 std::string cmCTest::GetTestModelString()
 {
-  switch ( m_TestModel )
+  switch ( this->TestModel )
     {
   case cmCTest::NIGHTLY:
     return "Nightly";
@@ -1041,12 +1041,12 @@ int cmCTest::RunTest(std::vector<const char*> argv,
                      std::string* output, int *retVal,
                      std::ostream* log)
 {
-  if(cmSystemTools::SameFile(argv[0], m_CTestSelf.c_str()) &&
-     !m_ForceNewCTestProcess)
+  if(cmSystemTools::SameFile(argv[0], this->CTestSelf.c_str()) &&
+     !this->ForceNewCTestProcess)
     {
     cmCTest inst;
-    inst.m_ConfigType = m_ConfigType;
-    inst.m_TimeOut = m_TimeOut;
+    inst.ConfigType = this->ConfigType;
+    inst.TimeOut = this->TimeOut;
     std::vector<std::string> args;
     for(unsigned int i =0; i < argv.size(); ++i)
       {
@@ -1086,7 +1086,7 @@ int cmCTest::RunTest(std::vector<const char*> argv,
     {
     cmsysProcess_SetOption(cp, cmsysProcess_Option_HideWindow, 1);
     }
-  cmsysProcess_SetTimeout(cp, m_TimeOut);
+  cmsysProcess_SetTimeout(cp, this->TimeOut);
   cmsysProcess_Execute(cp);
 
   char* data;
@@ -1145,7 +1145,7 @@ void cmCTest::StartXML(std::ostream& ostr)
 {
   ostr << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
     << "<Site BuildName=\"" << this->GetCTestConfiguration("BuildName")
-    << "\" BuildStamp=\"" << m_CurrentTag << "-"
+    << "\" BuildStamp=\"" << this->CurrentTag << "-"
     << this->GetTestModelString() << "\" Name=\""
     << this->GetCTestConfiguration("Site") << "\" Generator=\"ctest"
     << cmVersion::GetCMakeVersion()
@@ -1169,7 +1169,7 @@ int cmCTest::GenerateCTestNotesOutput(std::ostream& os,
     "<file:///Dart/Source/Server/XSL/Build.xsl> \"?>\n"
     << "<Site BuildName=\"" << this->GetCTestConfiguration("BuildName")
     << "\" BuildStamp=\""
-    << m_CurrentTag << "-" << this->GetTestModelString() << "\" Name=\""
+    << this->CurrentTag << "-" << this->GetTestModelString() << "\" Name=\""
     << this->GetCTestConfiguration("Site") << "\" Generator=\"ctest"
     << cmVersion::GetCMakeVersion()
     << "\">\n"
@@ -1210,7 +1210,7 @@ int cmCTest::GenerateCTestNotesOutput(std::ostream& os,
 int cmCTest::GenerateNotesFile(const std::vector<cmStdString> &files)
 {
   cmGeneratedFileStream ofs;
-  if ( !this->OpenOutputFile(m_CurrentTag, "Notes.xml", ofs) )
+  if ( !this->OpenOutputFile(this->CurrentTag, "Notes.xml", ofs) )
     {
     cmCTestLog(this, ERROR_MESSAGE, "Cannot open notes file" << std::endl);
     return 1;
@@ -1306,47 +1306,47 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
     if(this->CheckArgument(arg, "--ctest-config") && i < args.size() - 1)
       {
       i++;
-      this->m_CTestConfigFile= args[i];
+      this->CTestConfigFile= args[i];
       }
 
     if(this->CheckArgument(arg, "-C", "--build-config") &&
       i < args.size() - 1)
       {
       i++;
-      this->m_ConfigType = args[i];
-      cmSystemTools::ReplaceString(this->m_ConfigType, ".\\", "");
+      this->ConfigType = args[i];
+      cmSystemTools::ReplaceString(this->ConfigType, ".\\", "");
       }
 
     if(this->CheckArgument(arg, "--debug"))
       {
-      this->m_Debug = true;
+      this->Debug = true;
       }
     if(this->CheckArgument(arg, "--show-line-numbers"))
       {
-      this->m_ShowLineNumbers = true;
+      this->ShowLineNumbers = true;
       }
     if(this->CheckArgument(arg, "-Q", "--quiet"))
       {
-      this->m_Quiet = true;
+      this->Quiet = true;
       }
     if(this->CheckArgument(arg, "-V", "--verbose"))
       {
-      this->m_Verbose = true;
+      this->Verbose = true;
       }
     if(this->CheckArgument(arg, "-VV", "--extra-verbose"))
       {
-      this->m_ExtraVerbose = true;
-      this->m_Verbose = true;
+      this->ExtraVerbose = true;
+      this->Verbose = true;
       }
 
     if(this->CheckArgument(arg, "-N", "--show-only"))
       {
-      this->m_ShowOnly = true;
+      this->ShowOnly = true;
       }
 
     if(this->CheckArgument(arg, "-S", "--script") && i < args.size() - 1 )
       {
-      this->m_RunConfigurationScript = true;
+      this->RunConfigurationScript = true;
       i++;
       cmCTestScriptHandler* ch
         = static_cast<cmCTestScriptHandler*>(this->GetHandler("script"));
@@ -1361,30 +1361,30 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
 
     if(this->CheckArgument(arg, "--tomorrow-tag"))
       {
-      m_TomorrowTag = true;
+      this->TomorrowTag = true;
       }
     if(this->CheckArgument(arg, "--force-new-ctest-process"))
       {
-      m_ForceNewCTestProcess = true;
+      this->ForceNewCTestProcess = true;
       }
     if(this->CheckArgument(arg, "--interactive-debug-mode") &&
       i < args.size() - 1 )
       {
       i++;
-      m_InteractiveDebugMode = cmSystemTools::IsOn(args[i].c_str());
+      this->InteractiveDebugMode = cmSystemTools::IsOn(args[i].c_str());
       }
     if(this->CheckArgument(arg, "--submit-index") && i < args.size() - 1 )
       {
       i++;
-      m_SubmitIndex = atoi(args[i].c_str());
-      if ( m_SubmitIndex < 0 )
+      this->SubmitIndex = atoi(args[i].c_str());
+      if ( this->SubmitIndex < 0 )
         {
-        m_SubmitIndex = 0;
+        this->SubmitIndex = 0;
         }
       }
     if(this->CheckArgument(arg, "-D", "--dashboard") && i < args.size() - 1 )
       {
-      this->m_ProduceXML = true;
+      this->ProduceXML = true;
       i++;
       std::string targ = args[i];
       if ( targ == "Experimental" )
@@ -1591,7 +1591,7 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
     if(this->CheckArgument(arg, "-T", "--test-action") &&
       (i < args.size() -1) )
       {
-      this->m_ProduceXML = true;
+      this->ProduceXML = true;
       i++;
       if ( !this->SetTest(args[i].c_str(), false) )
         {
@@ -1676,14 +1676,14 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
       }
     if(this->CheckArgument(arg, "-A", "--add-notes") && i < args.size() - 1)
       {
-      this->m_ProduceXML = true;
+      this->ProduceXML = true;
       this->SetTest("Notes");
       i++;
       this->SetNotesFiles(args[i].c_str());
       }
     if(this->CheckArgument(arg, "--extra-submit") && i < args.size() - 1)
       {
-      this->m_ProduceXML = true;
+      this->ProduceXML = true;
       this->SetTest("Submit");
       i++;
       if ( !this->SubmitExtraFiles(args[i].c_str()) )
@@ -1697,8 +1697,8 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
       cmakeAndTest = true;
       }
     cmCTest::t_TestingHandlers::iterator it;
-    for ( it = m_TestingHandlers.begin();
-      it != m_TestingHandlers.end();
+    for ( it = this->TestingHandlers.begin();
+      it != this->TestingHandlers.end();
       ++ it )
       {
       if ( !it->second->ProcessCommandLineArguments(arg, i, args) )
@@ -1711,16 +1711,16 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
     }
 
   // default to the build type of ctest itself
-  if(m_ConfigType.size() == 0)
+  if(this->ConfigType.size() == 0)
     {
 #ifdef  CMAKE_INTDIR
-    m_ConfigType = CMAKE_INTDIR;
+    this->ConfigType = CMAKE_INTDIR;
 #endif
     }
 
   if(cmakeAndTest)
     {
-    m_Verbose = true;
+    this->Verbose = true;
     cmCTestBuildAndTestHandler* handler =
       static_cast<cmCTestBuildAndTestHandler*>(this->GetHandler("buildtest"));
     int retv = handler->ProcessHandler();
@@ -1735,34 +1735,34 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
     {
     int res;
     // call process directory
-    if (this->m_RunConfigurationScript)
+    if (this->RunConfigurationScript)
       {
-      if ( m_ExtraVerbose )
+      if ( this->ExtraVerbose )
         {
         cmCTestLog(this, OUTPUT, "* Extra verbosity turned on" << std::endl);
         }
       cmCTest::t_TestingHandlers::iterator it;
-      for ( it = m_TestingHandlers.begin();
-        it != m_TestingHandlers.end();
+      for ( it = this->TestingHandlers.begin();
+        it != this->TestingHandlers.end();
         ++ it )
         {
-        it->second->SetVerbose(this->m_ExtraVerbose);
-        it->second->SetSubmitIndex(m_SubmitIndex);
+        it->second->SetVerbose(this->ExtraVerbose);
+        it->second->SetSubmitIndex(this->SubmitIndex);
         }
-      this->GetHandler("script")->SetVerbose(m_Verbose);
+      this->GetHandler("script")->SetVerbose(this->Verbose);
       res = this->GetHandler("script")->ProcessHandler();
       }
     else
       {
-      m_ExtraVerbose = m_Verbose;
-      m_Verbose = true;
+      this->ExtraVerbose = this->Verbose;
+      this->Verbose = true;
       cmCTest::t_TestingHandlers::iterator it;
-      for ( it = m_TestingHandlers.begin();
-        it != m_TestingHandlers.end();
+      for ( it = this->TestingHandlers.begin();
+        it != this->TestingHandlers.end();
         ++ it )
         {
-        it->second->SetVerbose(this->m_Verbose);
-        it->second->SetSubmitIndex(m_SubmitIndex);
+        it->second->SetVerbose(this->Verbose);
+        it->second->SetSubmitIndex(this->SubmitIndex);
         }
       cmCTestLog(this, DEBUG, "Here: " << __LINE__ << std::endl);
       if ( !this->Initialize(
@@ -1789,18 +1789,18 @@ void cmCTest::FindRunningCMake(const char* arg0)
 {
   // Find our own executable.
   std::vector<cmStdString> failures;
-  m_CTestSelf = arg0;
-  cmSystemTools::ConvertToUnixSlashes(m_CTestSelf);
-  failures.push_back(m_CTestSelf);
-  m_CTestSelf = cmSystemTools::FindProgram(m_CTestSelf.c_str());
-  if(!cmSystemTools::FileExists(m_CTestSelf.c_str()))
+  this->CTestSelf = arg0;
+  cmSystemTools::ConvertToUnixSlashes(this->CTestSelf);
+  failures.push_back(this->CTestSelf);
+  this->CTestSelf = cmSystemTools::FindProgram(this->CTestSelf.c_str());
+  if(!cmSystemTools::FileExists(this->CTestSelf.c_str()))
     {
-    failures.push_back(m_CTestSelf);
-    m_CTestSelf =  "/usr/local/bin/ctest";
+    failures.push_back(this->CTestSelf);
+    this->CTestSelf =  "/usr/local/bin/ctest";
     }
-  if(!cmSystemTools::FileExists(m_CTestSelf.c_str()))
+  if(!cmSystemTools::FileExists(this->CTestSelf.c_str()))
     {
-    failures.push_back(m_CTestSelf);
+    failures.push_back(this->CTestSelf);
     cmOStringStream msg;
     msg << "CTEST can not find the command line program ctest.\n";
     msg << "  argv[0] = \"" << arg0 << "\"\n";
@@ -1814,31 +1814,31 @@ void cmCTest::FindRunningCMake(const char* arg0)
     }
   std::string dir;
   std::string file;
-  if(cmSystemTools::SplitProgramPath(m_CTestSelf.c_str(),
+  if(cmSystemTools::SplitProgramPath(this->CTestSelf.c_str(),
                                      dir, file, true))
     {
-    m_CMakeSelf = dir += "/cmake";
-    m_CMakeSelf += cmSystemTools::GetExecutableExtension();
-    if(cmSystemTools::FileExists(m_CMakeSelf.c_str()))
+    this->CMakeSelf = dir += "/cmake";
+    this->CMakeSelf += cmSystemTools::GetExecutableExtension();
+    if(cmSystemTools::FileExists(this->CMakeSelf.c_str()))
       {
       return;
       }
     }
-  failures.push_back(m_CMakeSelf);
+  failures.push_back(this->CMakeSelf);
 #ifdef CMAKE_BUILD_DIR
   std::string intdir = ".";
 #ifdef  CMAKE_INTDIR
   intdir = CMAKE_INTDIR;
 #endif
-  m_CMakeSelf = CMAKE_BUILD_DIR;
-  m_CMakeSelf += "/bin/";
-  m_CMakeSelf += intdir;
-  m_CMakeSelf += "/cmake";
-  m_CMakeSelf += cmSystemTools::GetExecutableExtension();
+  this->CMakeSelf = CMAKE_BUILD_DIR;
+  this->CMakeSelf += "/bin/";
+  this->CMakeSelf += intdir;
+  this->CMakeSelf += "/cmake";
+  this->CMakeSelf += cmSystemTools::GetExecutableExtension();
 #endif
-  if(!cmSystemTools::FileExists(m_CMakeSelf.c_str()))
+  if(!cmSystemTools::FileExists(this->CMakeSelf.c_str()))
     {
-    failures.push_back(m_CMakeSelf);
+    failures.push_back(this->CMakeSelf);
     cmOStringStream msg;
     msg << "CTEST can not find the command line program cmake.\n";
     msg << "  argv[0] = \"" << arg0 << "\"\n";
@@ -1859,7 +1859,7 @@ void cmCTest::SetNotesFiles(const char* notes)
     {
     return;
     }
-  m_NotesFiles = notes;
+  this->NotesFiles = notes;
 }
 
 //----------------------------------------------------------------------
@@ -1895,7 +1895,7 @@ int cmCTest::ReadCustomConfigurationFileTree(const char* dir)
     }
 
   cmCTest::t_TestingHandlers::iterator it;
-  for ( it = m_TestingHandlers.begin(); it != m_TestingHandlers.end(); ++ it )
+  for ( it = this->TestingHandlers.begin(); it != this->TestingHandlers.end(); ++ it )
     {
     it->second->PopulateCustomVectors(mf);
     }
@@ -1999,18 +1999,18 @@ std::string cmCTest::GetShortPathToFile(const char* cfname)
 //----------------------------------------------------------------------
 std::string cmCTest::GetCTestConfiguration(const char *name)
 {
-  if ( m_CTestConfigurationOverwrites.find(name) !=
-    m_CTestConfigurationOverwrites.end() )
+  if ( this->CTestConfigurationOverwrites.find(name) !=
+    this->CTestConfigurationOverwrites.end() )
     {
-    return m_CTestConfigurationOverwrites[name];
+    return this->CTestConfigurationOverwrites[name];
     }
-  return m_CTestConfiguration[name];
+  return this->CTestConfiguration[name];
 }
 
 //----------------------------------------------------------------------
 void cmCTest::EmptyCTestConfiguration()
 {
-  m_CTestConfiguration.clear();
+  this->CTestConfiguration.clear();
 }
 
 //----------------------------------------------------------------------
@@ -2022,53 +2022,53 @@ void cmCTest::SetCTestConfiguration(const char *name, const char* value)
     }
   if ( !value )
     {
-    m_CTestConfiguration.erase(name);
+    this->CTestConfiguration.erase(name);
     return;
     }
-  m_CTestConfiguration[name] = value;
+  this->CTestConfiguration[name] = value;
 }
 
 
 //----------------------------------------------------------------------
 std::string cmCTest::GetCurrentTag()
 {
-  return m_CurrentTag;
+  return this->CurrentTag;
 }
 
 //----------------------------------------------------------------------
 std::string cmCTest::GetBinaryDir()
 {
-  return m_BinaryDir;
+  return this->BinaryDir;
 }
 
 //----------------------------------------------------------------------
 std::string cmCTest::GetConfigType()
 {
-  return m_ConfigType;
+  return this->ConfigType;
 }
 
 //----------------------------------------------------------------------
 bool cmCTest::GetShowOnly()
 {
-  return m_ShowOnly;
+  return this->ShowOnly;
 }
 
 //----------------------------------------------------------------------
 void cmCTest::SetProduceXML(bool v)
 {
-  m_ProduceXML = v;
+  this->ProduceXML = v;
 }
 
 //----------------------------------------------------------------------
 bool cmCTest::GetProduceXML()
 {
-  return m_ProduceXML;
+  return this->ProduceXML;
 }
 
 //----------------------------------------------------------------------
 void cmCTest::AddSubmitFile(const char* name)
 {
-  m_SubmitFiles.insert(name);
+  this->SubmitFiles.insert(name);
 }
 
 //----------------------------------------------------------------------
@@ -2087,7 +2087,7 @@ void cmCTest::AddCTestConfigurationOverwrite(const char* encstr)
     }
   std::string key = overStr.substr(0, epos);
   std::string value = overStr.substr(epos+1, overStr.npos);
-  m_CTestConfigurationOverwrites[key] = value;
+  this->CTestConfigurationOverwrites[key] = value;
 }
 
 //----------------------------------------------------------------------
@@ -2161,7 +2161,7 @@ bool cmCTest::RunCommand(
       done = true;
       }
     if ( (res == cmsysProcess_Pipe_STDOUT ||
-        res == cmsysProcess_Pipe_STDERR) && m_ExtraVerbose )
+        res == cmsysProcess_Pipe_STDERR) && this->ExtraVerbose )
       {
       cmSystemTools::Stdout(data, length);
       }
@@ -2215,14 +2215,14 @@ bool cmCTest::RunCommand(
 //----------------------------------------------------------------------
 void cmCTest::SetOutputLogFileName(const char* name)
 {
-  if ( m_OutputLogFile)
+  if ( this->OutputLogFile)
     {
-    delete m_OutputLogFile;
-    m_OutputLogFile= 0;
+    delete this->OutputLogFile;
+    this->OutputLogFile= 0;
     }
   if ( name )
     {
-    m_OutputLogFile = new cmGeneratedFileStream(name);
+    this->OutputLogFile = new cmGeneratedFileStream(name);
     }
 }
 
@@ -2247,7 +2247,7 @@ static const char* cmCTestStringLogType[] =
 #endif
 
 #define cmCTestLogOutputFileLine(stream) \
-  if ( m_ShowLineNumbers ) \
+  if ( this->ShowLineNumbers ) \
     { \
     (stream) << std::endl << file << ":" << line << " "; \
     }
@@ -2258,58 +2258,58 @@ void cmCTest::Log(int logType, const char* file, int line, const char* msg)
     {
     return;
     }
-  if ( m_OutputLogFile )
+  if ( this->OutputLogFile )
     {
     bool display = true;
-    if ( logType == cmCTest::DEBUG && !m_Debug ) { display = false; }
-    if ( logType == cmCTest::HANDLER_VERBOSE_OUTPUT && !m_Debug &&
-      !m_ExtraVerbose ) { display = false; }
+    if ( logType == cmCTest::DEBUG && !this->Debug ) { display = false; }
+    if ( logType == cmCTest::HANDLER_VERBOSE_OUTPUT && !this->Debug &&
+      !this->ExtraVerbose ) { display = false; }
     if ( display )
       {
-      cmCTestLogOutputFileLine(*m_OutputLogFile);
-      if ( logType != m_OutputLogFileLastTag )
+      cmCTestLogOutputFileLine(*this->OutputLogFile);
+      if ( logType != this->OutputLogFileLastTag )
         {
-        *m_OutputLogFile << "[";
+        *this->OutputLogFile << "[";
         if ( logType >= OTHER || logType < 0 )
           {
-          *m_OutputLogFile << "OTHER";
+          *this->OutputLogFile << "OTHER";
           }
         else
           {
-          *m_OutputLogFile << cmCTestStringLogType[logType];
+          *this->OutputLogFile << cmCTestStringLogType[logType];
           }
-        *m_OutputLogFile << "] " << std::endl << std::flush;
+        *this->OutputLogFile << "] " << std::endl << std::flush;
         }
-      *m_OutputLogFile << msg << std::flush;
-      if ( logType != m_OutputLogFileLastTag )
+      *this->OutputLogFile << msg << std::flush;
+      if ( logType != this->OutputLogFileLastTag )
         {
-        *m_OutputLogFile << std::endl << std::flush;
-        m_OutputLogFileLastTag = logType;
+        *this->OutputLogFile << std::endl << std::flush;
+        this->OutputLogFileLastTag = logType;
         }
       }
     }
-  if ( !m_Quiet )
+  if ( !this->Quiet )
     {
     switch ( logType )
       {
     case DEBUG:
-      if ( m_Debug )
+      if ( this->Debug )
         {
         cmCTestLogOutputFileLine(std::cout);
         std::cout << msg;
         std::cout.flush();
         }
       break;
     case OUTPUT: case HANDLER_OUTPUT:
-      if ( m_Debug || m_Verbose )
+      if ( this->Debug || this->Verbose )
         {
         cmCTestLogOutputFileLine(std::cout);
         std::cout << msg;
         std::cout.flush();
         }
       break;
     case HANDLER_VERBOSE_OUTPUT:
-      if ( m_Debug || m_ExtraVerbose )
+      if ( this->Debug || this->ExtraVerbose )
         {
         cmCTestLogOutputFileLine(std::cout);
         std::cout << msg;