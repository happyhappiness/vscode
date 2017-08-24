@@ -9,8 +9,8 @@
   Copyright (c) 2002 Kitware, Inc., Insight Consortium.  All rights reserved.
   See Copyright.txt or http://www.cmake.org/HTML/Copyright.html for details.
 
-     This software is distributed WITHOUT ANY WARRANTY; without even 
-     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
+     This software is distributed WITHOUT ANY WARRANTY; without even
+     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
      PURPOSE.  See the above copyright notices for more information.
 
 =========================================================================*/
@@ -25,7 +25,7 @@
 #include <cmsys/Process.h>
 #include <cmsys/RegularExpression.hxx>
 
-#include <stdlib.h> 
+#include <stdlib.h>
 #include <math.h>
 #include <float.h>
 
@@ -44,38 +44,45 @@ void cmCTestCoverageHandler::Initialize()
 }
 
 //----------------------------------------------------------------------
-bool cmCTestCoverageHandler::StartCoverageLogFile(cmGeneratedFileStream& covLogFile, int logFileCount)
+bool cmCTestCoverageHandler::StartCoverageLogFile(
+  cmGeneratedFileStream& covLogFile, int logFileCount)
 {
   char covLogFilename[1024];
   sprintf(covLogFilename, "CoverageLog-%d", logFileCount);
-  cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Open file: " << covLogFilename << std::endl);
+  cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Open file: " << covLogFilename
+    << std::endl);
   if (!this->StartResultingXML(covLogFilename, covLogFile) )
     {
-    cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot open log file: " << covLogFilename << std::endl);
+    cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot open log file: "
+      << covLogFilename << std::endl);
     return false;
     }
   std::string local_start_time = m_CTest->CurrentTime();
   m_CTest->StartXML(covLogFile);
   covLogFile << "<CoverageLog>" << std::endl
-    << "\t<StartDateTime>" << local_start_time << "</StartDateTime>" << std::endl;
+    << "\t<StartDateTime>" << local_start_time << "</StartDateTime>"
+    << std::endl;
   return true;
 }
 
 //----------------------------------------------------------------------
-void cmCTestCoverageHandler::EndCoverageLogFile(cmGeneratedFileStream& ostr, int logFileCount)
+void cmCTestCoverageHandler::EndCoverageLogFile(cmGeneratedFileStream& ostr,
+  int logFileCount)
 {
   std::string local_end_time = m_CTest->CurrentTime();
   ostr << "\t<EndDateTime>" << local_end_time << "</EndDateTime>" << std::endl
     << "</CoverageLog>" << std::endl;
   m_CTest->EndXML(ostr);
   char covLogFilename[1024];
   sprintf(covLogFilename, "CoverageLog-%d.xml", logFileCount);
-  cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Close file: " << covLogFilename << std::endl);
+  cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Close file: "
+    << covLogFilename << std::endl);
   ostr.Close();
 }
 
 //----------------------------------------------------------------------
