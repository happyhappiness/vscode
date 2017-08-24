@@ -21,6 +21,7 @@
 
 #ifdef HAVE_CURL
 # include "cmCTestSubmit.h"
+# include "curl/curl.h"
 #endif
 
 #include <stdio.h>
@@ -183,6 +184,7 @@ cmCTest::cmCTest()
   m_Verbose               = false;
   m_DartMode              = false;
   m_ShowOnly              = false;
+  m_TestModel             = cmCTest::EXPERIMENTAL;
   int cc; 
   for ( cc=0; cc < cmCTest::LAST_TEST; cc ++ )
     {
@@ -258,7 +260,7 @@ void cmCTest::Initialize()
     std::ifstream tfin(tagfile.c_str());
     std::string tag;
     time_t tctime = time(0);
-    struct tm *lctime = gmtime(&tctime);
+    struct tm *lctime = localtime(&tctime);
     if ( tfin )
       {
       tfin >> tag;
@@ -280,6 +282,40 @@ void cmCTest::Initialize()
       }
     if ( tag.size() == 0 )
       {
+#ifdef HAVE_CURL
+      if ( m_TestModel == cmCTest::NIGHTLY )
+        {
+        int hour;
+        int min;
+        int sec;
+        char stz[100];
+        int tz;
+        tctime = time(0);
+        //Convert the nightly start time to seconds. Since we are
+        //providing only a time and a timezone, the current date of
+        //the local machine is assumed. Consequently, nightlySeconds
+        //is the time at which the nightly dashboard was opened or
+        //will be opened on the date of the current client machine.
+        //As such, this time may be in the past or in the future.
+        time_t ntime = curl_getdate(
+          m_DartConfiguration["NightlyStartTime"].c_str(), 
+          &tctime);
+        tctime = time(0);
+        std::cout << "Seconds: " << tctime << std::endl;
+        if ( ntime > tctime )
+          {
+          // If nightlySeconds is in the past, this is the current
+          // open dashboard, then return nightlySeconds.  If
+          // nightlySeconds is in the future, this is the next
+          // dashboard to be opened, so subtract 24 hours to get the
+          // time of the current open dashboard
+          ntime -= (24 * 60 * 60 );
+          std::cout << "Pick yesterday" << std::endl;
+          }
+        std::cout << "nightlySeconds: " << ntime << std::endl;
+        lctime = gmtime(&ntime);
+        }
+#endif
       char datestring[100];
       sprintf(datestring, "%04d%02d%02d-%02d%02d",
               lctime->tm_year + 1900,
@@ -434,8 +470,21 @@ int cmCTest::UpdateDirectory()
     return 1;
     }
 
-  std::string command = cvsCommand + " -z3 update " + cvsOptions;
+  std::string extra_update_opts;
+  if ( m_TestModel == cmCTest::NIGHTLY )
+    {
+    time_t currenttime = time(0);
+    struct tm* t = localtime(&currenttime);
+    char current_time[1024];
+    strftime(current_time, 1000, "%Y-%m-%d ", t);
+   
+    std::string today_update_date = current_time + 
+      m_DartConfiguration["NightlyStartTime"];
+    extra_update_opts += "-D \"" + today_update_date +"\"";
+    }
 
+  std::string command = cvsCommand + " -z3 update " + cvsOptions +
+    " " + extra_update_opts;
   std::ofstream os; 
   if ( !this->OpenOutputFile("", "Update.xml", os) )
     {
@@ -444,18 +493,18 @@ int cmCTest::UpdateDirectory()
   std::string start_time = ::CurrentTime();
  
 
-  std::string output;
+  std::string goutput;
   int retVal = 0;
   bool res = true;
   if ( !m_ShowOnly )
     {
-    res = cmSystemTools::RunCommand(command.c_str(), output, 
+    res = cmSystemTools::RunCommand(command.c_str(), goutput, 
                                     retVal, sourceDirectory.c_str(),
                                     m_Verbose);
     std::ofstream ofs;
     if ( this->OpenOutputFile("Temporary", "LastUpdate.log", ofs) )
       {
-      ofs << output;
+      ofs << goutput;
       ofs.close();
       }
     }
@@ -469,7 +518,8 @@ int cmCTest::UpdateDirectory()
      << "\t<Site>" <<m_DartConfiguration["Site"] << "</Site>\n"
      << "\t<BuildName>" << m_DartConfiguration["BuildName"]
      << "</BuildName>\n"
-     << "\t<BuildStamp>" << m_CurrentTag << "-Experimental</BuildStamp>\n"
+     << "\t<BuildStamp>" << m_CurrentTag << "-"
+     << this->GetTestModelString() << "</BuildStamp>\n"
      << "\t<StartDateTime>" << start_time << "</StartDateTime>\n"
      << "\t<UpdateCommand>" << command << "</UpdateCommand>\n"
      << "\t<UpdateReturnStatus>";
@@ -480,7 +530,7 @@ int cmCTest::UpdateDirectory()
   os << "</UpdateReturnStatus>" << std::endl;
 
   std::vector<cmStdString> lines;
-  cmSystemTools::Split(output.c_str(), lines);
+  cmSystemTools::Split(goutput.c_str(), lines);
   std::cout << "Updated; gathering version information" << std::endl;
   cmRegularExpression date_author("^date: +([^;]+); +author: +([^;]+); +state: +[^;]+;");
   cmRegularExpression revision("^revision +([^ ]*) *$");
@@ -501,9 +551,10 @@ int cmCTest::UpdateDirectory()
       {
       const char* file = line + 2;
       //std::cout << "Line" << cc << ": " << mod << " - " << file << std::endl;
-      std::string logcommand = cvsCommand + " -z3 log -N " + file;
+      std::string logcommand = cvsCommand + " -z3 log -N " + file +
+        " " + extra_update_opts;
       //std::cout << "Do log: " << logcommand << std::endl;
-      output = "";
+      std::string output;
       res = cmSystemTools::RunCommand(logcommand.c_str(), output, 
                                       retVal, sourceDirectory.c_str(),
                                       m_Verbose);
@@ -713,13 +764,15 @@ int cmCTest::UpdateDirectory()
   if (! res || retVal )
     {
     std::cerr << "Error(s) when updating the project" << std::endl;
+    std::cerr << "Output: " << goutput << std::endl;
     return 1;
     }
   return 0;
 }
 
 int cmCTest::ConfigureDirectory()
 {
+  std::cout << "Configure project" << std::endl;
   std::string cCommand = m_DartConfiguration["ConfigureCommand"];
   if ( cCommand.size() == 0 )
     {
@@ -743,6 +796,12 @@ int cmCTest::ConfigureDirectory()
     res = cmSystemTools::RunCommand(cCommand.c_str(), output, 
                                     retVal, buildDirectory.c_str(),
                                     m_Verbose);
+    std::ofstream ofs;
+    if ( this->OpenOutputFile("Temporary", "LastConfigure.log", ofs) )
+      {
+      ofs << output;
+      ofs.close();
+      }
     }
   else
     {
@@ -758,6 +817,7 @@ int cmCTest::ConfigureDirectory()
 
 int cmCTest::BuildDirectory()
 {
+  std::cout << "Build project" << std::endl;
   std::string makeCommand = m_DartConfiguration["MakeCommand"];
   if ( makeCommand.size() == 0 )
     {
@@ -932,6 +992,7 @@ int cmCTest::BuildDirectory()
  
 int cmCTest::CoverageDirectory()
 {
+  std::cout << "Performing coverage" << std::endl;
   std::vector<std::string> files;
   std::vector<std::string> cfiles;
   std::vector<std::string> cdirs;
@@ -1105,7 +1166,8 @@ int cmCTest::CoverageDirectory()
 
   log << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
       << "<Site BuildName=\"" << m_DartConfiguration["BuildName"]
-      << "\" BuildStamp=\"" << m_CurrentTag << "-Experimental\" Name=\""
+      << "\" BuildStamp=\"" << m_CurrentTag << "-"
+      << this->GetTestModelString() << "\" Name=\""
       << m_DartConfiguration["Site"] << "\">\n"
       << "<Coverage>\n"
       << "\t<StartDateTime>" << start_time << "</StartDateTime>" << std::endl;
@@ -1213,7 +1275,8 @@ int cmCTest::CoverageDirectory()
       local_start_time = ::CurrentTime();
       cfileoutput << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
                   << "<Site BuildName=\"" << m_DartConfiguration["BuildName"]
-                  << "\" BuildStamp=\"" << m_CurrentTag << "-Experimental\" Name=\""
+                  << "\" BuildStamp=\"" << m_CurrentTag << "-"
+                  << this->GetTestModelString() << "\" Name=\""
                   << m_DartConfiguration["Site"] << "\">\n"
                   << "<CoverageLog>\n"
                   << "\t<StartDateTime>" << local_start_time << "</StartDateTime>" << std::endl;
@@ -1346,7 +1409,8 @@ void cmCTest::GenerateDartBuildOutput(std::ostream& os,
 {
   os << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      << "<Site BuildName=\"" << m_DartConfiguration["BuildName"]
-     << "\" BuildStamp=\"" << m_CurrentTag << "-Experimental\" Name=\""
+     << "\" BuildStamp=\"" << m_CurrentTag << "-"
+     << this->GetTestModelString() << "\" Name=\""
      << m_DartConfiguration["Site"] << "\">\n"
      << "<Build>\n"
      << "\t<StartDateTime>" << m_StartBuild << "</StartDateTime>\n"
@@ -1578,6 +1642,7 @@ void cmCTest::ProcessDirectory(std::vector<std::string> &passed,
 
 int cmCTest::TestDirectory()
 {
+  std::cout << "Test project" << std::endl;
   std::vector<std::string> passed;
   std::vector<std::string> failed;
   int total;
@@ -1727,7 +1792,8 @@ std::string cmCTest::GetSubmitResultsPrefix()
 {
   std::string name = m_DartConfiguration["Site"] +
     "___" + m_DartConfiguration["BuildName"] +
-    "___" + m_CurrentTag + "-Experimental___XML___";
+    "___" + m_CurrentTag + "-" +
+    this->GetTestModelString() + "___XML___";
   return name;
 }
 
@@ -1745,7 +1811,8 @@ void cmCTest::GenerateDartOutput(std::ostream& os)
 
   os << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      << "<Site BuildName=\"" << m_DartConfiguration["BuildName"]
-     << "\" BuildStamp=\"" << m_CurrentTag << "-Experimental\" Name=\""
+     << "\" BuildStamp=\"" << m_CurrentTag << "-"
+     << this->GetTestModelString() << "\" Name=\""
      << m_DartConfiguration["Site"] << "\">\n"
      << "<Testing>\n"
      << "\t<StartDateTime>" << m_StartTest << "</StartDateTime>\n"
@@ -1846,3 +1913,16 @@ int cmCTest::ProcessTests()
     }
   return res;
 }
+
+std::string cmCTest::GetTestModelString()
+{
+  switch ( m_TestModel )
+    {
+    case cmCTest::NIGHTLY:
+      return "Nightly";
+    case cmCTest::CONTINUOUS:
+      return "Continuous";
+    }
+  return "Experimental";
+}
+