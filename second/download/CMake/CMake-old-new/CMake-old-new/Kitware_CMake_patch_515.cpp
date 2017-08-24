@@ -16,7 +16,7 @@
 =========================================================================*/
 
 #include "cmCTestTestHandler.h"
-
+#include "cmCTestMultiProcessHandler.h"
 #include "cmCTest.h"
 #include "cmake.h"
 #include "cmGeneratedFileStream.h"
@@ -500,11 +500,14 @@ int cmCTestTestHandler::ProcessHandler()
     }
   
   this->TestResults.clear();
-
-  cmCTestLog(this->CTest, HANDLER_OUTPUT,
-    (this->MemCheck ? "Memory check" : "Test")
-             << " project " << cmSystemTools::GetCurrentWorkingDirectory()
-             << std::endl);
+ // do not output startup if this is a sub-process for parallel tests
+  if(!this->CTest->GetParallelSubprocess())
+    {
+    cmCTestLog(this->CTest, HANDLER_OUTPUT,
+               (this->MemCheck ? "Memory check" : "Test")
+               << " project " << cmSystemTools::GetCurrentWorkingDirectory()
+               << std::endl);
+    }
   if ( ! this->PreProcessHandler() )
     {
     return -1;
@@ -517,7 +520,6 @@ int cmCTestTestHandler::ProcessHandler()
   std::vector<cmStdString> passed;
   std::vector<cmStdString> failed;
   int total;
-
   this->ProcessDirectory(passed, failed);
 
   total = int(passed.size()) + int(failed.size());
@@ -550,33 +552,37 @@ int cmCTestTestHandler::ProcessHandler()
       {
       percent = 99;
       }
-    cmCTestLog(this->CTest, HANDLER_OUTPUT, std::endl
-      << static_cast<int>(percent + .5) << "% tests passed, "
-      << failed.size() << " tests failed out of " << total << std::endl);
-    //fprintf(stderr,"\n%.0f%% tests passed, %i tests failed out of %i\n",
-    //  percent, int(failed.size()), total);
+    if(!this->CTest->GetParallelSubprocess())
+      {
+      cmCTestLog(this->CTest, HANDLER_OUTPUT, std::endl
+                 << static_cast<int>(percent + .5) << "% tests passed, "
+                 << failed.size() << " tests failed out of " 
+                 << total << std::endl);
+      }
 
     if (failed.size())
       {
       cmGeneratedFileStream ofs;
-
-      cmCTestLog(this->CTest, ERROR_MESSAGE, std::endl
-        << "The following tests FAILED:" << std::endl);
-      this->StartLogFile("TestsFailed", ofs);
-
-      std::vector<cmCTestTestHandler::cmCTestTestResult>::iterator ftit;
-      for(ftit = this->TestResults.begin();
-        ftit != this->TestResults.end(); ++ftit)
+      if(!this->CTest->GetParallelSubprocess())
         {
-        if ( ftit->Status != cmCTestTestHandler::COMPLETED )
+        cmCTestLog(this->CTest, ERROR_MESSAGE, std::endl
+                   << "The following tests FAILED:" << std::endl);
+        this->StartLogFile("TestsFailed", ofs);
+        
+        std::vector<cmCTestTestHandler::cmCTestTestResult>::iterator ftit;
+        for(ftit = this->TestResults.begin();
+            ftit != this->TestResults.end(); ++ftit)
           {
-          ofs << ftit->TestCount << ":" << ftit->Name << std::endl;
-          cmCTestLog(this->CTest, HANDLER_OUTPUT, "\t" << std::setw(3)
-            << ftit->TestCount << " - " << ftit->Name.c_str() << " ("
-            << this->GetTestStatus(ftit->Status) << ")" << std::endl);
+          if ( ftit->Status != cmCTestTestHandler::COMPLETED )
+            {
+            ofs << ftit->TestCount << ":" << ftit->Name << std::endl;
+            cmCTestLog(this->CTest, HANDLER_OUTPUT, "\t" << std::setw(3)
+                       << ftit->TestCount << " - " << ftit->Name.c_str() << " ("
+                       << this->GetTestStatus(ftit->Status) << ")" << std::endl);
+            }
           }
+        
         }
-
       }
     }
 