-bool cmCTestCoverageHandler::ShouldIDoCoverage(const char* file, const char* srcDir,
+bool cmCTestCoverageHandler::ShouldIDoCoverage(const char* file,
+  const char* srcDir,
   const char* binDir)
 {
   std::vector<cmsys::RegularExpression>::iterator sit;
@@ -93,8 +100,10 @@ bool cmCTestCoverageHandler::ShouldIDoCoverage(const char* file, const char* src
   std::string fSrcDir = cmSystemTools::CollapseFullPath(srcDir);
   std::string fBinDir = cmSystemTools::CollapseFullPath(binDir);
   std::string fFile = cmSystemTools::CollapseFullPath(file);
-  bool sourceSubDir = cmSystemTools::IsSubDirectory(fFile.c_str(), fSrcDir.c_str());
-  bool buildSubDir = cmSystemTools::IsSubDirectory(fFile.c_str(), fBinDir.c_str());
+  bool sourceSubDir = cmSystemTools::IsSubDirectory(fFile.c_str(),
+    fSrcDir.c_str());
+  bool buildSubDir = cmSystemTools::IsSubDirectory(fFile.c_str(),
+    fBinDir.c_str());
   // Always check parent directory of the file.
   std::string fileDir = cmSystemTools::GetFilenamePath(fFile.c_str());
   std::string checkDir;
@@ -124,7 +133,8 @@ bool cmCTestCoverageHandler::ShouldIDoCoverage(const char* file, const char* src
       fFile.c_str(), checkDir.c_str());
   if ( ndc.size() )
     {
-    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Found: " << ndc.c_str() << " so skip coverage of " << file << std::endl);
+    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Found: " << ndc.c_str()
+      << " so skip coverage of " << file << std::endl);
     return false;
     }
 
@@ -154,7 +164,8 @@ bool cmCTestCoverageHandler::ShouldIDoCoverage(const char* file, const char* src
     fFile.c_str(), checkDir.c_str());
   if ( ndc.size() )
     {
-    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Found: " << ndc.c_str() << " so skip coverage of: " << file << std::endl);
+    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Found: " << ndc.c_str()
+      << " so skip coverage of: " << file << std::endl);
     return false;
     }
   // Ok, nothing in source tree, nothing in binary tree
@@ -176,7 +187,8 @@ int cmCTestCoverageHandler::ProcessHandler()
   double elapsed_time_start = cmSystemTools::GetTime();
   if ( !this->StartLogFile("Coverage", ofs) )
     {
-    cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot create LastCoverage.log file" << std::endl);
+    cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot create LastCoverage.log file"
+      << std::endl);
     }
 
   ofs << "Performing coverage: " << elapsed_time_start << std::endl;
@@ -186,39 +198,42 @@ int cmCTestCoverageHandler::ProcessHandler()
 
   std::string asfGlob = sourceDir + "/*";
   std::string abfGlob = binaryDir + "/*";
- 
-  
+
+
   // Style 1
-  std::string st1gcovOutputRex1 = "[0-9]+\\.[0-9]+% of [0-9]+ (source |)lines executed in file (.*)$";
+  std::string st1gcovOutputRex1
+    = "[0-9]+\\.[0-9]+% of [0-9]+ (source |)lines executed in file (.*)$";
   std::string st1gcovOutputRex2 = "^Creating (.*\\.gcov)\\.";
   cmsys::RegularExpression st1re1(st1gcovOutputRex1.c_str());
   cmsys::RegularExpression st1re2(st1gcovOutputRex2.c_str());
- 
- 
+
+
   // Style 2
   std::string st2gcovOutputRex1 = "^File *[`'](.*)'$";
-  std::string st2gcovOutputRex2 = "Lines executed: *[0-9]+\\.[0-9]+% of [0-9]+$";
+  std::string st2gcovOutputRex2
+    = "Lines executed: *[0-9]+\\.[0-9]+% of [0-9]+$";
   std::string st2gcovOutputRex3 = "^(.*):creating [`'](.*\\.gcov)'";
   std::string st2gcovOutputRex4 = "^(.*):unexpected EOF *$";
   std::string st2gcovOutputRex5 = "^(.*):cannot open source file*$";
-  std::string st2gcovOutputRex6 = "^(.*):source file is newer than graph file `(.*)'$";
+  std::string st2gcovOutputRex6
+    = "^(.*):source file is newer than graph file `(.*)'$";
   cmsys::RegularExpression st2re1(st2gcovOutputRex1.c_str());
   cmsys::RegularExpression st2re2(st2gcovOutputRex2.c_str());
   cmsys::RegularExpression st2re3(st2gcovOutputRex3.c_str());
   cmsys::RegularExpression st2re4(st2gcovOutputRex4.c_str());
   cmsys::RegularExpression st2re5(st2gcovOutputRex5.c_str());
   cmsys::RegularExpression st2re6(st2gcovOutputRex6.c_str());
