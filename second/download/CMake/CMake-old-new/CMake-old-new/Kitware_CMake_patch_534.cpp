@@ -40,7 +40,7 @@ cmCTestCoverageHandler::cmCTestCoverageHandler()
 void cmCTestCoverageHandler::Initialize()
 {
   this->Superclass::Initialize();
-  m_CustomCoverageExclude.empty();
+  this->CustomCoverageExclude.empty();
 }
 
 //----------------------------------------------------------------------
@@ -49,16 +49,16 @@ bool cmCTestCoverageHandler::StartCoverageLogFile(
 {
   char covLogFilename[1024];
   sprintf(covLogFilename, "CoverageLog-%d", logFileCount);
-  cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Open file: " << covLogFilename
-    << std::endl);
+  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Open file: "
+    << covLogFilename << std::endl);
   if (!this->StartResultingXML(covLogFilename, covLogFile) )
     {
-    cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot open log file: "
+    cmCTestLog(this->CTest, ERROR_MESSAGE, "Cannot open log file: "
       << covLogFilename << std::endl);
     return false;
     }
-  std::string local_start_time = m_CTest->CurrentTime();
-  m_CTest->StartXML(covLogFile);
+  std::string local_start_time = this->CTest->CurrentTime();
+  this->CTest->StartXML(covLogFile);
   covLogFile << "<CoverageLog>" << std::endl
     << "\t<StartDateTime>" << local_start_time << "</StartDateTime>"
     << std::endl;
@@ -69,13 +69,13 @@ bool cmCTestCoverageHandler::StartCoverageLogFile(
 void cmCTestCoverageHandler::EndCoverageLogFile(cmGeneratedFileStream& ostr,
   int logFileCount)
 {
-  std::string local_end_time = m_CTest->CurrentTime();
+  std::string local_end_time = this->CTest->CurrentTime();
   ostr << "\t<EndDateTime>" << local_end_time << "</EndDateTime>" << std::endl
     << "</CoverageLog>" << std::endl;
-  m_CTest->EndXML(ostr);
+  this->CTest->EndXML(ostr);
   char covLogFilename[1024];
   sprintf(covLogFilename, "CoverageLog-%d.xml", logFileCount);
-  cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Close file: "
+  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Close file: "
     << covLogFilename << std::endl);
   ostr.Close();
 }
@@ -86,12 +86,12 @@ bool cmCTestCoverageHandler::ShouldIDoCoverage(const char* file,
   const char* binDir)
 {
   std::vector<cmsys::RegularExpression>::iterator sit;
-  for ( sit = m_CustomCoverageExcludeRegex.begin();
-    sit != m_CustomCoverageExcludeRegex.end(); ++ sit )
+  for ( sit = this->CustomCoverageExcludeRegex.begin();
+    sit != this->CustomCoverageExcludeRegex.end(); ++ sit )
     {
     if ( sit->find(file) )
       {
-      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "  File " << file
+      cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "  File " << file
         << " is excluded in CTestCustom.ctest" << std::endl;);
       return false;
       }
@@ -133,7 +133,7 @@ bool cmCTestCoverageHandler::ShouldIDoCoverage(const char* file,
       fFile.c_str(), checkDir.c_str());
   if ( ndc.size() )
     {
-    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Found: " << ndc.c_str()
+    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Found: " << ndc.c_str()
       << " so skip coverage of " << file << std::endl);
     return false;
     }
@@ -164,7 +164,7 @@ bool cmCTestCoverageHandler::ShouldIDoCoverage(const char* file,
     fFile.c_str(), checkDir.c_str());
   if ( ndc.size() )
     {
-    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Found: " << ndc.c_str()
+    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Found: " << ndc.c_str()
       << " so skip coverage of: " << file << std::endl);
     return false;
     }
@@ -179,16 +179,19 @@ int cmCTestCoverageHandler::ProcessHandler()
 {
   int error = 0;
 
-  std::string sourceDir = m_CTest->GetCTestConfiguration("SourceDirectory");
-  std::string binaryDir = m_CTest->GetCTestConfiguration("BuildDirectory");
-  std::string gcovCommand = m_CTest->GetCTestConfiguration("CoverageCommand");
+  std::string sourceDir
+    = this->CTest->GetCTestConfiguration("SourceDirectory");
+  std::string binaryDir
+    = this->CTest->GetCTestConfiguration("BuildDirectory");
+  std::string gcovCommand
+    = this->CTest->GetCTestConfiguration("CoverageCommand");
 
   cmGeneratedFileStream ofs;
   double elapsed_time_start = cmSystemTools::GetTime();
   if ( !this->StartLogFile("Coverage", ofs) )
     {
-    cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot create LastCoverage.log file"
-      << std::endl);
+    cmCTestLog(this->CTest, ERROR_MESSAGE,
+      "Cannot create LastCoverage.log file" << std::endl);
     }
 
   ofs << "Performing coverage: " << elapsed_time_start << std::endl;