@@ -677,8 +683,8 @@ void cmCTestTestHandler::ProcessOneTest(cmCTestTestProperties *it,
   
   // add the arguments
   std::vector<std::string>::const_iterator j = args.begin();
-  ++j;
-  ++j;
+  ++j; // skip test name
+  ++j; // skip command as it is in actualCommand
   std::vector<const char*> arguments;
   this->GenerateTestCommand(arguments);
   arguments.push_back(actualCommand.c_str());
@@ -917,23 +923,20 @@ void cmCTestTestHandler::ProcessOneTest(cmCTestTestProperties *it,
 }
 
 //----------------------------------------------------------------------
-void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
-                                          std::vector<cmStdString> &failed)
+void cmCTestTestHandler::ComputeTestList()
 {
-  std::string current_dir = cmSystemTools::GetCurrentWorkingDirectory();
-  this->TestList.clear();
-
-  this->GetListOfTests();
+  this->TestList.clear(); // clear list of test
+  if(this->CTest->GetParallelSubprocess())
+    {
+    this->LoadTestList();
+    return;
+    }
+  else
+    {
+    this->GetListOfTests();
+    }
   cmCTestTestHandler::ListOfTests::size_type tmsize = this->TestList.size();
 
-  this->StartTest = this->CTest->CurrentTime();
-  this->StartTestTime = static_cast<unsigned int>(cmSystemTools::GetTime());
-  double elapsed_time_start = cmSystemTools::GetTime();
-
-  *this->LogFile << "Start testing: " << this->StartTest << std::endl
-    << "----------------------------------------------------------"
-    << std::endl;
-
   // how many tests are in based on RegExp?
   int inREcnt = 0;
   cmCTestTestHandler::ListOfTests::iterator it;
@@ -953,10 +956,11 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
     {
     this->ExpandTestsToRunInformation(inREcnt);
     }
-
+  // Now create a final list of tests to run
   int cnt = 0;
   inREcnt = 0;
-  std::string last_directory = "";
+  std::string last_directory = ""; 
+  ListOfTests finalList;
   for ( it = this->TestList.begin(); it != this->TestList.end(); it ++ )
     {
     cnt ++;
@@ -965,23 +969,6 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
       inREcnt++;
       }
 
-    // if we are out of time then skip this test, we leave two minutes 
-    // to submit results
-    if (this->CTest->GetRemainingTimeAllowed() - 120 <= 0)
-      {
-      continue;
-      }
-    
-    if (!(last_directory == it->Directory))
-      {
-      cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-                 "Changing directory into " << it->Directory.c_str() << "\n");
-      *this->LogFile << "Changing directory into: " << it->Directory.c_str()
-                     << std::endl;
-      last_directory = it->Directory;
-      cmSystemTools::ChangeDirectory(it->Directory.c_str());
-      }
-
     if (this->UseUnion)
       {
       // if it is not in the list and not in the regexp then skip
@@ -1003,10 +990,322 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
         continue;
         }
       }
