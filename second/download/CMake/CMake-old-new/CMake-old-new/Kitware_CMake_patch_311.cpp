@@ -176,8 +176,8 @@ bool cmCTestCoverageHandler::StartCoverageLogFile(
 {
   char covLogFilename[1024];
   sprintf(covLogFilename, "CoverageLog-%d", logFileCount);
-  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Open file: "
-    << covLogFilename << std::endl);
+  cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Open file: "
+    << covLogFilename << std::endl, this->Quiet);
   if(!this->StartResultingXML(cmCTest::PartCoverage,
                               covLogFilename, covLogFile))
     {
@@ -209,8 +209,8 @@ void cmCTestCoverageHandler::EndCoverageLogFile(cmGeneratedFileStream& ostr,
   this->CTest->EndXML(ostr);
   char covLogFilename[1024];
   sprintf(covLogFilename, "CoverageLog-%d.xml", logFileCount);
-  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Close file: "
-    << covLogFilename << std::endl);
+  cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Close file: "
+    << covLogFilename << std::endl, this->Quiet);
   ostr.Close();
 }
 
@@ -230,8 +230,8 @@ bool cmCTestCoverageHandler::ShouldIDoCoverage(const char* file,
     {
     if ( sit->find(file) )
       {
-      cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "  File " << file
-        << " is excluded in CTestCustom.ctest" << std::endl;);
+      cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "  File " << file
+        << " is excluded in CTestCustom.ctest" << std::endl;, this->Quiet);
       return false;
       }
     }
@@ -272,8 +272,8 @@ bool cmCTestCoverageHandler::ShouldIDoCoverage(const char* file,
       fFile.c_str(), checkDir.c_str());
   if (!ndc.empty())
     {
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Found: " << ndc
-      << " so skip coverage of " << file << std::endl);
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Found: " << ndc
+      << " so skip coverage of " << file << std::endl, this->Quiet);
     return false;
     }
 
@@ -311,8 +311,8 @@ bool cmCTestCoverageHandler::ShouldIDoCoverage(const char* file,
     fFile.c_str(), checkDir.c_str());
   if (!ndc.empty())
     {
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Found: " << ndc
-      << " so skip coverage of: " << file << std::endl);
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Found: " << ndc
+      << " so skip coverage of: " << file << std::endl, this->Quiet);
     return false;
     }
   // Ok, nothing in source tree, nothing in binary tree
@@ -356,13 +356,15 @@ int cmCTestCoverageHandler::ProcessHandler()
   cmSystemTools::ConvertToUnixSlashes(sourceDir);
   cmSystemTools::ConvertToUnixSlashes(binaryDir);
 
-  cmCTestLog(this->CTest, HANDLER_OUTPUT, "Performing coverage" << std::endl);
+  cmCTestOptionalLog(this->CTest, HANDLER_OUTPUT,
+    "Performing coverage" << std::endl, this->Quiet);
 
   cmCTestCoverageHandlerContainer cont;
   cont.Error = error;
   cont.SourceDir = sourceDir;
   cont.BinaryDir = binaryDir;
   cont.OFS = &ofs;
+  cont.Quiet = this->Quiet;
 
   // setup the regex exclude stuff
   this->CustomCoverageExcludeRegex.clear();
@@ -442,9 +444,9 @@ int cmCTestCoverageHandler::ProcessHandler()
 
   if ( file_count == 0 )
     {
-    cmCTestLog(this->CTest, WARNING,
+    cmCTestOptionalLog(this->CTest, WARNING,
       " Cannot find any coverage files. Ignoring Coverage request."
-      << std::endl);
+      << std::endl, this->Quiet);
     return error;
     }
   cmGeneratedFileStream covSumFile;
@@ -476,10 +478,11 @@ int cmCTestCoverageHandler::ProcessHandler()
   long total_untested = 0;
   //std::string fullSourceDir = sourceDir + "/";
   //std::string fullBinaryDir = binaryDir + "/";
