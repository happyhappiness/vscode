@@ -45,7 +45,7 @@ class cmCTestSubdirCommand : public cmCommand
   virtual cmCommand* Clone()
     {
     cmCTestSubdirCommand* c = new cmCTestSubdirCommand;
-    c->m_TestHandler = m_TestHandler;
+    c->TestHandler = this->TestHandler;
     return c;
     }
 
@@ -66,7 +66,7 @@ class cmCTestSubdirCommand : public cmCommand
 
   cmTypeMacro(cmCTestSubdirCommand, cmCommand);
 
-  cmCTestTestHandler* m_TestHandler;
+  cmCTestTestHandler* TestHandler;
 };
 
 //----------------------------------------------------------------------
@@ -135,7 +135,7 @@ class cmCTestAddTestCommand : public cmCommand
   virtual cmCommand* Clone()
     {
     cmCTestAddTestCommand* c = new cmCTestAddTestCommand;
-    c->m_TestHandler = m_TestHandler;
+    c->TestHandler = this->TestHandler;
     return c;
     }
 
@@ -156,7 +156,7 @@ class cmCTestAddTestCommand : public cmCommand
 
   cmTypeMacro(cmCTestAddTestCommand, cmCommand);
 
-  cmCTestTestHandler* m_TestHandler;
+  cmCTestTestHandler* TestHandler;
 };
 
 //----------------------------------------------------------------------
@@ -167,7 +167,7 @@ bool cmCTestAddTestCommand::InitialPass(std::vector<std::string> const& args)
     this->SetError("called with incorrect number of arguments");
     return false;
     }
-  return m_TestHandler->AddTest(args);
+  return this->TestHandler->AddTest(args);
 }
 
 //----------------------------------------------------------------------
@@ -181,7 +181,7 @@ class cmCTestSetTestsPropertiesCommand : public cmCommand
     {
     cmCTestSetTestsPropertiesCommand* c
       = new cmCTestSetTestsPropertiesCommand;
-    c->m_TestHandler = m_TestHandler;
+    c->TestHandler = this->TestHandler;
     return c;
     }
 
@@ -202,14 +202,14 @@ class cmCTestSetTestsPropertiesCommand : public cmCommand
 
   cmTypeMacro(cmCTestSetTestsPropertiesCommand, cmCommand);
 
-  cmCTestTestHandler* m_TestHandler;
+  cmCTestTestHandler* TestHandler;
 };
 
 //----------------------------------------------------------------------
 bool cmCTestSetTestsPropertiesCommand::InitialPass(
   std::vector<std::string> const& args)
 {
-  return m_TestHandler->SetTestsProperties(args);
+  return this->TestHandler->SetTestsProperties(args);
 }
 
 //----------------------------------------------------------------------
