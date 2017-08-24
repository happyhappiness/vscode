@@ -9,8 +9,8 @@
   Copyright (c) 2002 Kitware, Inc., Insight Consortium.  All rights reserved.
   See Copyright.txt or http://www.cmake.org/HTML/Copyright.html for details.
 
-     This software is distributed WITHOUT ANY WARRANTY; without even 
-     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
+     This software is distributed WITHOUT ANY WARRANTY; without even
+     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
      PURPOSE.  See the above copyright notices for more information.
 
 =========================================================================*/
@@ -29,7 +29,7 @@
 #include "cmCommand.h"
 #include "cmSystemTools.h"
 
-#include <stdlib.h> 
+#include <stdlib.h>
 #include <math.h>
 #include <float.h>
 
@@ -42,7 +42,7 @@ class cmCTestSubdirCommand : public cmCommand
   /**
    * This is a virtual constructor for the command.
    */
-  virtual cmCommand* Clone() 
+  virtual cmCommand* Clone()
     {
     cmCTestSubdirCommand* c = new cmCTestSubdirCommand;
     c->m_TestHandler = m_TestHandler;
@@ -78,14 +78,14 @@ bool cmCTestSubdirCommand::InitialPass(std::vector<std::string> const& args)
     return false;
     }
   std::vector<std::string>::const_iterator it;
