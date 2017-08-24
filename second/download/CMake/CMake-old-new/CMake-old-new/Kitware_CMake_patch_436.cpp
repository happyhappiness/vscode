@@ -75,8 +75,8 @@ struct tm* cmCTest::GetNightlyTime(std::string str,
   char buf[1024];
   // add todays year day and month to the time in str because
   // curl_getdate no longer assumes the day is today
-  sprintf(buf, "%d%02d%02d %s", 
-          lctime->tm_year+1900, 
+  sprintf(buf, "%d%02d%02d %s",
+          lctime->tm_year+1900,
           lctime->tm_mon +1,
           lctime->tm_mday,
           str.c_str());
@@ -223,7 +223,7 @@ int cmCTest::HTTPRequest(std::string url, HTTPMethod method,
     default:
       break;
     }
-  
+
   ::curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
   ::curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);
   ::curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
@@ -237,7 +237,7 @@ int cmCTest::HTTPRequest(std::string url, HTTPMethod method,
 
   ::curl_easy_cleanup(curl);
   ::curl_global_cleanup();
-  
+
   return static_cast<int>(res);
 }
 #endif
@@ -300,7 +300,7 @@ cmCTest::cmCTest()
   this->ForceNewCTestProcess   = false;
   this->TomorrowTag            = false;
   this->Verbose                = false;
-  
+
   this->Debug                  = false;
   this->ShowLineNumbers        = false;
   this->Quiet                  = false;
@@ -760,7 +760,7 @@ bool cmCTest::UpdateCTestConfiguration()
     }
   else
     {
-    cmCTestLog(this, HANDLER_VERBOSE_OUTPUT, "Parse Config file:" 
+    cmCTestLog(this, HANDLER_VERBOSE_OUTPUT, "Parse Config file:"
                << fileName.c_str() << "\n");
     // parse the dart test file
     std::ifstream fin(fileName.c_str());
@@ -944,15 +944,15 @@ bool cmCTest::AddIfExists(Part part, const char* file)
 //----------------------------------------------------------------------
 bool cmCTest::CTestFileExists(const std::string& filename)
 {
-  std::string testingDir = this->BinaryDir + "/Testing/" + 
+  std::string testingDir = this->BinaryDir + "/Testing/" +
     this->CurrentTag + "/" + filename;
   return cmSystemTools::FileExists(testingDir.c_str());
 }
 
 //----------------------------------------------------------------------
 cmCTestGenericHandler* cmCTest::GetInitializedHandler(const char* handler)
 {
-  cmCTest::t_TestingHandlers::iterator it = 
+  cmCTest::t_TestingHandlers::iterator it =
     this->TestingHandlers.find(handler);
   if ( it == this->TestingHandlers.end() )
     {
@@ -965,7 +965,7 @@ cmCTestGenericHandler* cmCTest::GetInitializedHandler(const char* handler)
 //----------------------------------------------------------------------
 cmCTestGenericHandler* cmCTest::GetHandler(const char* handler)
 {
-  cmCTest::t_TestingHandlers::iterator it = 
+  cmCTest::t_TestingHandlers::iterator it =
     this->TestingHandlers.find(handler);
   if ( it == this->TestingHandlers.end() )
     {
@@ -1314,8 +1314,8 @@ int cmCTest::RunTest(std::vector<const char*> argv,
       {
       if(argv[i])
         {
-        // make sure we pass the timeout in for any build and test 
-        // invocations. Since --build-generator is required this is a 
+        // make sure we pass the timeout in for any build and test
+        // invocations. Since --build-generator is required this is a
         // good place to check for it, and to add the arguments in
         if (strcmp(argv[i],"--build-generator") == 0 && timeout > 0)
           {
@@ -1524,18 +1524,18 @@ void cmCTest::StartXML(std::ostream& ostr, bool append)
        << "\tNumberOfPhysicalCPU=\""<< info.GetNumberOfPhysicalCPU() << "\"\n"
        << "\tTotalVirtualMemory=\"" << info.GetTotalVirtualMemory() << "\"\n"
        << "\tTotalPhysicalMemory=\""<< info.GetTotalPhysicalMemory() << "\"\n"
-       << "\tLogicalProcessorsPerPhysical=\"" 
+       << "\tLogicalProcessorsPerPhysical=\""
        << info.GetLogicalProcessorsPerPhysical() << "\"\n"
-       << "\tProcessorClockFrequency=\"" 
-       << info.GetProcessorClockFrequency() << "\"\n" 
+       << "\tProcessorClockFrequency=\""
+       << info.GetProcessorClockFrequency() << "\"\n"
        << ">" << std::endl;
-  this->AddSiteProperties(ostr); 
+  this->AddSiteProperties(ostr);
 }
 
 //----------------------------------------------------------------------
 void cmCTest::AddSiteProperties(std::ostream& ostr)
 {
-  cmCTestScriptHandler* ch = 
+  cmCTestScriptHandler* ch =
     static_cast<cmCTestScriptHandler*>(this->GetHandler("script"));
   cmake* cm =  ch->GetCMake();
   // if no CMake then this is the old style script and props like
@@ -1547,9 +1547,9 @@ void cmCTest::AddSiteProperties(std::ostream& ostr)
   // This code should go when cdash is changed to use labels only
   const char* subproject = cm->GetProperty("SubProject", cmProperty::GLOBAL);
   if(subproject)
-    { 
+    {
     ostr << "<Subproject name=\"" << subproject << "\">\n";
-    const char* labels = 
+    const char* labels =
       ch->GetCMake()->GetProperty("SubProjectLabels", cmProperty::GLOBAL);
     if(labels)
       {
@@ -1566,11 +1566,11 @@ void cmCTest::AddSiteProperties(std::ostream& ostr)
       }
     ostr << "</Subproject>\n";
     }
-  
+
   // This code should stay when cdash only does label based sub-projects
   const char* label = cm->GetProperty("Label", cmProperty::GLOBAL);
   if(label)
-    { 
+    {
     ostr << "<Labels>\n";
     ostr << "  <Label>" << label << "</Label>\n";
     ostr << "</Labels>\n";
@@ -1762,7 +1762,7 @@ bool cmCTest::SubmitExtraFiles(const char* cfiles)
 
 
 //-------------------------------------------------------
-// for a -D argument convert the next argument into 
+// for a -D argument convert the next argument into
 // the proper list of dashboard steps via SetTest
 bool cmCTest::AddTestsForDashboardType(std::string &targ)
 {
@@ -1980,9 +1980,9 @@ bool cmCTest::CheckArgument(const std::string& arg, const char* varg1,
 
 
 //----------------------------------------------------------------------
-// Processes one command line argument (and its arguments if any) 
+// Processes one command line argument (and its arguments if any)
 // for many simple options and then returns
-void cmCTest::HandleCommandLineArguments(size_t &i, 
+void cmCTest::HandleCommandLineArguments(size_t &i,
                                          std::vector<std::string> &args)
 {
   std::string arg = args[i];
@@ -2031,14 +2031,14 @@ void cmCTest::HandleCommandLineArguments(size_t &i,
     i++;
     this->SetStopTime(args[i]);
     }
-  
+
   if(this->CheckArgument(arg, "-C", "--build-config") &&
      i < args.size() - 1)
     {
     i++;
     this->SetConfigType(args[i].c_str());
     }
-  
+
   if(this->CheckArgument(arg, "--debug"))
     {
     this->Debug = true;
@@ -2078,7 +2078,7 @@ void cmCTest::HandleCommandLineArguments(size_t &i,
     {
     this->OutputTestOutputOnTestFailure = true;
     }
-  
+
   if(this->CheckArgument(arg, "-N", "--show-only"))
     {
     this->ShowOnly = true;
@@ -2118,7 +2118,7 @@ void cmCTest::HandleCommandLineArguments(size_t &i,
       this->SubmitIndex = 0;
       }
     }
-  
+
   if(this->CheckArgument(arg, "--overwrite") && i < args.size() - 1)
     {
     i++;
@@ -2171,7 +2171,7 @@ void cmCTest::HandleCommandLineArguments(size_t &i,
     this->GetHandler("memcheck")->
       SetPersistentOption("ExcludeLabelRegularExpression", args[i].c_str());
     }
-  
+
   if(this->CheckArgument(arg, "-E", "--exclude-regex") &&
      i < args.size() - 1)
     {
@@ -2180,17 +2180,17 @@ void cmCTest::HandleCommandLineArguments(size_t &i,
       SetPersistentOption("ExcludeRegularExpression", args[i].c_str());
     this->GetHandler("memcheck")->
       SetPersistentOption("ExcludeRegularExpression", args[i].c_str());
-    }  
+    }
 }
 
 //----------------------------------------------------------------------
 // handle the -S -SR and -SP arguments
-void cmCTest::HandleScriptArguments(size_t &i, 
+void cmCTest::HandleScriptArguments(size_t &i,
                                     std::vector<std::string> &args,
                                     bool &SRArgumentSpecified)
 {
   std::string arg = args[i];
-  if(this->CheckArgument(arg, "-SP", "--script-new-process") && 
+  if(this->CheckArgument(arg, "-SP", "--script-new-process") &&
      i < args.size() - 1 )
     {
     this->RunConfigurationScript = true;
@@ -2203,8 +2203,8 @@ void cmCTest::HandleScriptArguments(size_t &i,
       ch->AddConfigurationScript(args[i].c_str(),false);
       }
     }
-  
-  if(this->CheckArgument(arg, "-SR", "--script-run") && 
+
+  if(this->CheckArgument(arg, "-SR", "--script-run") &&
      i < args.size() - 1 )
     {
     SRArgumentSpecified = true;
@@ -2214,7 +2214,7 @@ void cmCTest::HandleScriptArguments(size_t &i,
       = static_cast<cmCTestScriptHandler*>(this->GetHandler("script"));
     ch->AddConfigurationScript(args[i].c_str(),true);
     }
-  
+
   if(this->CheckArgument(arg, "-S", "--script") && i < args.size() - 1 )
     {
     this->RunConfigurationScript = true;
@@ -2396,7 +2396,7 @@ int cmCTest::Run(std::vector<std::string> &args, std::string* output)
     } // the close of the for argument loop
 
 
-  // now what sould cmake do? if --build-and-test was specified then 
+  // now what sould cmake do? if --build-and-test was specified then
   // we run the build and test handler and return
   if(cmakeAndTest)
     {
@@ -2410,7 +2410,7 @@ int cmCTest::Run(std::vector<std::string> &args, std::string* output)
 #endif
     if(retv != 0)
       {
-      cmCTestLog(this, DEBUG, "build and test failing returing: " << retv 
+      cmCTestLog(this, DEBUG, "build and test failing returing: " << retv
                  << std::endl);
       }
     return retv;
@@ -2438,14 +2438,14 @@ int cmCTest::Run(std::vector<std::string> &args, std::string* output)
       res = this->GetHandler("script")->ProcessHandler();
       if(res != 0)
         {
-        cmCTestLog(this, DEBUG, "running script failing returning: " << res 
+        cmCTestLog(this, DEBUG, "running script failing returning: " << res
                    << std::endl);
         }
 
       }
     else
       {
-      // What is this?  -V seems to be the same as -VV, 
+      // What is this?  -V seems to be the same as -VV,
       // and Verbose is always on in this case
       this->ExtraVerbose = this->Verbose;
       this->Verbose = true;
@@ -2472,7 +2472,7 @@ int cmCTest::Run(std::vector<std::string> &args, std::string* output)
       }
     if(res != 0)
       {
-      cmCTestLog(this, DEBUG, "Running a test(s) failed returning : " << res 
+      cmCTestLog(this, DEBUG, "Running a test(s) failed returning : " << res
                  << std::endl);
       }
     return res;