@@ -335,77 +335,77 @@ inline int GetNextRealNumber(std::string const& in,
 //----------------------------------------------------------------------
 cmCTestTestHandler::cmCTestTestHandler()
 {
-  m_UseUnion = false;
+  this->UseUnion = false;
 
-  m_UseIncludeRegExp       = false;
-  m_UseExcludeRegExp       = false;
-  m_UseExcludeRegExpFirst  = false;
+  this->UseIncludeRegExpFlag   = false;
+  this->UseExcludeRegExpFlag   = false;
+  this->UseExcludeRegExpFirst  = false;
 
-  m_CustomMaximumPassedTestOutputSize = 1 * 1024;
-  m_CustomMaximumFailedTestOutputSize = 300 * 1024;
+  this->CustomMaximumPassedTestOutputSize = 1 * 1024;
+  this->CustomMaximumFailedTestOutputSize = 300 * 1024;
 
-  m_MemCheck = false;
+  this->MemCheck = false;
 
-  m_LogFile = 0;
+  this->LogFile = 0;
 
-  m_DartStuff.compile("(<DartMeasurement.*/DartMeasurement[a-zA-Z]*>)");
+  this->DartStuff.compile("(<DartMeasurement.*/DartMeasurement[a-zA-Z]*>)");
 }
 
 //----------------------------------------------------------------------
 void cmCTestTestHandler::Initialize()
 {
   this->Superclass::Initialize();
 
-  m_ElapsedTestingTime = -1;
+  this->ElapsedTestingTime = -1;
 
-  m_TestResults.clear();
+  this->TestResults.clear();
 
-  m_CustomTestsIgnore.clear();
-  m_StartTest = "";
-  m_EndTest = "";
+  this->CustomTestsIgnore.clear();
+  this->StartTest = "";
+  this->EndTest = "";
 
-  m_CustomPreTest.clear();
-  m_CustomPostTest.clear();
-  m_CustomMaximumPassedTestOutputSize = 1 * 1024;
-  m_CustomMaximumFailedTestOutputSize = 300 * 1024;
+  this->CustomPreTest.clear();
+  this->CustomPostTest.clear();
+  this->CustomMaximumPassedTestOutputSize = 1 * 1024;
+  this->CustomMaximumFailedTestOutputSize = 300 * 1024;
 
-  m_TestsToRun.clear();
+  this->TestsToRun.clear();
 
-  m_UseIncludeRegExp = false;
-  m_UseExcludeRegExp = false;
-  m_UseExcludeRegExpFirst = false;
-  m_IncludeRegExp = "";
-  m_ExcludeRegExp = "";
+  this->UseIncludeRegExpFlag = false;
+  this->UseExcludeRegExpFlag = false;
+  this->UseExcludeRegExpFirst = false;
+  this->IncludeRegExp = "";
+  this->ExcludeRegExp = "";
 
   TestsToRunString = "";
-  m_UseUnion = false;
-  m_TestList.clear();
+  this->UseUnion = false;
+  this->TestList.clear();
 }
 
 //----------------------------------------------------------------------
 void cmCTestTestHandler::PopulateCustomVectors(cmMakefile *mf)
 {
   cmCTest::PopulateCustomVector(mf, "CTEST_CUSTOM_PRE_TEST",
-                                m_CustomPreTest);
+                                this->CustomPreTest);
   cmCTest::PopulateCustomVector(mf, "CTEST_CUSTOM_POST_TEST",
-                                m_CustomPostTest);
+                                this->CustomPostTest);
   cmCTest::PopulateCustomVector(mf,
                              "CTEST_CUSTOM_TESTS_IGNORE",
-                             m_CustomTestsIgnore);
+                             this->CustomTestsIgnore);
   cmCTest::PopulateCustomInteger(mf,
                              "CTEST_CUSTOM_MAXIMUM_PASSED_TEST_OUTPUT_SIZE",
-                             m_CustomMaximumPassedTestOutputSize);
+                             this->CustomMaximumPassedTestOutputSize);
   cmCTest::PopulateCustomInteger(mf,
                              "CTEST_CUSTOM_MAXIMUM_FAILED_TEST_OUTPUT_SIZE",
-                             m_CustomMaximumFailedTestOutputSize);
+                             this->CustomMaximumFailedTestOutputSize);
 }
 
 //----------------------------------------------------------------------
 int cmCTestTestHandler::PreProcessHandler()
 {
-  if ( !this->ExecuteCommands(m_CustomPreTest) )
+  if ( !this->ExecuteCommands(this->CustomPreTest) )
     {
-    cmCTestLog(m_CTest, ERROR_MESSAGE,
+    cmCTestLog(this->CTest, ERROR_MESSAGE,
       "Problem executing pre-test command(s)." << std::endl);
     return 0;
     }
@@ -415,9 +415,9 @@ int cmCTestTestHandler::PreProcessHandler()
 //----------------------------------------------------------------------
 int cmCTestTestHandler::PostProcessHandler()
 {
-  if ( !this->ExecuteCommands(m_CustomPostTest) )
+  if ( !this->ExecuteCommands(this->CustomPostTest) )
     {
-    cmCTestLog(m_CTest, ERROR_MESSAGE,
+    cmCTestLog(this->CTest, ERROR_MESSAGE,
       "Problem executing post-test command(s)." << std::endl);
     return 0;
     }
@@ -446,9 +446,10 @@ int cmCTestTestHandler::ProcessHandler()
     this->SetExcludeRegExp(val);
     }
 
-  m_TestResults.clear();
+  this->TestResults.clear();
 
-  cmCTestLog(m_CTest, HANDLER_OUTPUT, (m_MemCheck ? "Memory check" : "Test")
+  cmCTestLog(this->CTest, HANDLER_OUTPUT,
+    (this->MemCheck ? "Memory check" : "Test")
     << " project" << std::endl);
   if ( ! this->PreProcessHandler() )
     {
@@ -457,7 +458,7 @@ int cmCTestTestHandler::ProcessHandler()
 
   cmGeneratedFileStream mLogFile;
   this->StartLogFile("Tests", mLogFile);
-  m_LogFile = &mLogFile;
+  this->LogFile = &mLogFile;
 
   std::vector<cmStdString> passed;
   std::vector<cmStdString> failed;
@@ -469,23 +470,24 @@ int cmCTestTestHandler::ProcessHandler()
 
   if (total == 0)
     {
-    if ( !m_CTest->GetShowOnly() )
+    if ( !this->CTest->GetShowOnly() )
       {
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "No tests were found!!!"
+      cmCTestLog(this->CTest, ERROR_MESSAGE, "No tests were found!!!"
         << std::endl);
       }
     }
   else
     {
-    if (m_HandlerVerbose && passed.size() &&
-      (m_UseIncludeRegExp || m_UseExcludeRegExp))
+    if (this->HandlerVerbose && passed.size() &&
+      (this->UseIncludeRegExpFlag || this->UseExcludeRegExpFlag))
       {
-      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, std::endl
+      cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, std::endl
         << "The following tests passed:" << std::endl);
       for(std::vector<cmStdString>::iterator j = passed.begin();
           j != passed.end(); ++j)
         {
-        cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "\t" << *j << std::endl);
+        cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "\t" << *j
+          << std::endl);
         }
       }
 
@@ -494,7 +496,7 @@ int cmCTestTestHandler::ProcessHandler()
       {
       percent = 99;
       }
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, std::endl
+    cmCTestLog(this->CTest, HANDLER_OUTPUT, std::endl
       << static_cast<int>(percent + .5) << "% tests passed, "
       << failed.size() << " tests failed out of " << total << std::endl);
     //fprintf(stderr,"\n%.0f%% tests passed, %i tests failed out of %i\n",
@@ -504,53 +506,53 @@ int cmCTestTestHandler::ProcessHandler()
       {
       cmGeneratedFileStream ofs;
 
-      cmCTestLog(m_CTest, ERROR_MESSAGE, std::endl
+      cmCTestLog(this->CTest, ERROR_MESSAGE, std::endl
         << "The following tests FAILED:" << std::endl);
       this->StartLogFile("TestsFailed", ofs);
 
       std::vector<cmCTestTestHandler::cmCTestTestResult>::iterator ftit;
-      for(ftit = m_TestResults.begin();
-        ftit != m_TestResults.end(); ++ftit)
+      for(ftit = this->TestResults.begin();
+        ftit != this->TestResults.end(); ++ftit)
         {
-        if ( ftit->m_Status != cmCTestTestHandler::COMPLETED )
+        if ( ftit->Status != cmCTestTestHandler::COMPLETED )
           {
-          ofs << ftit->m_TestCount << ":" << ftit->m_Name << std::endl;
-          cmCTestLog(m_CTest, HANDLER_OUTPUT, "\t" << std::setw(3)
-            << ftit->m_TestCount << " - " << ftit->m_Name.c_str() << " ("
-            << this->GetTestStatus(ftit->m_Status) << ")" << std::endl);
+          ofs << ftit->TestCount << ":" << ftit->Name << std::endl;
+          cmCTestLog(this->CTest, HANDLER_OUTPUT, "\t" << std::setw(3)
+            << ftit->TestCount << " - " << ftit->Name.c_str() << " ("
+            << this->GetTestStatus(ftit->Status) << ")" << std::endl);
           }
         }
 
       }
     }
 
-  if ( m_CTest->GetProduceXML() )
+  if ( this->CTest->GetProduceXML() )
     {
     cmGeneratedFileStream xmlfile;
-    if( !this->StartResultingXML((m_MemCheck ? "DynamicAnalysis" : "Test"),
-        xmlfile) )
+    if( !this->StartResultingXML(
+        (this->MemCheck ? "DynamicAnalysis" : "Test"), xmlfile) )
       {
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot create "
-        << (m_MemCheck ? "memory check" : "testing")
+      cmCTestLog(this->CTest, ERROR_MESSAGE, "Cannot create "
+        << (this->MemCheck ? "memory check" : "testing")
         << " XML file" << std::endl);
-      m_LogFile = 0;
+      this->LogFile = 0;
       return 1;
       }
     this->GenerateDartOutput(xmlfile);
     }
 
   if ( ! this->PostProcessHandler() )
     {
-    m_LogFile = 0;
+    this->LogFile = 0;
     return -1;
     }
 
   if ( !failed.empty() )
     {
-    m_LogFile = 0;
+    this->LogFile = 0;
     return -1;
     }
-  m_LogFile = 0;
+  this->LogFile = 0;
   return 0;
 }
 
@@ -559,30 +561,30 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
                                           std::vector<cmStdString> &failed)
 {
   std::string current_dir = cmSystemTools::GetCurrentWorkingDirectory();
-  m_TestList.clear();
+  this->TestList.clear();
 
   this->GetListOfTests();
-  tm_ListOfTests::size_type tmsize = m_TestList.size();
+  cmCTestTestHandler::ListOfTests::size_type tmsize = this->TestList.size();
 
-  m_StartTest = m_CTest->CurrentTime();
+  this->StartTest = this->CTest->CurrentTime();
   double elapsed_time_start = cmSystemTools::GetTime();
 
-  *m_LogFile << "Start testing: " << m_StartTest << std::endl
+  *this->LogFile << "Start testing: " << this->StartTest << std::endl
     << "----------------------------------------------------------"
     << std::endl;
 
   // how many tests are in based on RegExp?
   int inREcnt = 0;
-  tm_ListOfTests::iterator it;
-  for ( it = m_TestList.begin(); it != m_TestList.end(); it ++ )
+  cmCTestTestHandler::ListOfTests::iterator it;
+  for ( it = this->TestList.begin(); it != this->TestList.end(); it ++ )
     {
-    if (it->m_IsInBasedOnREOptions)
+    if (it->IsInBasedOnREOptions)
       {
       inREcnt ++;
       }
     }
   // expand the test list based on the union flag
-  if (m_UseUnion)
+  if (this->UseUnion)
     {
     this->ExpandTestsToRunInformation((int)tmsize);
     }
@@ -594,80 +596,81 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
   int cnt = 0;
   inREcnt = 0;
   std::string last_directory = "";
-  for ( it = m_TestList.begin(); it != m_TestList.end(); it ++ )
+  for ( it = this->TestList.begin(); it != this->TestList.end(); it ++ )
     {
     cnt ++;
-    if (it->m_IsInBasedOnREOptions)
+    if (it->IsInBasedOnREOptions)
       {
       inREcnt++;
       }
-    const std::string& testname = it->m_Name;
-    std::vector<std::string>& args = it->m_Args;
+    const std::string& testname = it->Name;
+    std::vector<std::string>& args = it->Args;
     cmCTestTestResult cres;
-    cres.m_ExecutionTime = 0;
-    cres.m_ReturnValue = -1;
-    cres.m_Status = cmCTestTestHandler::NOT_RUN;
-    cres.m_TestCount = cnt;
+    cres.ExecutionTime = 0;
+    cres.ReturnValue = -1;
+    cres.Status = cmCTestTestHandler::NOT_RUN;
+    cres.TestCount = cnt;
 
-    if (!(last_directory == it->m_Directory))
+    if (!(last_directory == it->Directory))
       {
-      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Changing directory into "
-        << it->m_Directory.c_str() << "\n");
-      *m_LogFile << "Changing directory into: " << it->m_Directory.c_str()
+      cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+        "Changing directory into " << it->Directory.c_str() << "\n");
+      *this->LogFile << "Changing directory into: " << it->Directory.c_str()
         << std::endl;
-      last_directory = it->m_Directory;
-      cmSystemTools::ChangeDirectory(it->m_Directory.c_str());
+      last_directory = it->Directory;
+      cmSystemTools::ChangeDirectory(it->Directory.c_str());
       }
-    cres.m_Name = testname;
-    cres.m_Path = it->m_Directory.c_str();
+    cres.Name = testname;
+    cres.Path = it->Directory.c_str();
 
-    if (m_UseUnion)
+    if (this->UseUnion)
       {
       // if it is not in the list and not in the regexp then skip
-      if ((m_TestsToRun.size() &&
-           std::find(m_TestsToRun.begin(), m_TestsToRun.end(), cnt)
-           == m_TestsToRun.end()) && !it->m_IsInBasedOnREOptions)
+      if ((this->TestsToRun.size() &&
+           std::find(this->TestsToRun.begin(), this->TestsToRun.end(), cnt)
+           == this->TestsToRun.end()) && !it->IsInBasedOnREOptions)
         {
         continue;
         }
       }
     else
       {
       // is this test in the list of tests to run? If not then skip it
-      if ((m_TestsToRun.size() &&
-           std::find(m_TestsToRun.begin(), m_TestsToRun.end(), inREcnt)
-           == m_TestsToRun.end()) || !it->m_IsInBasedOnREOptions)
+      if ((this->TestsToRun.size() &&
+           std::find(this->TestsToRun.begin(),
+             this->TestsToRun.end(), inREcnt)
+           == this->TestsToRun.end()) || !it->IsInBasedOnREOptions)
         {
         continue;
         }
       }
 
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, std::setw(3) << cnt << "/");
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, std::setw(3) << tmsize << " ");
-    if ( m_MemCheck )
+    cmCTestLog(this->CTest, HANDLER_OUTPUT, std::setw(3) << cnt << "/");
+    cmCTestLog(this->CTest, HANDLER_OUTPUT, std::setw(3) << tmsize << " ");
+    if ( this->MemCheck )
       {
-      cmCTestLog(m_CTest, HANDLER_OUTPUT, "Memory Check");
+      cmCTestLog(this->CTest, HANDLER_OUTPUT, "Memory Check");
       }
     else
       {
-      cmCTestLog(m_CTest, HANDLER_OUTPUT, "Testing");
+      cmCTestLog(this->CTest, HANDLER_OUTPUT, "Testing");
       }
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, " ");
+    cmCTestLog(this->CTest, HANDLER_OUTPUT, " ");
     std::string outname = testname;
     outname.resize(30, ' ');