- 
+
   cmCTestLog(m_CTest, HANDLER_OUTPUT, "Performing coverage" << std::endl);
- 
+
   std::string coverage_start_time = m_CTest->CurrentTime();
- 
+
   std::string testingDir = m_CTest->GetBinaryDir() + "/Testing";
   std::string tempDir = testingDir + "/CoverageInfo";
   std::string currentDirectory = cmSystemTools::GetCurrentWorkingDirectory();
   cmSystemTools::MakeDirectory(tempDir.c_str());
   cmSystemTools::ChangeDirectory(tempDir.c_str());
- 
+
   cmGlob gl;
   gl.RecurseOn();
   std::string daGlob = binaryDir + "/*.da";
@@ -229,10 +244,11 @@ int cmCTestCoverageHandler::ProcessHandler()
   std::vector<std::string>& moreFiles = gl.GetFiles();
   files.insert(files.end(), moreFiles.begin(), moreFiles.end());
   std::vector<std::string>::iterator it;
- 
+
   if ( files.size() == 0 )
     {
-    cmCTestLog(m_CTest, ERROR_MESSAGE, " Cannot find any coverage files." << std::endl);
+    cmCTestLog(m_CTest, ERROR_MESSAGE, " Cannot find any coverage files."
+      << std::endl);
     // No coverage files is a valid thing, so the exit code is 0
     return 0;
     }
@@ -243,27 +259,30 @@ int cmCTestCoverageHandler::ProcessHandler()
     rexIt != m_CustomCoverageExclude.end();
     ++ rexIt )
     {
-    m_CustomCoverageExcludeRegex.push_back(cmsys::RegularExpression(rexIt->c_str()));
+    m_CustomCoverageExcludeRegex.push_back(
+      cmsys::RegularExpression(rexIt->c_str()));
     }
- 
+
   typedef std::vector<int> singleFileCoverageVector;
   typedef std::map<std::string, singleFileCoverageVector> totalCoverageMap;
- 
+
   totalCoverageMap totalCoverage;
- 
+
   int gcovStyle = 0;
 
   std::set<std::string> missingFiles;
- 
+
   std::string actualSourceFile = "";
-  cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Processing coverage (each . represents one file):" << std::endl);
+  cmCTestLog(m_CTest, HANDLER_OUTPUT,
+    "   Processing coverage (each . represents one file):" << std::endl);
   cmCTestLog(m_CTest, HANDLER_OUTPUT, "    ");
   int file_count = 0;
   for ( it = files.begin(); it != files.end(); ++ it )
     {
     cmCTestLog(m_CTest, HANDLER_OUTPUT, "." << std::flush);
     std::string fileDir = cmSystemTools::GetFilenamePath(it->c_str());
-    std::string command = "\"" + gcovCommand + "\" -l -o \"" + fileDir + "\" \"" + *it + "\"";
+    std::string command = "\"" + gcovCommand + "\" -l -o \"" + fileDir
+      + "\" \"" + *it + "\"";
     cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, command.c_str() << std::endl);
     std::string output = "";
     std::string errors = "";
@@ -272,36 +291,43 @@ int cmCTestCoverageHandler::ProcessHandler()
     ofs << "  Command: " << command.c_str() << std::endl;
     int res = m_CTest->RunCommand(command.c_str(), &output, &errors,
       &retVal, tempDir.c_str(), 0 /*m_TimeOut*/);
