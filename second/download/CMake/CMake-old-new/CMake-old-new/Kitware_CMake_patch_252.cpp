@@ -22,7 +22,7 @@
 #include "cmMakefile.h"
 #include "cmSystemTools.h"
 #include "cmGeneratedFileStream.h"
-#include "cmXMLSafe.h"
+#include "cmXMLWriter.h"
 
 #include <cmsys/Process.h>
 #include <cmsys/RegularExpression.hxx>
@@ -185,28 +185,13 @@ bool cmCTestCoverageHandler::StartCoverageLogFile(
       << covLogFilename << std::endl);
     return false;
     }
-  std::string local_start_time = this->CTest->CurrentTime();
-  this->CTest->StartXML(covLogFile, this->AppendXML);
-  covLogFile << "<CoverageLog>" << std::endl
-             << "\t<StartDateTime>" << local_start_time << "</StartDateTime>"
-             << "\t<StartTime>"
-             << static_cast<unsigned int>(cmSystemTools::GetTime())
-             << "</StartTime>"
-    << std::endl;
   return true;
 }
 
 //----------------------------------------------------------------------
 void cmCTestCoverageHandler::EndCoverageLogFile(cmGeneratedFileStream& ostr,
   int logFileCount)
 {
-  std::string local_end_time = this->CTest->CurrentTime();
-  ostr << "\t<EndDateTime>" << local_end_time << "</EndDateTime>" << std::endl
-       << "\t<EndTime>" <<
-       static_cast<unsigned int>(cmSystemTools::GetTime())
-       << "</EndTime>" << std::endl
-    << "</CoverageLog>" << std::endl;
-  this->CTest->EndXML(ostr);
   char covLogFilename[1024];
   sprintf(covLogFilename, "CoverageLog-%d.xml", logFileCount);
   cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Close file: "
@@ -215,6 +200,25 @@ void cmCTestCoverageHandler::EndCoverageLogFile(cmGeneratedFileStream& ostr,
 }
 
 //----------------------------------------------------------------------
+void cmCTestCoverageHandler::StartCoverageLogXML(cmXMLWriter& xml)
+{
+  this->CTest->StartXML(xml, this->AppendXML);
+  xml.StartElement("CoverageLog");
+  xml.Element("StartDateTime", this->CTest->CurrentTime());
+  xml.Element("StartTime",
+    static_cast<unsigned int>(cmSystemTools::GetTime()));
+}
+
+//----------------------------------------------------------------------
+void cmCTestCoverageHandler::EndCoverageLogXML(cmXMLWriter& xml)
+{
+  xml.Element("EndDateTime", this->CTest->CurrentTime());
+  xml.Element("EndTime", static_cast<unsigned int>(cmSystemTools::GetTime()));
+  xml.EndElement(); // CoverageLog
+  this->CTest->EndXML(xml);
+}
+
+//----------------------------------------------------------------------
 bool cmCTestCoverageHandler::ShouldIDoCoverage(const char* file,
   const char* srcDir,
   const char* binDir)
@@ -451,27 +455,30 @@ int cmCTestCoverageHandler::ProcessHandler()
     }
   cmGeneratedFileStream covSumFile;
   cmGeneratedFileStream covLogFile;
+  cmXMLWriter covSumXML(covSumFile);
+  cmXMLWriter covLogXML(covLogFile);
 
   if(!this->StartResultingXML(cmCTest::PartCoverage, "Coverage", covSumFile))
     {
     cmCTestLog(this->CTest, ERROR_MESSAGE,
       "Cannot open coverage summary file." << std::endl);
     return -1;
     }
+  covSumFile.setf(std::ios::fixed, std::ios::floatfield);
+  covSumFile.precision(2);
 
-  this->CTest->StartXML(covSumFile, this->AppendXML);
+  this->CTest->StartXML(covSumXML, this->AppendXML);
   // Produce output xml files
 
-  covSumFile << "<Coverage>" << std::endl
-    << "\t<StartDateTime>" << coverage_start_time << "</StartDateTime>"
-    << std::endl
-    << "\t<StartTime>" << coverage_start_time_time << "</StartTime>"
-    << std::endl;
+  covSumXML.StartElement("Coverage");
+  covSumXML.Element("StartDateTime", coverage_start_time);
+  covSumXML.Element("StartTime", coverage_start_time_time);
   int logFileCount = 0;
   if ( !this->StartCoverageLogFile(covLogFile, logFileCount) )
     {
     return -1;
     }