-  cmCTestLog(this->CTest, HANDLER_OUTPUT, std::endl);
-  cmCTestLog(this->CTest, HANDLER_OUTPUT,
-    "   Accumulating results (each . represents one file):" << std::endl);
-  cmCTestLog(this->CTest, HANDLER_OUTPUT, "    ");
+  cmCTestOptionalLog(this->CTest, HANDLER_OUTPUT, std::endl, this->Quiet);
+  cmCTestOptionalLog(this->CTest, HANDLER_OUTPUT,
+    "   Accumulating results (each . represents one file):" << std::endl,
+    this->Quiet);
+  cmCTestOptionalLog(this->CTest, HANDLER_OUTPUT, "    ", this->Quiet);
 
   std::vector<std::string> errorsWhileAccumulating;
 
@@ -488,14 +491,16 @@ int cmCTestCoverageHandler::ProcessHandler()
     fileIterator != cont.TotalCoverage.end();
     ++fileIterator )
     {
-    cmCTestLog(this->CTest, HANDLER_OUTPUT, "." << std::flush);
+    cmCTestOptionalLog(this->CTest, HANDLER_OUTPUT, "." << std::flush,
+      this->Quiet);
     file_count ++;
     if ( file_count % 50 == 0 )
       {
-      cmCTestLog(this->CTest, HANDLER_OUTPUT, " processed: " << file_count
+      cmCTestOptionalLog(this->CTest, HANDLER_OUTPUT, " processed: "
+        << file_count
         << " out of "
-        << cont.TotalCoverage.size() << std::endl);
-      cmCTestLog(this->CTest, HANDLER_OUTPUT, "    ");
+        << cont.TotalCoverage.size() << std::endl, this->Quiet);
+      cmCTestOptionalLog(this->CTest, HANDLER_OUTPUT, "    ", this->Quiet);
       }
 
     const std::string fullFileName = fileIterator->first;
@@ -504,15 +509,15 @@ int cmCTestCoverageHandler::ProcessHandler()
         sourceDir.c_str(), binaryDir.c_str());
     if ( !shouldIDoCoverage )
       {
-      cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+      cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
         ".NoDartCoverage found, so skip coverage check for: "
         << fullFileName
-        << std::endl);
+        << std::endl, this->Quiet);
       continue;
       }
 
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-      "Process file: " << fullFileName << std::endl);
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+      "Process file: " << fullFileName << std::endl, this->Quiet);
 
     if ( !cmSystemTools::FileExists(fullFileName.c_str()) )
       {
@@ -556,8 +561,9 @@ int cmCTestCoverageHandler::ProcessHandler()
 
     cmCTestCoverageHandlerContainer::SingleFileCoverageVector::size_type cc;
     std::string line;
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-      "Actually performing coverage for: " << fullFileName << std::endl);
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+      "Actually performing coverage for: " << fullFileName << std::endl,
+      this->Quiet);
     for ( cc= 0; cc < fcov.size(); cc ++ )
       {
       if ( !cmSystemTools::GetLineFromStream(ifs, line) &&
@@ -641,8 +647,8 @@ int cmCTestCoverageHandler::ProcessHandler()
       }
     int untested = 0;
     std::string line;
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-      "Actually performing coverage for: " << *i << std::endl);
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+      "Actually performing coverage for: " << *i << std::endl, this->Quiet);
     while (cmSystemTools::GetLineFromStream(ifs, line))
       {
       covLogFile << "\t\t<Line Number=\"" << untested << "\" Count=\"0\">"
@@ -736,8 +742,8 @@ int cmCTestCoverageHandler::ProcessHandler()
 //----------------------------------------------------------------------
 void cmCTestCoverageHandler::PopulateCustomVectors(cmMakefile *mf)
 {
-  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-    " Add coverage exclude regular expressions." << std::endl);
+  cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+    " Add coverage exclude regular expressions." << std::endl, this->Quiet);
   this->CTest->PopulateCustomVector(mf, "CTEST_CUSTOM_COVERAGE_EXCLUDE",
                                 this->CustomCoverageExclude);
   this->CTest->PopulateCustomVector(mf, "CTEST_EXTRA_COVERAGE_GLOB",
@@ -747,14 +753,14 @@ void cmCTestCoverageHandler::PopulateCustomVectors(cmMakefile *mf)
     it != this->CustomCoverageExclude.end();
     ++ it )
     {
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, " Add coverage exclude: "
-      << *it << std::endl);
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+      " Add coverage exclude: " << *it << std::endl, this->Quiet);
     }
   for ( it = this->ExtraCoverageGlobs.begin();
     it != this->ExtraCoverageGlobs.end(); ++it)
     {
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, " Add coverage glob: "
-      << *it << std::endl);
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+      " Add coverage glob: " << *it << std::endl, this->Quiet);
     }
 }
 
