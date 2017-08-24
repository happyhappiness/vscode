@@ -21,150 +21,52 @@
 
 cmCTestRunTest::cmCTestRunTest()
 {
-  this->OptimizeForCTest = true;
-  cmCTestTestHandler::cmCTestTestResult result;
-  this->TestResult = result;
 }
 
 cmCTestRunTest::~cmCTestRunTest()
 {
 }
 
-void cmCTestRunTest::SetTestHandler(cmCTestTestHandler * handler)
+bool cmCTestRunTest::IsRunning()
 {
-  this->TestHandler = handler;
-  this->CTest = handler->CTest;
+  return this->TestProcess->IsRunning();
 }
 
-//----------------------------------------------------------------------
-// Executes a test.  Returns whether it passed or failed
-bool cmCTestRunTest::Execute()
+//---------------------------------------------------------
+//waits .1 sec for output from this process.
+void cmCTestRunTest::CheckOutput()
 {
-  const std::string& testname = this->TestProperties->Name;
-  std::vector<std::string>& args = this->TestProperties->Args;
-  this->TestResult.Properties = this->TestProperties;
-  this->TestResult.ExecutionTime = 0;
-  this->TestResult.ReturnValue = -1;
-  this->TestResult.Status = cmCTestTestHandler::NOT_RUN;
-  this->TestResult.TestCount = this->TestProperties->Index;  
-  this->TestResult.Name = testname;
-  this->TestResult.Path = this->TestProperties->Directory.c_str();
-
-  cmCTestLog(this->CTest, HANDLER_OUTPUT, std::setw(3) 
-             << this->TestProperties->Index << "/");
-  cmCTestLog(this->CTest, HANDLER_OUTPUT, std::setw(3) 
-             << this->TestHandler->TotalNumberOfTests << " ");
-  if ( this->TestHandler->MemCheck )
-    {
-    cmCTestLog(this->CTest, HANDLER_OUTPUT, "Memory Check");
-    }
-  else
-    {
-    cmCTestLog(this->CTest, HANDLER_OUTPUT, "Testing");
-    }
-  cmCTestLog(this->CTest, HANDLER_OUTPUT, " ");
-  const int maxTestNameWidth = this->CTest->GetMaxTestNameWidth();
-  std::string outname = testname + " ";
-  outname.resize(maxTestNameWidth, '.');
-  *this->TestHandler->LogFile << this->TestProperties->Index << "/" 
-    << this->TestHandler->TotalNumberOfTests << " Testing: " 
-    << testname << std::endl;
-
-  if ( this->CTest->GetShowOnly() )
-    {
-    cmCTestLog(this->CTest, HANDLER_OUTPUT, outname.c_str() << std::endl);
-    }
-  else
-    {
-    cmCTestLog(this->CTest, HANDLER_OUTPUT, outname.c_str());
-    }
-
-  cmCTestLog(this->CTest, DEBUG, "Testing " << args[0].c_str() << " ... ");
-  // find the test executable
-  std::string actualCommand 
-    = this->TestHandler->FindTheExecutable(args[1].c_str());
-  std::string testCommand
-    = cmSystemTools::ConvertToOutputPath(actualCommand.c_str());
-
-  // continue if we did not find the executable
-  if (testCommand == "")
-    {
-    *this->TestHandler->LogFile << "Unable to find executable: " 
-                   << args[1].c_str() << std::endl;
-    cmCTestLog(this->CTest, ERROR_MESSAGE, "Unable to find executable: "
-               << args[1].c_str() << std::endl);
-    this->TestResult.Output = "Unable to find executable: " + args[1];
-    if ( !this->CTest->GetShowOnly() )
-      {
-      this->TestResult.FullCommandLine = actualCommand;
-      this->TestHandler->TestResults.push_back( this->TestResult );
-      return false;
-      }
-    }
-
-  // add the arguments
-  std::vector<std::string>::const_iterator j = args.begin();
-  ++j; // skip test name
-  ++j; // skip command as it is in actualCommand
-  std::vector<const char*> arguments;
-  this->TestHandler->GenerateTestCommand(arguments);
-  arguments.push_back(actualCommand.c_str());
-  for(;j != args.end(); ++j)
+  std::string out, err;
+  int pipe = this->TestProcess->CheckOutput(.1, out, err);
+  if(pipe == cmsysProcess_Pipe_STDOUT)
     {
-    testCommand += " ";
-    testCommand += cmSystemTools::EscapeSpaces(j->c_str());
-    arguments.push_back(j->c_str());
+    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, 
+               this->GetIndex() << ": " << out << std::endl);
+    this->ProcessOutput += out;
+    this->ProcessOutput += "\n";
     }
