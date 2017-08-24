@@ -302,6 +302,8 @@ cmCTestTestHandler::cmCTestTestHandler()
   
   m_MemCheck = false;
 
+  m_LogFile = 0;
+
   m_DartStuff.compile("(<DartMeasurement.*/DartMeasurement[a-zA-Z]*>)");
 }
 
@@ -406,6 +408,10 @@ int cmCTestTestHandler::ProcessHandler()
     return -1;
     }
 
+  cmGeneratedFileStream mLogFile;
+  this->StartLogFile("Tests", mLogFile);
+  m_LogFile = &mLogFile;
+
   std::vector<cmStdString> passed;
   std::vector<cmStdString> failed;
   int total;
@@ -474,20 +480,24 @@ int cmCTestTestHandler::ProcessHandler()
       {
       cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot create " << (m_MemCheck ? "memory check" : "testing")
         << " XML file" << std::endl);
+      m_LogFile = 0;
       return 1;
       }
     this->GenerateDartOutput(xmlfile);
     }
 
   if ( ! this->PostProcessHandler() )
     {
+    m_LogFile = 0;
     return -1;
     }
 
   if ( !failed.empty() )
     {
+    m_LogFile = 0;
     return -1;
     }
+  m_LogFile = 0;
   return 0;
 }
 
@@ -501,23 +511,12 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
   this->GetListOfTests();
   tm_ListOfTests::size_type tmsize = m_TestList.size();
 
-  cmGeneratedFileStream ofs;
-  cmGeneratedFileStream *olog = 0;
-  if ( !m_CTest->GetShowOnly() && tmsize > 0 && 
-    this->StartResultingXML((m_MemCheck?"MemCheck":"Test"), ofs) )
-    {
-    olog = &ofs;
-    }
-
   m_StartTest = m_CTest->CurrentTime();
   double elapsed_time_start = cmSystemTools::GetTime();
 
-  if ( olog )
-    {
-    *olog << "Start testing: " << m_StartTest << std::endl
-      << "----------------------------------------------------------"
-      << std::endl;
-    }
+  *m_LogFile << "Start testing: " << m_StartTest << std::endl
+    << "----------------------------------------------------------"
+    << std::endl;
 
   // how many tests are in based on RegExp?
   int inREcnt = 0;
@@ -559,6 +558,8 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
       {
       cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Changing directory into " 
         << it->m_Directory.c_str() << "\n");
+      *m_LogFile << "Changing directory into: " << it->m_Directory.c_str()
+        << std::endl;
       last_directory = it->m_Directory;
       cmSystemTools::ChangeDirectory(it->m_Directory.c_str());
       }
@@ -590,6 +591,8 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
     cmCTestLog(m_CTest, HANDLER_OUTPUT, std::setw(3) << tmsize << " Testing ");
     std::string outname = testname;
     outname.resize(30, ' ');
+    *m_LogFile << cnt << "/" << tmsize << " Testing: " << testname
+      << std::endl;
 
     if ( m_CTest->GetShowOnly() )
       {
@@ -608,6 +611,8 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
     // continue if we did not find the executable
     if (testCommand == "")
       {
+      *m_LogFile << "Unable to find executable: " << args[1].c_str()
+        << std::endl;
       cmCTestLog(m_CTest, ERROR_MESSAGE, "Unable to find executable: "
         << args[1].c_str() << std::endl);
       if ( !m_CTest->GetShowOnly() )
@@ -642,45 +647,42 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
 
 
     cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, std::endl << (m_MemCheck?"MemCheck":"Test") << " command: " << testCommand << std::endl);
-    if ( olog )
+    *m_LogFile << cnt << "/" << tmsize 
+      << " Test: " << testname.c_str() << std::endl;
+    *m_LogFile << "Command: ";
+    std::vector<cmStdString>::size_type ll;
+    for ( ll = 0; ll < arguments.size()-1; ll ++ )
       {
-      *olog << cnt << "/" << tmsize 
-        << " Test: " << testname.c_str() << std::endl;
-      *olog << "Command: ";
-      std::vector<cmStdString>::size_type ll;
-      for ( ll = 0; ll < arguments.size()-1; ll ++ )
-        {
-        *olog << "\"" << arguments[ll] << "\" ";
-        }
-      *olog 
-        << std::endl 
-        << "Directory: " << it->m_Directory << std::endl 
-        << "\"" << testname.c_str() << "\" start time: " 
-        << m_CTest->CurrentTime() << std::endl
-        << "Output:" << std::endl 
-        << "----------------------------------------------------------"
-        << std::endl;
+      *m_LogFile << "\"" << arguments[ll] << "\" ";
       }
+    *m_LogFile 
+      << std::endl 
+      << "Directory: " << it->m_Directory << std::endl 
+      << "\"" << testname.c_str() << "\" start time: " 
+      << m_CTest->CurrentTime() << std::endl
+      << "Output:" << std::endl 
+      << "----------------------------------------------------------"
+      << std::endl;
     int res = 0;
     double clock_start, clock_finish;
     clock_start = cmSystemTools::GetTime();
 
     if ( !m_CTest->GetShowOnly() )
       {
-      res = m_CTest->RunTest(arguments, &output, &retVal, olog);
+      res = m_CTest->RunTest(arguments, &output, &retVal, m_LogFile);
       }
 
     clock_finish = cmSystemTools::GetTime();
 
-    if ( olog )
+    if ( m_LogFile )
       {
       double ttime = clock_finish - clock_start;
       int hours = static_cast<int>(ttime / (60 * 60));
       int minutes = static_cast<int>(ttime / 60) % 60;
       int seconds = static_cast<int>(ttime) % 60;
       char buffer[100];
       sprintf(buffer, "%02d:%02d:%02d", hours, minutes, seconds);
-      *olog 
+      *m_LogFile 
         << "----------------------------------------------------------"
         << std::endl
         << "\"" << testname.c_str() << "\" end time: " 
@@ -776,9 +778,9 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<cmStdString> &passed,
 
   m_EndTest = m_CTest->CurrentTime();
   m_ElapsedTestingTime = cmSystemTools::GetTime() - elapsed_time_start;
-  if ( olog )
+  if ( m_LogFile )
     {
-    *olog << "End testing: " << m_EndTest << std::endl;
+    *m_LogFile << "End testing: " << m_EndTest << std::endl;
     }
   cmSystemTools::ChangeDirectory(current_dir.c_str());
 }