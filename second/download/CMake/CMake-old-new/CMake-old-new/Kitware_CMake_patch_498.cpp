@@ -523,14 +523,11 @@ int cmCTestTestHandler::ProcessHandler()
     }
   
   this->TestResults.clear();
- // do not output startup if this is a sub-process for parallel tests
-  if(!this->CTest->GetParallelSubprocess())
-    {
-    cmCTestLog(this->CTest, HANDLER_OUTPUT,
-               (this->MemCheck ? "Memory check" : "Test")
-               << " project " << cmSystemTools::GetCurrentWorkingDirectory()
-               << std::endl);
-    }
+
+  cmCTestLog(this->CTest, HANDLER_OUTPUT,
+             (this->MemCheck ? "Memory check" : "Test")
+             << " project " << cmSystemTools::GetCurrentWorkingDirectory()
+             << std::endl);
   if ( ! this->PreProcessHandler() )
     {
     return -1;
@@ -583,57 +580,49 @@ int cmCTestTestHandler::ProcessHandler()
       percent = 99;
       }
     
-    if(!this->CTest->GetParallelSubprocess())
-      {
-      cmCTestLog(this->CTest, HANDLER_OUTPUT, std::endl
-                 << static_cast<int>(percent + .5) << "% tests passed, "
-                 << failed.size() << " tests failed out of " 
-                 << total << std::endl); 
-      double totalTestTime = 0;
+    cmCTestLog(this->CTest, HANDLER_OUTPUT, std::endl
+               << static_cast<int>(percent + .5) << "% tests passed, "
+               << failed.size() << " tests failed out of " 
+               << total << std::endl); 
+    double totalTestTime = 0;
 
-      for(cmCTestTestHandler::TestResultsVector::size_type cc = 0;
-          cc < this->TestResults.size(); cc ++ )
-        {
-        cmCTestTestResult *result = &this->TestResults[cc];
-        totalTestTime += result->ExecutionTime;
-        }
-      
-      char realBuf[1024];
-      sprintf(realBuf, "%6.2f sec", (double)(clock_finish - clock_start));
-      cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nTotal Test time (real) = "
-                 << realBuf << "\n" );
-
-      char totalBuf[1024];
-      sprintf(totalBuf, "%6.2f sec", totalTestTime); 
-      cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nTotal Test time (parallel) = " 
-                 <<  totalBuf << "\n" );
-      
+    for(cmCTestTestHandler::TestResultsVector::size_type cc = 0;
+        cc < this->TestResults.size(); cc ++ )
+      {
+      cmCTestTestResult *result = &this->TestResults[cc];
+      totalTestTime += result->ExecutionTime;
       }
+    
+    char realBuf[1024];
+    sprintf(realBuf, "%6.2f sec", (double)(clock_finish - clock_start));
+    cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nTotal Test time (real) = "
+               << realBuf << "\n" );
+
+    char totalBuf[1024];
+    sprintf(totalBuf, "%6.2f sec", totalTestTime); 
+    cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nTotal Test time (parallel) = "
+               <<  totalBuf << "\n" );
 
     if (failed.size())
       {
       cmGeneratedFileStream ofs;
-      if(!this->CTest->GetParallelSubprocess())
+      cmCTestLog(this->CTest, ERROR_MESSAGE, std::endl
+                 << "The following tests FAILED:" << std::endl);
+      this->StartLogFile("TestsFailed", ofs);
+      
+      std::vector<cmCTestTestHandler::cmCTestTestResult>::iterator ftit;
+      for(ftit = this->TestResults.begin();
+          ftit != this->TestResults.end(); ++ftit)
         {
-        cmCTestLog(this->CTest, ERROR_MESSAGE, std::endl
-                   << "The following tests FAILED:" << std::endl);
-        this->StartLogFile("TestsFailed", ofs);
-        
-        std::vector<cmCTestTestHandler::cmCTestTestResult>::iterator ftit;
-        for(ftit = this->TestResults.begin();
-            ftit != this->TestResults.end(); ++ftit)
+        if ( ftit->Status != cmCTestTestHandler::COMPLETED )
           {
-          if ( ftit->Status != cmCTestTestHandler::COMPLETED )
-            {
-            ofs << ftit->TestCount << ":" << ftit->Name << std::endl;
-            cmCTestLog(this->CTest, HANDLER_OUTPUT, "\t" << std::setw(3)
-                       << ftit->TestCount << " - " 
-                       << ftit->Name.c_str() << " ("
-                       << this->GetTestStatus(ftit->Status) << ")" 
-                       << std::endl);
-            }
+          ofs << ftit->TestCount << ":" << ftit->Name << std::endl;
+          cmCTestLog(this->CTest, HANDLER_OUTPUT, "\t" << std::setw(3)
+                     << ftit->TestCount << " - " 
+                     << ftit->Name.c_str() << " ("
+                     << this->GetTestStatus(ftit->Status) << ")" 
+                     << std::endl);
           }
-        
         }
       }
     }