@@ -812,16 +818,16 @@ int cmCTestCoverageHandler::HandleCoberturaCoverage(
 
   if(cmSystemTools::FileExists(coverageXMLFile.c_str()))
     {
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
                "Parsing Cobertura XML file: " << coverageXMLFile
-               << std::endl);
+               << std::endl, this->Quiet);
     cov.ReadCoverageXML(coverageXMLFile.c_str());
     }
   else
     {
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
                "Cannot find Cobertura XML file: " << coverageXMLFile
-               << std::endl);
+               << std::endl, this->Quiet);
     }
   return static_cast<int>(cont->TotalCoverage.size());
 }
@@ -836,33 +842,33 @@ int cmCTestCoverageHandler::HandleMumpsCoverage(
     "/gtm_coverage.mcov";
   if(cmSystemTools::FileExists(coverageFile.c_str()))
     {
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
                "Parsing Cache Coverage: " << coverageFile
-               << std::endl);
+               << std::endl, this->Quiet);
     cov.ReadCoverageFile(coverageFile.c_str());
     return static_cast<int>(cont->TotalCoverage.size());
     }
   else
     {
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-               " Cannot find foobar GTM coverage file: " << coverageFile
-               << std::endl);
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+               " Cannot find GTM coverage file: " << coverageFile
+               << std::endl, this->Quiet);
     }
   cmParseCacheCoverage ccov(*cont, this->CTest);
   coverageFile = this->CTest->GetBinaryDir() +
     "/cache_coverage.cmcov";
   if(cmSystemTools::FileExists(coverageFile.c_str()))
     {
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
                "Parsing Cache Coverage: " << coverageFile
-               << std::endl);
+               << std::endl, this->Quiet);
     ccov.ReadCoverageFile(coverageFile.c_str());
     }
   else
     {
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
                " Cannot find Cache coverage file: " << coverageFile
-               << std::endl);
+               << std::endl, this->Quiet);
     }
   return static_cast<int>(cont->TotalCoverage.size());
 }
@@ -912,15 +918,15 @@ int cmCTestCoverageHandler::HandleJacocoCoverage(
   files=g.GetFiles();
   if (!files.empty())
     {
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-      "Found Jacoco Files, Performing Coverage" << std::endl);
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+      "Found Jacoco Files, Performing Coverage" << std::endl, this->Quiet);
     cov.LoadCoverageData(files);
     }
   else
     {
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
       " Cannot find Jacoco coverage files: " << coverageFile
-      << std::endl);
+      << std::endl, this->Quiet);
     }
   return static_cast<int>(cont->TotalCoverage.size());
 }
@@ -945,15 +951,16 @@ int cmCTestCoverageHandler::HandleDelphiCoverage(
   files=g.GetFiles();
   if (!files.empty())
     {
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-      "Found Delphi HTML Files, Performing Coverage" << std::endl);
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+      "Found Delphi HTML Files, Performing Coverage" << std::endl,
+      this->Quiet);
     cov.LoadCoverageData(files);
     }
   else
     {
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
       " Cannot find Delphi coverage files: " << coverageFile
-      << std::endl);
+      << std::endl, this->Quiet);
     }
   return static_cast<int>(cont->TotalCoverage.size());
 }
@@ -975,15 +982,16 @@ int cmCTestCoverageHandler::HandleBlanketJSCoverage(
   files=g.GetFiles();
   if (!files.empty())
     {
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-      "Found BlanketJS output JSON, Performing Coverage" << std::endl);
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+      "Found BlanketJS output JSON, Performing Coverage" << std::endl,
+      this->Quiet);
     cov.LoadCoverageData(files);
     }
   else
     {
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
        " Cannot find BlanketJS coverage files: " << coverageFile
-       << std::endl);
+       << std::endl, this->Quiet);
     }
   return static_cast<int>(cont->TotalCoverage.size());
   }
@@ -1039,9 +1047,9 @@ int cmCTestCoverageHandler::HandleGCovCoverage(
 
   if (files.empty())
     {
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
       " Cannot find any GCov coverage files."
-      << std::endl);
+      << std::endl, this->Quiet);
     // No coverage files is a valid thing, so the exit code is 0
     return 0;
     }