- 
+
     ofs << "  Output: " << output.c_str() << std::endl;
     ofs << "  Errors: " << errors.c_str() << std::endl;
     if ( ! res )
       {
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "Problem running coverage on file: " << it->c_str() << std::endl);
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "Command produced error: " << errors << std::endl);
+      cmCTestLog(m_CTest, ERROR_MESSAGE, "Problem running coverage on file: "
+        << it->c_str() << std::endl);
+      cmCTestLog(m_CTest, ERROR_MESSAGE, "Command produced error: " << errors
+        << std::endl);
       error ++;
       continue;
       }
     if ( retVal != 0 )
       {
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "Coverage command returned: " << retVal << " while processing: " << it->c_str() << std::endl);
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "Command produced error: " << error << std::endl);
+      cmCTestLog(m_CTest, ERROR_MESSAGE, "Coverage command returned: "
+        << retVal << " while processing: " << it->c_str() << std::endl);
+      cmCTestLog(m_CTest, ERROR_MESSAGE, "Command produced error: " << error
+        << std::endl);
       }
     cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT,
-      "--------------------------------------------------------------" << std::endl
+      "--------------------------------------------------------------"
+      << std::endl
       << output << std::endl
-      << "--------------------------------------------------------------" << std::endl);
+      << "--------------------------------------------------------------"
+      << std::endl);
     std::vector<cmStdString> lines;
     std::vector<cmStdString>::iterator line;
- 
- 
+
+
     // Globals for storing current source file and current gcov file;
     cmSystemTools::Split(output.c_str(), lines);
     for ( line = lines.begin(); line != lines.end(); ++line)
       {
       std::string sourceFile;
       std::string gcovFile;
-      cmCTestLog(m_CTest, DEBUG, "Line: [" << line->c_str() << "]" << std::endl);
+      cmCTestLog(m_CTest, DEBUG, "Line: [" << line->c_str() << "]"
+        << std::endl);
       if ( line->size() == 0 )
         {
         // Ignore empty line; probably style 2
@@ -312,13 +338,14 @@ int cmCTestCoverageHandler::ProcessHandler()
           {
           if ( gcovStyle != 1 )
             {
-            cmCTestLog(m_CTest, ERROR_MESSAGE, "Unknown gcov output style" << std::endl);
+            cmCTestLog(m_CTest, ERROR_MESSAGE, "Unknown gcov output style"
+              << std::endl);
             error ++;
             break;
             }
           gcovStyle = 1;
           }
- 
+
         actualSourceFile = "";
         sourceFile = st1re1.match(2);
         }
@@ -328,13 +355,14 @@ int cmCTestCoverageHandler::ProcessHandler()
           {
           if ( gcovStyle != 1 )
             {
-            cmCTestLog(m_CTest, ERROR_MESSAGE, "Unknown gcov output style" << std::endl);
+            cmCTestLog(m_CTest, ERROR_MESSAGE, "Unknown gcov output style"
+              << std::endl);
             error ++;
             break;
             }
           gcovStyle = 1;
           }
- 
+
         gcovFile = st1re2.match(1);
         }
       else if ( st2re1.find(line->c_str() ) )
@@ -343,13 +371,14 @@ int cmCTestCoverageHandler::ProcessHandler()
           {
           if ( gcovStyle != 2 )
             {
-            cmCTestLog(m_CTest, ERROR_MESSAGE, "Unknown gcov output style" << std::endl);
+            cmCTestLog(m_CTest, ERROR_MESSAGE, "Unknown gcov output style"
+              << std::endl);
             error ++;
             break;
             }
           gcovStyle = 2;
           }
- 
+
         actualSourceFile = "";
         sourceFile = st2re1.match(1);
         }
@@ -359,7 +388,8 @@ int cmCTestCoverageHandler::ProcessHandler()
           {
           if ( gcovStyle != 2 )
             {
-            cmCTestLog(m_CTest, ERROR_MESSAGE, "Unknown gcov output style" << std::endl);
+            cmCTestLog(m_CTest, ERROR_MESSAGE, "Unknown gcov output style"
+              << std::endl);
             error ++;
             break;
             }
@@ -372,13 +402,14 @@ int cmCTestCoverageHandler::ProcessHandler()
           {
           if ( gcovStyle != 2 )
             {
-            cmCTestLog(m_CTest, ERROR_MESSAGE, "Unknown gcov output style" << std::endl);
+            cmCTestLog(m_CTest, ERROR_MESSAGE, "Unknown gcov output style"
+              << std::endl);
             error ++;
             break;
             }
           gcovStyle = 2;
           }
- 
+
         gcovFile = st2re3.match(2);
         }
       else if ( st2re4.find(line->c_str() ) )
