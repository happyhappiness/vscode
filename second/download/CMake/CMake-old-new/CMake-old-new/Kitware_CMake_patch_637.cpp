@@ -34,7 +34,6 @@
 //----------------------------------------------------------------------
 cmCTestCoverageHandler::cmCTestCoverageHandler()
 {
-  m_Verbose = false; 
   m_CTest = 0;
 }
 
@@ -43,11 +42,11 @@ bool cmCTestCoverageHandler::StartLogFile(cmGeneratedFileStream& covLogFile, int
 {
   char covLogFilename[1024];
   sprintf(covLogFilename, "CoverageLog-%d.xml", logFileCount);
-  std::cout << "Open file: " << covLogFilename << std::endl;
+  cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Open file: " << covLogFilename << std::endl);
   if (!m_CTest->OpenOutputFile(m_CTest->GetCurrentTag(), 
       covLogFilename, covLogFile, true))
     {
-    std::cerr << "Cannot open log file: " << covLogFilename << std::endl;
+    cmCTestLog(m_CTest, ERROR, "Cannot open log file: " << covLogFilename << std::endl);
     return false;
     }
   std::string local_start_time = m_CTest->CurrentTime();
@@ -66,13 +65,13 @@ void cmCTestCoverageHandler::EndLogFile(cmGeneratedFileStream& ostr, int logFile
   m_CTest->EndXML(ostr);
   char covLogFilename[1024];
   sprintf(covLogFilename, "CoverageLog-%d.xml", logFileCount);
-  std::cout << "Close file: " << covLogFilename << std::endl;
+  cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Close file: " << covLogFilename << std::endl);
   ostr.close();
 }
 
 //----------------------------------------------------------------------
 bool cmCTestCoverageHandler::ShouldIDoCoverage(const char* file, const char* srcDir,
-  const char* binDir, bool verbose)
+  const char* binDir)
 {
   std::string fSrcDir = cmSystemTools::CollapseFullPath(srcDir);
   std::string fBinDir = cmSystemTools::CollapseFullPath(binDir);
@@ -108,10 +107,7 @@ bool cmCTestCoverageHandler::ShouldIDoCoverage(const char* file, const char* src
       fFile.c_str(), checkDir.c_str());
   if ( ndc.size() )
     {
-    if ( verbose )
-      {
-      std::cout << "Found: " << ndc.c_str() << " so skip coverage of " << file << std::endl;
-      }
+    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Found: " << ndc.c_str() << " so skip coverage of " << file << std::endl);
     return false;
     }
 
@@ -141,10 +137,7 @@ bool cmCTestCoverageHandler::ShouldIDoCoverage(const char* file, const char* src
     fFile.c_str(), checkDir.c_str());
   if ( ndc.size() )
     {
-    if ( verbose )
-      {
-      std::cout << "Found: " << ndc.c_str() << " so skip coverage of: " << file << std::endl;
-      }
+    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Found: " << ndc.c_str() << " so skip coverage of: " << file << std::endl);
     return false;
     }
   // Ok, nothing in source tree, nothing in binary tree
@@ -171,7 +164,7 @@ int cmCTestCoverageHandler::ProcessHandler()
   std::string gcovOutputRex = "[0-9]+\\.[0-9]+% of [0-9]+ (source |)lines executed in file (.*)$";
   std::string gcovOutputRex2 = "^Creating (.*\\.gcov)\\.";
 
-  std::cout << "Performing coverage" << std::endl;
+  cmCTestLog(m_CTest, HANDLER_OUTPUT, "Performing coverage" << std::endl);
   double elapsed_time_start = cmSystemTools::GetTime();
 
   std::string coverage_start_time = m_CTest->CurrentTime();
@@ -190,7 +183,7 @@ int cmCTestCoverageHandler::ProcessHandler()
 
   if ( files.size() == 0 )
     {
-    std::cerr << " Cannot find any coverage files." << std::endl;
+    cmCTestLog(m_CTest, ERROR, " Cannot find any coverage files." << std::endl);
     // No coverage files is a valid thing, so the exit code is 0
     return 0;
     }
@@ -209,24 +202,21 @@ int cmCTestCoverageHandler::ProcessHandler()
     {
     std::string fileDir = cmSystemTools::GetFilenamePath(it->c_str());
     std::string command = "\"" + gcovCommand + "\" -l -o \"" + fileDir + "\" \"" + *it + "\"";
-    if ( m_Verbose )
-      {
-      std::cout << command.c_str() << std::endl;
-      }
+    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, command.c_str() << std::endl);
     std::string output = "";
     int retVal = 0;
     int res = cmSystemTools::RunSingleCommand(command.c_str(), &output, 
       &retVal, tempDir.c_str(),
       false, 0 /*m_TimeOut*/);
     if ( ! res )
       {
-      std::cerr << "Problem running coverage on file: " << it->c_str() << std::endl;
+      cmCTestLog(m_CTest, ERROR, "Problem running coverage on file: " << it->c_str() << std::endl);
       error ++;
       continue;
       }
     if ( retVal != 0 )
       {
-      std::cerr << "Coverage command returned: " << retVal << " while processing: " << it->c_str() << std::endl;
+      cmCTestLog(m_CTest, ERROR, "Coverage command returned: " << retVal << " while processing: " << it->c_str() << std::endl);
       }
     std::vector<cmStdString> lines;
     std::vector<cmStdString>::iterator line;
@@ -242,29 +232,23 @@ int cmCTestCoverageHandler::ProcessHandler()
           file.substr(0, sourceDir.size()) == sourceDir &&
           file[sourceDir.size()] == '/' )
           {
-          if ( m_Verbose )
-            {
-            std::cout << "   produced s: " << file << std::endl;
-            }
+          cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "   produced s: " << file << std::endl);
           cfile = file;
           }
         // Binary dir?
         if ( file.size() > binaryDir.size() &&
           file.substr(0, binaryDir.size()) == binaryDir &&
           file[binaryDir.size()] == '/' )
           {
-          if ( m_Verbose )
-            {
-            std::cout << "   produce b: " << file << std::endl;
-            }
+          cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "   produce b: " << file << std::endl);
           cfile = file;
           }
         if ( cfile.empty() )
           {
-          std::cerr << "Something went wrong" << std::endl;
-          std::cerr << "File: [" << file << "]" << std::endl;
-          std::cerr << "s: [" << file.substr(0, sourceDir.size()) << "]" << std::endl;
-          std::cerr << "b: [" << file.substr(0, binaryDir.size()) << "]" << std::endl;
+          cmCTestLog(m_CTest, ERROR, "Something went wrong" << std::endl);
+          cmCTestLog(m_CTest, ERROR, "File: [" << file << "]" << std::endl);
+          cmCTestLog(m_CTest, ERROR, "s: [" << file.substr(0, sourceDir.size()) << "]" << std::endl);
+          cmCTestLog(m_CTest, ERROR, "b: [" << file.substr(0, binaryDir.size()) << "]" << std::endl);
           }
         }
       else if ( re2.find(line->c_str() ) )