@@ -1057,9 +1065,10 @@ int cmCTestCoverageHandler::HandleGCovCoverage(
   std::set<std::string> missingFiles;
 
   std::string actualSourceFile = "";
-  cmCTestLog(this->CTest, HANDLER_OUTPUT,
-    "   Processing coverage (each . represents one file):" << std::endl);
-  cmCTestLog(this->CTest, HANDLER_OUTPUT, "    ");
+  cmCTestOptionalLog(this->CTest, HANDLER_OUTPUT,
+    "   Processing coverage (each . represents one file):" << std::endl,
+    this->Quiet);
+  cmCTestOptionalLog(this->CTest, HANDLER_OUTPUT, "    ", this->Quiet);
   int file_count = 0;
 
   // make sure output from gcov is in English!
@@ -1072,7 +1081,8 @@ int cmCTestCoverageHandler::HandleGCovCoverage(
   //
   for ( it = files.begin(); it != files.end(); ++ it )
     {
-    cmCTestLog(this->CTest, HANDLER_OUTPUT, "." << std::flush);
+    cmCTestOptionalLog(this->CTest, HANDLER_OUTPUT, "." << std::flush,
+      this->Quiet);
 
     // Call gcov to get coverage data for this *.gcda file:
     //
@@ -1082,8 +1092,8 @@ int cmCTestCoverageHandler::HandleGCovCoverage(
       "-o \"" + fileDir + "\" " +
       "\"" + *it + "\"";
 
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, command.c_str()
-      << std::endl);
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT, command.c_str()
+      << std::endl, this->Quiet);
 
     std::string output = "";
     std::string errors = "";
@@ -1111,12 +1121,12 @@ int cmCTestCoverageHandler::HandleGCovCoverage(
       cmCTestLog(this->CTest, ERROR_MESSAGE,
         "Command produced error: " << cont->Error << std::endl);
       }
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
       "--------------------------------------------------------------"
       << std::endl
       << output << std::endl
       << "--------------------------------------------------------------"
-      << std::endl);
+      << std::endl, this->Quiet);
 
     std::vector<std::string> lines;
     std::vector<std::string>::iterator line;
@@ -1128,8 +1138,8 @@ int cmCTestCoverageHandler::HandleGCovCoverage(
       std::string sourceFile;
       std::string gcovFile;
 
-      cmCTestLog(this->CTest, DEBUG, "Line: [" << *line << "]"
-        << std::endl);
+      cmCTestOptionalLog(this->CTest, DEBUG, "Line: [" << *line << "]"
+        << std::endl, this->Quiet);
 
       if (line->empty())
         {
@@ -1229,8 +1239,8 @@ int cmCTestCoverageHandler::HandleGCovCoverage(
           break;
           }
 
-        cmCTestLog(this->CTest, WARNING, "Warning: " << st2re4.match(1)
-          << " had unexpected EOF" << std::endl);
+        cmCTestOptionalLog(this->CTest, WARNING, "Warning: " << st2re4.match(1)
+          << " had unexpected EOF" << std::endl, this->Quiet);
         }
       else if ( st2re5.find(line->c_str() ) )
         {
@@ -1246,8 +1256,8 @@ int cmCTestCoverageHandler::HandleGCovCoverage(
           break;
           }
 
-        cmCTestLog(this->CTest, WARNING, "Warning: Cannot open file: "
-          << st2re5.match(1) << std::endl);
+        cmCTestOptionalLog(this->CTest, WARNING, "Warning: Cannot open file: "
+          << st2re5.match(1) << std::endl, this->Quiet);
         }
       else if ( st2re6.find(line->c_str() ) )
         {
@@ -1263,8 +1273,9 @@ int cmCTestCoverageHandler::HandleGCovCoverage(
           break;
           }
 
-        cmCTestLog(this->CTest, WARNING, "Warning: File: " << st2re6.match(1)
-          << " is newer than " << st2re6.match(2) << std::endl);
+        cmCTestOptionalLog(this->CTest, WARNING, "Warning: File: "
+          << st2re6.match(1)
+          << " is newer than " << st2re6.match(2) << std::endl, this->Quiet);
         }
       else
         {
@@ -1291,8 +1302,8 @@ int cmCTestCoverageHandler::HandleGCovCoverage(
         cmCTestCoverageHandlerContainer::SingleFileCoverageVector& vec
           = cont->TotalCoverage[actualSourceFile];
 
-        cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "   in gcovFile: "
-          << gcovFile << std::endl);
+        cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+          "   in gcovFile: " << gcovFile << std::endl, this->Quiet);
 
         cmsys::ifstream ifile(gcovFile.c_str());
         if ( ! ifile )
@@ -1366,17 +1377,17 @@ int cmCTestCoverageHandler::HandleGCovCoverage(
         //
         if ( IsFileInDir(sourceFile, cont->SourceDir) )
           {
-          cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "   produced s: "
-            << sourceFile << std::endl);
+          cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+            "   produced s: " << sourceFile << std::endl, this->Quiet);
           *cont->OFS << "  produced in source dir: " << sourceFile
             << std::endl;
           actualSourceFile
             = cmSystemTools::CollapseFullPath(sourceFile);
           }
         else if ( IsFileInDir(sourceFile, cont->BinaryDir) )
           {
-          cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "   produced b: "
-            << sourceFile << std::endl);
+          cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+            "   produced b: " << sourceFile << std::endl, this->Quiet);
           *cont->OFS << "  produced in binary dir: " << sourceFile
             << std::endl;
           actualSourceFile