-    *m_LogFile << cnt << "/" << tmsize << " Testing: " << testname
+    *this->LogFile << cnt << "/" << tmsize << " Testing: " << testname
       << std::endl;
 
-    if ( m_CTest->GetShowOnly() )
+    if ( this->CTest->GetShowOnly() )
       {
-      cmCTestLog(m_CTest, HANDLER_OUTPUT, outname.c_str() << std::endl);
+      cmCTestLog(this->CTest, HANDLER_OUTPUT, outname.c_str() << std::endl);
       }
     else
       {
-      cmCTestLog(m_CTest, HANDLER_OUTPUT, outname.c_str());
+      cmCTestLog(this->CTest, HANDLER_OUTPUT, outname.c_str());
       }
 
-    cmCTestLog(m_CTest, DEBUG, "Testing " << args[0].c_str() << " ... ");
+    cmCTestLog(this->CTest, DEBUG, "Testing " << args[0].c_str() << " ... ");
     // find the test executable
     std::string actualCommand = this->FindTheExecutable(args[1].c_str());
     std::string testCommand
@@ -676,14 +679,14 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
     // continue if we did not find the executable
     if (testCommand == "")
       {
-      *m_LogFile << "Unable to find executable: " << args[1].c_str()
+      *this->LogFile << "Unable to find executable: " << args[1].c_str()
         << std::endl;
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "Unable to find executable: "
+      cmCTestLog(this->CTest, ERROR_MESSAGE, "Unable to find executable: "
         << args[1].c_str() << std::endl);
-      if ( !m_CTest->GetShowOnly() )
+      if ( !this->CTest->GetShowOnly() )
         {
-        cres.m_FullCommandLine = actualCommand;
-        m_TestResults.push_back( cres );
+        cres.FullCommandLine = actualCommand;
+        this->TestResults.push_back( cres );
         failed.push_back(testname);
         continue;
         }
@@ -711,68 +714,68 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
     int retVal = 0;
 
 
-    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, std::endl
-      << (m_MemCheck?"MemCheck":"Test") << " command: " << testCommand
+    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, std::endl
+      << (this->MemCheck?"MemCheck":"Test") << " command: " << testCommand
       << std::endl);
