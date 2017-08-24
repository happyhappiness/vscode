@@ -23,6 +23,7 @@
 #include "cmXMLSafe.h"
 #include "cmVersionMacros.h"
 #include "cmCTestCommand.h"
+#include "cmCTestStartCommand.h"
 
 #include "cmCTestBuildHandler.h"
 #include "cmCTestBuildAndTestHandler.h"
@@ -153,6 +154,78 @@ std::string cmCTest::CurrentTime()
   return cmXMLSafe(cmCTest::CleanString(current_time)).str();
 }
 
+#ifdef CMAKE_BUILD_WITH_CMAKE
+//----------------------------------------------------------------------------
+static size_t
+HTTPResponseCallback(void *ptr, size_t size, size_t nmemb, void *data)
+{
+  register int realsize = (int)(size * nmemb);
+
+  std::string *response
+    = static_cast<std::string*>(data);
+  const char* chPtr = static_cast<char*>(ptr);
+  *response += chPtr;
+
+  return realsize;
+}
+
+//----------------------------------------------------------------------------
+int cmCTest::HTTPRequest(std::string url, HTTPMethod method,
+                                       std::string& response,
+                                       std::string fields,
+                                       std::string putFile, int timeout)
+{
+  CURL* curl;
+  FILE* file;
+  ::curl_global_init(CURL_GLOBAL_ALL);
+  curl = ::curl_easy_init();
+
+  //set request options based on method
+  switch(method)
+    {
+    case cmCTest::HTTP_POST:
+      ::curl_easy_setopt(curl, CURLOPT_POST, 1);
+      ::curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fields.c_str());
+      break;
+    case cmCTest::HTTP_PUT:
+      if(!cmSystemTools::FileExists(putFile.c_str()))
+        {
+        response = "Error: File ";
+        response += putFile + " does not exist.\n";
+        return -1;
+        }
+      ::curl_easy_setopt(curl, CURLOPT_PUT, 1);
+      file = ::fopen(putFile.c_str(), "rb");
+      ::curl_easy_setopt(curl, CURLOPT_INFILE, file);
+      //fall through to append GET fields
+    case cmCTest::HTTP_GET:
+      if(fields.size())
+        {
+        url += "?" + fields;
+        }
+      break;
+    default:
+      break;
+    }
+  
+  ::curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
+  ::curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout);
+  ::curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1);
+
+  //set response options
+  ::curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, HTTPResponseCallback);
+  ::curl_easy_setopt(curl, CURLOPT_FILE, (void *)&response);
+  ::curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1);
+
+  CURLcode res = ::curl_easy_perform(curl);
+
+  ::curl_easy_cleanup(curl);
+  ::curl_global_cleanup();
+  
+  return static_cast<int>(res);
+}
+#endif
+
 //----------------------------------------------------------------------
 std::string cmCTest::MakeURLSafe(const std::string& str)
 {
@@ -219,12 +292,17 @@ cmCTest::cmCTest()
   this->ProduceXML             = false;
   this->ShowOnly               = false;
   this->RunConfigurationScript = false;
+  this->UseHTTP10              = false;
+  this->CompressTestOutput     = true;
+  this->ComputedCompressOutput = false;
   this->TestModel              = cmCTest::EXPERIMENTAL;
   this->MaxTestNameWidth       = 30;
   this->InteractiveDebugMode   = true;
   this->TimeOut                = 0;
+  this->GlobalTimeout          = 0;
   this->CompressXMLFiles       = false;
   this->CTestConfigFile        = "";
+  this->ScheduleType           = "";
   this->OutputLogFile          = 0;
   this->OutputLogFileLastTag   = -1;
   this->SuppressUpdatingCTestConfiguration = false;
@@ -295,6 +373,40 @@ void cmCTest::SetParallelLevel(int level)
 }
 
 //----------------------------------------------------------------------------