@@ -1387,19 +1398,19 @@ int cmCTestCoverageHandler::HandleGCovCoverage(
           {
           if ( missingFiles.find(sourceFile) == missingFiles.end() )
             {
-            cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-              "Something went wrong" << std::endl);
-            cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+            cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+              "Something went wrong" << std::endl, this->Quiet);
+            cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
               "Cannot find file: ["
-              << sourceFile << "]" << std::endl);
-            cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+              << sourceFile << "]" << std::endl, this->Quiet);
+            cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
               " in source dir: ["
               << cont->SourceDir << "]"
-              << std::endl);
-            cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+              << std::endl, this->Quiet);
+            cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
               " or binary dir: ["
               << cont->BinaryDir.size() << "]"
-              << std::endl);
+              << std::endl, this->Quiet);
             *cont->OFS << "  Something went wrong. Cannot find file: "
               << sourceFile
               << " in source dir: " << cont->SourceDir
@@ -1415,9 +1426,10 @@ int cmCTestCoverageHandler::HandleGCovCoverage(
 
     if ( file_count % 50 == 0 )
       {
-      cmCTestLog(this->CTest, HANDLER_OUTPUT, " processed: " << file_count
-        << " out of " << files.size() << std::endl);
-      cmCTestLog(this->CTest, HANDLER_OUTPUT, "    ");
+      cmCTestOptionalLog(this->CTest, HANDLER_OUTPUT, " processed: "
+        << file_count
+        << " out of " << files.size() << std::endl, this->Quiet);
+      cmCTestOptionalLog(this->CTest, HANDLER_OUTPUT, "    ", this->Quiet);
       }
     }
 
@@ -1435,32 +1447,32 @@ int cmCTestCoverageHandler::HandleLCovCoverage(
     = this->CTest->GetCTestConfiguration("CoverageExtraFlags");
   if ( lcovCommand != "codecov" )
     {
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
                " Not a valid Intel Coverage command."
-               << std::endl);
+               << std::endl, this->Quiet);
     return 0;
     }
   // There is only percentage completed output from LCOV
   std::string st2lcovOutputRex3 = "[0-9]+%";
   cmsys::RegularExpression st2re3(st2lcovOutputRex3.c_str());
 
-  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+  cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
     " This is coverage command: " << lcovCommand
-    << std::endl);
+    << std::endl, this->Quiet);
 
-  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+  cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
     " These are coverage command flags: " << lcovExtraFlags
-    << std::endl);
+    << std::endl, this->Quiet);
 
   std::vector<std::string> files;
   this->FindLCovFiles(files);
   std::vector<std::string>::iterator it;
 
   if (files.empty())
     {
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
       " Cannot find any LCov coverage files."
-      << std::endl);
+      << std::endl, this->Quiet);
     // No coverage files is a valid thing, so the exit code is 0
     return 0;
     }
