@@ -18,6 +18,7 @@
 #include "cmCTestTestHandler.h"
 #include "cmCTestMultiProcessHandler.h"
 #include "cmCTest.h"
+#include "cmCTestRunTest.h"
 #include "cmake.h"
 #include "cmGeneratedFileStream.h"
 #include <cmsys/Process.h>
@@ -589,15 +590,12 @@ int cmCTestTestHandler::ProcessHandler()
         cmCTestTestResult *result = &this->TestResults[cc];
         totalTestTime += result->ExecutionTime;
         }
-      this->PrintLabelSummary();
+      
       char buf[1024];
       sprintf(buf, "%6.2f sec", totalTestTime); 
       cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nTotal Test time = " 
                  <<  buf << "\n" );
-      if ( this->LogFile )
-        {
-        *this->LogFile << "\nTotal Test time = " << buf << std::endl;
-        }
+      
       }
 
     if (failed.size())
@@ -660,58 +658,6 @@ int cmCTestTestHandler::ProcessHandler()
 }
 
 //----------------------------------------------------------------------
-void cmCTestTestHandler::PrintLabelSummary()
-{
-  cmCTestTestHandler::ListOfTests::iterator it = this->TestList.begin();
-  cmCTestTestHandler::TestResultsVector::iterator ri =
-    this->TestResults.begin(); 
-  std::map<cmStdString, double> labelTimes;
-  std::set<cmStdString> labels;
-  // initialize maps
-  for(; it != this->TestList.end(); ++it)
-    {
-    cmCTestTestProperties& p = *it;
-    if(p.Labels.size() != 0)
-      { 
-      for(std::vector<std::string>::iterator l = p.Labels.begin();
-          l !=  p.Labels.end(); ++l)
-        {
-        labels.insert(*l);
-        labelTimes[*l] = 0;
-        }
-      }
-    }
-  it = this->TestList.begin();
-  ri = this->TestResults.begin(); 
-  // fill maps
-  for(; it != this->TestList.end(); ++it, ++ri)
-    {
-    cmCTestTestProperties& p = *it;
-    cmCTestTestResult &result = *ri;
-    if(p.Labels.size() != 0)
-      { 
-      for(std::vector<std::string>::iterator l = p.Labels.begin();
-          l !=  p.Labels.end(); ++l)
-        {
-        labelTimes[*l] += result.ExecutionTime;
-        }
-      }
-    }
-  // now print times
-  for(std::set<cmStdString>::const_iterator i = labels.begin();
-      i != labels.end(); ++i)
-    {
-    cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nTime in " 
-               << *i << " = " << labelTimes[*i] << " sec" ); 
-    if ( this->LogFile )
-        {
-        *this->LogFile << "\nTime in " << *i << " = "
-                       << labelTimes[*i] << " sec"  << std::endl;
-        }
-    }
-}
-
-//----------------------------------------------------------------------
 void cmCTestTestHandler::ProcessOneTest(cmCTestTestProperties *it,
                                         std::vector<cmStdString> &passed,
                                         std::vector<cmStdString> &failed,
@@ -950,10 +896,6 @@ void cmCTestTestHandler::ProcessOneTest(cmCTestTestProperties *it,
     char buf[1024];
     sprintf(buf, "%6.2f sec", cres.ExecutionTime);
     cmCTestLog(this->CTest, HANDLER_OUTPUT, buf << "\n" );
-    if ( this->LogFile )
-      {
-      *this->LogFile << "\nTest time = " << buf << std::endl;
-      }
     if (!output.empty() && output.find("<DartMeasurement") != output.npos)
       {
       if (this->DartStuff.find(output.c_str()))
@@ -1599,6 +1541,7 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
     << "----------------------------------------------------------"
     << std::endl;
   std::string last_directory = "";
+
   // run each test
   for (ListOfTests::iterator it = this->TestList.begin();
        it != this->TestList.end(); it ++ )
@@ -1613,9 +1556,20 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
       cmSystemTools::ChangeDirectory(it->Directory.c_str());
       }
     // process this one test
-    this->ProcessOneTest(&(*it), passed, failed, it->Index, 
-                         static_cast<int>(this->TotalNumberOfTests));
-    }
+    cmCTestRunTest testRun;
+    testRun.SetTestProperties(&(*it));
+    testRun.SetTestHandler(this);
+
+    bool testPassed = testRun.Execute(); //run the test
+    if(testPassed && !this->CTest->GetShowOnly())
+      {
+      passed.push_back(it->Name);
+      }
+    else if(!testPassed)
+      {
+      failed.push_back(it->Name);
+      }
+    }  
   this->EndTest = this->CTest->CurrentTime();
   this->EndTestTime = static_cast<unsigned int>(cmSystemTools::GetTime());
   this->ElapsedTestingTime = cmSystemTools::GetTime() - elapsed_time_start;