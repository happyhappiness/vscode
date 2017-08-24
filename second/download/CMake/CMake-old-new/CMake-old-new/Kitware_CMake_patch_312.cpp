@@ -527,10 +527,10 @@ int cmCTestTestHandler::ProcessHandler()
 
   this->TestResults.clear();
 
-  cmCTestLog(this->CTest, HANDLER_OUTPUT,
+  cmCTestOptionalLog(this->CTest, HANDLER_OUTPUT,
              (this->MemCheck ? "Memory check" : "Test")
              << " project " << cmSystemTools::GetCurrentWorkingDirectory()
-             << std::endl);
+             << std::endl, this->Quiet);
   if ( ! this->PreProcessHandler() )
     {
     return -1;
@@ -567,13 +567,13 @@ int cmCTestTestHandler::ProcessHandler()
     if (this->HandlerVerbose && !passed.empty() &&
       (this->UseIncludeRegExpFlag || this->UseExcludeRegExpFlag))
       {
-      cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, std::endl
-        << "The following tests passed:" << std::endl);
+      cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT, std::endl
+        << "The following tests passed:" << std::endl, this->Quiet);
       for(std::vector<std::string>::iterator j = passed.begin();
           j != passed.end(); ++j)
         {
-        cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "\t" << *j
-          << std::endl);
+        cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "\t" << *j
+          << std::endl, this->Quiet);
         }
       }
 
@@ -593,8 +593,8 @@ int cmCTestTestHandler::ProcessHandler()
       }
     char realBuf[1024];
     sprintf(realBuf, "%6.2f sec", (double)(clock_finish - clock_start));
-    cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nTotal Test time (real) = "
-               << realBuf << "\n" );
+    cmCTestOptionalLog(this->CTest, HANDLER_OUTPUT,
+      "\nTotal Test time (real) = " << realBuf << "\n", this->Quiet );
 
     if (!failed.empty())
       {
@@ -614,11 +614,11 @@ int cmCTestTestHandler::ProcessHandler()
         if ( ftit->Status != cmCTestTestHandler::COMPLETED )
           {
           ofs << ftit->TestCount << ":" << ftit->Name << std::endl;
-          cmCTestLog(this->CTest, HANDLER_OUTPUT, "\t" << std::setw(3)
+          cmCTestOptionalLog(this->CTest, HANDLER_OUTPUT, "\t" << std::setw(3)
                      << ftit->TestCount << " - "
                      << ftit->Name << " ("
                      << this->GetTestStatus(ftit->Status) << ")"
-                     << std::endl);
+                     << std::endl, this->Quiet);
           }
         }
       }
@@ -700,7 +700,8 @@ void cmCTestTestHandler::PrintLabelSummary()
   // now print times
   if(!labels.empty())
     {
-    cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nLabel Time Summary:");
+    cmCTestOptionalLog(this->CTest, HANDLER_OUTPUT, "\nLabel Time Summary:",
+      this->Quiet);
     }
   for(std::set<std::string>::const_iterator i = labels.begin();
       i != labels.end(); ++i)
@@ -709,8 +710,8 @@ void cmCTestTestHandler::PrintLabelSummary()
     label.resize(maxlen +3, ' ');
     char buf[1024];
     sprintf(buf, "%6.2f sec", labelTimes[*i]);
-    cmCTestLog(this->CTest, HANDLER_OUTPUT, "\n"
-               << label << " = " << buf );
+    cmCTestOptionalLog(this->CTest, HANDLER_OUTPUT, "\n"
+               << label << " = " << buf, this->Quiet );
     if ( this->LogFile )
       {
       *this->LogFile << "\n" << *i << " = "
@@ -723,7 +724,7 @@ void cmCTestTestHandler::PrintLabelSummary()
       {
       *this->LogFile << "\n";
       }
-    cmCTestLog(this->CTest, HANDLER_OUTPUT, "\n");
+    cmCTestOptionalLog(this->CTest, HANDLER_OUTPUT, "\n", this->Quiet);
     }
 
 }