+  this->StartCoverageLogXML(covLogXML);
   cmCTestCoverageHandlerContainer::TotalCoverageMap::iterator fileIterator;
   int cnt = 0;
   long total_tested = 0;
@@ -528,12 +535,14 @@ int cmCTestCoverageHandler::ProcessHandler()
 
     if ( ++cnt % 100 == 0 )
       {
+      this->EndCoverageLogXML(covLogXML);
       this->EndCoverageLogFile(covLogFile, logFileCount);
       logFileCount ++;
       if ( !this->StartCoverageLogFile(covLogFile, logFileCount) )
         {
         return -1;
         }
+      this->StartCoverageLogXML(covLogXML);
       }
 
     const std::string fileName
@@ -542,9 +551,10 @@ int cmCTestCoverageHandler::ProcessHandler()
       this->CTest->GetShortPathToFile(fullFileName.c_str());
     const cmCTestCoverageHandlerContainer::SingleFileCoverageVector& fcov
       = fileIterator->second;
-    covLogFile << "\t<File Name=\"" << cmXMLSafe(fileName)
-      << "\" FullPath=\"" << cmXMLSafe(shortFileName) << "\">\n"
-      << "\t\t<Report>" << std::endl;
+    covLogXML.StartElement("File");
+    covLogXML.Attribute("Name", fileName);
+    covLogXML.Attribute("FullPath", shortFileName);
+    covLogXML.StartElement("Report");
 
     cmsys::ifstream ifs(fullFileName.c_str());
     if ( !ifs)
@@ -576,9 +586,11 @@ int cmCTestCoverageHandler::ProcessHandler()
         error ++;
         break;
         }
-      covLogFile << "\t\t<Line Number=\"" << cc << "\" Count=\"" << fcov[cc]
-        << "\">"
-        << cmXMLSafe(line) << "</Line>" << std::endl;
+      covLogXML.StartElement("Line");
+      covLogXML.Attribute("Number", cc);
+      covLogXML.Attribute("Count", fcov[cc]);
+      covLogXML.Content(line);
+      covLogXML.EndElement(); // Line
       if ( fcov[cc] == 0 )
         {
         untested ++;
@@ -605,24 +617,19 @@ int cmCTestCoverageHandler::ProcessHandler()
       }
     total_tested += tested;
     total_untested += untested;
-    covLogFile << "\t\t</Report>" << std::endl
-      << "\t</File>" << std::endl;
-    covSumFile << "\t<File Name=\"" << cmXMLSafe(fileName)
-      << "\" FullPath=\"" << cmXMLSafe(
-        this->CTest->GetShortPathToFile(fullFileName.c_str()))
-      << "\" Covered=\"" << (tested+untested > 0 ? "true":"false") << "\">\n"
-      << "\t\t<LOCTested>" << tested << "</LOCTested>\n"
-      << "\t\t<LOCUnTested>" << untested << "</LOCUnTested>\n"
-      << "\t\t<PercentCoverage>";
-    covSumFile.setf(std::ios::fixed, std::ios::floatfield);
-    covSumFile.precision(2);
-    covSumFile << (cper) << "</PercentCoverage>\n"
-      << "\t\t<CoverageMetric>";
-    covSumFile.setf(std::ios::fixed, std::ios::floatfield);
-    covSumFile.precision(2);
-    covSumFile << (cmet) << "</CoverageMetric>\n";
-    this->WriteXMLLabels(covSumFile, shortFileName);
-    covSumFile << "\t</File>" << std::endl;
+    covLogXML.EndElement(); // Report
+    covLogXML.EndElement(); // File
+    covSumXML.StartElement("File");
+    covSumXML.Attribute("Name", fileName);
+    covSumXML.Attribute("FullPath",
+      this->CTest->GetShortPathToFile(fullFileName.c_str()));
+    covSumXML.Attribute("Covered", tested + untested > 0 ? "true" : "false");
+    covSumXML.Element("LOCTested", tested);
+    covSumXML.Element("LOCUnTested", untested);
+    covSumXML.Element("PercentCoverage", cper);
+    covSumXML.Element("CoverageMetric", cmet);
+    this->WriteXMLLabels(covSumXML, shortFileName);
+    covSumXML.EndElement(); // File
     }
 
   //Handle all the files in the extra coverage globs that have no cov data