-  std::string cwd = cmSystemTools::GetCurrentWorkingDirectory(); 
+  std::string cwd = cmSystemTools::GetCurrentWorkingDirectory();
   for ( it = args.begin(); it != args.end(); ++ it )
     {
     cmSystemTools::ChangeDirectory(cwd.c_str());
     std::string fname = cwd;
     fname += "/";
     fname += *it;
- 
+
     if ( !cmSystemTools::FileExists(fname.c_str()) )
       {
       // No subdirectory? So what...
@@ -111,7 +111,8 @@ bool cmCTestSubdirCommand::InitialPass(std::vector<std::string> const& args)
       }
     fname += "/";
     fname += testFilename;
-    bool readit = m_Makefile->ReadListFile( m_Makefile->GetCurrentListFile(), fname.c_str());
+    bool readit = m_Makefile->ReadListFile( m_Makefile->GetCurrentListFile(),
+      fname.c_str());
     cmSystemTools::ChangeDirectory(cwd.c_str());
     if(!readit)
       {
@@ -131,7 +132,7 @@ class cmCTestAddTestCommand : public cmCommand
   /**
    * This is a virtual constructor for the command.
    */
-  virtual cmCommand* Clone() 
+  virtual cmCommand* Clone()
     {
     cmCTestAddTestCommand* c = new cmCTestAddTestCommand;
     c->m_TestHandler = m_TestHandler;
@@ -176,9 +177,10 @@ class cmCTestSetTestsPropertiesCommand : public cmCommand
   /**
    * This is a virtual constructor for the command.
    */
-  virtual cmCommand* Clone() 
+  virtual cmCommand* Clone()
     {
-    cmCTestSetTestsPropertiesCommand* c = new cmCTestSetTestsPropertiesCommand;
+    cmCTestSetTestsPropertiesCommand* c
+      = new cmCTestSetTestsPropertiesCommand;
     c->m_TestHandler = m_TestHandler;
     return c;
     }
@@ -204,7 +206,8 @@ class cmCTestSetTestsPropertiesCommand : public cmCommand
 };
 
 //----------------------------------------------------------------------
-bool cmCTestSetTestsPropertiesCommand::InitialPass(std::vector<std::string> const& args)
+bool cmCTestSetTestsPropertiesCommand::InitialPass(
+  std::vector<std::string> const& args)
 {
   return m_TestHandler->SetTestsProperties(args);
 }
@@ -224,15 +227,15 @@ bool TryExecutable(const char *dir, const char *file,
     tryPath = dir;
     tryPath += "/";
     }
-  
+
   if (subdir && strcmp(subdir,""))
     {
     tryPath += subdir;
     tryPath += "/";
     }
-  
+
   tryPath += file;
-  
+
   // find the file without an executable extension
   if(cmSystemTools::FileExists(tryPath.c_str()))
     {
@@ -247,17 +250,17 @@ bool TryExecutable(const char *dir, const char *file,
     *fullPath = cmSystemTools::CollapseFullPath(tryPath.c_str());
     return true;
     }
-  
+
   // not found at all, return false
   return false;
 }
 
 //----------------------------------------------------------------------
 // get the next number in a string with numbers separated by ,
 // pos is the start of the search and pos2 is the end of the search
-// pos becomes pos2 after a call to GetNextNumber.   
+// pos becomes pos2 after a call to GetNextNumber.
 // -1 is returned at the end of the list.
-inline int GetNextNumber(std::string const& in, 
+inline int GetNextNumber(std::string const& in,
                          int& val,
                          std::string::size_type& pos,
                          std::string::size_type& pos2)
@@ -293,9 +296,9 @@ inline int GetNextNumber(std::string const& in,
 //----------------------------------------------------------------------
 // get the next number in a string with numbers separated by ,
 // pos is the start of the search and pos2 is the end of the search
-// pos becomes pos2 after a call to GetNextNumber.   
+// pos becomes pos2 after a call to GetNextNumber.
 // -1 is returned at the end of the list.
-inline int GetNextRealNumber(std::string const& in, 
+inline int GetNextRealNumber(std::string const& in,
                              double& val,
                              std::string::size_type& pos,
                              std::string::size_type& pos2)
@@ -328,19 +331,19 @@ inline int GetNextRealNumber(std::string const& in,
     }
 }
 
-                         
+
 //----------------------------------------------------------------------
 cmCTestTestHandler::cmCTestTestHandler()
 {
   m_UseUnion = false;
-  
+
   m_UseIncludeRegExp       = false;
   m_UseExcludeRegExp       = false;
   m_UseExcludeRegExpFirst  = false;
 
   m_CustomMaximumPassedTestOutputSize = 1 * 1024;
   m_CustomMaximumFailedTestOutputSize = 300 * 1024;
-  
+
   m_MemCheck = false;
 
   m_LogFile = 0;
@@ -382,18 +385,18 @@ void cmCTestTestHandler::Initialize()
 //----------------------------------------------------------------------
 void cmCTestTestHandler::PopulateCustomVectors(cmMakefile *mf)
 {
-  cmCTest::PopulateCustomVector(mf, "CTEST_CUSTOM_PRE_TEST", 
+  cmCTest::PopulateCustomVector(mf, "CTEST_CUSTOM_PRE_TEST",
                                 m_CustomPreTest);
-  cmCTest::PopulateCustomVector(mf, "CTEST_CUSTOM_POST_TEST", 
+  cmCTest::PopulateCustomVector(mf, "CTEST_CUSTOM_POST_TEST",
                                 m_CustomPostTest);
   cmCTest::PopulateCustomVector(mf,
-                             "CTEST_CUSTOM_TESTS_IGNORE", 
+                             "CTEST_CUSTOM_TESTS_IGNORE",
                              m_CustomTestsIgnore);
-  cmCTest::PopulateCustomInteger(mf, 
-                             "CTEST_CUSTOM_MAXIMUM_PASSED_TEST_OUTPUT_SIZE", 
+  cmCTest::PopulateCustomInteger(mf,
+                             "CTEST_CUSTOM_MAXIMUM_PASSED_TEST_OUTPUT_SIZE",
                              m_CustomMaximumPassedTestOutputSize);
-  cmCTest::PopulateCustomInteger(mf, 
-                             "CTEST_CUSTOM_MAXIMUM_FAILED_TEST_OUTPUT_SIZE", 
+  cmCTest::PopulateCustomInteger(mf,
+                             "CTEST_CUSTOM_MAXIMUM_FAILED_TEST_OUTPUT_SIZE",
                              m_CustomMaximumFailedTestOutputSize);
 }
 
@@ -402,7 +405,8 @@ int cmCTestTestHandler::PreProcessHandler()
 {
   if ( !this->ExecuteCommands(m_CustomPreTest) )
     {
-    cmCTestLog(m_CTest, ERROR_MESSAGE, "Problem executing pre-test command(s)." << std::endl);
+    cmCTestLog(m_CTest, ERROR_MESSAGE,
+      "Problem executing pre-test command(s)." << std::endl);
     return 0;
     }
   return 1;
@@ -413,7 +417,8 @@ int cmCTestTestHandler::PostProcessHandler()
 {
   if ( !this->ExecuteCommands(m_CustomPostTest) )
     {
-    cmCTestLog(m_CTest, ERROR_MESSAGE, "Problem executing post-test command(s)." << std::endl);
+    cmCTestLog(m_CTest, ERROR_MESSAGE,
+      "Problem executing post-test command(s)." << std::endl);
     return 0;
     }
   return 1;
@@ -443,7 +448,8 @@ int cmCTestTestHandler::ProcessHandler()
 
   m_TestResults.clear();
 
-  cmCTestLog(m_CTest, HANDLER_OUTPUT, (m_MemCheck ? "Memory check" : "Test") << " project" << std::endl);
+  cmCTestLog(m_CTest, HANDLER_OUTPUT, (m_MemCheck ? "Memory check" : "Test")
+    << " project" << std::endl);
   if ( ! this->PreProcessHandler() )
     {
     return -1;
@@ -465,18 +471,20 @@ int cmCTestTestHandler::ProcessHandler()
     {
     if ( !m_CTest->GetShowOnly() )
       {
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "No tests were found!!!" << std::endl);
+      cmCTestLog(m_CTest, ERROR_MESSAGE, "No tests were found!!!"
+        << std::endl);
       }
     }
   else
     {
-    if (m_HandlerVerbose && passed.size() && 
-      (m_UseIncludeRegExp || m_UseExcludeRegExp)) 
+    if (m_HandlerVerbose && passed.size() &&
+      (m_UseIncludeRegExp || m_UseExcludeRegExp))
       {
-      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, std::endl << "The following tests passed:" << std::endl);
+      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, std::endl
+        << "The following tests passed:" << std::endl);
       for(std::vector<cmStdString>::iterator j = passed.begin();
           j != passed.end(); ++j)
-        {   
+        {
         cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "\t" << *j << std::endl);
         }
       }
@@ -486,16 +494,18 @@ int cmCTestTestHandler::ProcessHandler()
       {
       percent = 99;
       }
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, std::endl << static_cast<int>(percent + .5) << "% tests passed, "
+    cmCTestLog(m_CTest, HANDLER_OUTPUT, std::endl
+      << static_cast<int>(percent + .5) << "% tests passed, "
       << failed.size() << " tests failed out of " << total << std::endl);
     //fprintf(stderr,"\n%.0f%% tests passed, %i tests failed out of %i\n",
     //  percent, int(failed.size()), total);
 
-    if (failed.size()) 
+    if (failed.size())
       {
       cmGeneratedFileStream ofs;
 
-      cmCTestLog(m_CTest, ERROR_MESSAGE, std::endl << "The following tests FAILED:" << std::endl);
+      cmCTestLog(m_CTest, ERROR_MESSAGE, std::endl
+        << "The following tests FAILED:" << std::endl);
       this->StartLogFile("TestsFailed", ofs);
 
       std::vector<cmCTestTestHandler::cmCTestTestResult>::iterator ftit;
@@ -505,9 +515,9 @@ int cmCTestTestHandler::ProcessHandler()
         if ( ftit->m_Status != cmCTestTestHandler::COMPLETED )
           {
           ofs << ftit->m_TestCount << ":" << ftit->m_Name << std::endl;
-          cmCTestLog(m_CTest, HANDLER_OUTPUT, "\t" << std::setw(3) << ftit->m_TestCount << " - " << ftit->m_Name.c_str() << " (" << this->GetTestStatus(ftit->m_Status) << ")" << std::endl);
-          //fprintf(stderr, "\t%3d - %s (%s)\n", ftit->m_TestCount, ftit->m_Name.c_str(),
-          //  this->GetTestStatus(ftit->m_Status));
+          cmCTestLog(m_CTest, HANDLER_OUTPUT, "\t" << std::setw(3)
+            << ftit->m_TestCount << " - " << ftit->m_Name.c_str() << " ("
+            << this->GetTestStatus(ftit->m_Status) << ")" << std::endl);
           }
         }
 
@@ -517,9 +527,11 @@ int cmCTestTestHandler::ProcessHandler()
   if ( m_CTest->GetProduceXML() )
     {
     cmGeneratedFileStream xmlfile;
-    if( !this->StartResultingXML((m_MemCheck ? "DynamicAnalysis" : "Test"), xmlfile) )
+    if( !this->StartResultingXML((m_MemCheck ? "DynamicAnalysis" : "Test"),
+        xmlfile) )
       {
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot create " << (m_MemCheck ? "memory check" : "testing")
+      cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot create "
+        << (m_MemCheck ? "memory check" : "testing")
         << " XML file" << std::endl);
       m_LogFile = 0;
       return 1;
@@ -543,7 +555,7 @@ int cmCTestTestHandler::ProcessHandler()
 }
 
 //----------------------------------------------------------------------
-void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed, 
+void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
                                           std::vector<cmStdString> &failed)
 {
   std::string current_dir = cmSystemTools::GetCurrentWorkingDirectory();
@@ -578,7 +590,7 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
     {
     this->ExpandTestsToRunInformation(inREcnt);
     }
-  
+
   int cnt = 0;
   inREcnt = 0;
   std::string last_directory = "";
@@ -599,7 +611,7 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
 
     if (!(last_directory == it->m_Directory))
       {
-      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Changing directory into " 
+      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Changing directory into "
         << it->m_Directory.c_str() << "\n");
       *m_LogFile << "Changing directory into: " << it->m_Directory.c_str()
         << std::endl;
@@ -608,12 +620,12 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
       }
     cres.m_Name = testname;
     cres.m_Path = it->m_Directory.c_str();
-    
+
     if (m_UseUnion)
       {
       // if it is not in the list and not in the regexp then skip
-      if ((m_TestsToRun.size() && 
-           std::find(m_TestsToRun.begin(), m_TestsToRun.end(), cnt) 
+      if ((m_TestsToRun.size() &&
+           std::find(m_TestsToRun.begin(), m_TestsToRun.end(), cnt)
            == m_TestsToRun.end()) && !it->m_IsInBasedOnREOptions)
         {
         continue;
@@ -622,8 +634,8 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
     else
       {
       // is this test in the list of tests to run? If not then skip it
-      if ((m_TestsToRun.size() && 
-           std::find(m_TestsToRun.begin(), m_TestsToRun.end(), inREcnt) 
+      if ((m_TestsToRun.size() &&
+           std::find(m_TestsToRun.begin(), m_TestsToRun.end(), inREcnt)
            == m_TestsToRun.end()) || !it->m_IsInBasedOnREOptions)
         {
         continue;
@@ -654,11 +666,12 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
       {
       cmCTestLog(m_CTest, HANDLER_OUTPUT, outname.c_str());
       }
-    
+
     cmCTestLog(m_CTest, DEBUG, "Testing " << args[0].c_str() << " ... ");
     // find the test executable
     std::string actualCommand = this->FindTheExecutable(args[1].c_str());
-    std::string testCommand = cmSystemTools::ConvertToOutputPath(actualCommand.c_str());
+    std::string testCommand
+      = cmSystemTools::ConvertToOutputPath(actualCommand.c_str());
 
     // continue if we did not find the executable
     if (testCommand == "")
@@ -670,7 +683,7 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
       if ( !m_CTest->GetShowOnly() )
         {
         cres.m_FullCommandLine = actualCommand;
-        m_TestResults.push_back( cres ); 
+        m_TestResults.push_back( cres );
         failed.push_back(testname);
         continue;
         }
@@ -698,21 +711,23 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
     int retVal = 0;
 
 
-    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, std::endl << (m_MemCheck?"MemCheck":"Test") << " command: " << testCommand << std::endl);
-    *m_LogFile << cnt << "/" << tmsize 
+    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, std::endl
+      << (m_MemCheck?"MemCheck":"Test") << " command: " << testCommand
+      << std::endl);
+    *m_LogFile << cnt << "/" << tmsize
       << " Test: " << testname.c_str() << std::endl;
     *m_LogFile << "Command: ";
     std::vector<cmStdString>::size_type ll;
     for ( ll = 0; ll < arguments.size()-1; ll ++ )
       {
       *m_LogFile << "\"" << arguments[ll] << "\" ";
       }
-    *m_LogFile 
-      << std::endl 
-      << "Directory: " << it->m_Directory << std::endl 
-      << "\"" << testname.c_str() << "\" start time: " 
+    *m_LogFile
+      << std::endl
+      << "Directory: " << it->m_Directory << std::endl
+      << "\"" << testname.c_str() << "\" start time: "
       << m_CTest->CurrentTime() << std::endl
-      << "Output:" << std::endl 
+      << "Output:" << std::endl
       << "----------------------------------------------------------"
       << std::endl;
     int res = 0;
@@ -734,12 +749,12 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
       int seconds = static_cast<int>(ttime) % 60;
       char buffer[100];
       sprintf(buffer, "%02d:%02d:%02d", hours, minutes, seconds);
-      *m_LogFile 
+      *m_LogFile
         << "----------------------------------------------------------"
         << std::endl
-        << "\"" << testname.c_str() << "\" end time: " 
+        << "\"" << testname.c_str() << "\" end time: "
         << m_CTest->CurrentTime() << std::endl
-        << "\"" << testname.c_str() << "\" time elapsed: " 
+        << "\"" << testname.c_str() << "\" time elapsed: "
         << buffer << std::endl
         << "----------------------------------------------------------"
         << std::endl << std::endl;
@@ -783,8 +798,8 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
           }
         }
 
-      if (res == cmsysProcess_State_Exited && 
-          (retVal == 0 || it->m_RequiredRegularExpressions.size()) && 
+      if (res == cmsysProcess_State_Exited &&
+          (retVal == 0 || it->m_RequiredRegularExpressions.size()) &&
           !forceFail)
         {
         cmCTestLog(m_CTest, HANDLER_OUTPUT,   "   Passed");
@@ -839,7 +854,8 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
           }
         else if ( res == cmsysProcess_State_Error )
           {
-          cmCTestLog(m_CTest, HANDLER_OUTPUT, "***Bad command " << res << std::endl);
+          cmCTestLog(m_CTest, HANDLER_OUTPUT, "***Bad command " << res
+            << std::endl);
           cres.m_Status = cmCTestTestHandler::BAD_COMMAND;
           }
         else
@@ -869,18 +885,21 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
           {
           std::string dartString = m_DartStuff.match(1);
           cmSystemTools::ReplaceString(output, dartString.c_str(),"");
-          cres.m_RegressionImages = this->GenerateRegressionImages(dartString);
+          cres.m_RegressionImages
+            = this->GenerateRegressionImages(dartString);
           }
         }
       }
 
     if ( cres.m_Status == cmCTestTestHandler::COMPLETED )
       {
-      this->CleanTestOutput(output, static_cast<size_t>(m_CustomMaximumPassedTestOutputSize));
+      this->CleanTestOutput(output, static_cast<size_t>(
+          m_CustomMaximumPassedTestOutputSize));
       }
     else
       {
-      this->CleanTestOutput(output, static_cast<size_t>(m_CustomMaximumFailedTestOutputSize));
+      this->CleanTestOutput(output, static_cast<size_t>(
+          m_CustomMaximumFailedTestOutputSize));
       }
 
     cres.m_Output = output;
@@ -948,29 +967,34 @@ void cmCTestTestHandler::GenerateDartOutput(std::ostream& os)
         m_CTest->GetShortPathToFile(result->m_Path.c_str())) << "</Path>\n"
       << "\t\t<FullName>" << cmCTest::MakeXMLSafe(
         m_CTest->GetShortPathToFile(testPath.c_str())) << "</FullName>\n"
-      << "\t\t<FullCommandLine>" 
-      << cmCTest::MakeXMLSafe(result->m_FullCommandLine) 
+      << "\t\t<FullCommandLine>"
+      << cmCTest::MakeXMLSafe(result->m_FullCommandLine)
       << "</FullCommandLine>\n"
       << "\t\t<Results>" << std::endl;
     if ( result->m_Status != cmCTestTestHandler::NOT_RUN )
       {
-      if ( result->m_Status != cmCTestTestHandler::COMPLETED || result->m_ReturnValue )
+      if ( result->m_Status != cmCTestTestHandler::COMPLETED ||
+        result->m_ReturnValue )
         {
-        os << "\t\t\t<NamedMeasurement type=\"text/string\" name=\"Exit Code\"><Value>"
-          << this->GetTestStatus(result->m_Status) << "</Value></NamedMeasurement>\n"
-          << "\t\t\t<NamedMeasurement type=\"text/string\" name=\"Exit Value\"><Value>"
-          << result->m_ReturnValue << "</Value></NamedMeasurement>" << std::endl;
+        os << "\t\t\t<NamedMeasurement type=\"text/string\" "
+          "name=\"Exit Code\"><Value>"
+          << this->GetTestStatus(result->m_Status) << "</Value>"
+          "</NamedMeasurement>\n"
+          << "\t\t\t<NamedMeasurement type=\"text/string\" "
+          "name=\"Exit Value\"><Value>"
+          << result->m_ReturnValue << "</Value></NamedMeasurement>"
+          << std::endl;
         }
       os << result->m_RegressionImages;
       os << "\t\t\t<NamedMeasurement type=\"numeric/double\" "
         << "name=\"Execution Time\"><Value>"
         << result->m_ExecutionTime << "</Value></NamedMeasurement>\n";
-      os 
+      os
         << "\t\t\t<NamedMeasurement type=\"text/string\" "
         << "name=\"Completion Status\"><Value>"
         << result->m_CompletionStatus << "</Value></NamedMeasurement>\n";
       }
-    os 
+    os
       << "\t\t\t<Measurement>\n"
       << "\t\t\t\t<Value>";
     os << cmCTest::MakeXMLSafe(result->m_Output);
@@ -982,7 +1006,7 @@ void cmCTestTestHandler::GenerateDartOutput(std::ostream& os)
     }
 
   os << "\t<EndDateTime>" << m_EndTest << "</EndDateTime>\n"
-     << "<ElapsedMinutes>" 
+     << "<ElapsedMinutes>"
      << static_cast<int>(m_ElapsedTestingTime/6)/10.0
      << "</ElapsedMinutes>"
     << "</Testing>" << std::endl;
@@ -996,11 +1020,13 @@ int cmCTestTestHandler::ExecuteCommands(std::vector<cmStdString>& vec)
   for ( it = vec.begin(); it != vec.end(); ++it )
     {
     int retVal = 0;
-    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Run command: " << *it << std::endl);
-    if ( !cmSystemTools::RunSingleCommand(it->c_str(), 0, &retVal, 0, true /*m_Verbose*/) || 
-      retVal != 0 )
+    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Run command: " << *it
+      << std::endl);
+    if ( !cmSystemTools::RunSingleCommand(it->c_str(), 0, &retVal, 0, true
+        /*m_Verbose*/) || retVal != 0 )
       {
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "Problem running command: " << *it << std::endl);
+      cmCTestLog(m_CTest, ERROR_MESSAGE, "Problem running command: " << *it
+        << std::endl);
       return 0;
       }
     }
@@ -1017,9 +1043,10 @@ std::string cmCTestTestHandler::FindTheExecutable(const char *exe)
   std::string file;
 
   cmSystemTools::SplitProgramPath(exe, dir, file);
-  // first try to find the executable given a config type subdir if there is one
-  if(m_CTest->GetConfigType() != "" && 
-    ::TryExecutable(dir.c_str(), file.c_str(), &fullPath, 
+  // first try to find the executable given a config type subdir if there is
+  // one
+  if(m_CTest->GetConfigType() != "" &&
+    ::TryExecutable(dir.c_str(), file.c_str(), &fullPath,
       m_CTest->GetConfigType().c_str()))
     {
     return fullPath;
@@ -1088,7 +1115,8 @@ std::string cmCTestTestHandler::FindTheExecutable(const char *exe)
     dir += m_CTest->GetConfigType();
     dir += "/";
     dir += file;
-    cmSystemTools::Error("config type specified on the command line, but test executable not found.",
+    cmSystemTools::Error("config type specified on the command line, but "
+      "test executable not found.",
       dir.c_str());
     return "";
     }
@@ -1107,27 +1135,30 @@ void cmCTestTestHandler::GetListOfTests()
     {
     m_ExcludeTestsRegularExpression.compile(m_ExcludeRegExp.c_str());
     }
-  cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Constructing a list of tests" << std::endl);
+  cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Constructing a list of tests"
+    << std::endl);
   cmake cm;
   cmGlobalGenerator gg;
   gg.SetCMakeInstance(&cm);
   std::auto_ptr<cmLocalGenerator> lg(gg.CreateLocalGenerator());
   lg->SetGlobalGenerator(&gg);
   cmMakefile *mf = lg->GetMakefile();
-  mf->AddDefinition("CTEST_CONFIGURATION_TYPE", m_CTest->GetConfigType().c_str());
+  mf->AddDefinition("CTEST_CONFIGURATION_TYPE",
+    m_CTest->GetConfigType().c_str());
 
   // Add handler for ADD_TEST
   cmCTestAddTestCommand* newCom1 = new cmCTestAddTestCommand;
   newCom1->m_TestHandler = this;
   cm.AddCommand(newCom1);
 
-  // Add handler for SUBDIR 
+  // Add handler for SUBDIR
   cmCTestSubdirCommand* newCom2 = new cmCTestSubdirCommand;
   newCom2->m_TestHandler = this;
   cm.AddCommand(newCom2);
 
   // Add handler for SET_SOURCE_FILES_PROPERTIES
-  cmCTestSetTestsPropertiesCommand* newCom3 = new cmCTestSetTestsPropertiesCommand;
+  cmCTestSetTestsPropertiesCommand* newCom3
+    = new cmCTestSetTestsPropertiesCommand;
   newCom3->m_TestHandler = this;
   cm.AddCommand(newCom3);
 
@@ -1155,13 +1186,14 @@ void cmCTestTestHandler::GetListOfTests()
     {
     return;
     }
-  cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Done constructing a list of tests" << std::endl);
+  cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT,
+    "Done constructing a list of tests" << std::endl);
 }
 
 //----------------------------------------------------------------------
 void cmCTestTestHandler::UseIncludeRegExp()
 {
-  this->m_UseIncludeRegExp = true;  
+  this->m_UseIncludeRegExp = true;
 }
 
 //----------------------------------------------------------------------
@@ -1170,7 +1202,7 @@ void cmCTestTestHandler::UseExcludeRegExp()
   this->m_UseExcludeRegExp = true;
   this->m_UseExcludeRegExpFirst = this->m_UseIncludeRegExp ? false : true;
 }
-  
+
 //----------------------------------------------------------------------
 const char* cmCTestTestHandler::GetTestStatus(int status)
 {
@@ -1187,7 +1219,7 @@ const char* cmCTestTestHandler::GetTestStatus(int status)
     "Completed"
   };
 
-  if ( status < cmCTestTestHandler::NOT_RUN || 
+  if ( status < cmCTestTestHandler::NOT_RUN ||
        status > cmCTestTestHandler::COMPLETED )
     {
     return "No Status";
@@ -1202,7 +1234,7 @@ void cmCTestTestHandler::ExpandTestsToRunInformation(int numTests)
     {
     return;
     }
-  
+
   int start;
   int end = -1;
   double stride = -1;
@@ -1239,7 +1271,7 @@ void cmCTestTestHandler::ExpandTestsToRunInformation(int numTests)
     {
     end = numTests;
     }
-  
+
   // if the stride wasn't specified then it defaults to 1
   if(stride == -1)
     {
@@ -1260,7 +1292,7 @@ void cmCTestTestHandler::ExpandTestsToRunInformation(int numTests)
   // sort the array
   std::sort(m_TestsToRun.begin(), m_TestsToRun.end(), std::less<int>());
   // remove duplicates
-  std::vector<int>::iterator new_end = 
+  std::vector<int>::iterator new_end =
     std::unique(m_TestsToRun.begin(), m_TestsToRun.end());
   m_TestsToRun.erase(new_end, m_TestsToRun.end());
 }
@@ -1273,27 +1305,27 @@ std::string cmCTestTestHandler::GenerateRegressionImages(
   const std::string& xml)
 {
   cmsys::RegularExpression twoattributes(
-    "<DartMeasurement" 
-    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
-    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
+    "<DartMeasurement"
+    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\""
+    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\""
     SPACE_REGEX "*>([^<]*)</DartMeasurement>");
   cmsys::RegularExpression threeattributes(
-    "<DartMeasurement" 
-    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
-    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
-    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
+    "<DartMeasurement"
+    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\""
+    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\""
+    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\""
     SPACE_REGEX "*>([^<]*)</DartMeasurement>");
   cmsys::RegularExpression fourattributes(
-    "<DartMeasurement" 
-    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
-    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
-    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
-    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
+    "<DartMeasurement"
+    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\""
+    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\""
+    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\""
+    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\""
     SPACE_REGEX "*>([^<]*)</DartMeasurement>");
   cmsys::RegularExpression measurementfile(
-    "<DartMeasurementFile" 
-    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
-    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
+    "<DartMeasurementFile"
+    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\""
+    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\""
     SPACE_REGEX "*>([^<]*)</DartMeasurementFile>");
 
   cmOStringStream ostr;
@@ -1304,42 +1336,54 @@ std::string cmCTestTestHandler::GenerateRegressionImages(
     if ( twoattributes.find(cxml) )
       {
       ostr
-        << "\t\t\t<NamedMeasurement" 
-        << " " << twoattributes.match(1) << "=\"" << twoattributes.match(2) << "\""
-        << " " << twoattributes.match(3) << "=\"" << twoattributes.match(4) << "\""
-        << "><Value>" << twoattributes.match(5) 
-        << "</Value></NamedMeasurement>" 
+        << "\t\t\t<NamedMeasurement"
+        << " " << twoattributes.match(1) << "=\""
+        << twoattributes.match(2) << "\""
+        << " " << twoattributes.match(3) << "=\""
+        << twoattributes.match(4) << "\""
+        << "><Value>" << twoattributes.match(5)
+        << "</Value></NamedMeasurement>"
         << std::endl;
-      cxml.erase(twoattributes.start(), twoattributes.end() - twoattributes.start());
+      cxml.erase(twoattributes.start(),
+        twoattributes.end() - twoattributes.start());
       }
     else if ( threeattributes.find(cxml) )
       {
       ostr
-        << "\t\t\t<NamedMeasurement" 
-        << " " << threeattributes.match(1) << "=\"" << threeattributes.match(2) << "\""
-        << " " << threeattributes.match(3) << "=\"" << threeattributes.match(4) << "\""
-        << " " << threeattributes.match(5) << "=\"" << threeattributes.match(6) << "\""
-        << "><Value>" << threeattributes.match(7) 
-        << "</Value></NamedMeasurement>" 
+        << "\t\t\t<NamedMeasurement"
+        << " " << threeattributes.match(1) << "=\""
+        << threeattributes.match(2) << "\""
+        << " " << threeattributes.match(3) << "=\""
+        << threeattributes.match(4) << "\""
+        << " " << threeattributes.match(5) << "=\""
+        << threeattributes.match(6) << "\""
+        << "><Value>" << threeattributes.match(7)
+        << "</Value></NamedMeasurement>"
         << std::endl;
-      cxml.erase(threeattributes.start(), threeattributes.end() - threeattributes.start());
+      cxml.erase(threeattributes.start(),
+        threeattributes.end() - threeattributes.start());
       }
     else if ( fourattributes.find(cxml) )
       {
       ostr
-        << "\t\t\t<NamedMeasurement" 
-        << " " << fourattributes.match(1) << "=\"" << fourattributes.match(2) << "\""
-        << " " << fourattributes.match(3) << "=\"" << fourattributes.match(4) << "\""
-        << " " << fourattributes.match(5) << "=\"" << fourattributes.match(6) << "\""
-        << " " << fourattributes.match(7) << "=\"" << fourattributes.match(8) << "\""
-        << "><Value>" << fourattributes.match(9) 
-        << "</Value></NamedMeasurement>" 
+        << "\t\t\t<NamedMeasurement"
+        << " " << fourattributes.match(1) << "=\""
+        << fourattributes.match(2) << "\""
+        << " " << fourattributes.match(3) << "=\""
+        << fourattributes.match(4) << "\""
+        << " " << fourattributes.match(5) << "=\""
+        << fourattributes.match(6) << "\""
+        << " " << fourattributes.match(7) << "=\""
+        << fourattributes.match(8) << "\""
+        << "><Value>" << fourattributes.match(9)
+        << "</Value></NamedMeasurement>"
         << std::endl;
-      cxml.erase(fourattributes.start(), fourattributes.end() - fourattributes.start());
+      cxml.erase(fourattributes.start(),
+        fourattributes.end() - fourattributes.start());
       }
     else if ( measurementfile.find(cxml) )
       {
-      const std::string& filename = 
+      const std::string& filename =
         cmCTest::CleanString(measurementfile.match(5));
       if ( cmSystemTools::FileExists(filename.c_str()) )
         {
@@ -1357,34 +1401,38 @@ std::string cmCTestTestHandler::GenerateRegressionImages(
           if ( cmSystemTools::LowerCase(k2) == "type" )
             {
             v2 = "text/string";
-            }          
-          
+            }
+
           ostr
-            << "\t\t\t<NamedMeasurement" 
+            << "\t\t\t<NamedMeasurement"
             << " " << k1 << "=\"" << v1 << "\""
             << " " << k2 << "=\"" << v2 << "\""
             << " encoding=\"none\""
-            << "><Value>Image " << filename.c_str() 
+            << "><Value>Image " << filename.c_str()
             << " is empty</Value></NamedMeasurement>";
           }
         else
           {
-          std::ifstream ifs(filename.c_str(), std::ios::in 
+          std::ifstream ifs(filename.c_str(), std::ios::in
 #ifdef _WIN32
                             | std::ios::binary
 #endif
             );
           unsigned char *file_buffer = new unsigned char [ len + 1 ];
           ifs.read(reinterpret_cast<char*>(file_buffer), len);
-          unsigned char *encoded_buffer = new unsigned char [ static_cast<int>(len * 1.5 + 5) ];
-          
-          unsigned long rlen = cmsysBase64_Encode(file_buffer, len, encoded_buffer, 1);
+          unsigned char *encoded_buffer
+            = new unsigned char [ static_cast<int>(len * 1.5 + 5) ];
+
+          unsigned long rlen
+            = cmsysBase64_Encode(file_buffer, len, encoded_buffer, 1);
           unsigned long cc;
-          
+
           ostr
-            << "\t\t\t<NamedMeasurement" 
-          << " " << measurementfile.match(1) << "=\"" << measurementfile.match(2) << "\""
-            << " " << measurementfile.match(3) << "=\"" << measurementfile.match(4) << "\""
+            << "\t\t\t<NamedMeasurement"
+            << " " << measurementfile.match(1) << "=\""
+            << measurementfile.match(2) << "\""
+            << " " << measurementfile.match(3) << "=\""
+            << measurementfile.match(4) << "\""
             << " encoding=\"base64\""
             << ">" << std::endl << "\t\t\t\t<Value>";
           for ( cc = 0; cc < rlen; cc ++ )
@@ -1396,7 +1444,7 @@ std::string cmCTestTestHandler::GenerateRegressionImages(
               }
             }
           ostr
-            << "</Value>" << std::endl << "\t\t\t</NamedMeasurement>" 
+            << "</Value>" << std::endl << "\t\t\t</NamedMeasurement>"
             << std::endl;
           delete [] file_buffer;
           delete [] encoded_buffer;
@@ -1410,14 +1458,17 @@ std::string cmCTestTestHandler::GenerateRegressionImages(
           idx = 2;
           }
         ostr
-          << "\t\t\t<NamedMeasurement" 
+          << "\t\t\t<NamedMeasurement"
           << " name=\"" << measurementfile.match(idx) << "\""
           << " text=\"text/string\""
-          << "><Value>File " << filename.c_str() << " not found</Value></NamedMeasurement>" 
+          << "><Value>File " << filename.c_str()
+          << " not found</Value></NamedMeasurement>"
           << std::endl;
-        cmCTestLog(m_CTest, HANDLER_OUTPUT, "File \"" << filename.c_str() << "\" not found." << std::endl);
+        cmCTestLog(m_CTest, HANDLER_OUTPUT, "File \"" << filename.c_str()
+          << "\" not found." << std::endl);
         }
-      cxml.erase(measurementfile.start(), measurementfile.end() - measurementfile.start());
+      cxml.erase(measurementfile.start(),
+        measurementfile.end() - measurementfile.start());
       }
     else
       {
@@ -1447,7 +1498,8 @@ void cmCTestTestHandler::SetTestsToRunInformation(const char* in)
     return;
     }
   this->TestsToRunString = in;
-  // if the argument is a file, then read it and use the contents as the string
+  // if the argument is a file, then read it and use the contents as the
+  // string
   if(cmSystemTools::FileExists(in))
     {
     std::ifstream fin(in);
@@ -1460,7 +1512,8 @@ void cmCTestTestHandler::SetTestsToRunInformation(const char* in)
 }
 
 //----------------------------------------------------------------------
-bool cmCTestTestHandler::CleanTestOutput(std::string& output, size_t remove_threshold)
+bool cmCTestTestHandler::CleanTestOutput(std::string& output,
+  size_t remove_threshold)
 {
   if ( remove_threshold == 0 )
     {
@@ -1512,15 +1565,17 @@ bool cmCTestTestHandler::CleanTestOutput(std::string& output, size_t remove_thre
     }
   if ( skipped )
     {
-    ostr << "..." << std::endl << "The rest of the test output was removed since it exceeds the threshold of "
+    ostr << "..." << std::endl << "The rest of the test output was removed "
+      "since it exceeds the threshold of "
       << remove_threshold << " characters." << std::endl;
     }
   output = ostr.str();
   return true;
 }
 
 //----------------------------------------------------------------------
-bool cmCTestTestHandler::SetTestsProperties(const std::vector<std::string>& args)
+bool cmCTestTestHandler::SetTestsProperties(
+  const std::vector<std::string>& args)
 {
   std::vector<std::string>::const_iterator it;
   std::vector<cmStdString> tests;
@@ -1567,7 +1622,8 @@ bool cmCTestTestHandler::SetTestsProperties(const std::vector<std::string>& args
             std::vector<std::string>::iterator crit;
             for ( crit = lval.begin(); crit != lval.end(); ++ crit )
               {
-              rtit->m_ErrorRegularExpressions.push_back(cmsys::RegularExpression(crit->c_str()));
+              rtit->m_ErrorRegularExpressions.push_back(
+                cmsys::RegularExpression(crit->c_str()));
               }
             }
           if ( key == "PASS_REGULAR_EXPRESSION" )
@@ -1577,7 +1633,8 @@ bool cmCTestTestHandler::SetTestsProperties(const std::vector<std::string>& args
             std::vector<std::string>::iterator crit;
             for ( crit = lval.begin(); crit != lval.end(); ++ crit )
               {
-              rtit->m_RequiredRegularExpressions.push_back(cmsys::RegularExpression(crit->c_str()));
+              rtit->m_RequiredRegularExpressions.push_back(
+                cmsys::RegularExpression(crit->c_str()));
               }
             }
           }
@@ -1601,7 +1658,7 @@ bool cmCTestTestHandler::AddTest(const std::vector<std::string>& args)
     {
     std::vector<cmStdString>::iterator it;
     bool found = false;
-    for ( it = m_CustomTestsIgnore.begin(); 
+    for ( it = m_CustomTestsIgnore.begin();
       it != m_CustomTestsIgnore.end(); ++ it )
       {
       if ( *it == testname )
@@ -1612,15 +1669,16 @@ bool cmCTestTestHandler::AddTest(const std::vector<std::string>& args)
       }
     if ( found )
       {
-      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Ignore memcheck: " << *it << std::endl);
+      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Ignore memcheck: "
+        << *it << std::endl);
       return true;
       }
     }
   else
     {
     std::vector<cmStdString>::iterator it;
     bool found = false;
-    for ( it = m_CustomTestsIgnore.begin(); 
+    for ( it = m_CustomTestsIgnore.begin();
       it != m_CustomTestsIgnore.end(); ++ it )
       {
       if ( *it == testname )
@@ -1631,7 +1689,8 @@ bool cmCTestTestHandler::AddTest(const std::vector<std::string>& args)
       }
     if ( found )
       {
-      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Ignore test: " << *it << std::endl);
+      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Ignore test: "
+        << *it << std::endl);
       return true;
       }
     }
@@ -1642,7 +1701,8 @@ bool cmCTestTestHandler::AddTest(const std::vector<std::string>& args)
   test.m_Directory = cmSystemTools::GetCurrentWorkingDirectory();
   test.m_IsInBasedOnREOptions = true;
   test.m_WillFail = false;
-  if (this->m_UseIncludeRegExp && !m_IncludeTestsRegularExpression.find(testname.c_str()))
+  if (this->m_UseIncludeRegExp &&
+    !m_IncludeTestsRegularExpression.find(testname.c_str()))
     {
     test.m_IsInBasedOnREOptions = false;
     }