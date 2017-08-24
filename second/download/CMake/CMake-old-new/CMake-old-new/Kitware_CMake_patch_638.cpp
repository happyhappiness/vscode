@@ -177,7 +177,7 @@ int cmCTestTestHandler::PreProcessHandler()
 {
   if ( !this->ExecuteCommands(m_CustomPreTest) )
     {
-    std::cerr << "Problem executing pre-test command(s)." << std::endl;
+    cmCTestLog(m_CTest, ERROR, "Problem executing pre-test command(s)." << std::endl);
     return 0;
     }
   return 1;
@@ -188,7 +188,7 @@ int cmCTestTestHandler::PostProcessHandler()
 {
   if ( !this->ExecuteCommands(m_CustomPostTest) )
     {
-    std::cerr << "Problem executing post-test command(s)." << std::endl;
+    cmCTestLog(m_CTest, ERROR, "Problem executing post-test command(s)." << std::endl);
     return 0;
     }
   return 1;
@@ -218,7 +218,7 @@ int cmCTestTestHandler::ProcessHandler()
 
   m_TestResults.clear();
 
-  std::cout << (m_MemCheck ? "Memory check" : "Test") << " project" << std::endl;
+  cmCTestLog(m_CTest, HANDLER_OUTPUT, (m_MemCheck ? "Memory check" : "Test") << " project" << std::endl);
   if ( ! this->PreProcessHandler() )
     {
     return -1;
@@ -236,19 +236,19 @@ int cmCTestTestHandler::ProcessHandler()
     {
     if ( !m_CTest->GetShowOnly() )
       {
-      std::cerr << "No tests were found!!!\n";
+      cmCTestLog(m_CTest, ERROR, "No tests were found!!!" << std::endl);
       }
     }
   else
     {
-    if (m_Verbose && passed.size() && 
+    if (m_HandlerVerbose && passed.size() && 
       (m_UseIncludeRegExp || m_UseExcludeRegExp)) 
       {
-      std::cerr << "\nThe following tests passed:\n";
+      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, std::endl << "The following tests passed:" << std::endl);
       for(std::vector<cmStdString>::iterator j = passed.begin();
           j != passed.end(); ++j)
         {   
-        std::cerr << "\t" << *j << "\n";
+        cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "\t" << *j << std::endl);
         }
       }
 
@@ -257,14 +257,16 @@ int cmCTestTestHandler::ProcessHandler()
       {
       percent = 99;
       }
-    fprintf(stderr,"\n%.0f%% tests passed, %i tests failed out of %i\n",
-      percent, int(failed.size()), total);
+    cmCTestLog(m_CTest, HANDLER_OUTPUT, std::endl << std::setprecision(0) << percent << "% tests passed, "
+      << failed.size() << " tests failed out of " << total << std::endl);
+    //fprintf(stderr,"\n%.0f%% tests passed, %i tests failed out of %i\n",
+    //  percent, int(failed.size()), total);
 
     if (failed.size()) 
       {
       cmGeneratedFileStream ofs;
 
-      std::cerr << "\nThe following tests FAILED:\n";
+      cmCTestLog(m_CTest, ERROR, std::endl << "The following tests FAILED:" << std::endl);
       m_CTest->OpenOutputFile("Temporary", "LastTestsFailed.log", ofs);
 
       std::vector<cmCTestTestHandler::cmCTestTestResult>::iterator ftit;
@@ -274,8 +276,9 @@ int cmCTestTestHandler::ProcessHandler()
         if ( ftit->m_Status != cmCTestTestHandler::COMPLETED )
           {
           ofs << ftit->m_TestCount << ":" << ftit->m_Name << std::endl;
-          fprintf(stderr, "\t%3d - %s (%s)\n", ftit->m_TestCount, ftit->m_Name.c_str(),
-            this->GetTestStatus(ftit->m_Status));
+          cmCTestLog(m_CTest, HANDLER_OUTPUT, "\t" << std::setw(3) << ftit->m_TestCount << " - " << ftit->m_Name.c_str() << " (" << this->GetTestStatus(ftit->m_Status) << ")" << std::endl);
+          //fprintf(stderr, "\t%3d - %s (%s)\n", ftit->m_TestCount, ftit->m_Name.c_str(),
+          //  this->GetTestStatus(ftit->m_Status));
           }
         }
 
@@ -288,8 +291,8 @@ int cmCTestTestHandler::ProcessHandler()
     if( !m_CTest->OpenOutputFile(m_CTest->GetCurrentTag(), 
         (m_MemCheck ? "DynamicAnalysis.xml" : "Test.xml"), xmlfile, true) )
       {
-      std::cerr << "Cannot create " << (m_MemCheck ? "memory check" : "testing")
-        << " XML file" << std::endl;
+      cmCTestLog(m_CTest, ERROR, "Cannot create " << (m_MemCheck ? "memory check" : "testing")
+        << " XML file" << std::endl);
       return 1;
       }
     this->GenerateDartOutput(xmlfile);
@@ -374,11 +377,8 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
 
     if (!(last_directory == it->m_Directory))
       {
-      if ( m_Verbose )
-        {
-        std::cerr << "Changing directory into " 
-          << it->m_Directory.c_str() << "\n";
-        }
+      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Changing directory into " 
+        << it->m_Directory.c_str() << "\n");
       last_directory = it->m_Directory;
       cmSystemTools::ChangeDirectory(it->m_Directory.c_str());
       }
@@ -405,34 +405,31 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
         continue;
         }
       }