-  arguments.push_back(0);
-
-  /**
-   * Run an executable command and put the stdout in output.
-   */
-  std::string output;
-  int retVal = 0;
-
-  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, std::endl
-             << (this->TestHandler->MemCheck?"MemCheck":"Test") 
-             << " command: " << testCommand
-             << std::endl);
-  *this->TestHandler->LogFile << this->TestProperties->Index << "/" 
-                 << this->TestHandler->TotalNumberOfTests
-                 << " Test: " << testname.c_str() << std::endl;
-  *this->TestHandler->LogFile << "Command: ";
-  std::vector<cmStdString>::size_type ll;
-  for ( ll = 0; ll < arguments.size()-1; ll ++ )
+  else if(pipe == cmsysProcess_Pipe_STDERR)
     {
-    *this->TestHandler->LogFile << "\"" << arguments[ll] << "\" ";
+    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, 
+               this->GetIndex() << ": " << err << std::endl);
+    this->ProcessOutput += err;
+    this->ProcessOutput += "\n";
     }
-  *this->TestHandler->LogFile
-    << std::endl
-    << "Directory: " << this->TestProperties->Directory << std::endl
-    << "\"" << testname.c_str() << "\" start time: "
-    << this->CTest->CurrentTime() << std::endl
-    << "Output:" << std::endl
-    << "----------------------------------------------------------"
-    << std::endl;
-  int res = 0;
-  double clock_start, clock_finish;
-  clock_start = cmSystemTools::GetTime();
+}
 
-  if ( !this->CTest->GetShowOnly() )
+//---------------------------------------------------------
+bool cmCTestRunTest::EndTest()
+{
+  //restore the old environment
+  if (this->ModifyEnv)
     {
-    res = this->RunTestProcess(arguments, &output, &retVal,
-                               this->TestHandler->LogFile,
-                               this->TestProperties->Timeout,
-                               &this->TestProperties->Environment);
-    this->ProcessOutput = output; //save process output in the object
+    cmSystemTools::RestoreEnv(this->OrigEnv);
     }
-
-  clock_finish = cmSystemTools::GetTime();  
-
-  this->TestResult.ExecutionTime = (double)(clock_finish - clock_start);
-  this->TestResult.FullCommandLine = testCommand;
+  this->WriteLogOutputTop();
   std::string reason;
-
   bool passed = true;
-
+  int res = this->TestProcess->GetProcessStatus();
+  int retVal = this->TestProcess->GetExitValue();
   if ( !this->CTest->GetShowOnly() )
     {
     std::vector<std::pair<cmsys::RegularExpression,
@@ -177,7 +79,7 @@ bool cmCTestRunTest::Execute()
             passIt != this->TestProperties->RequiredRegularExpressions.end();
             ++ passIt )
         {
-        if ( passIt->first.find(output.c_str()) )
+        if ( passIt->first.find(this->ProcessOutput.c_str()) )
           {
           found = true;
           reason = "Required regular expression found.";
@@ -204,7 +106,7 @@ bool cmCTestRunTest::Execute()
             passIt != this->TestProperties->ErrorRegularExpressions.end();
             ++ passIt )
         {
-        if ( passIt->first.find(output.c_str()) )
+        if ( passIt->first.find(this->ProcessOutput.c_str()) )
           {
           reason = "Error regular expression found in output.";
           reason += " Regex=[";
@@ -214,7 +116,6 @@ bool cmCTestRunTest::Execute()
           }
         }
       }
-
     if (res == cmsysProcess_State_Exited)
       {
       bool success = 
@@ -224,13 +125,12 @@ bool cmCTestRunTest::Execute()
         || (!success && this->TestProperties->WillFail))
         {
         this->TestResult.Status = cmCTestTestHandler::COMPLETED;
-        cmCTestLog(this->CTest, HANDLER_OUTPUT,   "   Passed  " );
+        cmCTestLog(this->CTest, HANDLER_OUTPUT, "   Passed  " );
         }
       else
         {
         this->TestResult.Status = cmCTestTestHandler::FAILED;
-        cmCTestLog(this->CTest, HANDLER_OUTPUT,
-                   "***Failed  " << reason );
+        cmCTestLog(this->CTest, HANDLER_OUTPUT, "***Failed  " << reason );
         }
       }
     else if ( res == cmsysProcess_State_Expired )
