@@ -177,12 +177,6 @@ bool cmCTestRunTest::EndTest(size_t completed, size_t total, bool started)
         this->TestResult.Status = cmCTestTestHandler::OTHER_FAULT;
       }
     }
-  else // if ( res == cmsysProcess_State_Error )
-    {
-    cmCTestLog(this->CTest, HANDLER_OUTPUT, "***Bad command " << res );
-    this->TestResult.Status = cmCTestTestHandler::BAD_COMMAND;
-    }
-
   passed = this->TestResult.Status == cmCTestTestHandler::COMPLETED;
   char buf[1024];
   sprintf(buf, "%6.2f sec", this->TestProcess->GetTotalTime());
@@ -258,16 +252,19 @@ bool cmCTestRunTest::EndTest(size_t completed, size_t total, bool started)
       << "----------------------------------------------------------"
       << std::endl << std::endl;
     }
+  // if the test actually stared and ran 
+  // record the results in TestResult 
   if(started)
     {
     this->TestResult.Output = this->ProcessOutput;
     this->TestResult.ReturnValue = this->TestProcess->GetExitValue();
     this->TestResult.CompletionStatus = "Completed";
     this->TestResult.ExecutionTime = this->TestProcess->GetTotalTime();
-    this->TestHandler->TestResults.push_back(this->TestResult);
-
     this->MemCheckPostProcess();
     }
+  // Always push the current TestResult onto the
+  // TestHandler vector
+  this->TestHandler->TestResults.push_back(this->TestResult);
   delete this->TestProcess;
   return passed;
 }
@@ -309,23 +306,26 @@ bool cmCTestRunTest::StartTest(size_t total)
   this->TestResult.Properties = this->TestProperties;
   this->TestResult.ExecutionTime = 0;
   this->TestResult.ReturnValue = -1;
-  this->TestResult.CompletionStatus = "Not Run";
-  this->TestResult.Status = cmCTestTestHandler::NOT_RUN;
+  this->TestResult.CompletionStatus = "Failed to start";
+  this->TestResult.Status = cmCTestTestHandler::BAD_COMMAND;
   this->TestResult.TestCount = this->TestProperties->Index;  
   this->TestResult.Name = this->TestProperties->Name;
   this->TestResult.Path = this->TestProperties->Directory.c_str();
   
   // log and return if we did not find the executable
   if (this->ActualCommand == "")
     {
+    // if the command was not found create a TestResult object
+    // that has that information 
     this->TestProcess = new cmProcess;
     *this->TestHandler->LogFile << "Unable to find executable: " 
                    << args[1].c_str() << std::endl;
     cmCTestLog(this->CTest, ERROR_MESSAGE, "Unable to find executable: "
                << args[1].c_str() << std::endl);
     this->TestResult.Output = "Unable to find executable: " + args[1];
     this->TestResult.FullCommandLine = "";
-    this->TestHandler->TestResults.push_back(this->TestResult);
+    this->TestResult.CompletionStatus = "Not Run";
+    this->TestResult.Status = cmCTestTestHandler::NOT_RUN;
     return false;
     }
   this->StartTime = this->CTest->CurrentTime();