-    
-    std::cerr.width(3);
-    std::cerr << cnt << "/";
-    std::cerr.width(3);
-    std::cerr << tmsize << " Testing ";
+
+    cmCTestLog(m_CTest, HANDLER_OUTPUT, std::setw(3) << cnt << "/");
+    cmCTestLog(m_CTest, HANDLER_OUTPUT, std::setw(3) << tmsize << " Testing ");
     std::string outname = testname;
     outname.resize(30, ' ');
 
     if ( m_CTest->GetShowOnly() )
       {
-      std::cerr << outname.c_str() << "\n";
+      cmCTestLog(m_CTest, HANDLER_OUTPUT, outname.c_str() << std::endl);
       }
     else
       {
-      std::cerr << outname.c_str();
-      std::cerr.flush();
+      cmCTestLog(m_CTest, HANDLER_OUTPUT, outname.c_str());
       }
     
-    //std::cerr << "Testing " << args[0] << " ... ";
+    cmCTestLog(m_CTest, DEBUG, "Testing " << args[0].Value.c_str() << " ... ");
     // find the test executable
     std::string actualCommand = this->FindTheExecutable(args[1].Value.c_str());
     std::string testCommand = cmSystemTools::ConvertToOutputPath(actualCommand.c_str());
 
     // continue if we did not find the executable
     if (testCommand == "")
       {
-      std::cerr << "Unable to find executable: " <<
-        args[1].Value.c_str() << "\n";
+      cmCTestLog(m_CTest, ERROR, "Unable to find executable: "
+        << args[1].Value.c_str() << std::endl);
       if ( !m_CTest->GetShowOnly() )
         {
         cres.m_FullCommandLine = actualCommand;
@@ -464,10 +461,7 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
     int retVal = 0;
 
 
-    if ( m_Verbose )
-      {
-      std::cout << std::endl << (m_MemCheck?"MemCheck":"Test") << " command: " << testCommand << std::endl;
-      }
+    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, std::endl << (m_MemCheck?"MemCheck":"Test") << " command: " << testCommand << std::endl);
     if ( olog )
       {
       *olog << cnt << "/" << tmsize 
@@ -524,7 +518,7 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
       {
       if (res == cmsysProcess_State_Exited && retVal == 0)
         {
-        std::cerr <<   "   Passed\n";
+        cmCTestLog(m_CTest, HANDLER_OUTPUT,   "   Passed" << std::endl);
         passed.push_back(testname);
         cres.m_Status = cmCTestTestHandler::COMPLETED;
         }
@@ -533,44 +527,44 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
         cres.m_Status = cmCTestTestHandler::FAILED;
         if ( res == cmsysProcess_State_Expired )
           {
-          std::cerr << "***Timeout\n";
+          cmCTestLog(m_CTest, HANDLER_OUTPUT, "***Timeout" << std::endl);
           cres.m_Status = cmCTestTestHandler::TIMEOUT;
           }
         else if ( res == cmsysProcess_State_Exception )
           {
-          std::cerr << "***Exception: ";
+          cmCTestLog(m_CTest, HANDLER_OUTPUT, "***Exception: ");
           switch ( retVal )
             {
           case cmsysProcess_Exception_Fault:
-            std::cerr << "SegFault";
+            cmCTestLog(m_CTest, HANDLER_OUTPUT, "SegFault");
             cres.m_Status = cmCTestTestHandler::SEGFAULT;
             break;
           case cmsysProcess_Exception_Illegal:
-            std::cerr << "Illegal";
+            cmCTestLog(m_CTest, HANDLER_OUTPUT, "Illegal");
             cres.m_Status = cmCTestTestHandler::ILLEGAL;
             break;
           case cmsysProcess_Exception_Interrupt:
-            std::cerr << "Interrupt";
+            cmCTestLog(m_CTest, HANDLER_OUTPUT, "Interrupt");
             cres.m_Status = cmCTestTestHandler::INTERRUPT;
             break;
           case cmsysProcess_Exception_Numerical:
-            std::cerr << "Numerical";
+            cmCTestLog(m_CTest, HANDLER_OUTPUT, "Numerical");
             cres.m_Status = cmCTestTestHandler::NUMERICAL;
             break;
           default:
-            std::cerr << "Other";
+            cmCTestLog(m_CTest, HANDLER_OUTPUT, "Other");
             cres.m_Status = cmCTestTestHandler::OTHER_FAULT;
             }
-           std::cerr << "\n";
+           cmCTestLog(m_CTest, HANDLER_OUTPUT, std::endl);
           }
         else if ( res == cmsysProcess_State_Error )
           {
-          std::cerr << "***Bad command " << res << "\n";
+          cmCTestLog(m_CTest, HANDLER_OUTPUT, "***Bad command " << res << std::endl);
           cres.m_Status = cmCTestTestHandler::BAD_COMMAND;
           }
         else
           {
-          std::cerr << "***Failed\n";
+          cmCTestLog(m_CTest, HANDLER_OUTPUT, "***Failed" << std::endl);
           }
         failed.push_back(testname);
         }
@@ -707,14 +701,11 @@ int cmCTestTestHandler::ExecuteCommands(std::vector<cmStdString>& vec)
   for ( it = vec.begin(); it != vec.end(); ++it )
     {
     int retVal = 0;
-    if ( m_Verbose )
-      {
-      std::cout << "Run command: " << *it << std::endl;
-      }
+    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Run command: " << *it << std::endl);
     if ( !cmSystemTools::RunSingleCommand(it->c_str(), 0, &retVal, 0, true /*m_Verbose*/) || 
       retVal != 0 )
       {
-      std::cerr << "Problem running command: " << *it << std::endl;
+      cmCTestLog(m_CTest, ERROR, "Problem running command: " << *it << std::endl);
       return 0;
       }
     }
@@ -874,10 +865,7 @@ void cmCTestTestHandler::GetListOfTests(tm_ListOfTests* testlist)
           }
         if ( found )
           {
-          if ( m_Verbose )
-            {
-            std::cout << "Ignore memcheck: " << *it << std::endl;
-            }
+          cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Ignore memcheck: " << *it << std::endl);
           continue;
           }
         }
@@ -896,10 +884,7 @@ void cmCTestTestHandler::GetListOfTests(tm_ListOfTests* testlist)
           }
         if ( found )
           {
-          if ( m_Verbose )
-            {
-            std::cout << "Ignore test: " << *it << std::endl;
-            }
+          cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Ignore test: " << *it << std::endl);
           continue;
           }
         }
@@ -1181,7 +1166,7 @@ std::string cmCTestTestHandler::GenerateRegressionImages(
           << " text=\"text/string\""
           << "><Value>File " << filename.c_str() << " not found</Value></NamedMeasurement>" 
           << std::endl;
-        std::cout << "File \"" << filename.c_str() << "\" not found." << std::endl;
+        cmCTestLog(m_CTest, HANDLER_OUTPUT, "File \"" << filename.c_str() << "\" not found." << std::endl);
         }
       cxml.erase(measurementfile.start(), measurementfile.end() - measurementfile.start());
       }