@@ -1471,9 +1483,10 @@ int cmCTestCoverageHandler::HandleLCovCoverage(
   std::set<std::string> missingFiles;
 
   std::string actualSourceFile = "";
-  cmCTestLog(this->CTest, HANDLER_OUTPUT,
-    "   Processing coverage (each . represents one file):" << std::endl);
-  cmCTestLog(this->CTest, HANDLER_OUTPUT, "    ");
+  cmCTestOptionalLog(this->CTest, HANDLER_OUTPUT,
+    "   Processing coverage (each . represents one file):" << std::endl,
+    this->Quiet);
+  cmCTestOptionalLog(this->CTest, HANDLER_OUTPUT, "    ", this->Quiet);
   int file_count = 0;
 
   // make sure output from lcov is in English!
@@ -1484,16 +1497,17 @@ int cmCTestCoverageHandler::HandleLCovCoverage(
   // directory. It collects all *.dyn files to generate .dpi file.
   for ( it = files.begin(); it != files.end(); ++ it )
     {
-    cmCTestLog(this->CTest, HANDLER_OUTPUT, "." << std::flush);
+    cmCTestOptionalLog(this->CTest, HANDLER_OUTPUT, "." << std::flush,
+      this->Quiet);
     std::string fileDir = cmSystemTools::GetFilenamePath(*it);
     cmSystemTools::ChangeDirectory(fileDir);
     std::string command = "\"" + lcovCommand + "\" " +
       lcovExtraFlags + " ";
 
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Current coverage dir: "
-               << fileDir << std::endl);
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, command.c_str()
-               << std::endl);
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+      "Current coverage dir: " << fileDir << std::endl, this->Quiet);
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT, command.c_str()
+      << std::endl, this->Quiet);
 
     std::string output = "";
     std::string errors = "";
@@ -1521,12 +1535,12 @@ int cmCTestCoverageHandler::HandleLCovCoverage(
       cmCTestLog(this->CTest, ERROR_MESSAGE,
         "Command produced error: " << cont->Error << std::endl);
       }
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
       "--------------------------------------------------------------"
       << std::endl
       << output << std::endl
       << "--------------------------------------------------------------"
-      << std::endl);
+      << std::endl, this->Quiet);
 
     std::vector<std::string> lines;
     std::vector<std::string>::iterator line;
@@ -1554,8 +1568,8 @@ int cmCTestCoverageHandler::HandleLCovCoverage(
       std::string daGlob;
       daGlob = dir;
       daGlob += "/*.LCOV";
-      cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-                 "   looking for LCOV files in: " << daGlob << std::endl);
+      cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+        "   looking for LCOV files in: " << daGlob << std::endl, this->Quiet);
       gl.FindFiles(daGlob);
       // Keep a list of all LCOV files
       lcovFiles.insert(lcovFiles.end(), gl.GetFiles().begin(),
@@ -1590,22 +1604,22 @@ int cmCTestCoverageHandler::HandleLCovCoverage(
         for(std::vector<std::string>::iterator t = lcovFiles.begin();
             t != lcovFiles.end(); ++t)
           {
-          cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Found LCOV File: "
-                     << *t << std::endl);
+          cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+            "Found LCOV File: " << *t << std::endl, this->Quiet);
           }
-        cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "SourceFile: "
-                   << sourceFile << std::endl);
-        cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "lCovFile: "
-                   << lcovFile << std::endl);
+        cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "SourceFile: "
+          << sourceFile << std::endl, this->Quiet);
+        cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "lCovFile: "
+        << lcovFile << std::endl, this->Quiet);
 
         // If we have some LCOV files to process
         if ( !lcovFile.empty() && !actualSourceFile.empty() )
           {
           cmCTestCoverageHandlerContainer::SingleFileCoverageVector& vec
             = cont->TotalCoverage[actualSourceFile];
 
-          cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "   in lcovFile: "
-                     << lcovFile << std::endl);
+          cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+            "   in lcovFile: " << lcovFile << std::endl, this->Quiet);
 
           cmsys::ifstream ifile(lcovFile.c_str());
           if ( ! ifile )