@@ -273,28 +173,29 @@ bool cmCTestRunTest::Execute()
     passed = this->TestResult.Status == cmCTestTestHandler::COMPLETED;
 
     char buf[1024];
-    sprintf(buf, "%6.2f sec", this->TestResult.ExecutionTime);
+    sprintf(buf, "%6.2f sec", this->TestProcess->GetTotalTime());
     cmCTestLog(this->CTest, HANDLER_OUTPUT, buf << "\n" );
     if ( this->TestHandler->LogFile )
       {
-      *this->TestHandler->LogFile << "\nTest time = " << buf << std::endl;
+      *this->TestHandler->LogFile << "Test time = " << buf << std::endl;
       }
-    this->DartProcessing(output);
+    this->DartProcessing();
     } 
-
   // if this is doing MemCheck then all the output needs to be put into
   // Output since that is what is parsed by cmCTestMemCheckHandler
   if(!this->TestHandler->MemCheck)
     {
     if ( this->TestResult.Status == cmCTestTestHandler::COMPLETED )
       {
-      this->TestHandler->CleanTestOutput(output, static_cast<size_t>
-                     (this->TestHandler->CustomMaximumPassedTestOutputSize));
+      this->TestHandler->CleanTestOutput(this->ProcessOutput, 
+          static_cast<size_t>
+          (this->TestHandler->CustomMaximumPassedTestOutputSize));
       }
     else
       {
-      this->TestHandler->CleanTestOutput(output, static_cast<size_t>
-                     (this->TestHandler->CustomMaximumFailedTestOutputSize));
+      this->TestHandler->CleanTestOutput(this->ProcessOutput,
+          static_cast<size_t>
+          (this->TestHandler->CustomMaximumFailedTestOutputSize));
       }
     }
   this->TestResult.Reason = reason;
@@ -308,7 +209,7 @@ bool cmCTestRunTest::Execute()
       reasonType = "Test Fail Reason";
       pass = false;
       }
-    double ttime = clock_finish - clock_start;
+    double ttime = this->TestProcess->GetTotalTime();
     int hours = static_cast<int>(ttime / (60 * 60));
     int minutes = static_cast<int>(ttime / 60) % 60;
     int seconds = static_cast<int>(ttime) % 60;
@@ -333,34 +234,99 @@ bool cmCTestRunTest::Execute()
         *this->TestHandler->LogFile << "Test Failed.\n";
         }
       }
-    *this->TestHandler->LogFile << "\"" << testname.c_str() << "\" end time: "
-      << this->CTest->CurrentTime() << std::endl
-      << "\"" << testname.c_str() << "\" time elapsed: "
+    *this->TestHandler->LogFile << "\"" << this->TestProperties->Name.c_str()
+      << "\" end time: " << this->CTest->CurrentTime() << std::endl
+      << "\"" << this->TestProperties->Name.c_str() << "\" time elapsed: "
       << buffer << std::endl
       << "----------------------------------------------------------"
       << std::endl << std::endl;
     }
-  this->TestResult.Output = output;
-  this->TestResult.ReturnValue = retVal;
+  this->TestResult.Output = this->ProcessOutput;
+  this->TestResult.ReturnValue = this->TestProcess->GetExitValue();
   this->TestResult.CompletionStatus = "Completed";
+  this->TestResult.ExecutionTime = this->TestProcess->GetTotalTime();
   this->TestHandler->TestResults.push_back( this->TestResult );
 
+  delete this->TestProcess;
   return passed;
 }
 