@@ -632,9 +639,10 @@ int cmCTestCoverageHandler::ProcessHandler()
     std::string fileName = cmSystemTools::GetFilenameName(*i);
     std::string fullPath = cont.SourceDir + "/" + *i;
 
-    covLogFile << "\t<File Name=\"" << cmXMLSafe(fileName)
-      << "\" FullPath=\"" << cmXMLSafe(*i) << "\">\n"
-      << "\t\t<Report>" << std::endl;
+    covLogXML.StartElement("File");
+    covLogXML.Attribute("Name", fileName);
+    covLogXML.Attribute("FullPath", *i);
+    covLogXML.StartElement("Report");
 
     cmsys::ifstream ifs(fullPath.c_str());
     if (!ifs)
@@ -651,24 +659,30 @@ int cmCTestCoverageHandler::ProcessHandler()
       "Actually performing coverage for: " << *i << std::endl, this->Quiet);
     while (cmSystemTools::GetLineFromStream(ifs, line))
       {
-      covLogFile << "\t\t<Line Number=\"" << untested << "\" Count=\"0\">"
-        << cmXMLSafe(line) << "</Line>" << std::endl;
+      covLogXML.StartElement("Line");
+      covLogXML.Attribute("Number", untested);
+      covLogXML.Attribute("Count", 0);
+      covLogXML.Content(line);
+      covLogXML.EndElement(); // Line
       untested ++;
       }
-    covLogFile << "\t\t</Report>\n\t</File>" << std::endl;
+    covLogXML.EndElement(); // Report
+    covLogXML.EndElement(); // File
 
     total_untested += untested;
-    covSumFile << "\t<File Name=\"" << cmXMLSafe(fileName)
-      << "\" FullPath=\"" << cmXMLSafe(i->c_str())
-      << "\" Covered=\"true\">\n"
-      << "\t\t<LOCTested>0</LOCTested>\n"
-      << "\t\t<LOCUnTested>" << untested << "</LOCUnTested>\n"
-      << "\t\t<PercentCoverage>0</PercentCoverage>\n"
-      << "\t\t<CoverageMetric>0</CoverageMetric>\n";
-    this->WriteXMLLabels(covSumFile, *i);
-    covSumFile << "\t</File>" << std::endl;
-    }
-
+    covSumXML.StartElement("File");
+    covSumXML.Attribute("Name", fileName);
+    covSumXML.Attribute("FullPath", *i);
+    covSumXML.Attribute("Covered", "true");
+    covSumXML.Element("LOCTested", 0);
+    covSumXML.Element("LOCUnTested", untested);
+    covSumXML.Element("PercentCoverage", 0);
+    covSumXML.Element("CoverageMetric", 0);
+    this->WriteXMLLabels(covSumXML, *i);
+    covSumXML.EndElement(); // File
+    }
+
+  this->EndCoverageLogXML(covLogXML);
   this->EndCoverageLogFile(covLogFile, logFileCount);
 
   if (!errorsWhileAccumulating.empty())
@@ -696,22 +710,17 @@ int cmCTestCoverageHandler::ProcessHandler()
 
   std::string end_time = this->CTest->CurrentTime();
 