@@ -1620,8 +1634,8 @@ int cmCTestCoverageHandler::HandleLCovCoverage(
 
             // Skip the first line
             cmSystemTools::GetLineFromStream(ifile, nl);
-            cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-                       "File is ready, start reading." << std::endl);
+            cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+              "File is ready, start reading." << std::endl, this->Quiet);
             while ( cmSystemTools::GetLineFromStream(ifile, nl) )
               {
               cnt ++;
@@ -1679,9 +1693,10 @@ int cmCTestCoverageHandler::HandleLCovCoverage(
 
     if ( file_count % 50 == 0 )
       {
-      cmCTestLog(this->CTest, HANDLER_OUTPUT, " processed: " << file_count
-                 << " out of " << files.size() << std::endl);
-      cmCTestLog(this->CTest, HANDLER_OUTPUT, "    ");
+      cmCTestOptionalLog(this->CTest, HANDLER_OUTPUT,
+        " processed: " << file_count << " out of " << files.size()
+        << std::endl, this->Quiet);
+      cmCTestOptionalLog(this->CTest, HANDLER_OUTPUT, "    ", this->Quiet);
       }
     }
 
@@ -1707,8 +1722,8 @@ void cmCTestCoverageHandler::FindGCovFiles(std::vector<std::string>& files)
 
     // Coverage files appear next to their object files in the target
     // support directory.
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-               "   globbing for coverage in: " << lmi->first << std::endl);
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+      "   globbing for coverage in: " << lmi->first << std::endl, this->Quiet);
     std::string daGlob = lmi->first;
     daGlob += "/*.da";
     gl.FindFiles(daGlob);
@@ -1740,12 +1755,12 @@ void cmCTestCoverageHandler::FindLCovFiles(std::vector<std::string>& files)
   std::string daGlob;
   daGlob = prevBinaryDir;
   daGlob += "/*.dpi";
-  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-             "   looking for dpi files in: " << daGlob << std::endl);
+  cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+    "   looking for dpi files in: " << daGlob << std::endl, this->Quiet);
   gl.FindFiles(daGlob);
   files.insert(files.end(), gl.GetFiles().begin(), gl.GetFiles().end());
-  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-             "Now searching in: " << daGlob << std::endl);
+  cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+    "Now searching in: " << daGlob << std::endl, this->Quiet);
 }
 
 //----------------------------------------------------------------------
@@ -1761,9 +1776,9 @@ int cmCTestCoverageHandler::HandleTracePyCoverage(
 
   if (files.empty())
     {
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
       " Cannot find any Python Trace.py coverage files."
-      << std::endl);
+      << std::endl, this->Quiet);
     // No coverage files is a valid thing, so the exit code is 0
     return 0;
     }
@@ -1791,13 +1806,13 @@ int cmCTestCoverageHandler::HandleTracePyCoverage(
 
     std::string actualSourceFile
       = cmSystemTools::CollapseFullPath(fileName);
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
       "   Check coverage for file: " << actualSourceFile
-      << std::endl);
+      << std::endl, this->Quiet);
     cmCTestCoverageHandlerContainer::SingleFileCoverageVector* vec
       = &cont->TotalCoverage[actualSourceFile];
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-      "   in file: " << *fileIt << std::endl);
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+      "   in file: " << *fileIt << std::endl, this->Quiet);
     cmsys::ifstream ifile(fileIt->c_str());
     if ( ! ifile )
       {
@@ -1850,9 +1865,9 @@ int cmCTestCoverageHandler::HandleTracePyCoverage(
           // So, this will be set to 0.
           cov = 0;
           }
-        cmCTestLog(this->CTest, DEBUG, "Prefix: " << prefix
+        cmCTestOptionalLog(this->CTest, DEBUG, "Prefix: " << prefix
           << " cov: " << cov
-          << std::endl);
+          << std::endl, this->Quiet);
         // Read the line number starting at the 10th character of the gcov
         // output line
         long lineIdx = cnt;
@@ -1945,18 +1960,16 @@ int cmCTestCoverageHandler::RunBullseyeCoverageBranch(
   // for each file run covbr on that file to get the coverage
   // information for that file
   std::string outputFile;
-  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-                 "run covbr: "
-                 << std::endl);
+  cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+    "run covbr: " << std::endl, this->Quiet);
 
   if(!this->RunBullseyeCommand(cont, "covbr", 0, outputFile))
     {
     cmCTestLog(this->CTest, ERROR_MESSAGE, "error running covbr for." << "\n");
     return -1;
     }
-  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-             "covbr output in  " << outputFile
-             << std::endl);
+  cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+    "covbr output in  " << outputFile << std::endl, this->Quiet);
   // open the output file
   cmsys::ifstream fin(outputFile.c_str());
   if(!fin)
