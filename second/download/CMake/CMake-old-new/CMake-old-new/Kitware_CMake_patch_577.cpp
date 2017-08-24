@@ -39,16 +39,16 @@ cmCTestCoverageHandler::cmCTestCoverageHandler()
 //----------------------------------------------------------------------
 void cmCTestCoverageHandler::Initialize()
 {
+  this->Superclass::Initialize();
 }
 
 //----------------------------------------------------------------------
-bool cmCTestCoverageHandler::StartLogFile(cmGeneratedFileStream& covLogFile, int logFileCount)
+bool cmCTestCoverageHandler::StartCoverageLogFile(cmGeneratedFileStream& covLogFile, int logFileCount)
 {
   char covLogFilename[1024];
-  sprintf(covLogFilename, "CoverageLog-%d.xml", logFileCount);
+  sprintf(covLogFilename, "CoverageLog-%d", logFileCount);
   cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Open file: " << covLogFilename << std::endl);
-  if (!m_CTest->OpenOutputFile(m_CTest->GetCurrentTag(), 
-      covLogFilename, covLogFile, true))
+  if (!this->StartResultingXML(covLogFilename, covLogFile) )
     {
     cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot open log file: " << covLogFilename << std::endl);
     return false;
@@ -61,7 +61,7 @@ bool cmCTestCoverageHandler::StartLogFile(cmGeneratedFileStream& covLogFile, int
 }
 
 //----------------------------------------------------------------------
-void cmCTestCoverageHandler::EndLogFile(cmGeneratedFileStream& ostr, int logFileCount)
+void cmCTestCoverageHandler::EndCoverageLogFile(cmGeneratedFileStream& ostr, int logFileCount)
 {
   std::string local_end_time = m_CTest->CurrentTime();
   ostr << "\t<EndDateTime>" << local_end_time << "</EndDateTime>" << std::endl
@@ -161,7 +161,7 @@ int cmCTestCoverageHandler::ProcessHandler()
 
   cmGeneratedFileStream ofs;
   double elapsed_time_start = cmSystemTools::GetTime();
-  if ( !m_CTest->OpenOutputFile("Temporary", "LastCoverage.log", ofs) )
+  if ( !this->StartLogFile("Coverage", ofs) )
     {
     cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot create LastCoverage.log file" << std::endl);
     }
@@ -333,10 +333,9 @@ int cmCTestCoverageHandler::ProcessHandler()
   cmGeneratedFileStream covSumFile;
   cmGeneratedFileStream covLogFile;
 
-  if (!m_CTest->OpenOutputFile(m_CTest->GetCurrentTag(), 
-      "Coverage.xml", covSumFile, true))
+  if (!this->StartResultingXML("Coverage", covSumFile))
     {
-    cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot open coverage summary file: Coverage.xml" << std::endl);
+    cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot open coverage summary file." << std::endl);
 
     return -1;
     }
@@ -347,7 +346,7 @@ int cmCTestCoverageHandler::ProcessHandler()
   covSumFile << "<Coverage>" << std::endl
     << "\t<StartDateTime>" << coverage_start_time << "</StartDateTime>" << std::endl;
   int logFileCount = 0;
-  if ( !this->StartLogFile(covLogFile, logFileCount) )
+  if ( !this->StartCoverageLogFile(covLogFile, logFileCount) )
     {
     return -1;
     }
@@ -364,9 +363,9 @@ int cmCTestCoverageHandler::ProcessHandler()
     if ( cnt == 100 )
       {
       cnt = 0;
-      this->EndLogFile(covLogFile, logFileCount);
+      this->EndCoverageLogFile(covLogFile, logFileCount);
       logFileCount ++;
-      if ( !this->StartLogFile(covLogFile, logFileCount) )
+      if ( !this->StartCoverageLogFile(covLogFile, logFileCount) )
         {
         return -1;
         }
@@ -468,7 +467,7 @@ int cmCTestCoverageHandler::ProcessHandler()
       << "\t</File>" << std::endl;
     cnt ++;
     }
-  this->EndLogFile(covLogFile, logFileCount);
+  this->EndCoverageLogFile(covLogFile, logFileCount);
 
   int total_lines = total_tested + total_untested;
   float percent_coverage = 100 * SAFEDIV(static_cast<float>(total_tested),