-    *m_LogFile << cnt << "/" << tmsize
+    *this->LogFile << cnt << "/" << tmsize
       << " Test: " << testname.c_str() << std::endl;
-    *m_LogFile << "Command: ";
+    *this->LogFile << "Command: ";
     std::vector<cmStdString>::size_type ll;
     for ( ll = 0; ll < arguments.size()-1; ll ++ )
       {
-      *m_LogFile << "\"" << arguments[ll] << "\" ";
+      *this->LogFile << "\"" << arguments[ll] << "\" ";
       }
-    *m_LogFile
+    *this->LogFile
       << std::endl
-      << "Directory: " << it->m_Directory << std::endl
+      << "Directory: " << it->Directory << std::endl
       << "\"" << testname.c_str() << "\" start time: "
-      << m_CTest->CurrentTime() << std::endl
+      << this->CTest->CurrentTime() << std::endl
       << "Output:" << std::endl
       << "----------------------------------------------------------"
       << std::endl;
     int res = 0;
     double clock_start, clock_finish;
     clock_start = cmSystemTools::GetTime();
 
-    if ( !m_CTest->GetShowOnly() )
+    if ( !this->CTest->GetShowOnly() )
       {
-      res = m_CTest->RunTest(arguments, &output, &retVal, m_LogFile);
+      res = this->CTest->RunTest(arguments, &output, &retVal, this->LogFile);
       }
 
     clock_finish = cmSystemTools::GetTime();
 
-    if ( m_LogFile )
+    if ( this->LogFile )
       {
       double ttime = clock_finish - clock_start;
       int hours = static_cast<int>(ttime / (60 * 60));
       int minutes = static_cast<int>(ttime / 60) % 60;
       int seconds = static_cast<int>(ttime) % 60;
       char buffer[100];
       sprintf(buffer, "%02d:%02d:%02d", hours, minutes, seconds);
-      *m_LogFile
+      *this->LogFile
         << "----------------------------------------------------------"
         << std::endl
         << "\"" << testname.c_str() << "\" end time: "
-        << m_CTest->CurrentTime() << std::endl
+        << this->CTest->CurrentTime() << std::endl
         << "\"" << testname.c_str() << "\" time elapsed: "
         << buffer << std::endl
         << "----------------------------------------------------------"
         << std::endl << std::endl;
       }
 
-    cres.m_ExecutionTime = (double)(clock_finish - clock_start);
-    cres.m_FullCommandLine = testCommand;
+    cres.ExecutionTime = (double)(clock_finish - clock_start);
+    cres.FullCommandLine = testCommand;
 