+bool cmCTest::ShouldCompressTestOutput()
+{
+  if(!this->ComputedCompressOutput)
+    {
+    std::string cdashVersion = this->GetCDashVersion();
+    //version >= 1.6?
+    bool cdashSupportsGzip = cmSystemTools::VersionCompare(
+      cmSystemTools::OP_GREATER, cdashVersion.c_str(), "1.6") ||
+      cmSystemTools::VersionCompare(cmSystemTools::OP_EQUAL,
+      cdashVersion.c_str(), "1.6");
+    this->CompressTestOutput &= cdashSupportsGzip;
+    this->ComputedCompressOutput = true;
+    }
+  return this->CompressTestOutput;
+}
+
+//----------------------------------------------------------------------------
+std::string cmCTest::GetCDashVersion()
+{
+#ifdef CMAKE_BUILD_WITH_CMAKE
+  //First query the server.  If that fails, fall back to the local setting
+  std::string response;
+  std::string url = "http://";
+  url += this->GetCTestConfiguration("DropSite") + "/CDash/api/getversion.php";
+  
+  int res = cmCTest::HTTPRequest(url, cmCTest::HTTP_GET, response);
+  
+  return res ? this->GetCTestConfiguration("CDashVersion") : response;
+#else
+  return this->GetCTestConfiguration("CDashVersion");
+#endif
+}
+
+//----------------------------------------------------------------------------
 cmCTest::Part cmCTest::GetPartFromName(const char* name)
 {
   // Look up by lower-case to make names case-insensitive.
@@ -310,8 +422,7 @@ cmCTest::Part cmCTest::GetPartFromName(const char* name)
 }
 
 //----------------------------------------------------------------------
