@@ -543,8 +543,15 @@ int cmCTestTestHandler::ProcessHandler()
   std::vector<cmStdString> passed;
   std::vector<cmStdString> failed;
   int total;
+
+  //start the real time clock
+  double clock_start, clock_finish;
+  clock_start = cmSystemTools::GetTime();
+
   this->ProcessDirectory(passed, failed);
 
+  clock_finish = cmSystemTools::GetTime();
+
   total = int(passed.size()) + int(failed.size());
 
   if (total == 0)
@@ -591,10 +598,15 @@ int cmCTestTestHandler::ProcessHandler()
         totalTestTime += result->ExecutionTime;
         }
       
-      char buf[1024];
-      sprintf(buf, "%6.2f sec", totalTestTime); 
-      cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nTotal Test time = " 
-                 <<  buf << "\n" );
+      char realBuf[1024];
+      sprintf(realBuf, "%6.2f sec", (double)(clock_finish - clock_start));
+      cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nTotal Test time (real) = "
+                 << realBuf << "\n" );
+
+      char totalBuf[1024];
+      sprintf(totalBuf, "%6.2f sec", totalTestTime); 
+      cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nTotal Test time (parallel) = " 
+                 <<  totalBuf << "\n" );
       
       }
 
@@ -1528,21 +1540,28 @@ std::string cmCTestTestHandler::SaveTestList()
   return fname;
 }
 
-void cmCTestTestHandler::ProcessParallel(std::vector<cmStdString> &passed,
+void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
                                          std::vector<cmStdString> &failed)
 {
   this->ComputeTestList();
   cmCTestMultiProcessHandler parallel;
   parallel.SetCTest(this->CTest);
-  parallel.SetParallelLevel(this->CTest->GetParallelLevel()); 
+  parallel.SetParallelLevel(this->CTest->GetParallelLevel());
+  parallel.SetTestHandler(this);
+
+  *this->LogFile << "Start testing: "
+    << this->CTest->CurrentTime() << std::endl
+    << "----------------------------------------------------------"
+    << std::endl;
+
   cmCTestMultiProcessHandler::TestSet depends;
   cmCTestMultiProcessHandler::TestMap tests;
-  std::map<int, cmStdString> testnames;
+  cmCTestMultiProcessHandler::PropertiesMap properties;
   for (ListOfTests::iterator it = this->TestList.begin();
        it != this->TestList.end(); it ++ )
     { 
     cmCTestTestProperties& p = *it;
-    testnames[p.Index] = p.Name;
+    
     if(p.Depends.size())
       {
       for(std::vector<std::string>::iterator i = p.Depends.begin();
@@ -1560,76 +1579,16 @@ void cmCTestTestHandler::ProcessParallel(std::vector<cmStdString> &passed,
         }
       }
     tests[it->Index] = depends;
+    properties[it->Index] = &*it;
     }
-  parallel.SetCTestCommand(this->CTest->GetCTestExecutable());
-  parallel.SetTests(tests, testnames);
-  std::string fname = this->SaveTestList();
-  parallel.SetTestCacheFile(fname.c_str());
+  parallel.SetTests(tests, properties);
   parallel.SetPassFailVectors(&passed, &failed);
   this->TestResults.clear();
   parallel.SetTestResults(&this->TestResults);
   parallel.RunTests();
-  cmSystemTools::RemoveFile(fname.c_str());
-}
-
-
-//----------------------------------------------------------------------
-void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
-                                          std::vector<cmStdString> &failed)
-{
-  if(this->CTest->GetParallelLevel() > 0)
-    {
-    this->ProcessParallel(passed, failed);
-    return;
-    }
-  // save the current working directory
-  std::string current_dir = cmSystemTools::GetCurrentWorkingDirectory();
-  // compute the list of tests to run
-  this->ComputeTestList();
-  this->StartTest = this->CTest->CurrentTime();
-  this->StartTestTime = static_cast<unsigned int>(cmSystemTools::GetTime());
-  double elapsed_time_start = cmSystemTools::GetTime();
-  *this->LogFile << "Start testing: " << this->StartTest << std::endl
-    << "----------------------------------------------------------"
-    << std::endl;
-  std::string last_directory = "";
 
-  // run each test
-  for (ListOfTests::iterator it = this->TestList.begin();
-       it != this->TestList.end(); it ++ )
-    {
-    if (!(last_directory == it->Directory))
-      {
-      cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-                 "Changing directory into " << it->Directory.c_str() << "\n");
-      *this->LogFile << "Changing directory into: " << it->Directory.c_str()
-                     << std::endl;
-      last_directory = it->Directory;
-      cmSystemTools::ChangeDirectory(it->Directory.c_str());
-      }
-    // process this one test
-    cmCTestRunTest testRun;
-    testRun.SetTestProperties(&(*it));
-    testRun.SetTestHandler(this);
-
-    bool testPassed = testRun.Execute(); //run the test
-    if(testPassed && !this->CTest->GetShowOnly())
-      {
-      passed.push_back(it->Name);
-      }
-    else if(!testPassed)
-      {
-      failed.push_back(it->Name);
-      }
-    }  
-  this->EndTest = this->CTest->CurrentTime();
-  this->EndTestTime = static_cast<unsigned int>(cmSystemTools::GetTime());
-  this->ElapsedTestingTime = cmSystemTools::GetTime() - elapsed_time_start;
-  if ( this->LogFile )
-    {
-    *this->LogFile << "End testing: " << this->EndTest << std::endl;
-    }
-  cmSystemTools::ChangeDirectory(current_dir.c_str());
+  *this->LogFile << "End testing: "
+     << this->CTest->CurrentTime() << std::endl;
 }
 
 //----------------------------------------------------------------------