-    if ( !m_CTest->GetShowOnly() )
+    if ( !this->CTest->GetShowOnly() )
       {
       bool testFailed = false;
       std::vector<cmsys::RegularExpression>::iterator passIt;
       bool forceFail = false;
-      if ( it->m_RequiredRegularExpressions.size() > 0 )
+      if ( it->RequiredRegularExpressions.size() > 0 )
         {
         bool found = false;
-        for ( passIt = it->m_RequiredRegularExpressions.begin();
-          passIt != it->m_RequiredRegularExpressions.end();
+        for ( passIt = it->RequiredRegularExpressions.begin();
+          passIt != it->RequiredRegularExpressions.end();
           ++ passIt )
           {
           if ( passIt->find(output.c_str()) )
@@ -785,10 +788,10 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
           forceFail = true;
           }
         }
-      if ( it->m_ErrorRegularExpressions.size() > 0 )
+      if ( it->ErrorRegularExpressions.size() > 0 )
         {
-        for ( passIt = it->m_ErrorRegularExpressions.begin();
-          passIt != it->m_ErrorRegularExpressions.end();
+        for ( passIt = it->ErrorRegularExpressions.begin();
+          passIt != it->ErrorRegularExpressions.end();
           ++ passIt )
           {
           if ( passIt->find(output.c_str()) )
@@ -799,76 +802,76 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
         }
 
       if (res == cmsysProcess_State_Exited &&
-          (retVal == 0 || it->m_RequiredRegularExpressions.size()) &&
+          (retVal == 0 || it->RequiredRegularExpressions.size()) &&
           !forceFail)
         {
-        cmCTestLog(m_CTest, HANDLER_OUTPUT,   "   Passed");
-        if ( it->m_WillFail )
+        cmCTestLog(this->CTest, HANDLER_OUTPUT,   "   Passed");
+        if ( it->WillFail )
           {
-          cmCTestLog(m_CTest, HANDLER_OUTPUT,   " - But it should fail!");
-          cres.m_Status = cmCTestTestHandler::FAILED;
+          cmCTestLog(this->CTest, HANDLER_OUTPUT,   " - But it should fail!");
+          cres.Status = cmCTestTestHandler::FAILED;
           testFailed = true;
           }
         else
           {
-          cres.m_Status = cmCTestTestHandler::COMPLETED;
+          cres.Status = cmCTestTestHandler::COMPLETED;
           }
-        cmCTestLog(m_CTest, HANDLER_OUTPUT, std::endl);
+        cmCTestLog(this->CTest, HANDLER_OUTPUT, std::endl);
         }
       else
         {
         testFailed = true;
 
-        cres.m_Status = cmCTestTestHandler::FAILED;
+        cres.Status = cmCTestTestHandler::FAILED;
         if ( res == cmsysProcess_State_Expired )
           {
-          cmCTestLog(m_CTest, HANDLER_OUTPUT, "***Timeout" << std::endl);
-          cres.m_Status = cmCTestTestHandler::TIMEOUT;
+          cmCTestLog(this->CTest, HANDLER_OUTPUT, "***Timeout" << std::endl);
+          cres.Status = cmCTestTestHandler::TIMEOUT;
           }
         else if ( res == cmsysProcess_State_Exception )
           {
-          cmCTestLog(m_CTest, HANDLER_OUTPUT, "***Exception: ");
+          cmCTestLog(this->CTest, HANDLER_OUTPUT, "***Exception: ");
           switch ( retVal )
             {
           case cmsysProcess_Exception_Fault:
-            cmCTestLog(m_CTest, HANDLER_OUTPUT, "SegFault");
-            cres.m_Status = cmCTestTestHandler::SEGFAULT;
+            cmCTestLog(this->CTest, HANDLER_OUTPUT, "SegFault");
+            cres.Status = cmCTestTestHandler::SEGFAULT;
             break;
           case cmsysProcess_Exception_Illegal:
-            cmCTestLog(m_CTest, HANDLER_OUTPUT, "Illegal");
-            cres.m_Status = cmCTestTestHandler::ILLEGAL;
+            cmCTestLog(this->CTest, HANDLER_OUTPUT, "Illegal");
+            cres.Status = cmCTestTestHandler::ILLEGAL;
             break;
           case cmsysProcess_Exception_Interrupt:
-            cmCTestLog(m_CTest, HANDLER_OUTPUT, "Interrupt");
-            cres.m_Status = cmCTestTestHandler::INTERRUPT;
+            cmCTestLog(this->CTest, HANDLER_OUTPUT, "Interrupt");
+            cres.Status = cmCTestTestHandler::INTERRUPT;
             break;
           case cmsysProcess_Exception_Numerical:
-            cmCTestLog(m_CTest, HANDLER_OUTPUT, "Numerical");
-            cres.m_Status = cmCTestTestHandler::NUMERICAL;
+            cmCTestLog(this->CTest, HANDLER_OUTPUT, "Numerical");
+            cres.Status = cmCTestTestHandler::NUMERICAL;
             break;
           default:
-            cmCTestLog(m_CTest, HANDLER_OUTPUT, "Other");
-            cres.m_Status = cmCTestTestHandler::OTHER_FAULT;
+            cmCTestLog(this->CTest, HANDLER_OUTPUT, "Other");
+            cres.Status = cmCTestTestHandler::OTHER_FAULT;
             }
-           cmCTestLog(m_CTest, HANDLER_OUTPUT, std::endl);
+           cmCTestLog(this->CTest, HANDLER_OUTPUT, std::endl);
           }
         else if ( res == cmsysProcess_State_Error )
           {
-          cmCTestLog(m_CTest, HANDLER_OUTPUT, "***Bad command " << res
+          cmCTestLog(this->CTest, HANDLER_OUTPUT, "***Bad command " << res
             << std::endl);
-          cres.m_Status = cmCTestTestHandler::BAD_COMMAND;
+          cres.Status = cmCTestTestHandler::BAD_COMMAND;
           }
         else
           {
           // Force fail will also be here?
-          cmCTestLog(m_CTest, HANDLER_OUTPUT, "***Failed");
-          if ( it->m_WillFail )
+          cmCTestLog(this->CTest, HANDLER_OUTPUT, "***Failed");
+          if ( it->WillFail )
             {
-            cres.m_Status = cmCTestTestHandler::COMPLETED;
-            cmCTestLog(m_CTest, HANDLER_OUTPUT, " - supposed to fail");
+            cres.Status = cmCTestTestHandler::COMPLETED;
+            cmCTestLog(this->CTest, HANDLER_OUTPUT, " - supposed to fail");
             testFailed = false;
             }
-          cmCTestLog(m_CTest, HANDLER_OUTPUT, std::endl);
+          cmCTestLog(this->CTest, HANDLER_OUTPUT, std::endl);
           }
         }
       if ( testFailed )
@@ -881,38 +884,38 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
         }
       if (!output.empty() && output.find("<DartMeasurement") != output.npos)
         {
-        if (m_DartStuff.find(output.c_str()))
+        if (this->DartStuff.find(output.c_str()))
           {
-          std::string dartString = m_DartStuff.match(1);
+          std::string dartString = this->DartStuff.match(1);
           cmSystemTools::ReplaceString(output, dartString.c_str(),"");
-          cres.m_RegressionImages
+          cres.RegressionImages
             = this->GenerateRegressionImages(dartString);
           }
         }
       }
 
-    if ( cres.m_Status == cmCTestTestHandler::COMPLETED )
+    if ( cres.Status == cmCTestTestHandler::COMPLETED )
       {
       this->CleanTestOutput(output, static_cast<size_t>(
-          m_CustomMaximumPassedTestOutputSize));
+          this->CustomMaximumPassedTestOutputSize));
       }
     else
       {
       this->CleanTestOutput(output, static_cast<size_t>(
-          m_CustomMaximumFailedTestOutputSize));
+          this->CustomMaximumFailedTestOutputSize));
       }
 
-    cres.m_Output = output;
-    cres.m_ReturnValue = retVal;
-    cres.m_CompletionStatus = "Completed";
-    m_TestResults.push_back( cres );
+    cres.Output = output;
+    cres.ReturnValue = retVal;
+    cres.CompletionStatus = "Completed";
+    this->TestResults.push_back( cres );
     }
 
-  m_EndTest = m_CTest->CurrentTime();
-  m_ElapsedTestingTime = cmSystemTools::GetTime() - elapsed_time_start;
-  if ( m_LogFile )
+  this->EndTest = this->CTest->CurrentTime();
+  this->ElapsedTestingTime = cmSystemTools::GetTime() - elapsed_time_start;
+  if ( this->LogFile )
     {
-    *m_LogFile << "End testing: " << m_EndTest << std::endl;
+    *this->LogFile << "End testing: " << this->EndTest << std::endl;
     }
   cmSystemTools::ChangeDirectory(current_dir.c_str());
 }
