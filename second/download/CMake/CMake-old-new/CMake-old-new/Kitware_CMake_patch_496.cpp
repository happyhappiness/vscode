@@ -92,9 +92,9 @@ bool cmCTestRunTest::EndTest(size_t completed, size_t total, bool started)
   this->WriteLogOutputTop(completed, total);
   std::string reason;
   bool passed = true;
-  int res = this->TestProcess->GetProcessStatus();
+  int res = started ? this->TestProcess->GetProcessStatus()
+                    : cmsysProcess_State_Error;
   int retVal = this->TestProcess->GetExitValue();
-
   std::vector<std::pair<cmsys::RegularExpression,
     std::string> >::iterator passIt;
   bool forceFail = false;
@@ -197,7 +197,6 @@ bool cmCTestRunTest::EndTest(size_t completed, size_t total, bool started)
     }
 
   passed = this->TestResult.Status == cmCTestTestHandler::COMPLETED;
-
   char buf[1024];
   sprintf(buf, "%6.2f sec", this->TestProcess->GetTotalTime());
   cmCTestLog(this->CTest, HANDLER_OUTPUT, buf << "\n" );
@@ -208,9 +207,9 @@ bool cmCTestRunTest::EndTest(size_t completed, size_t total, bool started)
   this->DartProcessing();
   // if this is doing MemCheck then all the output needs to be put into
   // Output since that is what is parsed by cmCTestMemCheckHandler
-  if(!this->TestHandler->MemCheck)
+  if(!this->TestHandler->MemCheck && started)
     {
-    if ( this->TestResult.Status == cmCTestTestHandler::COMPLETED )
+    if (this->TestResult.Status == cmCTestTestHandler::COMPLETED)
       {
       this->TestHandler->CleanTestOutput(this->ProcessOutput, 
           static_cast<size_t>
@@ -224,7 +223,7 @@ bool cmCTestRunTest::EndTest(size_t completed, size_t total, bool started)
       }
     }
   this->TestResult.Reason = reason;
-  if ( this->TestHandler->LogFile )
+  if (this->TestHandler->LogFile)
     {
     bool pass = true;
     const char* reasonType = "Test Pass Reason";
@@ -272,10 +271,10 @@ bool cmCTestRunTest::EndTest(size_t completed, size_t total, bool started)
     this->TestResult.ReturnValue = this->TestProcess->GetExitValue();
     this->TestResult.CompletionStatus = "Completed";
     this->TestResult.ExecutionTime = this->TestProcess->GetTotalTime();
-    this->TestHandler->TestResults.push_back( this->TestResult );
-    }
-  this->MemCheckPostProcess();
+    this->TestHandler->TestResults.push_back(this->TestResult);
 
+    this->MemCheckPostProcess();
+    }
   delete this->TestProcess;
   return passed;
 }
@@ -324,20 +323,18 @@ bool cmCTestRunTest::StartTest()
   this->TestResult.Name = this->TestProperties->Name;
   this->TestResult.Path = this->TestProperties->Directory.c_str();
   
-  // continue if we did not find the executable
-  if (this->TestCommand == "")
+  // log and return if we did not find the executable
+  if (this->ActualCommand == "")
     {
+    this->TestProcess = new cmProcess;
     *this->TestHandler->LogFile << "Unable to find executable: " 
                    << args[1].c_str() << std::endl;
     cmCTestLog(this->CTest, ERROR_MESSAGE, "Unable to find executable: "
                << args[1].c_str() << std::endl);
     this->TestResult.Output = "Unable to find executable: " + args[1];
-    if ( !this->CTest->GetShowOnly() )
-      {
-      this->TestResult.FullCommandLine = this->ActualCommand;
-      this->TestHandler->TestResults.push_back( this->TestResult );
-      return false;
-      }
+    this->TestResult.FullCommandLine = "";
+    this->TestHandler->TestResults.push_back(this->TestResult);
+    return false;
     }
   this->StartTime = this->CTest->CurrentTime();
 