@@ -387,60 +418,68 @@ int cmCTestCoverageHandler::ProcessHandler()
           {
           if ( gcovStyle != 2 )
             {
-            cmCTestLog(m_CTest, ERROR_MESSAGE, "Unknown gcov output style" << std::endl);
+            cmCTestLog(m_CTest, ERROR_MESSAGE, "Unknown gcov output style"
+              << std::endl);
             error ++;
             break;
             }
           gcovStyle = 2;
           }
- 
-        cmCTestLog(m_CTest, WARNING, "Warning: " << st2re4.match(1) << " had unexpected EOF" << std::endl);
+
+        cmCTestLog(m_CTest, WARNING, "Warning: " << st2re4.match(1)
+          << " had unexpected EOF" << std::endl);
         }
       else if ( st2re5.find(line->c_str() ) )
         {
         if ( gcovStyle != 0 )
           {
           if ( gcovStyle != 2 )
             {
-            cmCTestLog(m_CTest, ERROR_MESSAGE, "Unknown gcov output style" << std::endl);
+            cmCTestLog(m_CTest, ERROR_MESSAGE, "Unknown gcov output style"
+              << std::endl);
             error ++;
             break;
             }
           gcovStyle = 2;
           }
- 
-        cmCTestLog(m_CTest, WARNING, "Warning: Cannot open file: " << st2re5.match(1) << std::endl);
+
+        cmCTestLog(m_CTest, WARNING, "Warning: Cannot open file: "
+          << st2re5.match(1) << std::endl);
         }
       else if ( st2re6.find(line->c_str() ) )
         {
         if ( gcovStyle != 0 )
           {
           if ( gcovStyle != 2 )
             {
-            cmCTestLog(m_CTest, ERROR_MESSAGE, "Unknown gcov output style" << std::endl);
+            cmCTestLog(m_CTest, ERROR_MESSAGE, "Unknown gcov output style"
+              << std::endl);
             error ++;
             break;
             }
           gcovStyle = 2;
           }
- 
+
         cmCTestLog(m_CTest, WARNING, "Warning: File: " << st2re6.match(1)
           << " is newer than " << st2re6.match(2) << std::endl);
         }
       else
         {
-        cmCTestLog(m_CTest, ERROR_MESSAGE, "Unknown line: [" << line->c_str() << "]" << std::endl);
+        cmCTestLog(m_CTest, ERROR_MESSAGE, "Unknown line: [" << line->c_str()
+          << "]" << std::endl);
         error ++;
         //abort();
         }
       if ( !gcovFile.empty() && actualSourceFile.size() )
         {
         singleFileCoverageVector* vec = &totalCoverage[actualSourceFile];
-        cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "   in file: " << gcovFile << std::endl);
+        cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "   in file: "
+          << gcovFile << std::endl);
         std::ifstream ifile(gcovFile.c_str());
         if ( ! ifile )
           {
-          cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot open file: " << gcovFile << std::endl);
+          cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot open file: "
+            << gcovFile << std::endl);
           }
         else
           {
@@ -449,30 +488,33 @@ int cmCTestCoverageHandler::ProcessHandler()
           while ( cmSystemTools::GetLineFromStream(ifile, nl) )
             {
             cnt ++;
- 
+
             //TODO: Handle gcov 3.0 non-coverage lines
- 
+
             // Skip empty lines
             if ( !nl.size() )
               {
               continue;
               }
- 
+
             // Skip unused lines
             if ( nl.size() < 12 )
               {
               continue;
               }
 
-            // Read the coverage count from the beginning of the gcov output line
+            // Read the coverage count from the beginning of the gcov output
+            // line
             std::string prefix = nl.substr(0, 12);
             int cov = atoi(prefix.c_str());
-            // Read the line number starting at the 10th character of the gcov output line
+            // Read the line number starting at the 10th character of the gcov
+            // output line
             std::string lineNumber = nl.substr(10, 5);
             int lineIdx = atoi(lineNumber.c_str())-1;
             if ( lineIdx >= 0 )
               {
-              while ( vec->size() <= static_cast<singleFileCoverageVector::size_type>(lineIdx) )
+              while ( vec->size() <=
+                static_cast<singleFileCoverageVector::size_type>(lineIdx) )
                 {
                 vec->push_back(-1);
                 }
@@ -499,28 +541,39 @@ int cmCTestCoverageHandler::ProcessHandler()
           sourceFile.substr(0, sourceDir.size()) == sourceDir &&
           sourceFile[sourceDir.size()] == '/' )
           {
-          cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "   produced s: " << sourceFile.c_str() << std::endl);
-          ofs << "  produced in source dir: " << sourceFile.c_str() << std::endl;
-          actualSourceFile = cmSystemTools::CollapseFullPath(sourceFile.c_str());
+          cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "   produced s: "
+            << sourceFile.c_str() << std::endl);
+          ofs << "  produced in source dir: " << sourceFile.c_str()
+            << std::endl;
+          actualSourceFile
+            = cmSystemTools::CollapseFullPath(sourceFile.c_str());
           }
         // Binary dir?
         if ( sourceFile.size() > binaryDir.size() &&
           sourceFile.substr(0, binaryDir.size()) == binaryDir &&
           sourceFile[binaryDir.size()] == '/' )
           {
-          cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "   produced b: " << sourceFile.c_str() << std::endl);
-          ofs << "  produced in binary dir: " << sourceFile.c_str() << std::endl;
-          actualSourceFile = cmSystemTools::CollapseFullPath(sourceFile.c_str());
+          cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "   produced b: "
+            << sourceFile.c_str() << std::endl);
+          ofs << "  produced in binary dir: " << sourceFile.c_str()
+            << std::endl;
+          actualSourceFile
+            = cmSystemTools::CollapseFullPath(sourceFile.c_str());
           }
         if ( actualSourceFile.empty() )
           {
           if ( missingFiles.find(actualSourceFile) == missingFiles.end() )
             {
-            cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Something went wrong" << std::endl);
-            cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "File: [" << sourceFile.c_str() << "]" << std::endl);
-            cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "s: [" << sourceFile.substr(0, sourceDir.size()) << "]" << std::endl);
-            cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "b: [" << sourceFile.substr(0, binaryDir.size()) << "]" << std::endl);
-            ofs << "  Something went wrong. Cannot find: " << sourceFile.c_str()
+            cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Something went wrong"
+              << std::endl);
+            cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "File: ["
+              << sourceFile.c_str() << "]" << std::endl);
+            cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "s: ["
+              << sourceFile.substr(0, sourceDir.size()) << "]" << std::endl);
+            cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "b: ["
+              << sourceFile.substr(0, binaryDir.size()) << "]" << std::endl);
+            ofs << "  Something went wrong. Cannot find: "
+              << sourceFile.c_str()
               << " in source dir: " << sourceDir.c_str()
               << " or binary dir: " << binaryDir.c_str() << std::endl;
             missingFiles.insert(actualSourceFile);