@@ -273,14 +257,11 @@ int cmCTestCoverageHandler::ProcessHandler()
         if ( cfile.size() )
           {
           singleFileCoverageVector* vec = &totalCoverage[cfile];
-          if ( m_Verbose )
-            {
-            std::cout << "   in file: " << fname << std::endl;
-            }
+          cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "   in file: " << fname << std::endl);
           std::ifstream ifile(fname.c_str());
           if ( ! ifile )
             {
-            std::cerr << "Cannot open file: " << fname << std::endl;
+            cmCTestLog(m_CTest, ERROR, "Cannot open file: " << fname << std::endl);
             }
           else
             {
@@ -317,7 +298,7 @@ int cmCTestCoverageHandler::ProcessHandler()
         }
       else
         {
-        std::cerr << "Unknown line: " << line->c_str() << std::endl;
+        cmCTestLog(m_CTest, ERROR, "Unknown line: " << line->c_str() << std::endl);
         error ++;
         }
       }
@@ -329,7 +310,8 @@ int cmCTestCoverageHandler::ProcessHandler()
   if (!m_CTest->OpenOutputFile(m_CTest->GetCurrentTag(), 
       "Coverage.xml", covSumFile, true))
     {
-    std::cerr << "Cannot open coverage summary file: Coverage.xml" << std::endl;
+    cmCTestLog(m_CTest, ERROR, "Cannot open coverage summary file: Coverage.xml" << std::endl);
+
     return -1;
     }
 