-  covSumFile << "\t<LOCTested>" << total_tested << "</LOCTested>\n"
-    << "\t<LOCUntested>" << total_untested << "</LOCUntested>\n"
-    << "\t<LOC>" << total_lines << "</LOC>\n"
-    << "\t<PercentCoverage>";
-  covSumFile.setf(std::ios::fixed, std::ios::floatfield);
-  covSumFile.precision(2);
-  covSumFile << (percent_coverage)<< "</PercentCoverage>\n"
-    << "\t<EndDateTime>" << end_time << "</EndDateTime>\n"
-    << "\t<EndTime>" <<
-         static_cast<unsigned int>(cmSystemTools::GetTime())
-    << "</EndTime>\n";
-  covSumFile << "<ElapsedMinutes>" <<
-    static_cast<int>((cmSystemTools::GetTime() - elapsed_time_start)/6)/10.0
-    << "</ElapsedMinutes>"
-    << "</Coverage>" << std::endl;
-  this->CTest->EndXML(covSumFile);
+  covSumXML.Element("LOCTested", total_tested);
+  covSumXML.Element("LOCUntested", total_untested);
+  covSumXML.Element("LOC", total_lines);
+  covSumXML.Element("PercentCoverage", percent_coverage);
+  covSumXML.Element("EndDateTime", end_time);
+  covSumXML.Element("EndTime",
+    static_cast<unsigned int>(cmSystemTools::GetTime()));
+  covSumXML.Element("ElapsedMinutes",
+    static_cast<int>((cmSystemTools::GetTime() - elapsed_time_start)/6)/10.0);
+  covSumXML.EndElement(); // Coverage
+  this->CTest->EndXML(covSumXML);
 
   cmCTestLog(this->CTest, HANDLER_OUTPUT, "" << std::endl
     << "\tCovered LOC:         "
@@ -1952,11 +1961,13 @@ int cmCTestCoverageHandler::RunBullseyeCoverageBranch(
     }
   // create the output stream for the CoverageLog-N.xml file
   cmGeneratedFileStream covLogFile;
+  cmXMLWriter covLogXML(covLogFile);
   int logFileCount = 0;
   if ( !this->StartCoverageLogFile(covLogFile, logFileCount) )
     {
     return -1;
     }
+  this->StartCoverageLogXML(covLogXML);
   // for each file run covbr on that file to get the coverage
   // information for that file
   std::string outputFile;
@@ -2009,20 +2020,22 @@ int cmCTestCoverageHandler::RunBullseyeCoverageBranch(
       // if we are in a valid file close it because a new one started
       if(valid)
         {
-        covLogFile << "\t\t</Report>" << std::endl
-                   << "\t</File>" << std::endl;
+        covLogXML.EndElement(); // Report
+        covLogXML.EndElement(); // File
         }
       // only allow 100 files in each log file
       if ( count != 0 && count % 100 == 0 )
         {
         cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
           "start a new log file: " << count << std::endl, this->Quiet);
+        this->EndCoverageLogXML(covLogXML);
         this->EndCoverageLogFile(covLogFile, logFileCount);
         logFileCount ++;
         if ( !this->StartCoverageLogFile(covLogFile, logFileCount) )
           {
           return -1;
           }
+        this->StartCoverageLogXML(covLogXML);
         count++; // move on one
         }
       std::map<std::string, std::string>::iterator
@@ -2036,19 +2049,20 @@ int cmCTestCoverageHandler::RunBullseyeCoverageBranch(
           "Produce coverage for file: " << file << " " << count
           << std::endl, this->Quiet);
         // start the file output
-        covLogFile << "\t<File Name=\""
-                   << cmXMLSafe(i->first)
-                   << "\" FullPath=\"" << cmXMLSafe(
-                     this->CTest->GetShortPathToFile(
-                       i->second.c_str())) << "\">" << std::endl
-                   << "\t\t<Report>" << std::endl;
+        covLogXML.StartElement("File");
+        covLogXML.Attribute("Name", i->first);
+        covLogXML.Attribute("FullPath",
+          this->CTest->GetShortPathToFile(i->second.c_str()));
+        covLogXML.StartElement("Report");
         // write the bullseye header
         line =0;
         for(int k =0; bullseyeHelp[k] != 0; ++k)
           {
-          covLogFile << "\t\t<Line Number=\"" << line << "\" Count=\"-1\">"
-                     << cmXMLSafe(bullseyeHelp[k])
-                     << "</Line>" << std::endl;
+          covLogXML.StartElement("Line");
+          covLogXML.Attribute("Number", line);
+          covLogXML.Attribute("Count", -1);
+          covLogXML.Content(bullseyeHelp[k]);
+          covLogXML.EndElement(); // Line
           line++;
           }
         valid = true; // we are in a valid file section
@@ -2062,18 +2076,21 @@ int cmCTestCoverageHandler::RunBullseyeCoverageBranch(
     // we are not at a start file, and we are in a valid file output the line
     else if(valid)
       {
-      covLogFile << "\t\t<Line Number=\"" << line << "\" Count=\"-1\">"
-                 << cmXMLSafe(lineIn)
-                 << "</Line>" << std::endl;
+      covLogXML.StartElement("Line");
+      covLogXML.Attribute("Number", line);
+      covLogXML.Attribute("Count", -1);
+      covLogXML.Content(lineIn);
+      covLogXML.EndElement(); // Line
       line++;
       }
     }
   // if we ran out of lines a valid file then close that file
   if(valid)
     {
-    covLogFile << "\t\t</Report>" << std::endl
-               << "\t</File>" << std::endl;
+    covLogXML.EndElement(); // Report
+    covLogXML.EndElement(); // File
     }
+  this->EndCoverageLogXML(covLogXML);
   this->EndCoverageLogFile(covLogFile, logFileCount);
   return 1;
 }