@@ -531,17 +584,19 @@ int cmCTestCoverageHandler::ProcessHandler()
     file_count ++;
     if ( file_count % 50 == 0 )
       {
-      cmCTestLog(m_CTest, HANDLER_OUTPUT, " processed: " << file_count << " out of " << files.size() << std::endl);
+      cmCTestLog(m_CTest, HANDLER_OUTPUT, " processed: " << file_count
+        << " out of " << files.size() << std::endl);
       cmCTestLog(m_CTest, HANDLER_OUTPUT, "    ");
       }
     }
- 
+
   cmGeneratedFileStream covSumFile;
   cmGeneratedFileStream covLogFile;
 
   if (!this->StartResultingXML("Coverage", covSumFile))
     {
-    cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot open coverage summary file." << std::endl);
+    cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot open coverage summary file."
+      << std::endl);
 
     return -1;
     }
@@ -550,7 +605,8 @@ int cmCTestCoverageHandler::ProcessHandler()
   // Produce output xml files
 
   covSumFile << "<Coverage>" << std::endl
-    << "\t<StartDateTime>" << coverage_start_time << "</StartDateTime>" << std::endl;
+    << "\t<StartDateTime>" << coverage_start_time << "</StartDateTime>"
+    << std::endl;
   int logFileCount = 0;
   if ( !this->StartCoverageLogFile(covLogFile, logFileCount) )
     {
@@ -563,7 +619,8 @@ int cmCTestCoverageHandler::ProcessHandler()
   //std::string fullSourceDir = sourceDir + "/";
   //std::string fullBinaryDir = binaryDir + "/";
   cmCTestLog(m_CTest, HANDLER_OUTPUT, std::endl);
-  cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Acumulating results (each . represents one file):" << std::endl);
+  cmCTestLog(m_CTest, HANDLER_OUTPUT,
+    "   Acumulating results (each . represents one file):" << std::endl);
   cmCTestLog(m_CTest, HANDLER_OUTPUT, "    ");
 
   std::vector<std::string> errorsWhileAccumulating;
@@ -577,7 +634,8 @@ int cmCTestCoverageHandler::ProcessHandler()
     file_count ++;
     if ( file_count % 50 == 0 )
       {
-      cmCTestLog(m_CTest, HANDLER_OUTPUT, " processed: " << file_count << " out of "
+      cmCTestLog(m_CTest, HANDLER_OUTPUT, " processed: " << file_count
+        << " out of "
         << totalCoverage.size() << std::endl);
       cmCTestLog(m_CTest, HANDLER_OUTPUT, "    ");
       }
@@ -591,15 +649,19 @@ int cmCTestCoverageHandler::ProcessHandler()
         }
       }
     const std::string fullFileName = fileIterator->first;