-    
+    it->Index = cnt;  // save the index into the test list for this test
+    finalList.push_back(*it);
+    }
+  // Save the total number of tests before exclusions
+  this->TotalNumberOfTests = this->TestList.size();
+  // Set the TestList to the final list of all test
+  this->TestList = finalList;
+}
+ 
+bool cmCTestTestHandler::GetValue(const char* tag,
+                                  int& value,
+                                  std::ifstream& fin)
+{
+  std::string line;
+  cmSystemTools::GetLineFromStream(fin, line);
+  if(line == tag)
+    {
+    fin >> value;
+    cmSystemTools::GetLineFromStream(fin, line); // read blank line
+    }
+  else
+    {
+    cmCTestLog(this->CTest, ERROR_MESSAGE,
+               "parse error: missing tag: "
+               << tag << " found [" << line << "]" << std::endl);
+    return false;
+    }
+  return true;
+}
+
+bool cmCTestTestHandler::GetValue(const char* tag,
+                                  double& value,
+                                  std::ifstream& fin)
+{
+  std::string line;
+  cmSystemTools::GetLineFromStream(fin, line);
+  if(line == tag)
+    {
+    fin >> value;
+    cmSystemTools::GetLineFromStream(fin, line); // read blank line
+    }
+  else
+    {
+    cmCTestLog(this->CTest, ERROR_MESSAGE,
+               "parse error: missing tag: "
+               << tag << " found [" << line << "]" << std::endl);
+    return false;
+    }
+  return true;
+}
+
+bool cmCTestTestHandler::GetValue(const char* tag,
+                                  bool& value,
+                                  std::ifstream& fin)
+{
+  std::string line;
+  cmSystemTools::GetLineFromStream(fin, line);
+  if(line == tag)
+    {
+    fin >> value;
+    cmSystemTools::GetLineFromStream(fin, line); // read blank line
+    }
+  else
+    {
+    cmCTestLog(this->CTest, ERROR_MESSAGE,
+               "parse error: missing tag: "
+               << tag << " found [" << line << "]" << std::endl);
+    return false;
+    }
+  return true;
+}
+
+bool cmCTestTestHandler::GetValue(const char* tag,
+                                  size_t& value,
+                                  std::ifstream& fin)
+{
+  std::string line;
+  cmSystemTools::GetLineFromStream(fin, line);
+  if(line == tag)
+    {
+    fin >> value;
+    cmSystemTools::GetLineFromStream(fin, line); // read blank line
+    }
+  else
+    { 
+    cmCTestLog(this->CTest, ERROR_MESSAGE,
+               "parse error: missing tag: "
+               << tag << " found [" << line.c_str() << "]" << std::endl);
+    return false;
+    }
+  return true;
+}
+
+bool cmCTestTestHandler::GetValue(const char* tag,
+                                  std::string& value,
+                                  std::ifstream& fin)
+{
+  std::string line;
+  cmSystemTools::GetLineFromStream(fin, line);
+  if(line == tag)
+    {
+    return cmSystemTools::GetLineFromStream(fin, value);
+    }
+  else
+    {
+    cmCTestLog(this->CTest, ERROR_MESSAGE,
+               "parse error: missing tag: "
+               << tag << " found [" << line << "]" << std::endl);
+    return false;
+    }
+  return true;
+}
+
+
+// This should load only one test and is used in -j N mode.
+// it is used by the sub-process ctest runs which should have
+// only one -I N test to run.
+void cmCTestTestHandler::LoadTestList()
+{
+  this->TestList.clear();
+  std::string fname = this->CTest->GetBinaryDir()
+    + "/Testing/Temporary/PCache.txt";
+  std::ifstream fin(fname.c_str());
+  std::string line;
+  if(!fin)
+    {
+    cmCTestLog(this->CTest, ERROR_MESSAGE,
+               "Could not load PCache.txt file: "
+               << fname.c_str() << std::endl);
+    return;
+    }
+  bool ok = true;
+  int numTestsToRun;
+  ok = ok && this->GetValue("TotalNumberOfTests:", 
+                            this->TotalNumberOfTests, fin);
+  ok = ok && this->GetValue("NumberOfTestsToRun:", numTestsToRun, fin);
+  this->ExpandTestsToRunInformation(this->TotalNumberOfTests);
+  if(this->TestsToRun.size() != 1)
+    { 
+    cmCTestLog(this->CTest, ERROR_MESSAGE,
+               "Error when in parallel mode only one test should be run: "
+               << this->TestsToRun.size() << std::endl);
+    }
+  int testIndexToRun = this->TestsToRun[0];
+  this->CTest->SetParallelSubprocessId(testIndexToRun);
+  if(!ok)
+    {
+    return;
+    }
+  for(int i =0; i < numTestsToRun; i++)
+    {
+    cmCTestTestProperties p;
+    int numArgs;
+    bool ok = this->GetValue("Name:", p.Name, fin);
+    ok = ok && this->GetValue("Directory:", p.Directory, fin);
+    ok = ok && this->GetValue("Args:", numArgs, fin);
+    for(int j =0; j < numArgs; ++j)
+      {
+      cmSystemTools::GetLineFromStream(fin, line);
+      p.Args.push_back(line);
+      }
+    int numDep = 0;
+    ok = ok && this->GetValue("Depends:", numDep, fin);
+    for(int j =0; j < numDep; ++j)
+      {
+      cmSystemTools::GetLineFromStream(fin, line);
+      p.Depends.push_back(line);
+      }
+    int isinre;
+    ok = ok && this->GetValue("IsInBasedOnREOptions:", isinre, fin);
+    ok = ok && this->GetValue("WillFail:", p.WillFail, fin);
+    ok = ok && this->GetValue("TimeOut:", p.Timeout, fin);
+    ok = ok && this->GetValue("Index:", p.Index, fin);
+    if(!ok)
+      {
+      return;
+      }
+    if(p.Index == testIndexToRun)
+      {
+      // add the one test and stop reading
+      this->TestList.push_back(p);
+      return;
+      }
+    }
+}
+std::string cmCTestTestHandler::SaveTestList()
+{
+  std::string fname = this->CTest->GetBinaryDir()
+    + "/Testing/Temporary/PCache.txt";
+  cmGeneratedFileStream fout(fname.c_str());
+  if(!fout)
+    {
+    cmCTestLog(this->CTest, ERROR_MESSAGE, std::endl
+               << "Could not open PCache.txt for write:" 
+               << fname.c_str()
+               << std::endl);
+    }
+  fout << "TotalNumberOfTests:\n";
+  fout << this->TotalNumberOfTests << "\n";
+  fout << "NumberOfTestsToRun:\n";
+  fout << this->TestList.size() << "\n";
+  for (ListOfTests::iterator it = this->TestList.begin();
+       it != this->TestList.end(); it ++ )
+    {
+    cmCTestTestProperties& p = *it;
+    fout << "Name:\n"
+         << p.Name.c_str()
+         << "\nDirectory:\n"
+         << p.Directory.c_str()
+         << "\nArgs:\n"
+         << p.Args.size() << "\n";
+    for(std::vector<std::string>::iterator i = p.Args.begin();
+        i != p.Args.end(); ++i)
+      {
+      fout << i->c_str() << "\n";
+      }
+    fout << "Depends:\n" << p.Depends.size() << "\n";
+    for(std::vector<std::string>::iterator i = p.Depends.begin();
+        i != p.Depends.end(); ++i)
+      {
+      fout << i->c_str() << "\n";
+      }
+    fout << "IsInBasedOnREOptions:\n"
+         << p.IsInBasedOnREOptions
+         << "\nWillFail:\n"
+         << p.WillFail
+         << "\nTimeOut:\n"
+         << p.Timeout
+         << "\nIndex:\n"
+         << p.Index << "\n";
+    }
+  fout.close();
+  return fname;
+}
+
+void cmCTestTestHandler::ProcessParallel(std::vector<cmStdString> &passed,
+                                         std::vector<cmStdString> &failed)
+{
+  this->ComputeTestList();
+  cmCTestMultiProcessHandler parallel;
+  parallel.SetCTest(this->CTest);
+  parallel.SetParallelLevel(this->CTest->GetParallelLevel()); 
+  std::set<int> depends;
+  std::map<int, std::set<int> > tests; 
+  std::map<int, cmStdString> testnames;
+  for (ListOfTests::iterator it = this->TestList.begin();
+       it != this->TestList.end(); it ++ )
+    { 
+    cmCTestTestProperties& p = *it;
+    testnames[p.Index] = p.Name;
+    if(p.Depends.size())
+      {
+      for(std::vector<std::string>::iterator i = p.Depends.begin();
+        i != p.Depends.end(); ++i)
+        {
+        for(ListOfTests::iterator it2 = this->TestList.begin();
+            it2 != this->TestList.end(); it2 ++ )
+          {
+          if(it2->Name == *i)
+            {
+            depends.insert(it2->Index);
+            break; // break out of test loop as name can only match 1
+            }
+          }
+        }
+      }
+    tests[it->Index] = depends;
+    }
+  parallel.SetCTestCommand(this->CTest->GetCTestExecutable());
+  parallel.SetTests(tests, testnames);
+  std::string fname = this->SaveTestList();
+  parallel.SetTestCacheFile(fname.c_str());
+  parallel.SetPassFailVectors(&passed, &failed);
+  this->TestResults.clear();
+  parallel.SetTestResults(&this->TestResults);
+  parallel.RunTests();
+  cmSystemTools::RemoveFile(fname.c_str());
+}
+
+
+//----------------------------------------------------------------------
+void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
+                                          std::vector<cmStdString> &failed)
+{
+  if(this->CTest->GetParallelLevel() > 0)
+    {
+    this->ProcessParallel(passed, failed);
+    return;
+    }
+  // save the current working directory
+  std::string current_dir = cmSystemTools::GetCurrentWorkingDirectory();
+  // compute the list of tests to run
+  this->ComputeTestList();
+  this->StartTest = this->CTest->CurrentTime();
+  this->StartTestTime = static_cast<unsigned int>(cmSystemTools::GetTime());
+  double elapsed_time_start = cmSystemTools::GetTime();
+  *this->LogFile << "Start testing: " << this->StartTest << std::endl
+    << "----------------------------------------------------------"
+    << std::endl;
+  std::string last_directory = "";
+  // run each test
+  for (ListOfTests::iterator it = this->TestList.begin();
+       it != this->TestList.end(); it ++ )
+    {
+    if (!(last_directory == it->Directory))
+      {
+      cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+                 "Changing directory into " << it->Directory.c_str() << "\n");
+      *this->LogFile << "Changing directory into: " << it->Directory.c_str()
+                     << std::endl;
+      last_directory = it->Directory;
+      cmSystemTools::ChangeDirectory(it->Directory.c_str());
+      }
     // process this one test
-    this->ProcessOneTest(&(*it), passed, failed, cnt, 
-                         static_cast<int>(tmsize));
+    this->ProcessOneTest(&(*it), passed, failed, it->Index, 
+                         static_cast<int>(this->TotalNumberOfTests));
     }
 
   this->EndTest = this->CTest->CurrentTime();
@@ -1890,6 +2189,17 @@ bool cmCTestTestHandler::SetTestsProperties(
                   std::string(crit->c_str())));
               }
             }
+          if ( key == "DEPENDS" )
+            { 
+            std::vector<std::string> lval;
+            cmSystemTools::ExpandListArgument(val.c_str(), lval);
+            std::vector<std::string>::iterator crit;
+            for ( crit = lval.begin(); crit != lval.end(); ++ crit )
+              {
+              cmCTestTestProperties* tp = &(*rtit);
+              rtit->Depends.push_back(*crit);
+              }
+            }
           if ( key == "MEASUREMENT" )
             {
             size_t pos = val.find_first_of("=");