@@ -2143,23 +2160,20 @@ int cmCTestCoverageHandler::RunBullseyeSourceSummary(
   std::ostream& tmpLog = *cont->OFS;
   // copen the Coverage.xml file in the Testing directory
   cmGeneratedFileStream covSumFile;
+  cmXMLWriter xml(covSumFile);
   if(!this->StartResultingXML(cmCTest::PartCoverage, "Coverage", covSumFile))
     {
     cmCTestLog(this->CTest, ERROR_MESSAGE,
       "Cannot open coverage summary file." << std::endl);
     return 0;
     }
-  this->CTest->StartXML(covSumFile, this->AppendXML);
+  this->CTest->StartXML(xml, this->AppendXML);
   double elapsed_time_start = cmSystemTools::GetTime();
   std::string coverage_start_time = this->CTest->CurrentTime();
-  covSumFile << "<Coverage>" << std::endl
-             << "\t<StartDateTime>"
-             << coverage_start_time << "</StartDateTime>"
-             << std::endl
-             << "\t<StartTime>"
-             << static_cast<unsigned int>(cmSystemTools::GetTime())
-             << "</StartTime>"
-             << std::endl;
+  xml.StartElement("Coverage");
+  xml.Element("StartDateTime", coverage_start_time);
+  xml.Element("StartTime",
+    static_cast<unsigned int>(cmSystemTools::GetTime()));
   std::string stdline;
   std::string errline;
   // expected output:
@@ -2271,58 +2285,35 @@ int cmCTestCoverageHandler::RunBullseyeSourceSummary(
       tmpLog << "percentBranch: " << percentBranch << "\n";
       tmpLog << "percentCoverage: " << percent_coverage << "\n";
       tmpLog << "coverage metric: " << cmet << "\n";
-      covSumFile << "\t<File Name=\"" << cmXMLSafe(sourceFile)
-                 << "\" FullPath=\"" << cmXMLSafe(shortFileName)
-                 << "\" Covered=\"" << (cmet>0?"true":"false") << "\">\n"
-                 << "\t\t<BranchesTested>"
-                 << branchCovered
-                 << "</BranchesTested>\n"
-                 << "\t\t<BranchesUnTested>"
-                 << totalBranches - branchCovered
-                 << "</BranchesUnTested>\n"
-                 << "\t\t<FunctionsTested>"
-                 << functionsCalled
-                 << "</FunctionsTested>\n"
-                 << "\t\t<FunctionsUnTested>"
-                 << totalFunctions - functionsCalled
-                 << "</FunctionsUnTested>\n"
-        // Hack for conversion of function to loc assume a function
-        // has 100 lines of code
-                 << "\t\t<LOCTested>" << functionsCalled *100
-                 << "</LOCTested>\n"
-                 << "\t\t<LOCUnTested>"
-                 << (totalFunctions - functionsCalled)*100
-                 << "</LOCUnTested>\n"
-                 << "\t\t<PercentCoverage>";
-      covSumFile.setf(std::ios::fixed, std::ios::floatfield);
-      covSumFile.precision(2);
-      covSumFile << (cper) << "</PercentCoverage>\n"
-                 << "\t\t<CoverageMetric>";
-      covSumFile.setf(std::ios::fixed, std::ios::floatfield);
-      covSumFile.precision(2);
-      covSumFile << (cmet) << "</CoverageMetric>\n";
-      this->WriteXMLLabels(covSumFile, shortFileName);
-      covSumFile << "\t</File>" << std::endl;
+      xml.StartElement("File");
+      xml.Attribute("Name", sourceFile);
+      xml.Attribute("FullPath", shortFileName);
+      xml.Attribute("Covered", cmet > 0 ? "true" : "false");
+      xml.Element("BranchesTested", branchCovered);
+      xml.Element("BranchesUnTested", totalBranches - branchCovered);
+      xml.Element("FunctionsTested", functionsCalled);
+      xml.Element("FunctionsUnTested", totalFunctions - functionsCalled);
+      // Hack for conversion of function to loc assume a function
+      // has 100 lines of code
+      xml.Element("LOCTested", functionsCalled * 100);
+      xml.Element("LOCUnTested", (totalFunctions - functionsCalled) * 100);
+      xml.Element("PercentCoverage", cper);
+      xml.Element("CoverageMetric", cmet);
+      this->WriteXMLLabels(xml, shortFileName);
+      xml.EndElement(); // File
       }
     }
   std::string end_time = this->CTest->CurrentTime();