@@ -925,92 +928,92 @@ void cmCTestTestHandler::GenerateTestCommand(std::vector<const char*>&)
 //----------------------------------------------------------------------
 void cmCTestTestHandler::GenerateDartOutput(std::ostream& os)
 {
-  if ( !m_CTest->GetProduceXML() )
+  if ( !this->CTest->GetProduceXML() )
     {
     return;
     }
 
-  m_CTest->StartXML(os);
+  this->CTest->StartXML(os);
   os << "<Testing>\n"
-    << "\t<StartDateTime>" << m_StartTest << "</StartDateTime>\n"
+    << "\t<StartDateTime>" << this->StartTest << "</StartDateTime>\n"
     << "\t<TestList>\n";
-  tm_TestResultsVector::size_type cc;
-  for ( cc = 0; cc < m_TestResults.size(); cc ++ )
+  cmCTestTestHandler::TestResultsVector::size_type cc;
+  for ( cc = 0; cc < this->TestResults.size(); cc ++ )
     {
-    cmCTestTestResult *result = &m_TestResults[cc];
-    std::string testPath = result->m_Path + "/" + result->m_Name;
+    cmCTestTestResult *result = &this->TestResults[cc];
+    std::string testPath = result->Path + "/" + result->Name;
     os << "\t\t<Test>" << cmCTest::MakeXMLSafe(
-      m_CTest->GetShortPathToFile(testPath.c_str()))
+      this->CTest->GetShortPathToFile(testPath.c_str()))
       << "</Test>" << std::endl;
     }
   os << "\t</TestList>\n";
-  for ( cc = 0; cc < m_TestResults.size(); cc ++ )
+  for ( cc = 0; cc < this->TestResults.size(); cc ++ )
     {
-    cmCTestTestResult *result = &m_TestResults[cc];
+    cmCTestTestResult *result = &this->TestResults[cc];
     os << "\t<Test Status=\"";
-    if ( result->m_Status == cmCTestTestHandler::COMPLETED )
+    if ( result->Status == cmCTestTestHandler::COMPLETED )
       {
       os << "passed";
       }
-    else if ( result->m_Status == cmCTestTestHandler::NOT_RUN )
+    else if ( result->Status == cmCTestTestHandler::NOT_RUN )
       {
       os << "notrun";
       }
     else
       {
       os << "failed";
       }
-    std::string testPath = result->m_Path + "/" + result->m_Name;
+    std::string testPath = result->Path + "/" + result->Name;
     os << "\">\n"
-      << "\t\t<Name>" << cmCTest::MakeXMLSafe(result->m_Name) << "</Name>\n"
+      << "\t\t<Name>" << cmCTest::MakeXMLSafe(result->Name) << "</Name>\n"
       << "\t\t<Path>" << cmCTest::MakeXMLSafe(
-        m_CTest->GetShortPathToFile(result->m_Path.c_str())) << "</Path>\n"
+        this->CTest->GetShortPathToFile(result->Path.c_str())) << "</Path>\n"
       << "\t\t<FullName>" << cmCTest::MakeXMLSafe(
-        m_CTest->GetShortPathToFile(testPath.c_str())) << "</FullName>\n"
+        this->CTest->GetShortPathToFile(testPath.c_str())) << "</FullName>\n"
       << "\t\t<FullCommandLine>"
-      << cmCTest::MakeXMLSafe(result->m_FullCommandLine)
+      << cmCTest::MakeXMLSafe(result->FullCommandLine)
       << "</FullCommandLine>\n"
       << "\t\t<Results>" << std::endl;
-    if ( result->m_Status != cmCTestTestHandler::NOT_RUN )
+    if ( result->Status != cmCTestTestHandler::NOT_RUN )
       {
-      if ( result->m_Status != cmCTestTestHandler::COMPLETED ||
-        result->m_ReturnValue )
+      if ( result->Status != cmCTestTestHandler::COMPLETED ||
+        result->ReturnValue )
         {
         os << "\t\t\t<NamedMeasurement type=\"text/string\" "
           "name=\"Exit Code\"><Value>"
-          << this->GetTestStatus(result->m_Status) << "</Value>"
+          << this->GetTestStatus(result->Status) << "</Value>"
           "</NamedMeasurement>\n"
           << "\t\t\t<NamedMeasurement type=\"text/string\" "
           "name=\"Exit Value\"><Value>"
-          << result->m_ReturnValue << "</Value></NamedMeasurement>"
+          << result->ReturnValue << "</Value></NamedMeasurement>"
           << std::endl;
         }
-      os << result->m_RegressionImages;
+      os << result->RegressionImages;
       os << "\t\t\t<NamedMeasurement type=\"numeric/double\" "
         << "name=\"Execution Time\"><Value>"
-        << result->m_ExecutionTime << "</Value></NamedMeasurement>\n";
+        << result->ExecutionTime << "</Value></NamedMeasurement>\n";
       os
         << "\t\t\t<NamedMeasurement type=\"text/string\" "
         << "name=\"Completion Status\"><Value>"
-        << result->m_CompletionStatus << "</Value></NamedMeasurement>\n";
+        << result->CompletionStatus << "</Value></NamedMeasurement>\n";
       }
     os
       << "\t\t\t<Measurement>\n"
       << "\t\t\t\t<Value>";
-    os << cmCTest::MakeXMLSafe(result->m_Output);
+    os << cmCTest::MakeXMLSafe(result->Output);
     os
       << "</Value>\n"
       << "\t\t\t</Measurement>\n"
       << "\t\t</Results>\n"
       << "\t</Test>" << std::endl;
     }
 
-  os << "\t<EndDateTime>" << m_EndTest << "</EndDateTime>\n"
+  os << "\t<EndDateTime>" << this->EndTest << "</EndDateTime>\n"
      << "<ElapsedMinutes>"
-     << static_cast<int>(m_ElapsedTestingTime/6)/10.0
+     << static_cast<int>(this->ElapsedTestingTime/6)/10.0
      << "</ElapsedMinutes>"
     << "</Testing>" << std::endl;
-  m_CTest->EndXML(os);
+  this->CTest->EndXML(os);
 }
 
 //----------------------------------------------------------------------