@@ -224,11 +227,11 @@ int cmCTestCoverageHandler::ProcessHandler()
   cmsys::RegularExpression st2re5(st2gcovOutputRex5.c_str());
   cmsys::RegularExpression st2re6(st2gcovOutputRex6.c_str());
 
-  cmCTestLog(m_CTest, HANDLER_OUTPUT, "Performing coverage" << std::endl);
+  cmCTestLog(this->CTest, HANDLER_OUTPUT, "Performing coverage" << std::endl);
 
-  std::string coverage_start_time = m_CTest->CurrentTime();
+  std::string coverage_start_time = this->CTest->CurrentTime();
 
-  std::string testingDir = m_CTest->GetBinaryDir() + "/Testing";
+  std::string testingDir = this->CTest->GetBinaryDir() + "/Testing";
   std::string tempDir = testingDir + "/CoverageInfo";
   std::string currentDirectory = cmSystemTools::GetCurrentWorkingDirectory();
   cmSystemTools::MakeDirectory(tempDir.c_str());
@@ -247,19 +250,19 @@ int cmCTestCoverageHandler::ProcessHandler()
 
   if ( files.size() == 0 )
     {
-    cmCTestLog(m_CTest, ERROR_MESSAGE, " Cannot find any coverage files."
+    cmCTestLog(this->CTest, ERROR_MESSAGE, " Cannot find any coverage files."
       << std::endl);
     // No coverage files is a valid thing, so the exit code is 0
     return 0;
     }
 
-  m_CustomCoverageExcludeRegex.empty();
+  this->CustomCoverageExcludeRegex.empty();
   std::vector<cmStdString>::iterator rexIt;
-  for ( rexIt = m_CustomCoverageExclude.begin();
-    rexIt != m_CustomCoverageExclude.end();
+  for ( rexIt = this->CustomCoverageExclude.begin();
+    rexIt != this->CustomCoverageExclude.end();
     ++ rexIt )
     {
-    m_CustomCoverageExcludeRegex.push_back(
+    this->CustomCoverageExcludeRegex.push_back(
       cmsys::RegularExpression(rexIt->c_str()));
     }
 
@@ -273,44 +276,45 @@ int cmCTestCoverageHandler::ProcessHandler()
   std::set<std::string> missingFiles;
 
   std::string actualSourceFile = "";
-  cmCTestLog(m_CTest, HANDLER_OUTPUT,
+  cmCTestLog(this->CTest, HANDLER_OUTPUT,
     "   Processing coverage (each . represents one file):" << std::endl);
-  cmCTestLog(m_CTest, HANDLER_OUTPUT, "    ");
+  cmCTestLog(this->CTest, HANDLER_OUTPUT, "    ");
   int file_count = 0;
   for ( it = files.begin(); it != files.end(); ++ it )
     {
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, "." << std::flush);
+    cmCTestLog(this->CTest, HANDLER_OUTPUT, "." << std::flush);
     std::string fileDir = cmSystemTools::GetFilenamePath(it->c_str());
     std::string command = "\"" + gcovCommand + "\" -l -o \"" + fileDir
       + "\" \"" + *it + "\"";
-    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, command.c_str() << std::endl);
+    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, command.c_str()
+      << std::endl);
     std::string output = "";
     std::string errors = "";
     int retVal = 0;
     ofs << "* Run coverage for: " << fileDir.c_str() << std::endl;
     ofs << "  Command: " << command.c_str() << std::endl;
-    int res = m_CTest->RunCommand(command.c_str(), &output, &errors,
-      &retVal, tempDir.c_str(), 0 /*m_TimeOut*/);
+    int res = this->CTest->RunCommand(command.c_str(), &output, &errors,
+      &retVal, tempDir.c_str(), 0 /*this->TimeOut*/);
 
     ofs << "  Output: " << output.c_str() << std::endl;
     ofs << "  Errors: " << errors.c_str() << std::endl;
     if ( ! res )
       {
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "Problem running coverage on file: "
-        << it->c_str() << std::endl);
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "Command produced error: " << errors
-        << std::endl);
+      cmCTestLog(this->CTest, ERROR_MESSAGE,
+        "Problem running coverage on file: " << it->c_str() << std::endl);
+      cmCTestLog(this->CTest, ERROR_MESSAGE,
+        "Command produced error: " << errors << std::endl);
       error ++;
       continue;
       }
     if ( retVal != 0 )
       {
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "Coverage command returned: "
+      cmCTestLog(this->CTest, ERROR_MESSAGE, "Coverage command returned: "
         << retVal << " while processing: " << it->c_str() << std::endl);
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "Command produced error: " << error
-        << std::endl);
+      cmCTestLog(this->CTest, ERROR_MESSAGE,
+        "Command produced error: " << error << std::endl);
       }
