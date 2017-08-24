@@ -162,7 +162,8 @@ bool cmCTestCoverageHandler::StartCoverageLogFile(
   sprintf(covLogFilename, "CoverageLog-%d", logFileCount);
   cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Open file: "
     << covLogFilename << std::endl);
-  if (!this->StartResultingXML(covLogFilename, covLogFile) )
+  if(!this->StartResultingXML(cmCTest::PartCoverage,
+                              covLogFilename, covLogFile))
     {
     cmCTestLog(this->CTest, ERROR_MESSAGE, "Cannot open log file: "
       << covLogFilename << std::endl);
@@ -381,7 +382,7 @@ int cmCTestCoverageHandler::ProcessHandler()
   cmGeneratedFileStream covSumFile;
   cmGeneratedFileStream covLogFile;
 
-  if (!this->StartResultingXML("Coverage", covSumFile))
+  if(!this->StartResultingXML(cmCTest::PartCoverage, "Coverage", covSumFile))
     {
     cmCTestLog(this->CTest, ERROR_MESSAGE,
       "Cannot open coverage summary file." << std::endl);
@@ -1434,7 +1435,7 @@ int cmCTestCoverageHandler::RunBullseyeSourceSummary(
   std::ostream& tmpLog = *cont->OFS;
   // copen the Coverage.xml file in the Testing directory
   cmGeneratedFileStream covSumFile; 
-  if (!this->StartResultingXML("Coverage", covSumFile))
+  if(!this->StartResultingXML(cmCTest::PartCoverage, "Coverage", covSumFile))
     {
     cmCTestLog(this->CTest, ERROR_MESSAGE,
       "Cannot open coverage summary file." << std::endl);