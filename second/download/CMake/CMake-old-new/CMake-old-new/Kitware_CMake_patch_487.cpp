@@ -402,7 +402,7 @@ cmCTest::Part cmCTest::GetPartFromName(const char* name)
 }
 
 //----------------------------------------------------------------------
-int cmCTest::Initialize(const char* binary_dir, bool script)
+int cmCTest::Initialize(const char* binary_dir, cmCTestStartCommand* command)
 {
   cmCTestLog(this, DEBUG, "Here: " << __LINE__ << std::endl);
   if(!this->InteractiveDebugMode)
@@ -453,6 +453,8 @@ int cmCTest::Initialize(const char* binary_dir, bool script)
 
   if ( this->ProduceXML )
     {
+    // Verify "Testing" directory exists:
+    //
     std::string testingDir = this->BinaryDir + "/Testing";
     if ( cmSystemTools::FileExists(testingDir.c_str()) )
       {
@@ -472,73 +474,101 @@ int cmCTest::Initialize(const char* binary_dir, bool script)
         return 0;
         }
       }
+
+    // Create new "TAG" file or read existing one:
+    //
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
+    if (command->ShouldCreateNewTag())
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
+          }
+        std::string tagmode;
+        if ( cmSystemTools::GetLineFromStream(tfin, tagmode) )
+          {
+          if (tagmode.size() > 4 && !this->Parts[PartStart])
+            {
+            this->TestModel = cmCTest::GetTestModelFromString(tagmode.c_str());
+            }
           }
+        tfin.close();
         }
-      tfin.close();
-      }
-    if (tag.size() == 0 || script || this->Parts[PartStart])
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
+            this->GetCTestConfiguration("NightlyStartTime"), this->TomorrowTag);
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
-      if ( !script )
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
 
@@ -596,7 +626,7 @@ bool cmCTest::InitializeFromCommand(cmCTestStartCommand* command)
       }
     }
 
-  if ( !this->Initialize(bld_dir.c_str(), true) )
+  if ( !this->Initialize(bld_dir.c_str(), command) )
     {
     return false;
     }
@@ -2206,7 +2236,7 @@ int cmCTest::Run(std::vector<std::string> &args, std::string* output)
         it->second->SetSubmitIndex(this->SubmitIndex);
         }
       std::string cwd = cmSystemTools::GetCurrentWorkingDirectory();
-      if(!this->Initialize(cwd.c_str(), false))
+      if(!this->Initialize(cwd.c_str(), 0))
         {
         res = 12;
         cmCTestLog(this, ERROR_MESSAGE, "Problem initializing the dashboard."