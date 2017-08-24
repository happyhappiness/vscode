@@ -559,6 +559,292 @@ int cmCTestTestHandler::ProcessHandler()
 }
 
 //----------------------------------------------------------------------
+void cmCTestTestHandler::ProcessOneTest(cmCTestTestProperties *it,
+                                        std::vector<cmStdString> &passed,
+                                        std::vector<cmStdString> &failed,
+                                        int cnt, int tmsize)
+{
+  const std::string& testname = it->Name;
+  std::vector<std::string>& args = it->Args;
+  cmCTestTestResult cres;
+  cres.Properties = &*it;
+  cres.ExecutionTime = 0;
+  cres.ReturnValue = -1;
+  cres.Status = cmCTestTestHandler::NOT_RUN;
+  cres.TestCount = cnt;  
+  cres.Name = testname;
+  cres.Path = it->Directory.c_str();
+  
+  cmCTestLog(this->CTest, HANDLER_OUTPUT, std::setw(3) << cnt << "/");
+  cmCTestLog(this->CTest, HANDLER_OUTPUT, std::setw(3) << tmsize << " ");
+  if ( this->MemCheck )
+    {
+    cmCTestLog(this->CTest, HANDLER_OUTPUT, "Memory Check");
+    }
+  else
+    {
+    cmCTestLog(this->CTest, HANDLER_OUTPUT, "Testing");
+    }
+  cmCTestLog(this->CTest, HANDLER_OUTPUT, " ");
+  std::string outname = testname;
+  outname.resize(30, ' ');
+  *this->LogFile << cnt << "/" << tmsize << " Testing: " << testname
+                 << std::endl;
+  
+  if ( this->CTest->GetShowOnly() )
+    {
+    cmCTestLog(this->CTest, HANDLER_OUTPUT, outname.c_str() << std::endl);
+    }
+  else
+    {
+    cmCTestLog(this->CTest, HANDLER_OUTPUT, outname.c_str());
+    }
+  
+  cmCTestLog(this->CTest, DEBUG, "Testing " << args[0].c_str() << " ... ");
+  // find the test executable
+  std::string actualCommand = this->FindTheExecutable(args[1].c_str());
+  std::string testCommand
+    = cmSystemTools::ConvertToOutputPath(actualCommand.c_str());
+  
+  // continue if we did not find the executable
+  if (testCommand == "")
+    {
+    *this->LogFile << "Unable to find executable: " << args[1].c_str()
+                   << std::endl;
+    cmCTestLog(this->CTest, ERROR_MESSAGE, "Unable to find executable: "
+               << args[1].c_str() << std::endl);
+    cres.Output = "Unable to find executable: " + args[1];
+    if ( !this->CTest->GetShowOnly() )
+      {
+      cres.FullCommandLine = actualCommand;
+      this->TestResults.push_back( cres );
+      failed.push_back(testname);
+      return;
+      }
+    }
+  
+  // add the arguments
+  std::vector<std::string>::const_iterator j = args.begin();
+  ++j;
+  ++j;
+  std::vector<const char*> arguments;
+  this->GenerateTestCommand(arguments);
+  arguments.push_back(actualCommand.c_str());
+  for(;j != args.end(); ++j)
+    {
+    testCommand += " ";
+    testCommand += cmSystemTools::EscapeSpaces(j->c_str());
+    arguments.push_back(j->c_str());
+    }
+  arguments.push_back(0);
+  
+  /**
+   * Run an executable command and put the stdout in output.
+   */
+  std::string output;
+  int retVal = 0;
+  
+  
+  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, std::endl
+             << (this->MemCheck?"MemCheck":"Test") 
+             << " command: " << testCommand
+             << std::endl);
+  *this->LogFile << cnt << "/" << tmsize
+                 << " Test: " << testname.c_str() << std::endl;
+  *this->LogFile << "Command: ";
+  std::vector<cmStdString>::size_type ll;
+  for ( ll = 0; ll < arguments.size()-1; ll ++ )
+    {
+    *this->LogFile << "\"" << arguments[ll] << "\" ";
+    }
+  *this->LogFile
+    << std::endl
+    << "Directory: " << it->Directory << std::endl
+    << "\"" << testname.c_str() << "\" start time: "
+    << this->CTest->CurrentTime() << std::endl
+    << "Output:" << std::endl
+    << "----------------------------------------------------------"
+    << std::endl;
+  int res = 0;
+  double clock_start, clock_finish;
+  clock_start = cmSystemTools::GetTime();
+  
+  if ( !this->CTest->GetShowOnly() )
+    {
+    res = this->CTest->RunTest(arguments, &output, &retVal, this->LogFile,
+                               it->Timeout);
+    }
+  
+  clock_finish = cmSystemTools::GetTime();
+  
+  if ( this->LogFile )
+    {
+    double ttime = clock_finish - clock_start;
+    int hours = static_cast<int>(ttime / (60 * 60));
+    int minutes = static_cast<int>(ttime / 60) % 60;
+    int seconds = static_cast<int>(ttime) % 60;
+    char buffer[100];
+    sprintf(buffer, "%02d:%02d:%02d", hours, minutes, seconds);
+    *this->LogFile
+      << "----------------------------------------------------------"
+      << std::endl
+      << "\"" << testname.c_str() << "\" end time: "
+      << this->CTest->CurrentTime() << std::endl
+      << "\"" << testname.c_str() << "\" time elapsed: "
+      << buffer << std::endl
+      << "----------------------------------------------------------"
+      << std::endl << std::endl;
+    }
+  
+  cres.ExecutionTime = (double)(clock_finish - clock_start);
+  cres.FullCommandLine = testCommand;
+  
+  if ( !this->CTest->GetShowOnly() )
+    {
+    bool testFailed = false;
+    std::vector<cmsys::RegularExpression>::iterator passIt;
+    bool forceFail = false;
+    if ( it->RequiredRegularExpressions.size() > 0 )
+      {
+      bool found = false;
+      for ( passIt = it->RequiredRegularExpressions.begin();
+            passIt != it->RequiredRegularExpressions.end();
+            ++ passIt )
+        {
+        if ( passIt->find(output.c_str()) )
+          {
+          found = true;
+          }
+        }
+      if ( !found )
+        {
+        forceFail = true;
+        }
+      }
+    if ( it->ErrorRegularExpressions.size() > 0 )
+      {
+      for ( passIt = it->ErrorRegularExpressions.begin();
+            passIt != it->ErrorRegularExpressions.end();
+            ++ passIt )
+        {
+        if ( passIt->find(output.c_str()) )
+          {
+          forceFail = true;
+          }
+        }
+      }
+    
+    if (res == cmsysProcess_State_Exited &&
+        (retVal == 0 || it->RequiredRegularExpressions.size()) &&
+        !forceFail)
+      {
+      cmCTestLog(this->CTest, HANDLER_OUTPUT,   "   Passed");
+      if ( it->WillFail )
+        {
+        cmCTestLog(this->CTest, HANDLER_OUTPUT,   " - But it should fail!");
+        cres.Status = cmCTestTestHandler::FAILED;
+        testFailed = true;
+          }
+      else
+        {
+        cres.Status = cmCTestTestHandler::COMPLETED;
+        }
+      cmCTestLog(this->CTest, HANDLER_OUTPUT, std::endl);
+      }
+    else
+      {
+      testFailed = true;
+      
+      cres.Status = cmCTestTestHandler::FAILED;
+      if ( res == cmsysProcess_State_Expired )
+        {
+        cmCTestLog(this->CTest, HANDLER_OUTPUT, "***Timeout" << std::endl);
+        cres.Status = cmCTestTestHandler::TIMEOUT;
+        }
+      else if ( res == cmsysProcess_State_Exception )
+        {
+        cmCTestLog(this->CTest, HANDLER_OUTPUT, "***Exception: ");
+        switch ( retVal )
+          {
+          case cmsysProcess_Exception_Fault:
+            cmCTestLog(this->CTest, HANDLER_OUTPUT, "SegFault");
+            cres.Status = cmCTestTestHandler::SEGFAULT;
+            break;
+          case cmsysProcess_Exception_Illegal:
+            cmCTestLog(this->CTest, HANDLER_OUTPUT, "Illegal");
+            cres.Status = cmCTestTestHandler::ILLEGAL;
+            break;
+          case cmsysProcess_Exception_Interrupt:
+            cmCTestLog(this->CTest, HANDLER_OUTPUT, "Interrupt");
+            cres.Status = cmCTestTestHandler::INTERRUPT;
+            break;
+          case cmsysProcess_Exception_Numerical:
+            cmCTestLog(this->CTest, HANDLER_OUTPUT, "Numerical");
+            cres.Status = cmCTestTestHandler::NUMERICAL;
+            break;
+          default:
+            cmCTestLog(this->CTest, HANDLER_OUTPUT, "Other");
+            cres.Status = cmCTestTestHandler::OTHER_FAULT;
+          }
+        cmCTestLog(this->CTest, HANDLER_OUTPUT, std::endl);
+        }
+      else if ( res == cmsysProcess_State_Error )
+        {
+        cmCTestLog(this->CTest, HANDLER_OUTPUT, "***Bad command " << res
+                   << std::endl);
+        cres.Status = cmCTestTestHandler::BAD_COMMAND;
+        }
+      else
+        {
+        // Force fail will also be here?
+        cmCTestLog(this->CTest, HANDLER_OUTPUT, "***Failed");
+        if ( it->WillFail )
+          {
+          cres.Status = cmCTestTestHandler::COMPLETED;
+          cmCTestLog(this->CTest, HANDLER_OUTPUT, " - supposed to fail");
+          testFailed = false;
+          }
+        cmCTestLog(this->CTest, HANDLER_OUTPUT, std::endl);
+        }
+      }
+    if ( testFailed )
+      {
+      failed.push_back(testname);
+      }
+    else
+      {
+      passed.push_back(testname);
+      }
+    if (!output.empty() && output.find("<DartMeasurement") != output.npos)
+      {
+      if (this->DartStuff.find(output.c_str()))
+        {
+        std::string dartString = this->DartStuff.match(1);
+        cmSystemTools::ReplaceString(output, dartString.c_str(),"");
+        cres.RegressionImages
+          = this->GenerateRegressionImages(dartString);
+        }
+      }
+    }
+
+  if ( cres.Status == cmCTestTestHandler::COMPLETED )
+    {
+    this->CleanTestOutput(output, static_cast<size_t>
+                          (this->CustomMaximumPassedTestOutputSize));
+    }
+  else
+    {
+    this->CleanTestOutput(output, static_cast<size_t>
+                          (this->CustomMaximumFailedTestOutputSize));
+    }
+
+  cres.Output = output;
+  cres.ReturnValue = retVal;
+  cres.CompletionStatus = "Completed";
+  this->TestResults.push_back( cres );
+}
+
+//----------------------------------------------------------------------
 void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
                                           std::vector<cmStdString> &failed)
 {
@@ -612,27 +898,16 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
       {
       continue;
       }
-
-    const std::string& testname = it->Name;
-    std::vector<std::string>& args = it->Args;
-    cmCTestTestResult cres;
-    cres.Properties = &*it;
-    cres.ExecutionTime = 0;
-    cres.ReturnValue = -1;
-    cres.Status = cmCTestTestHandler::NOT_RUN;
-    cres.TestCount = cnt;
-
+    
     if (!(last_directory == it->Directory))
       {
       cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-        "Changing directory into " << it->Directory.c_str() << "\n");
+                 "Changing directory into " << it->Directory.c_str() << "\n");
       *this->LogFile << "Changing directory into: " << it->Directory.c_str()