-int cmCTest::Initialize(const char* binary_dir, bool new_tag,
-  bool verbose_tag)
+int cmCTest::Initialize(const char* binary_dir, cmCTestStartCommand* command)
 {
   cmCTestLog(this, DEBUG, "Here: " << __LINE__ << std::endl);
   if(!this->InteractiveDebugMode)
@@ -362,6 +473,8 @@ int cmCTest::Initialize(const char* binary_dir, bool new_tag,
 
   if ( this->ProduceXML )
     {
+    // Verify "Testing" directory exists:
+    //
     std::string testingDir = this->BinaryDir + "/Testing";
     if ( cmSystemTools::FileExists(testingDir.c_str()) )
       {
@@ -381,84 +494,114 @@ int cmCTest::Initialize(const char* binary_dir, bool new_tag,
         return 0;
         }
       }
+
+    // Create new "TAG" file or read existing one:
+    //
+    bool createNewTag = true;
+    if (command)
+      {
+      createNewTag = command->ShouldCreateNewTag();
+      }
+
     std::string tagfile = testingDir + "/TAG";
     std::ifstream tfin(tagfile.c_str());
     std::string tag;
-    time_t tctime = time(0);
-    if ( this->TomorrowTag )
-      {
-      tctime += ( 24 * 60 * 60 );
-      }
-    struct tm *lctime = gmtime(&tctime);
-    if ( tfin && cmSystemTools::GetLineFromStream(tfin, tag) )
-      {
-      int year = 0;
-      int mon = 0;
-      int day = 0;
-      int hour = 0;
-      int min = 0;
-      sscanf(tag.c_str(), "%04d%02d%02d-%02d%02d",
-             &year, &mon, &day, &hour, &min);
-      if ( year != lctime->tm_year + 1900 ||
-           mon != lctime->tm_mon+1 ||
-           day != lctime->tm_mday )
+
+    if (createNewTag)
+      {
+      time_t tctime = time(0);
+      if ( this->TomorrowTag )
         {
-        tag = "";
+        tctime += ( 24 * 60 * 60 );
         }
-      std::string tagmode;
-      if ( cmSystemTools::GetLineFromStream(tfin, tagmode) )
+      struct tm *lctime = gmtime(&tctime);
+      if ( tfin && cmSystemTools::GetLineFromStream(tfin, tag) )
         {
-        if (tagmode.size() > 4 && !this->Parts[PartStart])
+        int year = 0;
+        int mon = 0;
+        int day = 0;
+        int hour = 0;
+        int min = 0;
+        sscanf(tag.c_str(), "%04d%02d%02d-%02d%02d",
+               &year, &mon, &day, &hour, &min);
+        if ( year != lctime->tm_year + 1900 ||
+             mon != lctime->tm_mon+1 ||
+             day != lctime->tm_mday )
           {
-          this->TestModel = cmCTest::GetTestModelFromString(tagmode.c_str());
+          tag = "";
           }
+        std::string tagmode;
+        if ( cmSystemTools::GetLineFromStream(tfin, tagmode) )
+          {
+          if (tagmode.size() > 4 && !this->Parts[PartStart])
+            {
+            this->TestModel = cmCTest::GetTestModelFromString(tagmode.c_str());
+            }
+          }
+        tfin.close();
         }
-      tfin.close();
-      }
-    if (tag.size() == 0 || new_tag || this->Parts[PartStart])
-      {
-      cmCTestLog(this, DEBUG, "TestModel: " << this->GetTestModelString()
-        << std::endl);
-      cmCTestLog(this, DEBUG, "TestModel: " << this->TestModel << std::endl);
-      if ( this->TestModel == cmCTest::NIGHTLY )
+      if (tag.size() == 0 || (0 != command) || this->Parts[PartStart])
         {
-        lctime = this->GetNightlyTime(
-          this->GetCTestConfiguration("NightlyStartTime"), this->TomorrowTag);
+        cmCTestLog(this, DEBUG, "TestModel: " << this->GetTestModelString()
+          << std::endl);
+        cmCTestLog(this, DEBUG, "TestModel: " << this->TestModel << std::endl);
+        if ( this->TestModel == cmCTest::NIGHTLY )
+          {
+          lctime = this->GetNightlyTime(
+            this->GetCTestConfiguration("NightlyStartTime"),
+            this->TomorrowTag);
+          }
+        char datestring[100];
+        sprintf(datestring, "%04d%02d%02d-%02d%02d",
+                lctime->tm_year + 1900,
+                lctime->tm_mon+1,
+                lctime->tm_mday,
+                lctime->tm_hour,
+                lctime->tm_min);
+        tag = datestring;
+        std::ofstream ofs(tagfile.c_str());
+        if ( ofs )
+          {
+          ofs << tag << std::endl;
+          ofs << this->GetTestModelString() << std::endl;
+          }
+        ofs.close();
+        if ( 0 == command )
+          {
+          cmCTestLog(this, OUTPUT, "Create new tag: " << tag << " - "
+            << this->GetTestModelString() << std::endl);
+          }
         }
-      char datestring[100];
-      sprintf(datestring, "%04d%02d%02d-%02d%02d",
-              lctime->tm_year + 1900,
-              lctime->tm_mon+1,
-              lctime->tm_mday,
-              lctime->tm_hour,
-              lctime->tm_min);
-      tag = datestring;
-      std::ofstream ofs(tagfile.c_str());
-      if ( ofs )
+      }
+    else
+      {
+      if ( tfin )
         {
-        ofs << tag << std::endl;
-        ofs << this->GetTestModelString() << std::endl;
+        cmSystemTools::GetLineFromStream(tfin, tag);
+        tfin.close();
         }
-      ofs.close();
-      if ( verbose_tag )
+
+      if ( tag.empty() )
         {
-        cmCTestLog(this, OUTPUT, "Create new tag: " << tag << " - "
-          << this->GetTestModelString() << std::endl);
+        cmCTestLog(this, ERROR_MESSAGE,
+          "Cannot read existing TAG file in " << testingDir
+          << std::endl);
+        return 0;
         }
+
+      cmCTestLog(this, OUTPUT, "  Use existing tag: " << tag << " - "
+        << this->GetTestModelString() << std::endl);
       }
+
     this->CurrentTag = tag;
     }
+
   return 1;
 }
 
 //----------------------------------------------------------------------
-bool cmCTest::InitializeFromCommand(cmCTestCommand* command, bool first)
+bool cmCTest::InitializeFromCommand(cmCTestStartCommand* command)
 {
-  if ( !first && !this->CurrentTag.empty() )
-    {
-    return true;
-    }
-
   std::string src_dir
     = this->GetCTestConfiguration("SourceDirectory").c_str();
   std::string bld_dir = this->GetCTestConfiguration("BuildDirectory").c_str();
@@ -486,17 +629,11 @@ bool cmCTest::InitializeFromCommand(cmCTestCommand* command, bool first)
       return false;
       }
     }
-  else if ( !first )
+  else
     {
     cmCTestLog(this, WARNING, "Cannot locate CTest configuration: "
       << fname.c_str() << std::endl);
     }
-  else
-    {
-    cmCTestLog(this, HANDLER_OUTPUT, "   Cannot locate CTest configuration: "
-      << fname.c_str() << std::endl
-      << "   Delay the initialization of CTest" << std::endl);
-    }
 
   this->SetCTestConfigurationFromCMakeVariable(mf, "NightlyStartTime",
     "CTEST_NIGHTLY_START_TIME");
@@ -516,12 +653,8 @@ bool cmCTest::InitializeFromCommand(cmCTestCommand* command, bool first)
       }
     }
 