@@ -1020,13 +1023,13 @@ int cmCTestTestHandler::ExecuteCommands(std::vector<cmStdString>& vec)
   for ( it = vec.begin(); it != vec.end(); ++it )
     {
     int retVal = 0;
-    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Run command: " << *it
+    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Run command: " << *it
       << std::endl);
     if ( !cmSystemTools::RunSingleCommand(it->c_str(), 0, &retVal, 0, true
-        /*m_Verbose*/) || retVal != 0 )
+        /*this->Verbose*/) || retVal != 0 )
       {
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "Problem running command: " << *it
-        << std::endl);
+      cmCTestLog(this->CTest, ERROR_MESSAGE, "Problem running command: "
+        << *it << std::endl);
       return 0;
       }
     }
@@ -1045,9 +1048,9 @@ std::string cmCTestTestHandler::FindTheExecutable(const char *exe)
   cmSystemTools::SplitProgramPath(exe, dir, file);
   // first try to find the executable given a config type subdir if there is
   // one
-  if(m_CTest->GetConfigType() != "" &&
+  if(this->CTest->GetConfigType() != "" &&
     ::TryExecutable(dir.c_str(), file.c_str(), &fullPath,
-      m_CTest->GetConfigType().c_str()))
+      this->CTest->GetConfigType().c_str()))
     {
     return fullPath;
     }
@@ -1064,7 +1067,7 @@ std::string cmCTestTestHandler::FindTheExecutable(const char *exe)
     return fullPath;
     }
 
-  if ( m_CTest->GetConfigType() == "" )
+  if ( this->CTest->GetConfigType() == "" )
     {
     // No config type, so try to guess it
     if (::TryExecutable(dir.c_str(),file.c_str(),&fullPath,"Deployment"))
@@ -1109,10 +1112,10 @@ std::string cmCTestTestHandler::FindTheExecutable(const char *exe)
       }
     }
 
-  if ( m_CTest->GetConfigType() != "" )
+  if ( this->CTest->GetConfigType() != "" )
     {
     dir += "/";
-    dir += m_CTest->GetConfigType();
+    dir += this->CTest->GetConfigType();
     dir += "/";
     dir += file;
     cmSystemTools::Error("config type specified on the command line, but "
@@ -1127,39 +1130,39 @@ std::string cmCTestTestHandler::FindTheExecutable(const char *exe)
 //----------------------------------------------------------------------
 void cmCTestTestHandler::GetListOfTests()
 {
-  if ( !m_IncludeRegExp.empty() )
+  if ( !this->IncludeRegExp.empty() )
     {
-    m_IncludeTestsRegularExpression.compile(m_IncludeRegExp.c_str());
+    this->IncludeTestsRegularExpression.compile(this->IncludeRegExp.c_str());
     }
-  if ( !m_ExcludeRegExp.empty() )
+  if ( !this->ExcludeRegExp.empty() )
     {
-    m_ExcludeTestsRegularExpression.compile(m_ExcludeRegExp.c_str());
+    this->ExcludeTestsRegularExpression.compile(this->ExcludeRegExp.c_str());
     }
-  cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Constructing a list of tests"
-    << std::endl);
+  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+    "Constructing a list of tests" << std::endl);
   cmake cm;
   cmGlobalGenerator gg;
   gg.SetCMakeInstance(&cm);
   std::auto_ptr<cmLocalGenerator> lg(gg.CreateLocalGenerator());
   lg->SetGlobalGenerator(&gg);
   cmMakefile *mf = lg->GetMakefile();
   mf->AddDefinition("CTEST_CONFIGURATION_TYPE",
-    m_CTest->GetConfigType().c_str());
+    this->CTest->GetConfigType().c_str());
 
   // Add handler for ADD_TEST
   cmCTestAddTestCommand* newCom1 = new cmCTestAddTestCommand;
-  newCom1->m_TestHandler = this;
+  newCom1->TestHandler = this;
   cm.AddCommand(newCom1);
 
   // Add handler for SUBDIR
   cmCTestSubdirCommand* newCom2 = new cmCTestSubdirCommand;
-  newCom2->m_TestHandler = this;
+  newCom2->TestHandler = this;
   cm.AddCommand(newCom2);
 
   // Add handler for SET_SOURCE_FILES_PROPERTIES
   cmCTestSetTestsPropertiesCommand* newCom3
     = new cmCTestSetTestsPropertiesCommand;
-  newCom3->m_TestHandler = this;
+  newCom3->TestHandler = this;
   cm.AddCommand(newCom3);
 
   const char* testFilename;
@@ -1186,21 +1189,21 @@ void cmCTestTestHandler::GetListOfTests()
     {
     return;
     }
-  cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT,
+  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
     "Done constructing a list of tests" << std::endl);
 }
 
 //----------------------------------------------------------------------
 void cmCTestTestHandler::UseIncludeRegExp()
 {
-  this->m_UseIncludeRegExp = true;
+  this->UseIncludeRegExpFlag = true;
 }
 
 //----------------------------------------------------------------------
 void cmCTestTestHandler::UseExcludeRegExp()
 {
-  this->m_UseExcludeRegExp = true;
-  this->m_UseExcludeRegExpFirst = this->m_UseIncludeRegExp ? false : true;
+  this->UseExcludeRegExpFlag = true;
+  this->UseExcludeRegExpFirst = this->UseIncludeRegExpFlag ? false : true;
 }
 
 //----------------------------------------------------------------------
@@ -1253,9 +1256,9 @@ void cmCTestTestHandler::ExpandTestsToRunInformation(int numTests)
         // now read specific numbers
         while(GetNextNumber(this->TestsToRunString, val, pos, pos2))
           {
-          m_TestsToRun.push_back(val);
+          this->TestsToRun.push_back(val);
           }
-        m_TestsToRun.push_back(val);
+        this->TestsToRun.push_back(val);
         }
       }
     }
@@ -1284,17 +1287,18 @@ void cmCTestTestHandler::ExpandTestsToRunInformation(int numTests)
     int i = 0;
     while (i*stride + start <= end)
       {
-      m_TestsToRun.push_back(static_cast<int>(i*stride+start));
+      this->TestsToRun.push_back(static_cast<int>(i*stride+start));
       ++i;
       }
     }
 
   // sort the array
-  std::sort(m_TestsToRun.begin(), m_TestsToRun.end(), std::less<int>());
+  std::sort(this->TestsToRun.begin(), this->TestsToRun.end(),
+    std::less<int>());
   // remove duplicates
   std::vector<int>::iterator new_end =
-    std::unique(m_TestsToRun.begin(), m_TestsToRun.end());
-  m_TestsToRun.erase(new_end, m_TestsToRun.end());
+    std::unique(this->TestsToRun.begin(), this->TestsToRun.end());
+  this->TestsToRun.erase(new_end, this->TestsToRun.end());
 }
 
 //----------------------------------------------------------------------