+void cmCTestRunTest::SetTestHandler(cmCTestTestHandler * handler)
+{
+  this->TestHandler = handler;
+  this->CTest = handler->CTest;
+}
+
+//----------------------------------------------------------------------
+// Starts the execution of a test.  Returns once it has started
+bool cmCTestRunTest::StartTest()
+{
+  std::vector<std::string>& args = this->TestProperties->Args;
+  this->TestResult.Properties = this->TestProperties;
+  this->TestResult.ExecutionTime = 0;
+  this->TestResult.ReturnValue = -1;
+  this->TestResult.Status = cmCTestTestHandler::NOT_RUN;
+  this->TestResult.TestCount = this->TestProperties->Index;  
+  this->TestResult.Name = this->TestProperties->Name;
+  this->TestResult.Path = this->TestProperties->Directory.c_str();
+  
+  // find the test executable
+  this->ActualCommand 
+    = this->TestHandler->FindTheExecutable(args[1].c_str());
+  this->TestCommand
+    = cmSystemTools::ConvertToOutputPath(this->ActualCommand.c_str());
+
+  // continue if we did not find the executable
+  if (this->TestCommand == "")
+    {
+    *this->TestHandler->LogFile << "Unable to find executable: " 
+                   << args[1].c_str() << std::endl;
+    cmCTestLog(this->CTest, ERROR_MESSAGE, "Unable to find executable: "
+               << args[1].c_str() << std::endl);
+    this->TestResult.Output = "Unable to find executable: " + args[1];
+    if ( !this->CTest->GetShowOnly() )
+      {
+      this->TestResult.FullCommandLine = this->ActualCommand;
+      this->TestHandler->TestResults.push_back( this->TestResult );
+      return false;
+      }
+    }
+
+  /**
+   * Run an executable command and put the stdout in output.
+   */
+  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, std::endl
+             << this->Index << ": "
+             << (this->TestHandler->MemCheck?"MemCheck":"Test") 
+             << " command: " << this->TestCommand
+             << std::endl);
+
+  this->StartTime = this->CTest->CurrentTime();
+
+  if ( !this->CTest->GetShowOnly() )
+    {
+    return this->CreateProcess(this->ActualCommand,
+                               this->TestProperties->Args,
+                               this->TestProperties->Timeout,
+                               &this->TestProperties->Environment);
+    }
+  return true;
+}
+
 //----------------------------------------------------------------------