-  covSumFile << "\t<LOCTested>" << total_tested << "</LOCTested>\n"
-    << "\t<LOCUntested>" << total_untested << "</LOCUntested>\n"
-    << "\t<LOC>" << total_functions << "</LOC>\n"
-    << "\t<PercentCoverage>";
-  covSumFile.setf(std::ios::fixed, std::ios::floatfield);
-  covSumFile.precision(2);
-  covSumFile
-    << SAFEDIV(percent_coverage,number_files)<< "</PercentCoverage>\n"
-    << "\t<EndDateTime>" << end_time << "</EndDateTime>\n"
-    << "\t<EndTime>" << static_cast<unsigned int>(cmSystemTools::GetTime())
-    << "</EndTime>\n";
-  covSumFile
-    << "<ElapsedMinutes>" <<
-    static_cast<int>((cmSystemTools::GetTime() - elapsed_time_start)/6)/10.0
-    << "</ElapsedMinutes>"
-    << "</Coverage>" << std::endl;
-  this->CTest->EndXML(covSumFile);
+  xml.Element("LOCTested", total_tested);
+  xml.Element("LOCUntested", total_untested);
+  xml.Element("LOC", total_functions);
+  xml.Element("PercentCoverage", SAFEDIV(percent_coverage, number_files));
+  xml.Element("EndDateTime", end_time);
+  xml.Element("EndTime", static_cast<unsigned int>(cmSystemTools::GetTime()));
+  xml.Element("ElapsedMinutes",
+    static_cast<int>((cmSystemTools::GetTime() - elapsed_time_start)/6)/10.0);
+  xml.EndElement(); // Coverage
+  this->CTest->EndXML(xml);
 
   // Now create the coverage information for each file
   return this->RunBullseyeCoverageBranch(cont,
@@ -2514,19 +2505,19 @@ void cmCTestCoverageHandler::LoadLabels(const char* dir)
 }
 
 //----------------------------------------------------------------------
-void cmCTestCoverageHandler::WriteXMLLabels(std::ostream& os,
+void cmCTestCoverageHandler::WriteXMLLabels(cmXMLWriter& xml,
                                             std::string const& source)
 {
   LabelMapType::const_iterator li = this->SourceLabels.find(source);
   if(li != this->SourceLabels.end() && !li->second.empty())
     {
-    os << "\t\t<Labels>\n";
+    xml.StartElement("Labels");
     for(LabelSet::const_iterator lsi = li->second.begin();
         lsi != li->second.end(); ++lsi)
       {
-      os << "\t\t\t<Label>" << cmXMLSafe(this->Labels[*lsi]) << "</Label>\n";
+      xml.Element("Label", this->Labels[*lsi]);
       }
-    os << "\t\t</Labels>\n";
+    xml.EndElement(); // Labels
     }
 }
 