@@ -808,7 +797,6 @@ void cmCTestTestHandler::ProcessOneTest(cmCTestTestProperties *it,
   std::string output;
   int retVal = 0;
   
-  
   cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, std::endl
              << (this->MemCheck?"MemCheck":"Test") 
              << " command: " << testCommand
@@ -839,9 +827,7 @@ void cmCTestTestHandler::ProcessOneTest(cmCTestTestProperties *it,
                                it->Timeout, &it->Environment);
     }
 
-  clock_finish = cmSystemTools::GetTime();  
-
-
+  clock_finish = cmSystemTools::GetTime();
   
   cres.ExecutionTime = (double)(clock_finish - clock_start);
   cres.FullCommandLine = testCommand;
@@ -1118,15 +1104,7 @@ void cmCTestTestHandler::CheckLabelFilter(cmCTestTestProperties& it)
 void cmCTestTestHandler::ComputeTestList()
 {
   this->TestList.clear(); // clear list of test
-  if(this->CTest->GetParallelSubprocess())
-    {
-    this->LoadTestList();
-    return;
-    }
-  else
-    {
-    this->GetListOfTests();
-    }
+  this->GetListOfTests();
   cmCTestTestHandler::ListOfTests::size_type tmsize = this->TestList.size();
   // how many tests are in based on RegExp?
   int inREcnt = 0;
@@ -1325,225 +1303,42 @@ bool cmCTestTestHandler::GetValue(const char* tag,
   return ret;
 }
 
-
-// This should load only one test and is used in -j N mode.
-// it is used by the sub-process ctest runs which should have
-// only one -I N test to run.
-void cmCTestTestHandler::LoadTestList()
+//---------------------------------------------------------------------
+void cmCTestTestHandler::PrintTestList()
 {
-  this->TestList.clear();
-  std::string fname = this->CTest->GetBinaryDir()
-    + "/Testing/Temporary/PCache.txt";
-  std::ifstream fin(fname.c_str());
-  std::string line;
-  if(!fin)
-    {
-    cmCTestLog(this->CTest, ERROR_MESSAGE,
-               "Could not load PCache.txt file: "
-               << fname.c_str() << std::endl);
-    return;
-    }
-  bool ok = true;
-  int numTestsToRun = 0;
-  ok = ok && this->GetValue("TotalNumberOfTests:", 
-                            this->TotalNumberOfTests, fin);
-  ok = ok && this->GetValue("NumberOfTestsToRun:", numTestsToRun, fin);
-  this->ExpandTestsToRunInformation(this->TotalNumberOfTests);
-  if(this->TestsToRun.size() != 1)
-    { 
-    cmCTestLog(this->CTest, ERROR_MESSAGE,
-               "Error when in parallel mode only one test should be run: "
-               << this->TestsToRun.size() << std::endl);
-    }
-  int testIndexToRun = this->TestsToRun[0];
-  this->CTest->SetParallelSubprocessId(testIndexToRun);
-  if(!ok)
-    {
-    return;
-    }
-  for(int i =0; i < numTestsToRun; i++)
-    {
-    cmCTestTestProperties p;
-    int numArgs = 0;
-    ok = this->GetValue("Name:", p.Name, fin);
-    ok = ok && this->GetValue("Directory:", p.Directory, fin);
-    ok = ok && this->GetValue("Args:", numArgs, fin);
-    for(int j =0; j < numArgs; ++j)
-      {
-      cmSystemTools::GetLineFromStream(fin, line);
-      p.Args.push_back(line);
-      }
-    int numDep = 0;
-    ok = ok && this->GetValue("Depends:", numDep, fin);
-    for(int j =0; j < numDep; ++j)
-      {
-      cmSystemTools::GetLineFromStream(fin, line);
-      p.Depends.push_back(line);
-      }
-    int numErrRegex = 0;
-    ok = ok && this->GetValue("ErrorRegularExpressions:", 
-                              numErrRegex, fin);
-    for(int j =0; j < numErrRegex; j++)
-      {
-      cmSystemTools::GetLineFromStream(fin, line);
-      std::pair<cmsys::RegularExpression, std::string> rpair;
-      rpair.first.compile(line.c_str());
-      rpair.second = line;
-      p.ErrorRegularExpressions.push_back(rpair);
-      }
-    int numReqRegex = 0;
-    ok = ok && this->GetValue("RequiredRegularExpressions:", 
-                              numReqRegex, fin);
-    for(int j =0; j < numReqRegex; j++)
-      {
-      cmSystemTools::GetLineFromStream(fin, line);
-      std::pair<cmsys::RegularExpression, std::string> rpair;
-      rpair.first.compile(line.c_str());
-      rpair.second = line;
-      p.RequiredRegularExpressions.push_back(rpair);
-      }
-    int numMeasure = 0;
-    ok = ok && this->GetValue("Measurements:", 
-                              numMeasure, fin);
-    for(int j =0; j < numMeasure; j++)
-      {
-      cmStdString m;
-      cmStdString v;
-      cmSystemTools::GetLineFromStream(fin, line);
-      m = line;
-      cmSystemTools::GetLineFromStream(fin, line);
-      v = line;
-      p.Measurements[m] = v;
-      }
-    int isinre;
-    ok = ok && this->GetValue("IsInBasedOnREOptions:", isinre, fin);
-    ok = ok && this->GetValue("WillFail:", p.WillFail, fin);
-    ok = ok && this->GetValue("TimeOut:", p.Timeout, fin);
-    ok = ok && this->GetValue("Index:", p.Index, fin);
-    int numEnv = 0;
-    ok = ok && this->GetValue("Environment:", 
-                              numEnv, fin);
-    for(int j =0; j < numEnv; j++)
-      {
-      cmSystemTools::GetLineFromStream(fin, line);
-      p.Environment.push_back(line);
-      }
-    int numLabels = 0;
-    ok = ok && this->GetValue("Labels:",
-                              numLabels, fin);
-    for(int j =0; j < numLabels; j++)
-      {
-      cmSystemTools::GetLineFromStream(fin, line);
-      p.Labels.push_back(line);
-      }
-    if(!ok)
-      {
-      cmCTestLog(this->CTest, ERROR_MESSAGE,
-                 "Internal Error reading cached test information."
-                 << std::endl);
-      return;
-      }
-    if(p.Index == testIndexToRun)
-      {
-      // add the one test and stop reading
-      this->TestList.push_back(p);
-      return;
-      }
-    }
-}
-std::string cmCTestTestHandler::SaveTestList()
-{
-  std::string fname = this->CTest->GetBinaryDir()
-    + "/Testing/Temporary/PCache.txt";
-  cmGeneratedFileStream fout(fname.c_str());
-  if(!fout)
-    {
-    cmCTestLog(this->CTest, ERROR_MESSAGE, std::endl
-               << "Could not open PCache.txt for write:" 
-               << fname.c_str()
-               << std::endl);
-    }
-  fout << "TotalNumberOfTests:\n";
-  fout << this->TotalNumberOfTests << "\n";
-  fout << "NumberOfTestsToRun:\n";
-  fout << this->TestList.size() << "\n";
+  int total = this->TotalNumberOfTests;
   for (ListOfTests::iterator it = this->TestList.begin();
        it != this->TestList.end(); it ++ )
-    {
+    { 
     cmCTestTestProperties& p = *it;
-    fout << "Name:\n"
-         << p.Name.c_str()
-         << "\nDirectory:\n"
-         << p.Directory.c_str()
-         << "\nArgs:\n"
-         << p.Args.size() << "\n";
-    for(std::vector<std::string>::iterator i = p.Args.begin();
-        i != p.Args.end(); ++i)
-      {
-      fout << i->c_str() << "\n";
-      }
-    fout << "Depends:\n" << p.Depends.size() << "\n";
-    for(std::vector<std::string>::iterator i = p.Depends.begin();
-        i != p.Depends.end(); ++i)
-      {
-      fout << i->c_str() << "\n";
-      }
-    std::vector<std::pair<cmsys::RegularExpression,
-      std::string> >::iterator regxi;
-    fout << "ErrorRegularExpressions:\n" << 
-      p.ErrorRegularExpressions.size() << "\n";
-    for(regxi  = p.ErrorRegularExpressions.begin(); 
-        regxi != p.ErrorRegularExpressions.end(); regxi++)
+    cmCTestLog(this->CTest, HANDLER_OUTPUT, std::setw(3) 
+             << p.Index << "/");
+    cmCTestLog(this->CTest, HANDLER_OUTPUT, std::setw(3) 
+             << total << " ");
+    if (this->MemCheck)
       {
-      fout << regxi->second << "\n";
+      cmCTestLog(this->CTest, HANDLER_OUTPUT, "Memory Check");
       }
-    fout << "RequiredRegularExpressions:\n" << 
-      p.RequiredRegularExpressions.size() << "\n";
-    for(regxi  = p.RequiredRegularExpressions.begin(); 
-        regxi != p.RequiredRegularExpressions.end(); regxi++)
+     else
       {
-      fout << regxi->second << "\n";
-      }
-    fout << "Measurements:\n" << 
-      p.Measurements.size() << "\n";
-    for(std::map<cmStdString, cmStdString>::const_iterator m =
-          p.Measurements.begin(); m != p.Measurements.end(); ++m)
-      {
-      fout << m->first << "\n";
-      fout << m->second << "\n";
-      }
-
-    fout << "IsInBasedOnREOptions:\n"
-         << p.IsInBasedOnREOptions
-         << "\nWillFail:\n"
-         << p.WillFail
-         << "\nTimeOut:\n"
-         << p.Timeout
-         << "\nIndex:\n"
-         << p.Index << "\n";
-    fout << "Environment:\n" << 
-      p.Environment.size() << "\n";
-    for(std::vector<std::string>::const_iterator e =
-          p.Environment.begin(); e != p.Environment.end(); ++e)
-      {
-      fout << *e << "\n";
-      }
-    fout << "Labels:\n" <<
-      p.Labels.size() << "\n";
-    for(std::vector<std::string>::const_iterator e =
-          p.Labels.begin(); e != p.Labels.end(); ++e)
-      {
-      fout << *e << "\n";
+      cmCTestLog(this->CTest, HANDLER_OUTPUT, "Testing");
       }
+    cmCTestLog(this->CTest, HANDLER_OUTPUT, " ");
+    cmCTestLog(this->CTest, HANDLER_OUTPUT, p.Name.c_str() << std::endl);
     }
-  fout.close();
-  return fname;
 }
 
+//---------------------------------------------------------------------
 void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
                                          std::vector<cmStdString> &failed)
 {
   this->ComputeTestList();
+
+  if(this->CTest->GetShowOnly())
+    {
+    this->PrintTestList();
+    return;
+    }
   cmCTestMultiProcessHandler parallel;
   parallel.SetCTest(this->CTest);
   parallel.SetParallelLevel(this->CTest->GetParallelLevel());