@@ -267,7 +267,7 @@ void cmCTest::Initialize()
   fin.close();
   if ( m_DartMode )
     {
-    std::string testingDir = m_ToplevelPath + "/Testing/CDart";
+    std::string testingDir = m_ToplevelPath + "/Testing";
     if ( cmSystemTools::FileExists(testingDir.c_str()) )
       {
       if ( !cmSystemTools::FileIsDirectory(testingDir.c_str()) )
@@ -290,7 +290,7 @@ void cmCTest::Initialize()
     std::ifstream tfin(tagfile.c_str());
     std::string tag;
     time_t tctime = time(0);
-    struct tm *lctime = localtime(&tctime);
+    struct tm *lctime = gmtime(&tctime);
     if ( tfin )
       {
       tfin >> tag;
@@ -494,7 +494,7 @@ int cmCTest::UpdateDirectory()
   std::string command = cvsCommand + " -z3 update " + cvsOptions +
     " " + extra_update_opts;
   std::ofstream os; 
-  if ( !this->OpenOutputFile("", "Update.xml", os) )
+  if ( !this->OpenOutputFile(m_CurrentTag, "Update.xml", os) )
     {
     std::cout << "Cannot open log file" << std::endl;
     }
@@ -810,7 +810,7 @@ int cmCTest::ConfigureDirectory()
   if ( !m_ShowOnly )
     {
     std::ofstream os; 
-    if ( !this->OpenOutputFile("", "Configure.xml", os) )
+    if ( !this->OpenOutputFile(m_CurrentTag, "Configure.xml", os) )
       {
       std::cout << "Cannot open log file" << std::endl;
       }
@@ -1027,7 +1027,7 @@ int cmCTest::BuildDirectory()
       }
     }
 
-  if( !this->OpenOutputFile("", "Build.xml", ofs) )
+  if( !this->OpenOutputFile(m_CurrentTag, "Build.xml", ofs) )
     {
     std::cerr << "Cannot create build XML file" << std::endl;
     return 1;
@@ -1140,13 +1140,13 @@ int cmCTest::CoverageDirectory()
     return 1;
     }
   log.close();
-  if (!this->OpenOutputFile("", "Coverage.xml", log))
+  if (!this->OpenOutputFile(m_CurrentTag, "Coverage.xml", log))
     {
     std::cout << "Cannot open log file" << std::endl;
     return 1;
     }
 
-  std::string opath = m_ToplevelPath + "/Testing/CDart/Coverage";
+  std::string opath = m_ToplevelPath + "/Testing/" + m_CurrentTag + "/Coverage";
   
   for ( cc = 0; cc < files.size(); cc ++ )
     {
@@ -1291,7 +1291,7 @@ int cmCTest::CoverageDirectory()
   int cfileoutputcount = 0;
   char cfileoutputname[100];
   sprintf(cfileoutputname, "CoverageLog-%d.xml", cfileoutputcount++);
-  if (!this->OpenOutputFile("", cfileoutputname, cfileoutput))
+  if (!this->OpenOutputFile(m_CurrentTag, cfileoutputname, cfileoutput))
     {
     std::cout << "Cannot open log file" << std::endl;
     return 1;
@@ -1308,7 +1308,7 @@ int cmCTest::CoverageDirectory()
                   << "</Site>" << std::endl;
       cfileoutput.close();
       sprintf(cfileoutputname, "CoverageLog-%d.xml", cfileoutputcount++);
-      if (!this->OpenOutputFile("", cfileoutputname, cfileoutput))
+      if (!this->OpenOutputFile(m_CurrentTag, cfileoutputname, cfileoutput))
         {
         std::cout << "Cannot open log file" << std::endl;
         return 1;
@@ -1417,7 +1417,7 @@ int cmCTest::CoverageDirectory()
 bool cmCTest::OpenOutputFile(const std::string& path, 
                      const std::string& name, std::ofstream& stream)
 {
-  std::string testingDir = m_ToplevelPath + "/Testing/CDart";
+  std::string testingDir = m_ToplevelPath + "/Testing";
   if ( path.size() > 0 )
     {
     testingDir += "/" + path;
@@ -1736,7 +1736,7 @@ int cmCTest::TestDirectory()
   if ( m_DartMode )
     {
     std::ofstream ofs;
-    if( !this->OpenOutputFile("", "Test.xml", ofs) )
+    if( !this->OpenOutputFile(m_CurrentTag, "Test.xml", ofs) )
       {
       std::cerr << "Cannot create testing XML file" << std::endl;
       return 1;
@@ -1788,7 +1788,7 @@ int cmCTest::SubmitResults()
       m_DartConfiguration["DropSitePassword"] + "@" + 
       m_DartConfiguration["DropSite"] + 
       m_DartConfiguration["DropLocation"];
-    if ( !submit.SubmitUsingFTP(m_ToplevelPath+"/Testing/CDart", files, prefix, url) )
+    if ( !submit.SubmitUsingFTP(m_ToplevelPath+"/Testing/"+m_CurrentTag, files, prefix, url) )
       {
       return 0;
       }
@@ -1812,7 +1812,7 @@ int cmCTest::SubmitResults()
       url += "@";
       }
     url += m_DartConfiguration["DropSite"] + m_DartConfiguration["DropLocation"];
-    if ( !submit.SubmitUsingHTTP(m_ToplevelPath+"/Testing/CDart", files, prefix, url) )
+    if ( !submit.SubmitUsingHTTP(m_ToplevelPath+"/Testing/"+m_CurrentTag, files, prefix, url) )
       {
       return 0;
       }
@@ -1833,7 +1833,7 @@ int cmCTest::SubmitResults()
 
 bool cmCTest::CTestFileExists(const std::string& filename)
 {
-  std::string testingDir = m_ToplevelPath + "/Testing/CDart/" +
+  std::string testingDir = m_ToplevelPath + "/Testing/" + m_CurrentTag + "/" +
     filename;
   return cmSystemTools::FileExists(testingDir.c_str());
 }
@@ -1854,11 +1854,6 @@ void cmCTest::GenerateDartOutput(std::ostream& os)
     return;
     }
 
-  if ( m_TestResults.size() == 0 )
-    {
-    return;
-    }
-
   os << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      << "<Site BuildName=\"" << m_DartConfiguration["BuildName"]
      << "\" BuildStamp=\"" << m_CurrentTag << "-"