-    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT,
+    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
       "--------------------------------------------------------------"
       << std::endl
       << output << std::endl
@@ -326,7 +330,7 @@ int cmCTestCoverageHandler::ProcessHandler()
       {
       std::string sourceFile;
       std::string gcovFile;
-      cmCTestLog(m_CTest, DEBUG, "Line: [" << line->c_str() << "]"
+      cmCTestLog(this->CTest, DEBUG, "Line: [" << line->c_str() << "]"
         << std::endl);
       if ( line->size() == 0 )
         {
@@ -338,7 +342,7 @@ int cmCTestCoverageHandler::ProcessHandler()
           {
           if ( gcovStyle != 1 )
             {
-            cmCTestLog(m_CTest, ERROR_MESSAGE, "Unknown gcov output style"
+            cmCTestLog(this->CTest, ERROR_MESSAGE, "Unknown gcov output style"
               << std::endl);
             error ++;
             break;
@@ -355,7 +359,7 @@ int cmCTestCoverageHandler::ProcessHandler()
           {
           if ( gcovStyle != 1 )
             {
-            cmCTestLog(m_CTest, ERROR_MESSAGE, "Unknown gcov output style"
+            cmCTestLog(this->CTest, ERROR_MESSAGE, "Unknown gcov output style"
               << std::endl);
             error ++;
             break;
@@ -371,7 +375,7 @@ int cmCTestCoverageHandler::ProcessHandler()
           {
           if ( gcovStyle != 2 )
             {
-            cmCTestLog(m_CTest, ERROR_MESSAGE, "Unknown gcov output style"
+            cmCTestLog(this->CTest, ERROR_MESSAGE, "Unknown gcov output style"
               << std::endl);
             error ++;
             break;
@@ -388,7 +392,7 @@ int cmCTestCoverageHandler::ProcessHandler()
           {
           if ( gcovStyle != 2 )
             {
-            cmCTestLog(m_CTest, ERROR_MESSAGE, "Unknown gcov output style"
+            cmCTestLog(this->CTest, ERROR_MESSAGE, "Unknown gcov output style"
               << std::endl);
             error ++;
             break;
@@ -402,7 +406,7 @@ int cmCTestCoverageHandler::ProcessHandler()
           {
           if ( gcovStyle != 2 )
             {
-            cmCTestLog(m_CTest, ERROR_MESSAGE, "Unknown gcov output style"
+            cmCTestLog(this->CTest, ERROR_MESSAGE, "Unknown gcov output style"
               << std::endl);
             error ++;
             break;
@@ -418,15 +422,15 @@ int cmCTestCoverageHandler::ProcessHandler()
           {
           if ( gcovStyle != 2 )
             {
-            cmCTestLog(m_CTest, ERROR_MESSAGE, "Unknown gcov output style"
+            cmCTestLog(this->CTest, ERROR_MESSAGE, "Unknown gcov output style"
               << std::endl);
             error ++;
             break;
             }
           gcovStyle = 2;
           }
 
-        cmCTestLog(m_CTest, WARNING, "Warning: " << st2re4.match(1)
+        cmCTestLog(this->CTest, WARNING, "Warning: " << st2re4.match(1)
           << " had unexpected EOF" << std::endl);
         }
       else if ( st2re5.find(line->c_str() ) )
@@ -435,15 +439,15 @@ int cmCTestCoverageHandler::ProcessHandler()
           {
           if ( gcovStyle != 2 )
             {
-            cmCTestLog(m_CTest, ERROR_MESSAGE, "Unknown gcov output style"
+            cmCTestLog(this->CTest, ERROR_MESSAGE, "Unknown gcov output style"
               << std::endl);
             error ++;
             break;
             }
           gcovStyle = 2;
           }
 
-        cmCTestLog(m_CTest, WARNING, "Warning: Cannot open file: "
+        cmCTestLog(this->CTest, WARNING, "Warning: Cannot open file: "
           << st2re5.match(1) << std::endl);
         }
       else if ( st2re6.find(line->c_str() ) )
@@ -452,33 +456,33 @@ int cmCTestCoverageHandler::ProcessHandler()
           {
           if ( gcovStyle != 2 )
             {
-            cmCTestLog(m_CTest, ERROR_MESSAGE, "Unknown gcov output style"
+            cmCTestLog(this->CTest, ERROR_MESSAGE, "Unknown gcov output style"
               << std::endl);
             error ++;
             break;
             }
           gcovStyle = 2;
           }
 
-        cmCTestLog(m_CTest, WARNING, "Warning: File: " << st2re6.match(1)
+        cmCTestLog(this->CTest, WARNING, "Warning: File: " << st2re6.match(1)
           << " is newer than " << st2re6.match(2) << std::endl);
         }
       else
         {
-        cmCTestLog(m_CTest, ERROR_MESSAGE, "Unknown line: [" << line->c_str()
-          << "]" << std::endl);
+        cmCTestLog(this->CTest, ERROR_MESSAGE,
+          "Unknown line: [" << line->c_str() << "]" << std::endl);
         error ++;
         //abort();
         }
       if ( !gcovFile.empty() && actualSourceFile.size() )
         {
         singleFileCoverageVector* vec = &totalCoverage[actualSourceFile];
-        cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "   in file: "
+        cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "   in file: "
           << gcovFile << std::endl);
         std::ifstream ifile(gcovFile.c_str());
         if ( ! ifile )
           {
-          cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot open file: "
+          cmCTestLog(this->CTest, ERROR_MESSAGE, "Cannot open file: "
             << gcovFile << std::endl);
           }
         else
@@ -541,7 +545,7 @@ int cmCTestCoverageHandler::ProcessHandler()
           sourceFile.substr(0, sourceDir.size()) == sourceDir &&
           sourceFile[sourceDir.size()] == '/' )
           {
-          cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "   produced s: "
+          cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "   produced s: "
             << sourceFile.c_str() << std::endl);
           ofs << "  produced in source dir: " << sourceFile.c_str()
             << std::endl;
@@ -553,7 +557,7 @@ int cmCTestCoverageHandler::ProcessHandler()
           sourceFile.substr(0, binaryDir.size()) == binaryDir &&
           sourceFile[binaryDir.size()] == '/' )
           {
-          cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "   produced b: "
+          cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "   produced b: "
             << sourceFile.c_str() << std::endl);
           ofs << "  produced in binary dir: " << sourceFile.c_str()
             << std::endl;
@@ -564,13 +568,13 @@ int cmCTestCoverageHandler::ProcessHandler()
           {
           if ( missingFiles.find(actualSourceFile) == missingFiles.end() )
             {
-            cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Something went wrong"
-              << std::endl);
-            cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "File: ["
+            cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+              "Something went wrong" << std::endl);
+            cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "File: ["
               << sourceFile.c_str() << "]" << std::endl);
-            cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "s: ["
+            cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "s: ["
               << sourceFile.substr(0, sourceDir.size()) << "]" << std::endl);
-            cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "b: ["
+            cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "b: ["
               << sourceFile.substr(0, binaryDir.size()) << "]" << std::endl);
             ofs << "  Something went wrong. Cannot find: "
               << sourceFile.c_str()
@@ -584,9 +588,9 @@ int cmCTestCoverageHandler::ProcessHandler()
     file_count ++;
     if ( file_count % 50 == 0 )
       {
-      cmCTestLog(m_CTest, HANDLER_OUTPUT, " processed: " << file_count
+      cmCTestLog(this->CTest, HANDLER_OUTPUT, " processed: " << file_count
         << " out of " << files.size() << std::endl);
-      cmCTestLog(m_CTest, HANDLER_OUTPUT, "    ");
+      cmCTestLog(this->CTest, HANDLER_OUTPUT, "    ");
       }
     }
 
@@ -595,13 +599,13 @@ int cmCTestCoverageHandler::ProcessHandler()
 
   if (!this->StartResultingXML("Coverage", covSumFile))
     {
-    cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot open coverage summary file."
-      << std::endl);
+    cmCTestLog(this->CTest, ERROR_MESSAGE,
+      "Cannot open coverage summary file." << std::endl);
 
     return -1;
     }
 
-  m_CTest->StartXML(covSumFile);
+  this->CTest->StartXML(covSumFile);
   // Produce output xml files
 
   covSumFile << "<Coverage>" << std::endl
@@ -618,10 +622,10 @@ int cmCTestCoverageHandler::ProcessHandler()
   long total_untested = 0;
   //std::string fullSourceDir = sourceDir + "/";
   //std::string fullBinaryDir = binaryDir + "/";
-  cmCTestLog(m_CTest, HANDLER_OUTPUT, std::endl);
-  cmCTestLog(m_CTest, HANDLER_OUTPUT,
+  cmCTestLog(this->CTest, HANDLER_OUTPUT, std::endl);
+  cmCTestLog(this->CTest, HANDLER_OUTPUT,
     "   Acumulating results (each . represents one file):" << std::endl);
-  cmCTestLog(m_CTest, HANDLER_OUTPUT, "    ");
+  cmCTestLog(this->CTest, HANDLER_OUTPUT, "    ");
 
   std::vector<std::string> errorsWhileAccumulating;
 
@@ -630,14 +634,14 @@ int cmCTestCoverageHandler::ProcessHandler()
     fileIterator != totalCoverage.end();
     ++fileIterator )
     {
-    cmCTestLog(m_CTest, HANDLER_OUTPUT, "." << std::flush);
+    cmCTestLog(this->CTest, HANDLER_OUTPUT, "." << std::flush);
     file_count ++;
     if ( file_count % 50 == 0 )
       {
-      cmCTestLog(m_CTest, HANDLER_OUTPUT, " processed: " << file_count
+      cmCTestLog(this->CTest, HANDLER_OUTPUT, " processed: " << file_count
         << " out of "
         << totalCoverage.size() << std::endl);
-      cmCTestLog(m_CTest, HANDLER_OUTPUT, "    ");
+      cmCTestLog(this->CTest, HANDLER_OUTPUT, "    ");
       }
     if ( cnt % 100 == 0 )
       {
@@ -653,14 +657,14 @@ int cmCTestCoverageHandler::ProcessHandler()
       = cmSystemTools::GetFilenameName(fullFileName.c_str());
     std::string fullFilePath
       = cmSystemTools::GetFilenamePath(fullFileName.c_str());
-    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Process file: "
+    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Process file: "
       << fullFileName << std::endl);
 
     cmSystemTools::ConvertToUnixSlashes(fullFilePath);
 
     if ( !cmSystemTools::FileExists(fullFileName.c_str()) )
       {
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot find file: "
+      cmCTestLog(this->CTest, ERROR_MESSAGE, "Cannot find file: "
         << fullFileName.c_str() << std::endl);
       continue;
       }
@@ -670,7 +674,7 @@ int cmCTestCoverageHandler::ProcessHandler()
         sourceDir.c_str(), binaryDir.c_str());
     if ( !shouldIDoCoverage )
       {
-      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT,
+      cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
         ".NoDartCoverage found, so skip coverage check for: "
         << fullFileName.c_str()
         << std::endl);
@@ -679,8 +683,9 @@ int cmCTestCoverageHandler::ProcessHandler()
 
     const singleFileCoverageVector& fcov = fileIterator->second;
     covLogFile << "\t<File Name=\""
-      << m_CTest->MakeXMLSafe(fileName.c_str())
-      << "\" FullPath=\"" << m_CTest->MakeXMLSafe(m_CTest->GetShortPathToFile(
+      << this->CTest->MakeXMLSafe(fileName.c_str())
+      << "\" FullPath=\"" << this->CTest->MakeXMLSafe(
+        this->CTest->GetShortPathToFile(
           fileIterator->first.c_str())) << "\">" << std::endl
       << "\t\t<Report>" << std::endl;
 
@@ -712,7 +717,7 @@ int cmCTestCoverageHandler::ProcessHandler()
         }
       covLogFile << "\t\t<Line Number=\"" << cc << "\" Count=\"" << fcov[cc]
         << "\">"
-        << m_CTest->MakeXMLSafe(line.c_str()) << "</Line>" << std::endl;
+        << this->CTest->MakeXMLSafe(line.c_str()) << "</Line>" << std::endl;
       if ( fcov[cc] == 0 )
         {
         untested ++;
@@ -741,9 +746,9 @@ int cmCTestCoverageHandler::ProcessHandler()
     total_untested += untested;
     covLogFile << "\t\t</Report>" << std::endl
       << "\t</File>" << std::endl;
-    covSumFile << "\t<File Name=\"" << m_CTest->MakeXMLSafe(fileName)
-      << "\" FullPath=\"" << m_CTest->MakeXMLSafe(
-        m_CTest->GetShortPathToFile(fullFileName.c_str()))
+    covSumFile << "\t<File Name=\"" << this->CTest->MakeXMLSafe(fileName)
+      << "\" FullPath=\"" << this->CTest->MakeXMLSafe(
+        this->CTest->GetShortPathToFile(fullFileName.c_str()))
       << "\" Covered=\"" << (cmet>0?"true":"false") << "\">\n"
       << "\t\t<LOCTested>" << tested << "</LOCTested>\n"
       << "\t\t<LOCUnTested>" << untested << "</LOCUnTested>\n"
@@ -762,15 +767,16 @@ int cmCTestCoverageHandler::ProcessHandler()
 
   if ( errorsWhileAccumulating.size() > 0 )
     {
-    cmCTestLog(m_CTest, ERROR_MESSAGE, std::endl);
-    cmCTestLog(m_CTest, ERROR_MESSAGE, "Error(s) while acumulating results:"
-      << std::endl);
+    cmCTestLog(this->CTest, ERROR_MESSAGE, std::endl);
+    cmCTestLog(this->CTest, ERROR_MESSAGE,
+      "Error(s) while acumulating results:" << std::endl);
     std::vector<std::string>::iterator erIt;
     for ( erIt = errorsWhileAccumulating.begin();
       erIt != errorsWhileAccumulating.end();
       ++ erIt )
       {
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "  " << erIt->c_str() << std::endl);
+      cmCTestLog(this->CTest, ERROR_MESSAGE,
+        "  " << erIt->c_str() << std::endl);
       }
     }
 
@@ -782,7 +788,7 @@ int cmCTestCoverageHandler::ProcessHandler()
     percent_coverage = 0;
     }
 
-  std::string end_time = m_CTest->CurrentTime();
+  std::string end_time = this->CTest->CurrentTime();
 
   covSumFile << "\t<LOCTested>" << total_tested << "</LOCTested>\n"
     << "\t<LOCUntested>" << total_untested << "</LOCUntested>\n"
@@ -796,9 +802,9 @@ int cmCTestCoverageHandler::ProcessHandler()
     static_cast<int>((cmSystemTools::GetTime() - elapsed_time_start)/6)/10.0
     << "</ElapsedMinutes>"
     << "</Coverage>" << std::endl;
-  m_CTest->EndXML(covSumFile);
+  this->CTest->EndXML(covSumFile);
 
-  cmCTestLog(m_CTest, HANDLER_OUTPUT, "\tCovered LOC:         "
+  cmCTestLog(this->CTest, HANDLER_OUTPUT, "\tCovered LOC:         "
     << total_tested << std::endl
     << "\tNot covered LOC:     " << total_untested << std::endl
     << "\tTotal LOC:           " << total_lines << std::endl
@@ -827,16 +833,16 @@ int cmCTestCoverageHandler::ProcessHandler()
 //----------------------------------------------------------------------
 void cmCTestCoverageHandler::PopulateCustomVectors(cmMakefile *mf)
 {
-  cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT,
+  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
     " Add coverage exclude regular expressions." << std::endl);
   cmCTest::PopulateCustomVector(mf, "CTEST_CUSTOM_COVERAGE_EXCLUDE",
-                                m_CustomCoverageExclude);
+                                this->CustomCoverageExclude);
   std::vector<cmStdString>::iterator it;
-  for ( it = m_CustomCoverageExclude.begin();
-    it != m_CustomCoverageExclude.end();
+  for ( it = this->CustomCoverageExclude.begin();
+    it != this->CustomCoverageExclude.end();
     ++ it )
     {
-    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, " Add coverage exclude: "
+    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, " Add coverage exclude: "
       << it->c_str() << std::endl);
     }
 }