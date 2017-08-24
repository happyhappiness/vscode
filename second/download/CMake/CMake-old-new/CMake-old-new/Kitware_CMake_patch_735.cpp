@@ -19,6 +19,10 @@
 #include "cmSystemTools.h"
 #include "cmListFileCache.h"
 
+#ifdef HAVE_CURL
+# include "cmCTestSubmit.h"
+#endif
+
 #include <stdio.h>
 #include <time.h>
 
@@ -261,7 +265,7 @@ void cmCTest::Initialize()
       sscanf(tag.c_str(), "%04d%02d%02d-%02d%02d",
              &year, &mon, &day, &hour, &min);
       if ( year != lctime->tm_year + 1900 ||
-           mon != lctime->tm_mon ||
+           mon != lctime->tm_mon+1 ||
            day != lctime->tm_mday )
         {
         tag = "";
@@ -273,7 +277,7 @@ void cmCTest::Initialize()
       char datestring[100];
       sprintf(datestring, "%04d%02d%02d-%02d%02d",
               lctime->tm_year + 1900,
-              lctime->tm_mon,
+              lctime->tm_mon+1,
               lctime->tm_mday,
               lctime->tm_hour,
               lctime->tm_min);
@@ -320,6 +324,10 @@ bool cmCTest::SetTest(const char* ttype)
     {
     m_Tests[cmCTest::PURIFY_TEST] = 1;
     }
+  else if ( cmSystemTools::LowerCase(ttype) == "submit" )
+    {
+    m_Tests[cmCTest::SUBMIT_TEST] = 1;
+    }
   else
     {
     std::cerr << "Don't know about test \"" << ttype << "\" yet..." << std::endl;
@@ -1360,6 +1368,63 @@ int cmCTest::TestDirectory()
   return int(failed.size());
 }
 
+int cmCTest::SubmitResults()
+{
+#ifdef HAVE_CURL
+  std::vector<std::string> files;
+  std::string prefix = this->GetSubmitResultsPrefix();
+  if ( this->CTestFileExists("Build.xml") )
+    {
+    files.push_back("Build.xml");
+    }
+  if ( this->CTestFileExists("Test.xml") )
+    {
+    files.push_back("Test.xml");
+    }
+  if ( this->CTestFileExists("Coverage.xml") )
+    {
+    files.push_back("Coverage.xml");
+    }
+  if ( this->CTestFileExists("Purify.xml") )
+    {
+    files.push_back("Purify.xml");
+    }
+  cmCTestSubmit submit;
+  if ( m_DartConfiguration["DropMethod"] == "" ||
+       m_DartConfiguration["DropMethod"] ==  "ftp" )
+    {
+    std::cout << "FTP submit method" << std::endl;
+    std::string url = "ftp://";
+    url += m_DartConfiguration["DropSiteUser"] + ":" + 
+      m_DartConfiguration["DropSitePassword"] + "@" + 
+      m_DartConfiguration["DropSite"] + 
+      m_DartConfiguration["DropLocation:"];
+    submit.SubmitUsingFTP(files, prefix, url);
+    }
+  else
+    {
+    std::cout << "SCP submit not yet implemented" << std::endl;
+    }
+                          
+#endif
+  return 0;
+}
+
+bool cmCTest::CTestFileExists(const std::string& filename)
+{
+  std::string testingDir = m_ToplevelPath + "/Testing/CDart/" +
+    filename;
+  return cmSystemTools::FileExists(testingDir.c_str());
+}
+
+std::string cmCTest::GetSubmitResultsPrefix()
+{
+  std::string name = m_DartConfiguration["Site"] +
+    "___" + m_DartConfiguration["BuildName"] +
+    "___" + m_CurrentTag + "-Experimental___XML___";
+  return name;
+}
+
 void cmCTest::GenerateDartOutput(std::ostream& os)
 {
   if ( !m_DartMode )
@@ -1465,5 +1530,13 @@ int cmCTest::ProcessTests()
     {
     std::cerr << "Purify test is not yet implemented" << std::endl;
     }
+  if ( m_Tests[SUBMIT_TEST] || m_Tests[ALL_TEST] )
+    {
+#ifdef HAVE_CURL
+    this->SubmitResults();
+#else
+    std::cerr << "Submit test is not yet implemented" << std::endl;
+#endif
+    }
   return res;
 }