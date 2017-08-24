@@ -44,7 +44,7 @@
 #define CTEST_TEST_ERRORS 0x08
 #define CTEST_MEMORY_ERRORS 0x10
 
-static struct tm* GetNightlyTime(std::string str)
+static struct tm* GetNightlyTime(std::string str, bool tomorrowtag)
 {
   struct tm* lctime;
   time_t tctime = time(0);
@@ -64,10 +64,15 @@ static struct tm* GetNightlyTime(std::string str)
     // nightlySeconds is in the future, this is the next
     // dashboard to be opened, so subtract 24 hours to get the
     // time of the current open dashboard
-    ntime -= (24 * 60 * 60 );
+    ntime -= ( 24 * 60 * 60 );
     //std::cout << "Pick yesterday" << std::endl;
     }
   //std::cout << "nightlySeconds: " << ntime << std::endl;
+  if ( tomorrowtag )
+    {
+    std::cout << "Add a day" << std::endl;
+    ntime += ( 24 * 60 * 60 );
+    }
   lctime = gmtime(&ntime);
   return lctime;
 }
@@ -307,6 +312,7 @@ bool TryExecutable(const char *dir, const char *file,
 
 cmCTest::cmCTest() 
 { 
+  m_TomorrowTag            = false;
   m_BuildNoCMake           = false;
   m_BuildNoClean           = false;
   m_BuildTwoConfig         = false;
@@ -361,6 +367,10 @@ int cmCTest::Initialize()
     std::ifstream tfin(tagfile.c_str());
     std::string tag;
     time_t tctime = time(0);
+    if ( m_TomorrowTag )
+      {
+      tctime += ( 24 * 60 * 60 );
+      }
     struct tm *lctime = gmtime(&tctime);
     if ( tfin && cmSystemTools::GetLineFromStream(tfin, tag) )
       {
@@ -393,7 +403,8 @@ int cmCTest::Initialize()
       //std::cout << "TestModel: " << m_TestModel << std::endl;
       if ( m_TestModel == cmCTest::NIGHTLY )
         {
-        lctime = ::GetNightlyTime(m_DartConfiguration["NightlyStartTime"]);
+        lctime = ::GetNightlyTime(m_DartConfiguration["NightlyStartTime"],
+          m_TomorrowTag);
         }
       char datestring[100];
       sprintf(datestring, "%04d%02d%02d-%02d%02d",
@@ -618,7 +629,8 @@ int cmCTest::UpdateDirectory()
   std::string extra_update_opts;
   if ( m_TestModel == cmCTest::NIGHTLY )
     {
-    struct tm* t = ::GetNightlyTime(m_DartConfiguration["NightlyStartTime"]);
+    struct tm* t = ::GetNightlyTime(m_DartConfiguration["NightlyStartTime"],
+      m_TomorrowTag);
     char current_time[1024];
     sprintf(current_time, "%04d-%02d-%02d %02d:%02d:%02d UTC",
       t->tm_year + 1900,
@@ -3779,6 +3791,10 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
       this->m_ConfigurationScripts.push_back(args[i]);
       }
 
+    if( arg.find("--tomorrow-tag",0) == 0 )
+      {
+      m_TomorrowTag = true;
+      }
     if( arg.find("-D",0) == 0 && i < args.size() - 1 )
       {
       this->m_DartMode = true;