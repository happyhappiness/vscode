@@ -50,17 +50,19 @@ bool cmCTestCoverageHandler::StartLogFile(std::ofstream& covLogFile, int logFile
     return false;
     }
   std::string local_start_time = m_CTest->CurrentTime();
+  m_CTest->StartXML(covLogFile);
   covLogFile << "<CoverageLog>" << std::endl
     << "\t<StartDateTime>" << local_start_time << "</StartDateTime>" << std::endl;
   return true;
 }
 
 //----------------------------------------------------------------------
-void cmCTestCoverageHandler::StopLogFile(std::ofstream& ostr, int logFileCount)
+void cmCTestCoverageHandler::EndLogFile(std::ofstream& ostr, int logFileCount)
 {
   std::string local_end_time = m_CTest->CurrentTime();
   ostr << "\t<EndDateTime>" << local_end_time << "</EndDateTime>" << std::endl
     << "</CoverageLog>" << std::endl;
+  m_CTest->EndXML(ostr);
   char covLogFilename[1024];
   sprintf(covLogFilename, "CoverageLog-%d.xml", logFileCount);
   std::cout << "Close file: " << covLogFilename << std::endl;
@@ -276,7 +278,6 @@ int cmCTestCoverageHandler::CoverageDirectory(cmCTest *ctest_inst)
             {
             std::cout << "   in file: " << fname << std::endl;
             }
-          singleFileCoverageVector cov;
           std::ifstream ifile(fname.c_str());
           if ( ! ifile )
             {
@@ -356,7 +357,7 @@ int cmCTestCoverageHandler::CoverageDirectory(cmCTest *ctest_inst)
     if ( cnt == 100 )
       {
       cnt = 0;
-      this->StopLogFile(covLogFile, logFileCount);
+      this->EndLogFile(covLogFile, logFileCount);
       logFileCount ++;
       if ( !this->StartLogFile(covLogFile, logFileCount) )
         {
@@ -396,7 +397,8 @@ int cmCTestCoverageHandler::CoverageDirectory(cmCTest *ctest_inst)
     const singleFileCoverageVector& fcov = fileIterator->second;
     covLogFile << "\t<File Name=\""
       << m_CTest->MakeXMLSafe(fileName.c_str())
-      << "\" FullPath=\"" << m_CTest->MakeXMLSafe(fileIterator->first) << "\">" << std::endl
+      << "\" FullPath=\"" << m_CTest->MakeXMLSafe(m_CTest->GetShortPathToFile(
+          fileIterator->first.c_str())) << "\">" << std::endl
       << "\t\t<Report>" << std::endl;
 
     std::ifstream ifs(fullFileName.c_str());
@@ -449,7 +451,8 @@ int cmCTestCoverageHandler::CoverageDirectory(cmCTest *ctest_inst)
     covLogFile << "\t\t</Report>" << std::endl
       << "\t</File>" << std::endl;
     covSumFile << "\t<File Name=\"" << m_CTest->MakeXMLSafe(fileName)
-      << "\" FullPath=\"" << m_CTest->MakeXMLSafe(fullFileName)
+      << "\" FullPath=\"" << m_CTest->MakeXMLSafe(
+        m_CTest->GetShortPathToFile(fullFileName.c_str()))
       << "\" Covered=\"" << (cmet>0?"true":"false") << "\">\n"
       << "\t\t<LOCTested>" << tested << "</LOCTested>\n"
       << "\t\t<LOCUnTested>" << untested << "</LOCUnTested>\n"
@@ -464,7 +467,7 @@ int cmCTestCoverageHandler::CoverageDirectory(cmCTest *ctest_inst)
       << "\t</File>" << std::endl;
     cnt ++;
     }
-  this->StopLogFile(covLogFile, logFileCount);
+  this->EndLogFile(covLogFile, logFileCount);
 
   int total_lines = total_tested + total_untested;
   float percent_coverage = 100 * SAFEDIV(static_cast<float>(total_tested),