@@ -1464,7 +1468,7 @@ std::string cmCTestTestHandler::GenerateRegressionImages(
           << "><Value>File " << filename.c_str()
           << " not found</Value></NamedMeasurement>"
           << std::endl;
-        cmCTestLog(m_CTest, HANDLER_OUTPUT, "File \"" << filename.c_str()
+        cmCTestLog(this->CTest, HANDLER_OUTPUT, "File \"" << filename.c_str()
           << "\" not found." << std::endl);
         }
       cxml.erase(measurementfile.start(),
@@ -1481,13 +1485,13 @@ std::string cmCTestTestHandler::GenerateRegressionImages(
 //----------------------------------------------------------------------
 void cmCTestTestHandler::SetIncludeRegExp(const char *arg)
 {
-  m_IncludeRegExp = arg;
+  this->IncludeRegExp = arg;
 }
 
 //----------------------------------------------------------------------
 void cmCTestTestHandler::SetExcludeRegExp(const char *arg)
 {
-  m_ExcludeRegExp = arg;
+  this->ExcludeRegExp = arg;
 }
 
 //----------------------------------------------------------------------
@@ -1606,14 +1610,16 @@ bool cmCTestTestHandler::SetTestsProperties(
     std::vector<cmStdString>::const_iterator tit;
     for ( tit = tests.begin(); tit != tests.end(); ++ tit )
       {
-      tm_ListOfTests::iterator rtit;
-      for ( rtit = m_TestList.begin(); rtit != m_TestList.end(); ++ rtit )
+      cmCTestTestHandler::ListOfTests::iterator rtit;
+      for ( rtit = this->TestList.begin();
+        rtit != this->TestList.end();
+        ++ rtit )
         {
-        if ( *tit == rtit->m_Name )
+        if ( *tit == rtit->Name )
           {
           if ( key == "WILL_FAIL" )
             {
-            rtit->m_WillFail = cmSystemTools::IsOn(val.c_str());
+            rtit->WillFail = cmSystemTools::IsOn(val.c_str());
             }
           if ( key == "FAIL_REGULAR_EXPRESSION" )
             {
@@ -1622,7 +1628,7 @@ bool cmCTestTestHandler::SetTestsProperties(
             std::vector<std::string>::iterator crit;
             for ( crit = lval.begin(); crit != lval.end(); ++ crit )
               {
-              rtit->m_ErrorRegularExpressions.push_back(
+              rtit->ErrorRegularExpressions.push_back(
                 cmsys::RegularExpression(crit->c_str()));
               }
             }
@@ -1633,7 +1639,7 @@ bool cmCTestTestHandler::SetTestsProperties(
             std::vector<std::string>::iterator crit;
             for ( crit = lval.begin(); crit != lval.end(); ++ crit )
               {
-              rtit->m_RequiredRegularExpressions.push_back(
+              rtit->RequiredRegularExpressions.push_back(
                 cmsys::RegularExpression(crit->c_str()));
               }
             }
@@ -1648,18 +1654,18 @@ bool cmCTestTestHandler::SetTestsProperties(
 bool cmCTestTestHandler::AddTest(const std::vector<std::string>& args)
 {
   const std::string& testname = args[0];
-  if (this->m_UseExcludeRegExp &&
-    this->m_UseExcludeRegExpFirst &&
-    m_ExcludeTestsRegularExpression.find(testname.c_str()))
+  if (this->UseExcludeRegExpFlag &&
+    this->UseExcludeRegExpFirst &&
+    this->ExcludeTestsRegularExpression.find(testname.c_str()))
     {
     return true;
     }
-  if ( m_MemCheck )
+  if ( this->MemCheck )
     {
     std::vector<cmStdString>::iterator it;
     bool found = false;
-    for ( it = m_CustomTestsIgnore.begin();
-      it != m_CustomTestsIgnore.end(); ++ it )
+    for ( it = this->CustomTestsIgnore.begin();
+      it != this->CustomTestsIgnore.end(); ++ it )
       {
       if ( *it == testname )
         {
@@ -1669,7 +1675,7 @@ bool cmCTestTestHandler::AddTest(const std::vector<std::string>& args)
       }
     if ( found )
       {
-      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Ignore memcheck: "
+      cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Ignore memcheck: "
         << *it << std::endl);
       return true;
       }
@@ -1678,8 +1684,8 @@ bool cmCTestTestHandler::AddTest(const std::vector<std::string>& args)
     {
     std::vector<cmStdString>::iterator it;
     bool found = false;
-    for ( it = m_CustomTestsIgnore.begin();
-      it != m_CustomTestsIgnore.end(); ++ it )
+    for ( it = this->CustomTestsIgnore.begin();
+      it != this->CustomTestsIgnore.end(); ++ it )
       {
       if ( *it == testname )
         {
@@ -1689,30 +1695,30 @@ bool cmCTestTestHandler::AddTest(const std::vector<std::string>& args)
       }
     if ( found )
       {
-      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Ignore test: "
+      cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Ignore test: "
         << *it << std::endl);
       return true;
       }
     }
 
   cmCTestTestProperties test;
-  test.m_Name = testname;
-  test.m_Args = args;
-  test.m_Directory = cmSystemTools::GetCurrentWorkingDirectory();
-  test.m_IsInBasedOnREOptions = true;
-  test.m_WillFail = false;
-  if (this->m_UseIncludeRegExp &&
-    !m_IncludeTestsRegularExpression.find(testname.c_str()))
+  test.Name = testname;
+  test.Args = args;
+  test.Directory = cmSystemTools::GetCurrentWorkingDirectory();
+  test.IsInBasedOnREOptions = true;
+  test.WillFail = false;
+  if (this->UseIncludeRegExpFlag &&
+    !this->IncludeTestsRegularExpression.find(testname.c_str()))
     {
-    test.m_IsInBasedOnREOptions = false;
+    test.IsInBasedOnREOptions = false;
     }
-  else if (this->m_UseExcludeRegExp &&
-    !this->m_UseExcludeRegExpFirst &&
-    m_ExcludeTestsRegularExpression.find(testname.c_str()))
+  else if (this->UseExcludeRegExpFlag &&
+    !this->UseExcludeRegExpFirst &&
+    this->ExcludeTestsRegularExpression.find(testname.c_str()))
     {
-    test.m_IsInBasedOnREOptions = false;
+    test.IsInBasedOnREOptions = false;
     }
-  m_TestList.push_back(test);
+  this->TestList.push_back(test);
   return true;
 }
 