-    const std::string fileName = cmSystemTools::GetFilenameName(fullFileName.c_str());
-    std::string fullFilePath = cmSystemTools::GetFilenamePath(fullFileName.c_str());
-    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Process file: " << fullFileName << std::endl);
+    const std::string fileName
+      = cmSystemTools::GetFilenameName(fullFileName.c_str());
+    std::string fullFilePath
+      = cmSystemTools::GetFilenamePath(fullFileName.c_str());
+    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Process file: "
+      << fullFileName << std::endl);
 
     cmSystemTools::ConvertToUnixSlashes(fullFilePath);
 
     if ( !cmSystemTools::FileExists(fullFileName.c_str()) )
       {
-      cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot find file: " << fullFileName.c_str() << std::endl);
+      cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot find file: "
+        << fullFileName.c_str() << std::endl);
       continue;
       }
 
@@ -608,7 +670,8 @@ int cmCTestCoverageHandler::ProcessHandler()
         sourceDir.c_str(), binaryDir.c_str());
     if ( !shouldIDoCoverage )
       {
-      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, ".NoDartCoverage found, so skip coverage check for: "
+      cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT,
+        ".NoDartCoverage found, so skip coverage check for: "
         << fullFileName.c_str()
         << std::endl);
       continue;
@@ -641,12 +704,14 @@ int cmCTestCoverageHandler::ProcessHandler()
       if ( !cmSystemTools::GetLineFromStream(ifs, line) )
         {
         cmOStringStream ostr;
-        ostr << "Problem reading source file: " << fullFileName.c_str() << " line:" << cc;
+        ostr << "Problem reading source file: " << fullFileName.c_str()
+          << " line:" << cc;
         errorsWhileAccumulating.push_back(ostr.str());
         error ++;
         break;
         }