@@ -1063,6 +1064,7 @@ void cmCTestTestHandler::ProcessDirectory(std::vector<std::string> &passed,
   parallel->SetCTest(this->CTest);
   parallel->SetParallelLevel(this->CTest->GetParallelLevel());
   parallel->SetTestHandler(this);
+  parallel->SetQuiet(this->Quiet);
 
   *this->LogFile << "Start testing: "
     << this->CTest->CurrentTime() << std::endl
@@ -1334,8 +1336,8 @@ int cmCTestTestHandler::ExecuteCommands(std::vector<std::string>& vec)
   for ( it = vec.begin(); it != vec.end(); ++it )
     {
     int retVal = 0;
-    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Run command: " << *it
-      << std::endl);
+    cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Run command: " <<
+      *it << std::endl, this->Quiet);
     if ( !cmSystemTools::RunSingleCommand(it->c_str(), 0, &retVal, 0,
                                           cmSystemTools::OUTPUT_MERGE
         /*this->Verbose*/) || retVal != 0 )
@@ -1541,8 +1543,7 @@ ::FindExecutable(cmCTest *ctest,
     for(std::vector<std::string>::iterator i = failed.begin();
         i != failed.end(); ++i)
       {
-      cmCTestLog(ctest, HANDLER_OUTPUT,
-                 i->c_str() << "\n");
+      cmCTestLog(ctest, HANDLER_OUTPUT, i->c_str() << "\n");
       }
     }
 
@@ -1571,8 +1572,8 @@ void cmCTestTestHandler::GetListOfTests()
     {
     this->ExcludeTestsRegularExpression.compile(this->ExcludeRegExp.c_str());
     }
-  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-    "Constructing a list of tests" << std::endl);
+  cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+    "Constructing a list of tests" << std::endl, this->Quiet);
   cmake cm;
   cmGlobalGenerator gg;
   gg.SetCMakeInstance(&cm);
@@ -1628,8 +1629,8 @@ void cmCTestTestHandler::GetListOfTests()
     {
     return;
     }
-  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
-    "Done constructing a list of tests" << std::endl);
+  cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+    "Done constructing a list of tests" << std::endl, this->Quiet);
 }
 
 //----------------------------------------------------------------------
@@ -2016,8 +2017,8 @@ std::string cmCTestTestHandler::GenerateRegressionImages(
           << "><Value>File " << filename
           << " not found</Value></NamedMeasurement>"
           << std::endl;
-        cmCTestLog(this->CTest, HANDLER_OUTPUT, "File \"" << filename
-          << "\" not found." << std::endl);
+        cmCTestOptionalLog(this->CTest, HANDLER_OUTPUT, "File \"" << filename
+          << "\" not found." << std::endl, this->Quiet);
         }
       cxml.erase(measurementfile.start(),
         measurementfile.end() - measurementfile.start());
@@ -2265,7 +2266,8 @@ bool cmCTestTestHandler::SetTestsProperties(
 bool cmCTestTestHandler::AddTest(const std::vector<std::string>& args)
 {
   const std::string& testname = args[0];
-  cmCTestLog(this->CTest, DEBUG, "Add test: " << args[0] << std::endl);
+  cmCTestOptionalLog(this->CTest, DEBUG, "Add test: " << args[0] << std::endl,
+    this->Quiet);
 
   if (this->UseExcludeRegExpFlag &&
     this->UseExcludeRegExpFirst &&
@@ -2288,8 +2290,8 @@ bool cmCTestTestHandler::AddTest(const std::vector<std::string>& args)
       }
     if ( found )
       {
-      cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Ignore memcheck: "
-        << *it << std::endl);
+      cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT,
+        "Ignore memcheck: " << *it << std::endl, this->Quiet);
       return true;
       }
     }
@@ -2308,8 +2310,8 @@ bool cmCTestTestHandler::AddTest(const std::vector<std::string>& args)
       }
     if ( found )
       {
-      cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Ignore test: "
-        << *it << std::endl);
+      cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Ignore test: "
+        << *it << std::endl, this->Quiet);
       return true;
       }
     }
@@ -2318,8 +2320,8 @@ bool cmCTestTestHandler::AddTest(const std::vector<std::string>& args)
   test.Name = testname;
   test.Args = args;
   test.Directory = cmSystemTools::GetCurrentWorkingDirectory();
-  cmCTestLog(this->CTest, DEBUG, "Set test directory: "
-    << test.Directory << std::endl);
+  cmCTestOptionalLog(this->CTest, DEBUG, "Set test directory: "
+    << test.Directory << std::endl, this->Quiet);
 
   test.IsInBasedOnREOptions = true;
   test.WillFail = false;