@@ -2002,10 +2015,8 @@ int cmCTestCoverageHandler::RunBullseyeCoverageBranch(
       // only allow 100 files in each log file
       if ( count != 0 && count % 100 == 0 )
         {
-        cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-                   "start a new log file: "
-                   << count
-                   << std::endl);
+        cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+          "start a new log file: " << count << std::endl, this->Quiet);
         this->EndCoverageLogFile(covLogFile, logFileCount);
         logFileCount ++;
         if ( !this->StartCoverageLogFile(covLogFile, logFileCount) )
@@ -2021,10 +2032,9 @@ int cmCTestCoverageHandler::RunBullseyeCoverageBranch(
         {
         // we have a new file so count it in the output
         count++;
-        cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-                   "Produce coverage for file: "
-                   << file << " " << count
-                   << std::endl);
+        cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+          "Produce coverage for file: " << file << " " << count
+          << std::endl, this->Quiet);
         // start the file output
         covLogFile << "\t<File Name=\""
                    << cmXMLSafe(i->first)
@@ -2083,13 +2093,13 @@ int cmCTestCoverageHandler::RunBullseyeCommand(
     }
   if(arg)
     {
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-               "Run : " << program << " " << arg << "\n");
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+      "Run : " << program << " " << arg << "\n", this->Quiet);
     }
   else
     {
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-               "Run : " << program << "\n");
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+      "Run : " << program << "\n", this->Quiet);
     }
   // create a process object and start it
   cmCTestRunProcess runCoverageSrc;
@@ -2215,17 +2225,17 @@ int cmCTestCoverageHandler::RunBullseyeSourceSummary(
                                   cont->BinaryDir.c_str());
       if ( !shouldIDoCoverage )
         {
-        cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-                   ".NoDartCoverage found, so skip coverage check for: "
-                   << file
-                   << std::endl);
+        cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+          ".NoDartCoverage found, so skip coverage check for: "
+          << file
+          << std::endl, this->Quiet);
         continue;
         }
 
-      cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-                 "Doing coverage for: "
-                 << file
-                 << std::endl);
+      cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+        "Doing coverage for: "
+        << file
+        << std::endl, this->Quiet);
 
       coveredFiles.push_back(sourceFile);
       coveredFilesFullPath.push_back(file);
@@ -2328,23 +2338,23 @@ int cmCTestCoverageHandler::HandleBullseyeCoverage(
   const char* covfile = cmSystemTools::GetEnv("COVFILE");
   if(!covfile || strlen(covfile) == 0)
     {
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-               " COVFILE environment variable not found, not running "
-               " bullseye\n");
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+      " COVFILE environment variable not found, not running "
+      " bullseye\n", this->Quiet);
     return 0;
     }
-  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-             " run covsrc with COVFILE=["
-             << covfile
-             << "]" << std::endl);
+  cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+    " run covsrc with COVFILE=["
+    << covfile
+    << "]" << std::endl, this->Quiet);
   if(!this->RunBullseyeSourceSummary(cont))
     {
     cmCTestLog(this->CTest, ERROR_MESSAGE,
                "Error running bullseye summary.\n");
     return 0;
     }
-  cmCTestLog(this->CTest, DEBUG, "HandleBullseyeCoverage return 1 "
-             << std::endl);
+  cmCTestOptionalLog(this->CTest, DEBUG, "HandleBullseyeCoverage return 1 "
+  << std::endl, this->Quiet);
   return 1;
 }
 
@@ -2438,8 +2448,8 @@ void cmCTestCoverageHandler::LoadLabels()
   std::string fileList = this->CTest->GetBinaryDir();
   fileList += cmake::GetCMakeFilesDirectory();
   fileList += "/TargetDirectories.txt";
-  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-             " target directory list [" << fileList << "]\n");
+  cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+    " target directory list [" << fileList << "]\n", this->Quiet);
   cmsys::ifstream finList(fileList.c_str());
   std::string line;
   while(cmSystemTools::GetLineFromStream(finList, line))
@@ -2460,8 +2470,8 @@ void cmCTestCoverageHandler::LoadLabels(const char* dir)
     return;
     }
 
-  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-             " loading labels from [" << fname << "]\n");
+  cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+    " loading labels from [" << fname << "]\n", this->Quiet);
   bool inTarget = true;
   std::string source;
   std::string line;