-void cmCTestRunTest::DartProcessing(std::string& output)
+void cmCTestRunTest::DartProcessing()
 {
-  if (!output.empty() && output.find("<DartMeasurement") != output.npos)
+  if (!this->ProcessOutput.empty() && 
+     this->ProcessOutput.find("<DartMeasurement") != this->ProcessOutput.npos)
     {
-    if (this->TestHandler->DartStuff.find(output.c_str()))
+    if (this->TestHandler->DartStuff.find(this->ProcessOutput.c_str()))
       {
       std::string dartString = this->TestHandler->DartStuff.match(1);
       // keep searching and replacing until none are left
-      while (this->TestHandler->DartStuff1.find(output.c_str()))
+      while (this->TestHandler->DartStuff1.find(this->ProcessOutput.c_str()))
         {
         // replace the exact match for the string
-        cmSystemTools::ReplaceString(output,
+        cmSystemTools::ReplaceString(this->ProcessOutput,
                          this->TestHandler->DartStuff1.match(1).c_str(), "");
         }
       this->TestResult.RegressionImages
@@ -370,13 +336,27 @@ void cmCTestRunTest::DartProcessing(std::string& output)
 }
 
 //----------------------------------------------------------------------
-int cmCTestRunTest::RunTestProcess(std::vector<const char*> argv,
-                     std::string* output, int *retVal,
-                     std::ostream* log, double testTimeOut,
+bool cmCTestRunTest::CreateProcess(std::string command,
+                     std::vector<std::string> args,
+                     double testTimeOut,
                      std::vector<std::string>* environment)
 {
+  std::vector<std::string> commandArgs;
+  std::vector<std::string>::iterator i = args.begin();
+
+  ++i; //skip test name
+  ++i; //skip executable name
+  for(; i != args.end(); ++i)
+    {
+    commandArgs.push_back(*i);
+    }
+  this->TestProcess = new cmProcess;
+  this->TestProcess->SetId(this->Index);
+  this->TestProcess->SetCommand(command.c_str());
+  this->TestProcess->SetCommandArguments(commandArgs);
+
   std::vector<std::string> origEnv;
-  bool modifyEnv = (environment && environment->size()>0);
+  this->ModifyEnv = (environment && environment->size()>0);
 
   // determine how much time we have
   double timeout = this->CTest->GetRemainingTimeAllowed() - 120;
@@ -395,154 +375,89 @@ int cmCTestRunTest::RunTestProcess(std::vector<const char*> argv,
     {
     timeout = 1;
     }
-  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-             "Test timeout computed to be: " << timeout << "\n");
-
-  if(cmSystemTools::SameFile(argv[0], this->CTest->CTestSelf.c_str()) &&
-     !this->CTest->ForceNewCTestProcess &&
-     this->OptimizeForCTest)
-    {
-    cmCTest inst;
-    inst.ConfigType = this->CTest->ConfigType;
-    inst.TimeOut = timeout;
-
-    // Capture output of the child ctest.
-    cmOStringStream oss;
-    inst.SetStreams(&oss, &oss);
-
-    std::vector<std::string> args;
-    for(unsigned int i =0; i < argv.size(); ++i)
-      {
-      if(argv[i])
-        {
-        // make sure we pass the timeout in for any build and test 
-        // invocations. Since --build-generator is required this is a 
-        // good place to check for it, and to add the arguments in
-        if (strcmp(argv[i],"--build-generator") == 0 && timeout)
-          {
-          args.push_back("--test-timeout");
-          cmOStringStream msg;
-          msg << timeout;
-          args.push_back(msg.str());
-          }
-        args.push_back(argv[i]);
-        }
-      }
-    if ( log )
-      {
-      *log << "* Run internal CTest" << std::endl;
-      }
-    std::string oldpath = cmSystemTools::GetCurrentWorkingDirectory();
-
-    if (modifyEnv)
-      {
-      origEnv = cmSystemTools::AppendEnv(environment);
-      }
-
-    *retVal = inst.Run(args, output);
-    *output += oss.str();
-    if ( log )
-      {
-      *log << output->c_str();
-      }
-    cmSystemTools::ChangeDirectory(oldpath.c_str());
-
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-      "Internal cmCTest object used to run test." << std::endl
-      <<  *output << std::endl);
-
-    if (modifyEnv)
-      {
-      cmSystemTools::RestoreEnv(origEnv);
-      }
+  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, this->Index << ": "
+             << "Test timeout computed to be: " << timeout << "\n");
 
-    return cmsysProcess_State_Exited;
-    }
-  std::vector<char> tempOutput;
-  if ( output )
+  if (this->ModifyEnv)
     {
-    *output = "";
+    this->OrigEnv = cmSystemTools::AppendEnv(environment);
     }
 
-  if (modifyEnv)
+  return this->TestProcess->StartProcess();
+}
+
+void cmCTestRunTest::WriteLogOutputTop()
+{
+  /* Not sure whether we want to prepend the test index anymore
+  cmCTestLog(this->CTest, HANDLER_OUTPUT, std::setw(3)
+             << this->Index << ": ");*/
+  cmCTestLog(this->CTest, HANDLER_OUTPUT, std::setw(3) 
+             << this->TestProperties->Index << "/");
+  cmCTestLog(this->CTest, HANDLER_OUTPUT, std::setw(3) 
+             << this->TestHandler->TotalNumberOfTests << " ");
+  if ( this->TestHandler->MemCheck )
     {
-    origEnv = cmSystemTools::AppendEnv(environment);
+    cmCTestLog(this->CTest, HANDLER_OUTPUT, "Memory Check");
     }
-
-  cmsysProcess* cp = cmsysProcess_New();
-  cmsysProcess_SetCommand(cp, &*argv.begin());
-  cmCTestLog(this->CTest, DEBUG, "Command is: " << argv[0] << std::endl);
-  if(cmSystemTools::GetRunCommandHideConsole())
+  else
     {
-    cmsysProcess_SetOption(cp, cmsysProcess_Option_HideWindow, 1);
+    cmCTestLog(this->CTest, HANDLER_OUTPUT, "Testing");
     }
+  cmCTestLog(this->CTest, HANDLER_OUTPUT, " ");
+  const int maxTestNameWidth = this->CTest->GetMaxTestNameWidth();
+  std::string outname = this->TestProperties->Name + " ";
+  outname.resize(maxTestNameWidth, '.');
 
-  cmsysProcess_SetTimeout(cp, timeout);
-  cmsysProcess_Execute(cp);
-
-  char* data;
-  int length;
-  while(cmsysProcess_WaitForData(cp, &data, &length, 0))
+  // add the arguments
+  std::vector<std::string>::const_iterator j = 
+    this->TestProperties->Args.begin();
+  ++j; // skip test name
+  ++j; // skip command as it is in actualCommand
+  std::vector<const char*> arguments;
+  this->TestHandler->GenerateTestCommand(arguments);
+  arguments.push_back(this->ActualCommand.c_str());
+  for(;j != this->TestProperties->Args.end(); ++j)
     {
-    if ( output )
-      {
-      tempOutput.insert(tempOutput.end(), data, data+length);
-      }
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-      cmCTestLogWrite(data, length));
-    if ( log )
-      {
-      log->write(data, length);
-      }
+    this->TestCommand += " ";
+    this->TestCommand += cmSystemTools::EscapeSpaces(j->c_str());
+    arguments.push_back(j->c_str());
     }
+  arguments.push_back(0);
+  this->TestResult.FullCommandLine = this->TestCommand;
 
-  cmsysProcess_WaitForExit(cp, 0);
-  if(output && tempOutput.begin() != tempOutput.end())
+  *this->TestHandler->LogFile << this->TestProperties->Index << "/" 
+    << this->TestHandler->TotalNumberOfTests << " Testing: " 
+    << this->TestProperties->Name << std::endl;
+  *this->TestHandler->LogFile << this->TestProperties->Index << "/" 
+    << this->TestHandler->TotalNumberOfTests
+    << " Test: " << this->TestProperties->Name.c_str() << std::endl;
+  *this->TestHandler->LogFile << "Command: ";
+  std::vector<cmStdString>::size_type ll;
+  for ( ll = 0; ll < arguments.size()-1; ll ++ )
     {
-    //We are waiting for exit before finally appending to the output
-    output->append(&*tempOutput.begin(), tempOutput.size());
+    *this->TestHandler->LogFile << "\"" << arguments[ll] << "\" ";
     }
-  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "-- Process completed"
-    << std::endl);
+  *this->TestHandler->LogFile << std::endl
+    << "Directory: " << this->TestProperties->Directory << std::endl
+    << "\"" << this->TestProperties->Name.c_str() << "\" start time: "
+    << this->StartTime << std::endl;
 
-  int result = cmsysProcess_GetState(cp);
+  *this->TestHandler->LogFile
+    << "Output:" << std::endl
+    << "----------------------------------------------------------"
+    << std::endl;
+  *this->TestHandler->LogFile
+    << this->ProcessOutput.c_str() << "<end of output>" << std::endl;
 
-  if(result == cmsysProcess_State_Exited)
-    {
-    *retVal = cmsysProcess_GetExitValue(cp);
-    if(*retVal != 0 && this->CTest->OutputTestOutputOnTestFailure)
-      {
-        this->CTest->OutputTestErrors(tempOutput);
-      }
-    }
-  else if(result == cmsysProcess_State_Exception)
-    {
-    if(this->CTest->OutputTestOutputOnTestFailure)
-      {
-        this->CTest->OutputTestErrors(tempOutput);
-      }
-    *retVal = cmsysProcess_GetExitException(cp);
-    std::string outerr = "\n*** Exception executing: ";
-    outerr += cmsysProcess_GetExceptionString(cp);
-    *output += outerr;
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, outerr.c_str()
-      << std::endl << std::flush);
-    }
-  else if(result == cmsysProcess_State_Error)
+  if ( this->CTest->GetShowOnly() )
     {
-    std::string outerr = "\n*** ERROR executing: ";
-    outerr += cmsysProcess_GetErrorString(cp);
-    *output += outerr;
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, outerr.c_str()
-      << std::endl << std::flush);
+    cmCTestLog(this->CTest, HANDLER_OUTPUT, outname.c_str() << std::endl);
     }
-  cmsysProcess_Delete(cp);
-
-  if (modifyEnv)
+  else
     {
-    cmSystemTools::RestoreEnv(origEnv);
+    cmCTestLog(this->CTest, HANDLER_OUTPUT, outname.c_str());
     }
 
-  return result;
+  cmCTestLog(this->CTest, DEBUG, "Testing " 
+             << this->TestProperties->Name.c_str() << " ... ");
 }
-