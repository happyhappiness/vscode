@@ -20,6 +20,7 @@
 #include "cmCTest.h"
 #include "cmake.h"
 #include "cmSystemTools.h"
+#include "cmGeneratedFileStream.h"
 #include "cmGlob.h"
 #include <cmsys/Process.h>
 #include <cmsys/RegularExpression.hxx>
@@ -38,13 +39,13 @@ cmCTestCoverageHandler::cmCTestCoverageHandler()
 }
 
 //----------------------------------------------------------------------
-bool cmCTestCoverageHandler::StartLogFile(std::ofstream& covLogFile, int logFileCount)
+bool cmCTestCoverageHandler::StartLogFile(cmGeneratedFileStream& covLogFile, int logFileCount)
 {
   char covLogFilename[1024];
   sprintf(covLogFilename, "CoverageLog-%d.xml", logFileCount);
   std::cout << "Open file: " << covLogFilename << std::endl;
   if (!m_CTest->OpenOutputFile(m_CTest->GetCurrentTag(), 
-      covLogFilename, covLogFile))
+      covLogFilename, covLogFile, true))
     {
     std::cerr << "Cannot open log file: " << covLogFilename << std::endl;
     return false;
@@ -57,7 +58,7 @@ bool cmCTestCoverageHandler::StartLogFile(std::ofstream& covLogFile, int logFile
 }
 
 //----------------------------------------------------------------------
-void cmCTestCoverageHandler::EndLogFile(std::ofstream& ostr, int logFileCount)
+void cmCTestCoverageHandler::EndLogFile(cmGeneratedFileStream& ostr, int logFileCount)
 {
   std::string local_end_time = m_CTest->CurrentTime();
   ostr << "\t<EndDateTime>" << local_end_time << "</EndDateTime>" << std::endl
@@ -324,11 +325,11 @@ int cmCTestCoverageHandler::CoverageDirectory(cmCTest *ctest_inst)
       }
     }
 
-  std::ofstream covSumFile;
-  std::ofstream covLogFile;
+  cmGeneratedFileStream covSumFile;
+  cmGeneratedFileStream covLogFile;
 
   if (!m_CTest->OpenOutputFile(m_CTest->GetCurrentTag(), 
-      "Coverage.xml", covSumFile))
+      "Coverage.xml", covSumFile, true))
     {
     std::cerr << "Cannot open coverage summary file: Coverage.xml" << std::endl;
     return 1;