-  if ( !this->Initialize(bld_dir.c_str(), true, false) )
+  if ( !this->Initialize(bld_dir.c_str(), command) )
     {
-    if ( this->GetCTestConfiguration("NightlyStartTime").empty() && first)
-      {
-      return true;
-      }
     return false;
     }
   cmCTestLog(this, OUTPUT, "   Use " << this->GetTestModelString()
@@ -1716,6 +1849,23 @@ void cmCTest::HandleCommandLineArguments(size_t &i,
     int plevel = atoi(arg.substr(2).c_str());
     this->SetParallelLevel(plevel);
     }
+
+  if(this->CheckArgument(arg, "--no-compress-output"))
+    {
+    this->CompressTestOutput = false;
+    }
+
+  if(this->CheckArgument(arg, "--http1.0"))
+    {
+    this->UseHTTP10 = true;
+    }
+
+  if(this->CheckArgument(arg, "--timeout") && i < args.size() - 1)
+    {
+    i++;
+    double timeout = (double)atof(args[i].c_str());
+    this->GlobalTimeout = timeout;
+    }
   
   if(this->CheckArgument(arg, "-C", "--build-config") &&
      i < args.size() - 1)
@@ -2027,6 +2177,11 @@ int cmCTest::Run(std::vector<std::string> &args, std::string* output)
       cmakeAndTest = true;
       }
 
+    if(this->CheckArgument(arg, "--schedule-random"))
+      {
+      this->ScheduleType = "Random";
+      }
+
     // pass the argument to all the handlers as well, but i may no longer be
     // set to what it was originally so I'm not sure this is working as
     // intended
@@ -2107,8 +2262,8 @@ int cmCTest::Run(std::vector<std::string> &args, std::string* output)
         it->second->SetVerbose(this->Verbose);
         it->second->SetSubmitIndex(this->SubmitIndex);
         }
-      if ( !this->Initialize(
-          cmSystemTools::GetCurrentWorkingDirectory().c_str()) )
+      std::string cwd = cmSystemTools::GetCurrentWorkingDirectory();
+      if(!this->Initialize(cwd.c_str(), 0))
         {
         res = 12;
         cmCTestLog(this, ERROR_MESSAGE, "Problem initializing the dashboard."
@@ -2769,4 +2924,3 @@ void cmCTest::OutputTestErrors(std::vector<char> const &process_output)
     }
   cmCTestLog(this, HANDLER_OUTPUT, test_outputs << std::endl << std::flush);
 }
-