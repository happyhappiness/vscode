@@ -14,10 +14,34 @@
      PURPOSE.  See the above copyright notices for more information.
 
 =========================================================================*/
-#include <stdio.h>
 #include "ctest.h"
 #include "cmRegularExpression.h"
 #include "cmSystemTools.h"
+
+#include <stdio.h>
+#include <time.h>
+
+static std::string CleanString(std::string str)
+{
+  std::string::size_type spos = str.find_first_not_of(" \n\t");
+  std::string::size_type epos = str.find_last_not_of(" \n\t");
+  if ( spos == str.npos )
+    {
+    return std::string();
+    }
+  if ( epos != str.npos )
+    {
+    epos ++;
+    }
+  return str.substr(spos, epos);
+}
+
+static std::string CurrentTime()
+{
+  time_t currenttime = time(0);
+  return ::CleanString(ctime(&currenttime));
+}
+
 bool TryExecutable(const char *dir, const char *file,
                    std::string *fullPath, const char *subdir)
 {
@@ -50,6 +74,132 @@ bool TryExecutable(const char *dir, const char *file,
   return false;
 }
 
+ctest::ctest() 
+{ 
+  m_UseIncludeRegExp      = false;
+  m_UseExcludeRegExp      = false;
+  m_UseExcludeRegExpFirst = false;
+  m_Verbose               = false;
+  m_DartMode              = false;
+  int cc; 
+  for ( cc=0; cc < ctest::LAST_TEST; cc ++ )
+    {
+    m_Tests[cc] = 0;
+    }
+}
+
+void ctest::Initialize()
+{
+  m_ToplevelPath = cmSystemTools::GetCurrentWorkingDirectory();
+  // parse the dart test file
+  std::ifstream fin("DartConfiguration.tcl");
+  if(!fin)
+    {
+    return;
+    }
+
+  char buffer[1024];
+  while ( fin )
+    {
+    buffer[0] = 0;
+    fin.getline(buffer, 1023);
+    buffer[1023] = 0;
+    std::string line = ::CleanString(buffer);
+    while ( fin && (line[line.size()-1] == '\\') )
+      {
+      line = line.substr(0, line.size()-1);
+      buffer[0] = 0;
+      fin.getline(buffer, 1023);
+      buffer[1023] = 0;
+      line += ::CleanString(buffer);
+      }
+    if ( line[0] == '#' )
+      {
+      continue;
+      }
+    if ( line.size() == 0 )
+      {
+      continue;
+      }
+    std::string::size_type cpos = line.find_first_of(":");
+    if ( cpos == line.npos )
+      {
+      continue;
+      }
+    std::string key = line.substr(0, cpos);
+    std::string value = ::CleanString(line.substr(cpos+1, line.npos));
+    m_DartConfiguration[key] = value;
+    }
+  fin.close();
+}
+
+bool ctest::SetTest(const char* ttype)
+{
+  if ( cmSystemTools::LowerCase(ttype) == "all" )
+    {
+    m_Tests[ctest::ALL_TEST] = 1;
+    }
+  else if ( cmSystemTools::LowerCase(ttype) == "update" )
+    {
+    m_Tests[ctest::UPDATE_TEST] = 1;
+    }
+  else if ( cmSystemTools::LowerCase(ttype) == "build" )
+    {
+    m_Tests[ctest::BUILD_TEST] = 1;
+    }
+  else if ( cmSystemTools::LowerCase(ttype) == "test" )
+    {
+    m_Tests[ctest::TEST_TEST] = 1;
+    }
+  else if ( cmSystemTools::LowerCase(ttype) == "coverage" )
+    {
+    m_Tests[ctest::COVERAGE_TEST] = 1;
+    }
+  else if ( cmSystemTools::LowerCase(ttype) == "purify" )
+    {
+    m_Tests[ctest::PURIFY_TEST] = 1;
+    }
+  else
+    {
+    std::cerr << "Don't know about test \"" << ttype << "\" yet..." << std::endl;
+    return false;
+    }
+  return true;
+}
+
+void ctest::Finalize()
+{
+  if ( m_DartMode )
+    {
+    std::string testingDir = m_ToplevelPath + "/Testing/CDart";
+    if ( cmSystemTools::FileExists(testingDir.c_str()) )
+      {
+      if ( !cmSystemTools::FileIsDirectory(testingDir.c_str()) )
+        {
+        std::cerr << "File " << testingDir << " is in the place of the testing directory"
+                  << std::endl;
+        return;
+        }
+      }
+    else
+      {
+      if ( !cmSystemTools::MakeDirectory(testingDir.c_str()) )
+        {
+        std::cerr << "Cannot create directory " << testingDir
+                  << std::endl;
+        return;
+        }
+      }
+    std::string testxml = testingDir + "/Test.xml";
+    ofstream ofs(testxml.c_str());
+    if( !ofs )
+      {
+      std::cerr << "Cannot create testing XML file" << std::endl;
+      return;
+      }
+    this->GenerateDartOutput(ofs);
+    }
+}
 
 std::string ctest::FindExecutable(const char *exe)
 {
@@ -115,6 +265,52 @@ std::string ctest::FindExecutable(const char *exe)
   return fullPath;
 }
 
+void ctest::UpdateDirectory()
+{
+  std::string cvsCommand = m_DartConfiguration["CVSCommand"];
+  if ( cvsCommand.size() == 0 )
+    {
+    std::cerr << "Cannot find CVSCommand key in the DartConfiguration.tcl" << std::endl;
+    return;
+    }
+  std::string cvsOptions = m_DartConfiguration["CVSUpdateOptions"];
+  if ( cvsOptions.size() == 0 )
+    {
+    std::cerr << "Cannot find CVSUpdateOptions key in the DartConfiguration.tcl" << std::endl;
+    return;
+    }
+
+  std::string command = cvsCommand + " update " + cvsOptions;
+
+  std::string output;
+  int retVal;
+  bool res = cmSystemTools::RunCommand(command.c_str(), output, 
+                                       retVal, 0, true);
+  if (! res || retVal )
+    {
+    std::cerr << "Error(s) when updating the project" << std::endl;
+    }
+}
+
+void ctest::BuildDirectory()
+{
+  std::string makeCommand = m_DartConfiguration["MakeCommand"];
+  if ( makeCommand.size() == 0 )
+    {
+    std::cerr << "Cannot find MakeCommand key in the DartConfiguration.tcl" << std::endl;
+    return;
+    }
+  std::string output;
+  int retVal;
+  bool res = cmSystemTools::RunCommand(makeCommand.c_str(), output, 
+                                       retVal, 0, true);
+  if (! res || retVal )
+    {
+    std::cerr << "Error(s) when building project" << std::endl;
+    }
+  // To do:
+  // Add parsing of output for errors and warnings.
+}
 
 void ctest::ProcessDirectory(std::vector<std::string> &passed, 
                              std::vector<std::string> &failed)
@@ -144,7 +340,7 @@ void ctest::ProcessDirectory(std::vector<std::string> &passed,
   while ( fin )
     {
     if(cmSystemTools::ParseFunction(fin, name, args, "DartTestfile.txt",
-				    parseError))
+                                    parseError))
       {
       if (name == "SUBDIRS")
         {
@@ -182,18 +378,22 @@ void ctest::ProcessDirectory(std::vector<std::string> &passed,
           {
           continue;
           }
+
+        cmCTestTestResult cres;
+
         if (firstTest)
           {
           std::string nwd = cmSystemTools::GetCurrentWorkingDirectory();
           std::cerr << "Changing directory into " << nwd.c_str() << "\n";
           firstTest = 0;
           }
+        cres.m_Name = args[0];
         fprintf(stderr,"Testing %-30s ",args[0].c_str());
         fflush(stderr);
         //std::cerr << "Testing " << args[0] << " ... ";
         // find the test executable
         std::string testCommand = 
-			cmSystemTools::EscapeSpaces(this->FindExecutable(args[1].c_str()).c_str());
+          cmSystemTools::EscapeSpaces(this->FindExecutable(args[1].c_str()).c_str());
         // continue if we did not find the executable
         if (testCommand == "")
           {
@@ -202,7 +402,7 @@ void ctest::ProcessDirectory(std::vector<std::string> &passed,
           continue;
           }
         
-	testCommand = cmSystemTools::ConvertToOutputPath(testCommand.c_str());
+        testCommand = cmSystemTools::ConvertToOutputPath(testCommand.c_str());
         // add the arguments
         std::vector<std::string>::iterator j = args.begin();
         ++j;
@@ -217,8 +417,19 @@ void ctest::ProcessDirectory(std::vector<std::string> &passed,
          */
         std::string output;
         int retVal;
-        if (!cmSystemTools::RunCommand(testCommand.c_str(), output, 
-                                       retVal, 0, false) || retVal != 0)
+
+        clock_t clock_start, clock_finish;
+        double clocks_per_sec = (double)CLOCKS_PER_SEC;
+        clock_start = clock();
+
+        bool res = cmSystemTools::RunCommand(testCommand.c_str(), output, 
+                                             retVal, 0, false);
+        clock_finish = clock();
+
+        cres.m_ExecutionTime = (double)(clock_finish - clock_start) / clocks_per_sec;
+        cres.m_FullCommandLine = testCommand;
+
+        if (!res || retVal != 0)
           {
           fprintf(stderr,"***Failed\n");
           if (output != "")
@@ -252,21 +463,174 @@ void ctest::ProcessDirectory(std::vector<std::string> &passed,
             }
           passed.push_back(args[0]); 
           }
+        cres.m_Output = output;
+        cres.m_ReturnValue = retVal;
+        std::string nwd = cmSystemTools::GetCurrentWorkingDirectory();
+        if ( nwd.size() > m_ToplevelPath.size() )
+          {
+          nwd = "." + nwd.substr(m_ToplevelPath.size(), nwd.npos);
+          }
+        cres.m_Path = nwd;
+        cres.m_CompletionStatus = "Completed";
+        m_TestResults.push_back( cres );
         }
       }
     }
+}
+
+void ctest::GenerateDartOutput(std::ostream& os)
+{
+  if ( !m_DartMode )
+    {
+    return;
+    }
+
+  if ( m_TestResults.size() == 0 )
+    {
+    return;
+    }
+
+  time_t tctime = time(0);
+  struct tm *lctime = gmtime(&tctime);
+  char datestring[100];
+  sprintf(datestring, "%4d%02d%02d-%d%d",
+          lctime->tm_year + 1900,
+          lctime->tm_mon,
+          lctime->tm_mday,
+          lctime->tm_hour,
+          lctime->tm_min);
+
+  os << "Try to create dart output file" << std::endl;
+  os << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
+     << "<Site BuildName=\"" << m_DartConfiguration["BuildName"]
+     << "\" BuildStamp=\"" << datestring << "-Experimental\" Name=\""
+     << m_DartConfiguration["Site"] << "\">\n"
+     << "<Testing>\n"
+     << "  <StartDateTime>" << ::CurrentTime() << " </StartDateTime>\n"
+     << "  <TestList>\n";
+  tm_TestResultsVector::size_type cc;
+  for ( cc = 0; cc < m_TestResults.size(); cc ++ )
+    {
+    cmCTestTestResult *result = &m_TestResults[cc];
+    os << "    <Test>" << result->m_Path << "/" << result->m_Name 
+       << "</Test>" << std::endl;
+    }
+  os << "  </TestList>\n";
+  for ( cc = 0; cc < m_TestResults.size(); cc ++ )
+    {
+    cmCTestTestResult *result = &m_TestResults[cc];
+    os << "  <Test Status=\"" << (result->m_ReturnValue?"failed":"passed") 
+       << "\">\n"
+       << "    <Name>" << result->m_Name << "</Name>\n"
+       << "    <Path>" << result->m_Path << "</Path>\n"
+       << "    <FullName>" << result->m_Path << "/" << result->m_Name << "</FullName>\n"
+       << "    <FullCommandLine>" << result->m_FullCommandLine << "</FullCommandLine>\n"
+       << "    <Results>" << std::endl;
+    if ( result->m_ReturnValue )
+      {
+      os << "      <NamedMeasurement type=\"text/string\" name=\"Exit Code\"><Value>"
+         << "CHILDSTATUS" << "</Value></NamedMeasurement>\n"
+         << "      <NamedMeasurement type=\"text/string\" name=\"Exit Value\"><Value>"
+         << result->m_ReturnValue << "</Value></NamedMeasurement>" << std::endl;
+      }
+    os << "      <NamedMeasurement type=\"numeric/double\" "
+       << "name=\"Execution Time\"><Value>"
+       << result->m_ExecutionTime << "</Value></NamedMeasurement>\n"
+       << "      <NamedMeasurement type=\"text/string\" "
+       << "name=\"Completion Status\"><Value>"
+       << result->m_CompletionStatus << "</Value></NamedMeasurement>\n"
+       << "      <Measurement>\n"
+       << "        <Value>" << result->m_Output << "</value>\n"
+       << "      </Measurement>\n"
+       << "    </Results>\n"
+       << "  </Test>" << std::endl;
+    }
   
+  os << "<EndDateTime>" << ::CurrentTime() << "</EndDateTime>\n"
+     << "</Testing>\n"
+     << "</Site>" << std::endl;
+}
+
+int ctest::ProcessTests()
+{
+  int res = 0;
+  bool notest = true;
+  int cc;
+
+  for ( cc = 0; cc < LAST_TEST; cc ++ )
+    {
+    if ( m_Tests[cc] )
+      {
+      notest = false;
+      break;
+      }
+    }
+  if ( m_Tests[UPDATE_TEST] || m_Tests[ALL_TEST] )
+    {
+    this->UpdateDirectory();
+    }
+  if ( m_Tests[BUILD_TEST] || m_Tests[ALL_TEST] )
+    {
+    this->BuildDirectory();
+    }
+  if ( m_Tests[TEST_TEST] || m_Tests[ALL_TEST] || notest )
+    {
+    std::vector<std::string> passed;
+    std::vector<std::string> failed;
+    int total;
+
+    this->ProcessDirectory(passed, failed);
+
+    total = int(passed.size()) + int(failed.size());
+
+    if (total == 0)
+      {
+      std::cerr << "No tests were found!!!\n";
+      }
+    else
+      {
+      if (passed.size() && (m_UseIncludeRegExp || m_UseExcludeRegExp)) 
+        {
+        std::cerr << "\nThe following tests passed:\n";
+        for(std::vector<std::string>::iterator j = passed.begin();
+            j != passed.end(); ++j)
+          {   
+          std::cerr << "\t" << *j << "\n";
+          }
+        }
+
+      float percent = float(passed.size()) * 100.0f / total;
+      fprintf(stderr,"\n%.0f%% tests passed, %i tests failed out of %i\n",
+              percent, int(failed.size()), total);
+
+      if (failed.size()) 
+        {
+        std::cerr << "\nThe following tests FAILED:\n";
+        for(std::vector<std::string>::iterator j = failed.begin();
+            j != failed.end(); ++j)
+          {   
+          std::cerr << "\t" << *j << "\n";
+          }
+        }
+      }
+
+    res += int(failed.size());
+    }
+  if ( m_Tests[COVERAGE_TEST] || m_Tests[ALL_TEST] )
+    {
+    std::cerr << "Coverage test is not yet implemented" << std::endl;
+    }
+  if ( m_Tests[PURIFY_TEST] || m_Tests[ALL_TEST] )
+    {
+    std::cerr << "Purify test is not yet implemented" << std::endl;
+    }
+  return res;
 }
 
 
 // this is a test driver program for cmake.
 int main (int argc, char *argv[])
 {
-  std::vector<std::string> passed;
-  std::vector<std::string> failed;
-  int total;
-  
-
   ctest inst;
   
   // look at the args
@@ -293,6 +657,12 @@ int main (int argc, char *argv[])
       {
       inst.m_Verbose = true;
       }
+
+    if( ( arg.find("-T",0) == 0 || arg.find("--dart-mode",0) == 0 ) && (i < args.size() -1) )
+      {
+      inst.m_DartMode = true;
+      inst.SetTest(args[i+1].c_str());
+      }
     
     if(arg.find("-R",0) == 0 && i < args.size() - 1)
       {
@@ -328,39 +698,10 @@ int main (int argc, char *argv[])
     }
 
   // call process directory
-  inst.ProcessDirectory(passed, failed);
-  total = int(passed.size()) + int(failed.size());
+  inst.Initialize();
+  int res = inst.ProcessTests();
+  inst.Finalize();
 
-  if (total == 0)
-    {
-    std::cerr << "No tests were found!!!\n";
-    }
-  else
-    {
-    if (passed.size() && (inst.m_UseIncludeRegExp || inst.m_UseExcludeRegExp)) 
-      {
-      std::cerr << "\nThe following tests passed:\n";
-      for(std::vector<std::string>::iterator j = passed.begin();
-          j != passed.end(); ++j)
-        {   
-        std::cerr << "\t" << *j << "\n";
-        }
-      }
-
-    float percent = float(passed.size()) * 100.0f / total;
-    fprintf(stderr,"\n%.0f%% tests passed, %i tests failed out of %i\n",
-            percent, int(failed.size()), total);
-
-    if (failed.size()) 
-      {
-      std::cerr << "\nThe following tests FAILED:\n";
-      for(std::vector<std::string>::iterator j = failed.begin();
-          j != failed.end(); ++j)
-        {   
-        std::cerr << "\t" << *j << "\n";
-        }
-      }
-    }
-  
-  return int(failed.size());
+  return res;
 }
+