-      covLogFile << "\t\t<Line Number=\"" << cc << "\" Count=\"" << fcov[cc] << "\">"
+      covLogFile << "\t\t<Line Number=\"" << cc << "\" Count=\"" << fcov[cc]
+        << "\">"
         << m_CTest->MakeXMLSafe(line.c_str()) << "</Line>" << std::endl;
       if ( fcov[cc] == 0 )
         {
@@ -698,7 +763,8 @@ int cmCTestCoverageHandler::ProcessHandler()
   if ( errorsWhileAccumulating.size() > 0 )
     {
     cmCTestLog(m_CTest, ERROR_MESSAGE, std::endl);
-    cmCTestLog(m_CTest, ERROR_MESSAGE, "Error(s) while acumulating results:" << std::endl);
+    cmCTestLog(m_CTest, ERROR_MESSAGE, "Error(s) while acumulating results:"
+      << std::endl);
     std::vector<std::string>::iterator erIt;
     for ( erIt = errorsWhileAccumulating.begin();
       erIt != errorsWhileAccumulating.end();
@@ -726,24 +792,25 @@ int cmCTestCoverageHandler::ProcessHandler()
   covSumFile.precision(2);
   covSumFile << (percent_coverage)<< "</PercentCoverage>\n"
     << "\t<EndDateTime>" << end_time << "</EndDateTime>\n";
-  covSumFile << "<ElapsedMinutes>" << 
+  covSumFile << "<ElapsedMinutes>" <<
     static_cast<int>((cmSystemTools::GetTime() - elapsed_time_start)/6)/10.0
     << "</ElapsedMinutes>"
     << "</Coverage>" << std::endl;
   m_CTest->EndXML(covSumFile);
 
-  cmCTestLog(m_CTest, HANDLER_OUTPUT, "\tCovered LOC:         " << total_tested << std::endl
+  cmCTestLog(m_CTest, HANDLER_OUTPUT, "\tCovered LOC:         "
+    << total_tested << std::endl
     << "\tNot covered LOC:     " << total_untested << std::endl
     << "\tTotal LOC:           " << total_lines << std::endl
-    << "\tPercentage Coverage: " 
+    << "\tPercentage Coverage: "
     << std::setiosflags(std::ios::fixed)
     << std::setprecision(2)
     << (percent_coverage) << "%" << std::endl);
 
   ofs << "\tCovered LOC:         " << total_tested << std::endl
     << "\tNot covered LOC:     " << total_untested << std::endl
     << "\tTotal LOC:           " << total_lines << std::endl
-    << "\tPercentage Coverage: " 
+    << "\tPercentage Coverage: "
     << std::setiosflags(std::ios::fixed)
     << std::setprecision(2)
     << (percent_coverage) << "%" << std::endl;
@@ -760,14 +827,16 @@ int cmCTestCoverageHandler::ProcessHandler()
 //----------------------------------------------------------------------
 void cmCTestCoverageHandler::PopulateCustomVectors(cmMakefile *mf)
 {
-  cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, " Add coverage exclude regular expressions." << std::endl);
-  cmCTest::PopulateCustomVector(mf, "CTEST_CUSTOM_COVERAGE_EXCLUDE", 
+  cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT,
+    " Add coverage exclude regular expressions." << std::endl);
+  cmCTest::PopulateCustomVector(mf, "CTEST_CUSTOM_COVERAGE_EXCLUDE",
                                 m_CustomCoverageExclude);
   std::vector<cmStdString>::iterator it;
   for ( it = m_CustomCoverageExclude.begin();
     it != m_CustomCoverageExclude.end();
     ++ it )
     {
-    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, " Add coverage exclude: " << it->c_str() << std::endl);
+    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, " Add coverage exclude: "
+      << it->c_str() << std::endl);
     }
 }