-        << std::endl;
+                     << std::endl;
       last_directory = it->Directory;
       cmSystemTools::ChangeDirectory(it->Directory.c_str());
       }
-    cres.Name = testname;
-    cres.Path = it->Directory.c_str();
 
     if (this->UseUnion)
       {
@@ -649,278 +924,15 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
       // is this test in the list of tests to run? If not then skip it
       if ((this->TestsToRun.size() &&
            std::find(this->TestsToRun.begin(),
-             this->TestsToRun.end(), inREcnt)
+                     this->TestsToRun.end(), inREcnt)
            == this->TestsToRun.end()) || !it->IsInBasedOnREOptions)
         {
         continue;
         }
       }
-
-    cmCTestLog(this->CTest, HANDLER_OUTPUT, std::setw(3) << cnt << "/");
-    cmCTestLog(this->CTest, HANDLER_OUTPUT, std::setw(3) << tmsize << " ");
-    if ( this->MemCheck )
-      {
-      cmCTestLog(this->CTest, HANDLER_OUTPUT, "Memory Check");
-      }
-    else
-      {
-      cmCTestLog(this->CTest, HANDLER_OUTPUT, "Testing");
-      }
-    cmCTestLog(this->CTest, HANDLER_OUTPUT, " ");
-    std::string outname = testname;
-    outname.resize(30, ' ');
-    *this->LogFile << cnt << "/" << tmsize << " Testing: " << testname
-      << std::endl;
-
-    if ( this->CTest->GetShowOnly() )
-      {
-      cmCTestLog(this->CTest, HANDLER_OUTPUT, outname.c_str() << std::endl);
-      }
-    else
-      {
-      cmCTestLog(this->CTest, HANDLER_OUTPUT, outname.c_str());
-      }
-
-    cmCTestLog(this->CTest, DEBUG, "Testing " << args[0].c_str() << " ... ");
-    // find the test executable
-    std::string actualCommand = this->FindTheExecutable(args[1].c_str());
-    std::string testCommand
-      = cmSystemTools::ConvertToOutputPath(actualCommand.c_str());
-
-    // continue if we did not find the executable
-    if (testCommand == "")
-      {
-      *this->LogFile << "Unable to find executable: " << args[1].c_str()
-        << std::endl;
-      cmCTestLog(this->CTest, ERROR_MESSAGE, "Unable to find executable: "
-        << args[1].c_str() << std::endl);
-      cres.Output = "Unable to find executable: " + args[1];
-      if ( !this->CTest->GetShowOnly() )
-        {
-        cres.FullCommandLine = actualCommand;
-        this->TestResults.push_back( cres );
-        failed.push_back(testname);
-        continue;
-        }
-      }
-
-    // add the arguments
-    std::vector<std::string>::const_iterator j = args.begin();
-    ++j;
-    ++j;
-    std::vector<const char*> arguments;
-    this->GenerateTestCommand(arguments);
-    arguments.push_back(actualCommand.c_str());
-    for(;j != args.end(); ++j)
-      {
-      testCommand += " ";
-      testCommand += cmSystemTools::EscapeSpaces(j->c_str());
-      arguments.push_back(j->c_str());
-      }
-    arguments.push_back(0);
-
-    /**
-     * Run an executable command and put the stdout in output.
-     */
-    std::string output;
-    int retVal = 0;
-
-
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, std::endl
-      << (this->MemCheck?"MemCheck":"Test") << " command: " << testCommand
-      << std::endl);
-    *this->LogFile << cnt << "/" << tmsize
-      << " Test: " << testname.c_str() << std::endl;
-    *this->LogFile << "Command: ";
-    std::vector<cmStdString>::size_type ll;
-    for ( ll = 0; ll < arguments.size()-1; ll ++ )
-      {
-      *this->LogFile << "\"" << arguments[ll] << "\" ";
-      }
-    *this->LogFile
-      << std::endl
-      << "Directory: " << it->Directory << std::endl
-      << "\"" << testname.c_str() << "\" start time: "
-      << this->CTest->CurrentTime() << std::endl
-      << "Output:" << std::endl
-      << "----------------------------------------------------------"
-      << std::endl;
-    int res = 0;
-    double clock_start, clock_finish;
-    clock_start = cmSystemTools::GetTime();
-
-    if ( !this->CTest->GetShowOnly() )
-      {
-      res = this->CTest->RunTest(arguments, &output, &retVal, this->LogFile);
-      }
-
-    clock_finish = cmSystemTools::GetTime();
-
-    if ( this->LogFile )
-      {
-      double ttime = clock_finish - clock_start;
-      int hours = static_cast<int>(ttime / (60 * 60));
-      int minutes = static_cast<int>(ttime / 60) % 60;
-      int seconds = static_cast<int>(ttime) % 60;
-      char buffer[100];
-      sprintf(buffer, "%02d:%02d:%02d", hours, minutes, seconds);
-      *this->LogFile
-        << "----------------------------------------------------------"
-        << std::endl
-        << "\"" << testname.c_str() << "\" end time: "
-        << this->CTest->CurrentTime() << std::endl
-        << "\"" << testname.c_str() << "\" time elapsed: "
-        << buffer << std::endl
-        << "----------------------------------------------------------"
-        << std::endl << std::endl;
-      }
-
-    cres.ExecutionTime = (double)(clock_finish - clock_start);
-    cres.FullCommandLine = testCommand;
-
-    if ( !this->CTest->GetShowOnly() )
-      {
-      bool testFailed = false;
-      std::vector<cmsys::RegularExpression>::iterator passIt;
-      bool forceFail = false;
-      if ( it->RequiredRegularExpressions.size() > 0 )
-        {
-        bool found = false;
-        for ( passIt = it->RequiredRegularExpressions.begin();
-          passIt != it->RequiredRegularExpressions.end();
-          ++ passIt )
-          {
-          if ( passIt->find(output.c_str()) )
-            {
-            found = true;
-            }
-          }
-        if ( !found )
-          {
-          forceFail = true;
-          }
-        }
-      if ( it->ErrorRegularExpressions.size() > 0 )
-        {
-        for ( passIt = it->ErrorRegularExpressions.begin();
-          passIt != it->ErrorRegularExpressions.end();
-          ++ passIt )
-          {
-          if ( passIt->find(output.c_str()) )
-            {
-            forceFail = true;
-            }
-          }
-        }
-
-      if (res == cmsysProcess_State_Exited &&
-          (retVal == 0 || it->RequiredRegularExpressions.size()) &&
-          !forceFail)
-        {
-        cmCTestLog(this->CTest, HANDLER_OUTPUT,   "   Passed");
-        if ( it->WillFail )
-          {
-          cmCTestLog(this->CTest, HANDLER_OUTPUT,   " - But it should fail!");
-          cres.Status = cmCTestTestHandler::FAILED;
-          testFailed = true;
-          }
-        else
-          {
-          cres.Status = cmCTestTestHandler::COMPLETED;
-          }
-        cmCTestLog(this->CTest, HANDLER_OUTPUT, std::endl);
-        }
-      else
-        {
-        testFailed = true;
-
-        cres.Status = cmCTestTestHandler::FAILED;
-        if ( res == cmsysProcess_State_Expired )
-          {
-          cmCTestLog(this->CTest, HANDLER_OUTPUT, "***Timeout" << std::endl);
-          cres.Status = cmCTestTestHandler::TIMEOUT;
-          }
-        else if ( res == cmsysProcess_State_Exception )
-          {
-          cmCTestLog(this->CTest, HANDLER_OUTPUT, "***Exception: ");
-          switch ( retVal )
-            {
-          case cmsysProcess_Exception_Fault:
-            cmCTestLog(this->CTest, HANDLER_OUTPUT, "SegFault");
-            cres.Status = cmCTestTestHandler::SEGFAULT;
-            break;
-          case cmsysProcess_Exception_Illegal:
-            cmCTestLog(this->CTest, HANDLER_OUTPUT, "Illegal");
-            cres.Status = cmCTestTestHandler::ILLEGAL;
-            break;
-          case cmsysProcess_Exception_Interrupt:
-            cmCTestLog(this->CTest, HANDLER_OUTPUT, "Interrupt");
-            cres.Status = cmCTestTestHandler::INTERRUPT;
-            break;
-          case cmsysProcess_Exception_Numerical:
-            cmCTestLog(this->CTest, HANDLER_OUTPUT, "Numerical");
-            cres.Status = cmCTestTestHandler::NUMERICAL;
-            break;
-          default:
-            cmCTestLog(this->CTest, HANDLER_OUTPUT, "Other");
-            cres.Status = cmCTestTestHandler::OTHER_FAULT;
-            }
-           cmCTestLog(this->CTest, HANDLER_OUTPUT, std::endl);
-          }
-        else if ( res == cmsysProcess_State_Error )
-          {
-          cmCTestLog(this->CTest, HANDLER_OUTPUT, "***Bad command " << res
-            << std::endl);
-          cres.Status = cmCTestTestHandler::BAD_COMMAND;
-          }
-        else
-          {
-          // Force fail will also be here?
-          cmCTestLog(this->CTest, HANDLER_OUTPUT, "***Failed");
-          if ( it->WillFail )
-            {
-            cres.Status = cmCTestTestHandler::COMPLETED;
-            cmCTestLog(this->CTest, HANDLER_OUTPUT, " - supposed to fail");
-            testFailed = false;
-            }
-          cmCTestLog(this->CTest, HANDLER_OUTPUT, std::endl);
-          }
-        }
-      if ( testFailed )
-        {
-        failed.push_back(testname);
-        }
-      else
-        {
-        passed.push_back(testname);
-        }
-      if (!output.empty() && output.find("<DartMeasurement") != output.npos)
-        {
-        if (this->DartStuff.find(output.c_str()))
-          {
-          std::string dartString = this->DartStuff.match(1);
-          cmSystemTools::ReplaceString(output, dartString.c_str(),"");
-          cres.RegressionImages
-            = this->GenerateRegressionImages(dartString);
-          }
-        }
-      }
-
-    if ( cres.Status == cmCTestTestHandler::COMPLETED )
-      {
-      this->CleanTestOutput(output, static_cast<size_t>(
-          this->CustomMaximumPassedTestOutputSize));
-      }
-    else
-      {
-      this->CleanTestOutput(output, static_cast<size_t>(
-          this->CustomMaximumFailedTestOutputSize));
-      }
-
-    cres.Output = output;
-    cres.ReturnValue = retVal;
-    cres.CompletionStatus = "Completed";
-    this->TestResults.push_back( cres );
+    
+    // process this one test
+    this->ProcessOneTest(&(*it), passed, failed, cnt, tmsize);
     }
 
   this->EndTest = this->CTest->CurrentTime();
@@ -1647,6 +1659,10 @@ bool cmCTestTestHandler::SetTestsProperties(
             {
             rtit->WillFail = cmSystemTools::IsOn(val.c_str());
             }
+          if ( key == "TIMEOUT" )
+            {
+            rtit->Timeout = atof(val.c_str());
+            }
           if ( key == "FAIL_REGULAR_EXPRESSION" )
             {
             std::vector<std::string> lval;
@@ -1751,6 +1767,7 @@ bool cmCTestTestHandler::AddTest(const std::vector<std::string>& args)
   
   test.IsInBasedOnREOptions = true;
   test.WillFail = false;
+  test.Timeout = 0;
   if (this->UseIncludeRegExpFlag &&
     !this->IncludeTestsRegularExpression.find(testname.c_str()))
     {