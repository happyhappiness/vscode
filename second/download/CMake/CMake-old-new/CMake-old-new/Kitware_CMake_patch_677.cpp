@@ -20,7 +20,6 @@
 #include "cmLocalGenerator.h"
 #include "cmGlobalGenerator.h"
 #include <cmsys/Directory.hxx>
-#include "cmListFileCache.h"
 #include "cmGlob.h"
 
 #include "cmCTestSubmit.h"
@@ -1826,49 +1825,44 @@ void cmCTest::GenerateDartBuildOutput(std::ostream& os,
   this->EndXML(os);
 }
   
-void cmCTest::ProcessDirectory(cmCTest::tm_VectorOfStrings &passed, 
-                             cmCTest::tm_VectorOfStrings &failed,
-                             bool memcheck, std::ostream* logfile)
+void cmCTest::GetListOfTests(tm_ListOfTests* testlist, bool memcheck)
 {
   // does the DartTestfile.txt exist ?
   if(!cmSystemTools::FileExists("DartTestfile.txt"))
     {
     return;
     }
-  
+
   // parse the file
   std::ifstream fin("DartTestfile.txt");
   if(!fin)
     {
     return;
     }
 
-  int firstTest = 1;
-
   cmsys::RegularExpression ireg(this->m_IncludeRegExp.c_str());
   cmsys::RegularExpression ereg(this->m_ExcludeRegExp.c_str());
-  cmsys::RegularExpression dartStuff("(<DartMeasurement.*/DartMeasurement[a-zA-Z]*>)");
 
   cmListFileCache cache;
   cmListFile* listFile = cache.GetFileCache("DartTestfile.txt", false);
   for(std::vector<cmListFileFunction>::const_iterator f =
-        listFile->m_Functions.begin(); f != listFile->m_Functions.end(); ++f)
+    listFile->m_Functions.begin(); f != listFile->m_Functions.end(); ++f)
     {
     const cmListFileFunction& lff = *f;
     const std::string& name = lff.m_Name;
-    const std::vector<cmListFileArgument>& args = lff.m_Arguments;
+    const tm_VectorOfListFileArgs& args = lff.m_Arguments;
     if (name == "SUBDIRS")
       {
       std::string cwd = cmSystemTools::GetCurrentWorkingDirectory();
-      for(std::vector<cmListFileArgument>::const_iterator j = args.begin();
-          j != args.end(); ++j)
+      for(tm_VectorOfListFileArgs::const_iterator j = args.begin();
+        j != args.end(); ++j)
         {
         std::string nwd = cwd + "/";
         nwd += j->Value;
         if (cmSystemTools::FileIsDirectory(nwd.c_str()))
           {
           cmSystemTools::ChangeDirectory(nwd.c_str());
-          this->ProcessDirectory(passed, failed, memcheck, logfile);
+          this->GetListOfTests(testlist, memcheck);
           }
         }
       // return to the original directory
@@ -1877,9 +1871,10 @@ void cmCTest::ProcessDirectory(cmCTest::tm_VectorOfStrings &passed,
 
     if (name == "ADD_TEST")
       {
+      const std::string& testname = args[0].Value;
       if (this->m_UseExcludeRegExp &&
-          this->m_UseExcludeRegExpFirst &&
-          ereg.find(args[0].Value.c_str()))
+        this->m_UseExcludeRegExpFirst &&
+        ereg.find(testname.c_str()))
         {
         continue;
         }
@@ -1890,7 +1885,7 @@ void cmCTest::ProcessDirectory(cmCTest::tm_VectorOfStrings &passed,
         for ( it = m_CustomMemCheckIgnore.begin(); 
           it != m_CustomMemCheckIgnore.end(); ++ it )
           {
-          if ( *it == args[0].Value )
+          if ( *it == testname )
             {
             found = true;
             break;
@@ -1912,7 +1907,7 @@ void cmCTest::ProcessDirectory(cmCTest::tm_VectorOfStrings &passed,
         for ( it = m_CustomTestsIgnore.begin(); 
           it != m_CustomTestsIgnore.end(); ++ it )
           {
-          if ( *it == args[0].Value )
+          if ( *it == testname )
             {
             found = true;
             break;
@@ -1929,206 +1924,276 @@ void cmCTest::ProcessDirectory(cmCTest::tm_VectorOfStrings &passed,
         }
 
 
-      if (this->m_UseIncludeRegExp && !ireg.find(args[0].Value.c_str()))
+      if (this->m_UseIncludeRegExp && !ireg.find(testname.c_str()))
         {
         continue;
         }
       if (this->m_UseExcludeRegExp &&
         !this->m_UseExcludeRegExpFirst &&
-        ereg.find(args[0].Value.c_str()))
+        ereg.find(testname.c_str()))
         {
         continue;
         }
 
-      cmCTestTestResult cres;
-      cres.m_Status = cmCTest::NOT_RUN;
+      cmCTestTestProperties test;
+      test.Name = testname;
+      test.Args = args;
+      test.Directory = cmSystemTools::GetCurrentWorkingDirectory();
+      testlist->push_back(test);
+      }
+    }
+}
 
-      if (firstTest)
-        {
-        std::string nwd = cmSystemTools::GetCurrentWorkingDirectory();
-        if ( m_Verbose )
-          {
-          std::cerr << "Changing directory into " << nwd.c_str() << "\n";
-          }
-        firstTest = 0;
-        }
-      cres.m_Name = args[0].Value;
-      if ( m_ShowOnly )
-        {
-        std::cout << args[0].Value << std::endl;
-        }
-      else
+void cmCTest::ProcessDirectory(cmCTest::tm_VectorOfStrings &passed, 
+                             cmCTest::tm_VectorOfStrings &failed,
+                             bool memcheck)
+{
+  cmsys::RegularExpression dartStuff("(<DartMeasurement.*/DartMeasurement[a-zA-Z]*>)");
+  tm_ListOfTests testlist;
+  this->GetListOfTests(&testlist, memcheck);
+  tm_ListOfTests::size_type tmsize = testlist.size();
+
+  std::ofstream ofs;
+  std::ofstream *olog = 0;
+  if ( !m_ShowOnly && tmsize > 0 && 
+    this->OpenOutputFile("Temporary", 
+      (memcheck?"LastMemCheck.xml":"LastTest.log"), ofs) )
+    {
+    olog = &ofs;
+    }
+
+  m_StartTest = ::CurrentTime();
+
+  if ( olog )
+    {
+    *olog << "Start testing: " << m_StartTest << std::endl
+      << "----------------------------------------------------------"
+      << std::endl;
+    }
+
+  int cnt = 0;
+  tm_ListOfTests::iterator it;
+  std::string last_directory = "";
+  for ( it = testlist.begin(); it != testlist.end(); it ++ )
+    {
+    cnt ++;
+    const std::string& testname = it->Name;
+    tm_VectorOfListFileArgs& args = it->Args;
+    cmCTestTestResult cres;
+    cres.m_Status = cmCTest::NOT_RUN;
+
+    if (last_directory != it->Directory)
+      {
+      if ( m_Verbose )
         {
-        fprintf(stderr,"Testing %-30s ",args[0].Value.c_str());
-        fflush(stderr);
+        std::cerr << "Changing directory into " 
+          << it->Directory.c_str() << "\n";
         }
-      //std::cerr << "Testing " << args[0] << " ... ";
-      // find the test executable
-      std::string actualCommand = this->FindTheExecutable(args[1].Value.c_str());
-      std::string testCommand = cmSystemTools::ConvertToOutputPath(actualCommand.c_str());
-      std::string memcheckcommand = "";
-
-      // continue if we did not find the executable
-      if (testCommand == "")
+      last_directory = it->Directory;
+      }
+    cres.m_Name = testname;
+    if ( m_ShowOnly )
+      {
+      fprintf(stderr,"%3d/%3d Testing %-30s\n", cnt, tmsize, testname.c_str());
+      }
+    else
+      {
+      fprintf(stderr,"%3d/%3d Testing %-30s ", cnt, tmsize, testname.c_str());
+      fflush(stderr);
+      }
+    //std::cerr << "Testing " << args[0] << " ... ";
+    // find the test executable
+    std::string actualCommand = this->FindTheExecutable(args[1].Value.c_str());
+    std::string testCommand = cmSystemTools::ConvertToOutputPath(actualCommand.c_str());
+    std::string memcheckcommand = "";
+
+    // continue if we did not find the executable
+    if (testCommand == "")
+      {
+      std::cerr << "Unable to find executable: " <<
+        args[1].Value.c_str() << "\n";
+      if ( !m_ShowOnly )
         {
-        std::cerr << "Unable to find executable: " <<
-          args[1].Value.c_str() << "\n";
         m_TestResults.push_back( cres ); 
-        failed.push_back(args[0].Value);
+        failed.push_back(testname);
         continue;
         }
+      }
 
-      // add the arguments
-      std::vector<cmListFileArgument>::const_iterator j = args.begin();
-      ++j;
-      ++j;
-      std::vector<const char*> arguments;
-      if ( memcheck )
-        {
-        cmCTest::tm_VectorOfStrings::size_type pp;
-        arguments.push_back(m_MemoryTester.c_str());
-        memcheckcommand = m_MemoryTester;
-        for ( pp = 0; pp < m_MemoryTesterOptionsParsed.size(); pp ++ )
-          {
-          arguments.push_back(m_MemoryTesterOptionsParsed[pp].c_str());
-          memcheckcommand += " ";
-          memcheckcommand += cmSystemTools::EscapeSpaces(m_MemoryTesterOptionsParsed[pp].c_str());
-          }
-        }
-      arguments.push_back(actualCommand.c_str());
-      for(;j != args.end(); ++j)
+    // add the arguments
+    tm_VectorOfListFileArgs::const_iterator j = args.begin();
+    ++j;
+    ++j;
+    std::vector<const char*> arguments;
+    if ( memcheck )
+      {
+      cmCTest::tm_VectorOfStrings::size_type pp;
+      arguments.push_back(m_MemoryTester.c_str());
+      memcheckcommand = m_MemoryTester;
+      for ( pp = 0; pp < m_MemoryTesterOptionsParsed.size(); pp ++ )
         {
-        testCommand += " ";
-        testCommand += cmSystemTools::EscapeSpaces(j->Value.c_str());
-        arguments.push_back(j->Value.c_str());
+        arguments.push_back(m_MemoryTesterOptionsParsed[pp].c_str());
+        memcheckcommand += " ";
+        memcheckcommand += cmSystemTools::EscapeSpaces(m_MemoryTesterOptionsParsed[pp].c_str());
         }
-      arguments.push_back(0);
+      }
+    arguments.push_back(actualCommand.c_str());
+    for(;j != args.end(); ++j)
+      {
+      testCommand += " ";
+      testCommand += cmSystemTools::EscapeSpaces(j->Value.c_str());
+      arguments.push_back(j->Value.c_str());
+      }
+    arguments.push_back(0);
 
-      /**
-       * Run an executable command and put the stdout in output.
-       */
-      std::string output;
-      int retVal = 0;
+    /**
+     * Run an executable command and put the stdout in output.
+     */
+    std::string output;
+    int retVal = 0;
 
-      double clock_start, clock_finish;
-      clock_start = cmSystemTools::GetTime();
 
-      if ( m_Verbose )
-        {
-        std::cout << std::endl << (memcheck?"MemCheck":"Test") << " command: " << testCommand << std::endl;
-        if ( memcheck )
-          {
-          std::cout << "Memory check command: " << memcheckcommand << std::endl;
-          }
-        }
-      if ( logfile )
-        {
-        *logfile << "Command: ";
-        tm_VectorOfStrings::size_type ll;
-        for ( ll = 0; ll < arguments.size()-1; ll ++ )
-          {
-          *logfile << "\"" << arguments[ll] << "\" ";
-          }
-        *logfile 
-          << std::endl 
-          << "Directory: " << cmSystemTools::GetCurrentWorkingDirectory() << std::endl 
-          << "Output:" << std::endl 
-          << "----------------------------------------------------------"
-          << std::endl;
-        }
-      int res = 0;
-      if ( !m_ShowOnly )
+    if ( m_Verbose )
+      {
+      std::cout << std::endl << (memcheck?"MemCheck":"Test") << " command: " << testCommand << std::endl;
+      if ( memcheck )
         {
-        res = this->RunTest(arguments, &output, &retVal, logfile);
+        std::cout << "Memory check command: " << memcheckcommand << std::endl;
         }
-      if ( logfile )
+      }
+    if ( olog )
+      {
+      *olog << cnt << "/" << tmsize 
+        << " Test: " << testname.c_str() << std::endl;
+      *olog << "Command: ";
+      tm_VectorOfStrings::size_type ll;
+      for ( ll = 0; ll < arguments.size()-1; ll ++ )
         {
-        *logfile 
-          << "----------------------------------------------------------"
-          << std::endl << std::endl;
+        *olog << "\"" << arguments[ll] << "\" ";
         }
-      
-      clock_finish = cmSystemTools::GetTime();
+      *olog 
+        << std::endl 
+        << "Directory: " << it->Directory << std::endl 
+        << "\"" << testname.c_str() << "\" start time: " 
+        << ::CurrentTime() << std::endl
+        << "Output:" << std::endl 
+        << "----------------------------------------------------------"
+        << std::endl;
+      }
+    int res = 0;
+    double clock_start, clock_finish;
+    clock_start = cmSystemTools::GetTime();
+
+    if ( !m_ShowOnly )
+      {
+      res = this->RunTest(arguments, &output, &retVal, olog);
+      }
 
-      cres.m_ExecutionTime = (double)(clock_finish - clock_start);
-      cres.m_FullCommandLine = testCommand;
+    clock_finish = cmSystemTools::GetTime();
 
-      if ( !m_ShowOnly )
+    if ( olog )
+      {
+      double ttime = clock_finish - clock_start;
+      int hours = static_cast<int>(ttime / (60 * 60));
+      int minutes = static_cast<int>(ttime / 60) % 60;
+      int seconds = static_cast<int>(ttime) % 60;
+      char buffer[100];
+      sprintf(buffer, "%02d:%02d:%02d", hours, minutes, seconds);
+      *olog 
+        << "----------------------------------------------------------"
+        << std::endl
+        << "\"" << testname.c_str() << "\" end time: " 
+        << ::CurrentTime() << std::endl
+        << "\"" << testname.c_str() << "\" time elapsed: " 
+        << buffer << std::endl
+        << "----------------------------------------------------------"
+        << std::endl << std::endl;
+      }
+
+    cres.m_ExecutionTime = (double)(clock_finish - clock_start);
+    cres.m_FullCommandLine = testCommand;
+
+    if ( !m_ShowOnly )
+      {
+      if (res == cmsysProcess_State_Exited && retVal == 0)
+        {
+        fprintf(stderr,"   Passed\n");
+        passed.push_back(testname);
+        cres.m_Status = cmCTest::COMPLETED;
+        }
+      else
         {
-        if (res == cmsysProcess_State_Exited && retVal == 0)
+        cres.m_Status = cmCTest::FAILED;
+        if ( res == cmsysProcess_State_Expired )
           {
-          fprintf(stderr,"   Passed\n");
-          passed.push_back(args[0].Value);
-          cres.m_Status = cmCTest::COMPLETED;
+          fprintf(stderr,"***Timeout\n");
+          cres.m_Status = cmCTest::TIMEOUT;
           }
-        else
+        else if ( res == cmsysProcess_State_Exception )
           {
-          cres.m_Status = cmCTest::FAILED;
-          if ( res == cmsysProcess_State_Expired )
-            {
-            fprintf(stderr,"***Timeout\n");
-            cres.m_Status = cmCTest::TIMEOUT;
-            }
-          else if ( res == cmsysProcess_State_Exception )
+          fprintf(stderr,"***Exception: ");
+          switch ( retVal )
             {
-            fprintf(stderr,"***Exception: ");
-            switch ( retVal )
-              {
-            case cmsysProcess_Exception_Fault:
-              fprintf(stderr,"SegFault");
-              cres.m_Status = cmCTest::SEGFAULT;
-              break;
-            case cmsysProcess_Exception_Illegal:
-              fprintf(stderr,"Illegal");
-              cres.m_Status = cmCTest::ILLEGAL;
-              break;
-            case cmsysProcess_Exception_Interrupt:
-              fprintf(stderr,"Interrupt");
-              cres.m_Status = cmCTest::INTERRUPT;
-              break;
-            case cmsysProcess_Exception_Numerical:
-              fprintf(stderr,"Numerical");
-              cres.m_Status = cmCTest::NUMERICAL;
-              break;
-            default:
-              fprintf(stderr,"Other");
-              cres.m_Status = cmCTest::OTHER_FAULT;
-              }
-            fprintf(stderr,"\n");
-            }
-          else if ( res == cmsysProcess_State_Error )
-            {
-            fprintf(stderr,"***Bad command %d\n", res);
-            cres.m_Status = cmCTest::BAD_COMMAND;
-            }
-          else
-            {
-            fprintf(stderr,"***Failed\n");
+          case cmsysProcess_Exception_Fault:
+            fprintf(stderr,"SegFault");
+            cres.m_Status = cmCTest::SEGFAULT;
+            break;
+          case cmsysProcess_Exception_Illegal:
+            fprintf(stderr,"Illegal");
+            cres.m_Status = cmCTest::ILLEGAL;
+            break;
+          case cmsysProcess_Exception_Interrupt:
+            fprintf(stderr,"Interrupt");
+            cres.m_Status = cmCTest::INTERRUPT;
+            break;
+          case cmsysProcess_Exception_Numerical:
+            fprintf(stderr,"Numerical");
+            cres.m_Status = cmCTest::NUMERICAL;
+            break;
+          default:
+            fprintf(stderr,"Other");
+            cres.m_Status = cmCTest::OTHER_FAULT;
             }
-          failed.push_back(args[0].Value);
+          fprintf(stderr,"\n");
           }
-        if (output != "")
+        else if ( res == cmsysProcess_State_Error )
           {
-          if (dartStuff.find(output.c_str()))
-            {
-            std::string dartString = dartStuff.match(1);
-            cmSystemTools::ReplaceString(output, dartString.c_str(),"");
-            cres.m_RegressionImages = this->GenerateRegressionImages(dartString);
-            }
+          fprintf(stderr,"***Bad command %d\n", res);
+          cres.m_Status = cmCTest::BAD_COMMAND;
+          }
+        else
+          {
+          fprintf(stderr,"***Failed\n");
           }
+        failed.push_back(testname);
         }
-      cres.m_Output = output;
-      cres.m_ReturnValue = retVal;
-      std::string nwd = cmSystemTools::GetCurrentWorkingDirectory();
-      if ( nwd.size() > m_ToplevelPath.size() )
+      if (output != "")
         {
-        nwd = "." + nwd.substr(m_ToplevelPath.size(), nwd.npos);
+        if (dartStuff.find(output.c_str()))
+          {
+          std::string dartString = dartStuff.match(1);
+          cmSystemTools::ReplaceString(output, dartString.c_str(),"");
+          cres.m_RegressionImages = this->GenerateRegressionImages(dartString);
+          }
         }
-      cmSystemTools::ReplaceString(nwd, "\\", "/");
-      cres.m_Path = nwd;
-      cres.m_CompletionStatus = "Completed";
-      m_TestResults.push_back( cres );
       }
+    cres.m_Output = output;
+    cres.m_ReturnValue = retVal;
+    std::string nwd = cmSystemTools::GetCurrentWorkingDirectory();
+    if ( nwd.size() > m_ToplevelPath.size() )
+      {
+      nwd = "." + nwd.substr(m_ToplevelPath.size(), nwd.npos);
+      }
+    cmSystemTools::ReplaceString(nwd, "\\", "/");
+    cres.m_Path = nwd;
+    cres.m_CompletionStatus = "Completed";
+    m_TestResults.push_back( cres );
+    }
+
+  m_EndTest = ::CurrentTime();
+  if ( olog )
+    {
+    *olog << "End testing: " << m_EndTest << std::endl;
     }
 }
 
@@ -2255,15 +2320,7 @@ int cmCTest::TestDirectory(bool memcheck)
   cmCTest::tm_VectorOfStrings failed;
   int total;
 
-  std::ofstream ofs;
-  std::ofstream *olog = 0;
-  if ( this->OpenOutputFile("Temporary", (memcheck?"LastMemCheck.xml":"LastTest.log"), ofs) )
-    {
-    olog = &ofs;
-    }
-  m_StartTest = ::CurrentTime();
-  this->ProcessDirectory(passed, failed, memcheck, olog);
-  m_EndTest = ::CurrentTime();
+  this->ProcessDirectory(passed, failed, memcheck);
 
   total = int(passed.size()) + int(failed.size());
 