@@ -366,30 +348,24 @@ int cmCTestCoverageHandler::ProcessHandler()
     const std::string fullFileName = fileIterator->first;
     const std::string fileName = cmSystemTools::GetFilenameName(fullFileName.c_str());
     std::string fullFilePath = cmSystemTools::GetFilenamePath(fullFileName.c_str());
-    if ( m_Verbose )
-      {
-      std::cerr << "Process file: " << fullFileName << std::endl;
-      }
+    cmCTestLog(m_CTest, ERROR, "Process file: " << fullFileName << std::endl);
 
     cmSystemTools::ConvertToUnixSlashes(fullFilePath);
 
     if ( !cmSystemTools::FileExists(fullFileName.c_str()) )
       {
-      std::cerr << "Cannot find file: " << fullFileName.c_str() << std::endl;
+      cmCTestLog(m_CTest, ERROR, "Cannot find file: " << fullFileName.c_str() << std::endl);
       continue;
       }
 
     bool shouldIDoCoverage
       = this->ShouldIDoCoverage(fullFileName.c_str(),
-        sourceDir.c_str(), binaryDir.c_str(), m_Verbose);
+        sourceDir.c_str(), binaryDir.c_str());
     if ( !shouldIDoCoverage )
       {
-      if ( m_Verbose )
-        {
-        std::cerr << ".NoDartCoverage found, so skip coverage check for: "
-          << fullFileName.c_str()
-          << std::endl;
-        }
+      cmCTestLog(m_CTest, ERROR, ".NoDartCoverage found, so skip coverage check for: "
+        << fullFileName.c_str()
+        << std::endl);
       continue;
       }
 
@@ -403,7 +379,7 @@ int cmCTestCoverageHandler::ProcessHandler()
     std::ifstream ifs(fullFileName.c_str());
     if ( !ifs)
       {
-      std::cerr << "Cannot open source file: " << fullFileName.c_str() << std::endl;
+      cmCTestLog(m_CTest, ERROR, "Cannot open source file: " << fullFileName.c_str() << std::endl);
       error ++;
       continue;
       }
@@ -417,7 +393,7 @@ int cmCTestCoverageHandler::ProcessHandler()
       {
       if ( !cmSystemTools::GetLineFromStream(ifs, line) )
         {
-        std::cerr << "Problem reading source file: " << fullFileName.c_str() << " line:" << cc << std::endl;
+        cmCTestLog(m_CTest, ERROR, "Problem reading source file: " << fullFileName.c_str() << " line:" << cc << std::endl);
         error ++;
         break;
         }
@@ -434,7 +410,7 @@ int cmCTestCoverageHandler::ProcessHandler()
       }
     if ( cmSystemTools::GetLineFromStream(ifs, line) )
       {
-      std::cerr << "Looks like there are more lines in the file: " << line << std::endl;
+      cmCTestLog(m_CTest, ERROR, "Looks like there are more lines in the file: " << line << std::endl);
       }
     float cper = 0;
     float cmet = 0;
@@ -492,14 +468,13 @@ int cmCTestCoverageHandler::ProcessHandler()
     << "</Coverage>" << std::endl;
   m_CTest->EndXML(covSumFile);
 
-  std::cout << "\tCovered LOC:         " << total_tested << std::endl
+  cmCTestLog(m_CTest, HANDLER_OUTPUT, "\tCovered LOC:         " << total_tested << std::endl
     << "\tNot covered LOC:     " << total_untested << std::endl
     << "\tTotal LOC:           " << total_lines << std::endl
-    << "\tPercentage Coverage: ";
-
-  std::cout.setf(std::ios::fixed, std::ios::floatfield);
-  std::cout.precision(2);
-  std::cout << (percent_coverage) << "%" << std::endl;
+    << "\tPercentage Coverage: " 
+    << std::setiosflags(std::ios::fixed)
+    << std::setprecision(2)
+    << (percent_coverage) << "%" << std::endl);
 
   cmSystemTools::ChangeDirectory(currentDirectory.c_str());
 