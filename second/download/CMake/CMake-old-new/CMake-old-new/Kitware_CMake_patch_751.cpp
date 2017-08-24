@@ -197,6 +197,71 @@ void ctest::Initialize()
     m_DartConfiguration[key] = value;
     }
   fin.close();
+  if ( m_DartMode )
+    {
+    std::string testingDir = m_ToplevelPath + "/Testing/CDart";
+    if ( cmSystemTools::FileExists(testingDir.c_str()) )
+      {
+      if ( !cmSystemTools::FileIsDirectory(testingDir.c_str()) )
+        {
+        std::cerr << "File " << testingDir << " is in the place of the testing directory"
+                  << std::endl;
+        return;
+        }
+      }
+    else
+      {
+      if ( !cmSystemTools::MakeDirectory(testingDir.c_str()) )
+        {
+        std::cerr << "Cannot create directory " << testingDir
+                  << std::endl;
+        return;
+        }
+      }
+    std::string tagfile = testingDir + "/TAG";
+    std::ifstream tfin(tagfile.c_str());
+    std::string tag;
+    time_t tctime = time(0);
+    struct tm *lctime = gmtime(&tctime);
+    if ( tfin )
+      {
+      tfin >> tag;
+      tfin.close();
+      int year = 0;
+      int mon = 0;
+      int day = 0;
+      int hour = 0;
+      int min = 0;
+      sscanf(tag.c_str(), "%04d%02d%02d-%02d%02d",
+             &year, &mon, &day, &hour, &min);
+      if ( year != lctime->tm_year + 1900 ||
+           mon != lctime->tm_mon ||
+           day != lctime->tm_mday )
+        {
+        tag = "";
+        }
+
+      }
+    if ( tag.size() == 0 )
+      {
+      char datestring[100];
+      sprintf(datestring, "%04d%02d%02d-%02d%02d",
+              lctime->tm_year + 1900,
+              lctime->tm_mon,
+              lctime->tm_mday,
+              lctime->tm_hour,
+              lctime->tm_min);
+      tag = datestring;
+      std::ofstream ofs(tagfile.c_str());
+      if ( ofs )
+        {
+        ofs << tag << std::endl;
+        }
+      ofs.close();
+      std::cout << "Create new tag: " << tag << std::endl;
+      }
+    m_CurrentTag = tag;
+    }
 }
 
 bool ctest::SetTest(const char* ttype)
@@ -239,36 +304,6 @@ bool ctest::SetTest(const char* ttype)
 
 void ctest::Finalize()
 {
-  if ( m_DartMode )
-    {
-    std::string testingDir = m_ToplevelPath + "/Testing/CDart";
-    if ( cmSystemTools::FileExists(testingDir.c_str()) )
-      {
-      if ( !cmSystemTools::FileIsDirectory(testingDir.c_str()) )
-        {
-        std::cerr << "File " << testingDir << " is in the place of the testing directory"
-                  << std::endl;
-        return;
-        }
-      }
-    else
-      {
-      if ( !cmSystemTools::MakeDirectory(testingDir.c_str()) )
-        {
-        std::cerr << "Cannot create directory " << testingDir
-                  << std::endl;
-        return;
-        }
-      }
-    std::string testxml = testingDir + "/Test.xml";
-    std::ofstream ofs(testxml.c_str());
-    if( !ofs )
-      {
-      std::cerr << "Cannot create testing XML file" << std::endl;
-      return;
-      }
-    this->GenerateDartOutput(ofs);
-    }
 }
 
 std::string ctest::FindExecutable(const char *exe)
@@ -335,26 +370,26 @@ std::string ctest::FindExecutable(const char *exe)
   return fullPath;
 }
 
-void ctest::UpdateDirectory()
+int ctest::UpdateDirectory()
 {
   std::string cvsCommand = m_DartConfiguration["CVSCommand"];
   if ( cvsCommand.size() == 0 )
     {
     std::cerr << "Cannot find CVSCommand key in the DartConfiguration.tcl" << std::endl;
-    return;
+    return 1;
     }
   std::string cvsOptions = m_DartConfiguration["CVSUpdateOptions"];
   if ( cvsOptions.size() == 0 )
     {
     std::cerr << "Cannot find CVSUpdateOptions key in the DartConfiguration.tcl" << std::endl;
-    return;
+    return 1;
     }
 
   std::string sourceDirectory = m_DartConfiguration["SourceDirectory"];
   if ( sourceDirectory.size() == 0 )
     {
     std::cerr << "Cannot find SourceDirectory  key in the DartConfiguration.tcl" << std::endl;
-    return;
+    return 1;
     }
 
   std::string command = cvsCommand + " update " + cvsOptions;
@@ -367,23 +402,25 @@ void ctest::UpdateDirectory()
   if (! res || retVal )
     {
     std::cerr << "Error(s) when updating the project" << std::endl;
+    return 1;
     }
+  return 0;
 }
 
-void ctest::ConfigureDirectory()
+int ctest::ConfigureDirectory()
 {
   std::string cCommand = m_DartConfiguration["ConfigureCommand"];
   if ( cCommand.size() == 0 )
     {
     std::cerr << "Cannot find ConfigureCommand key in the DartConfiguration.tcl" << std::endl;
-    return;
+    return 1;
     }
 
   std::string buildDirectory = m_DartConfiguration["BuildDirectory"];
   if ( buildDirectory.size() == 0 )
     {
     std::cerr << "Cannot find BuildDirectory  key in the DartConfiguration.tcl" << std::endl;
-    return;
+    return 1;
     }
 
   std::string output;
@@ -394,29 +431,33 @@ void ctest::ConfigureDirectory()
   if (! res || retVal )
     {
     std::cerr << "Error(s) when updating the project" << std::endl;
+    return 1;
     }
+  return 0;
 }
 
-void ctest::BuildDirectory()
+int ctest::BuildDirectory()
 {
   std::string makeCommand = m_DartConfiguration["MakeCommand"];
   if ( makeCommand.size() == 0 )
     {
     std::cerr << "Cannot find MakeCommand key in the DartConfiguration.tcl" << std::endl;
-    return;
+    return 1;
     }
   std::string buildDirectory = m_DartConfiguration["BuildDirectory"];
   if ( buildDirectory.size() == 0 )
     {
     std::cerr << "Cannot find BuildDirectory  key in the DartConfiguration.tcl" << std::endl;
-    return;
+    return 1;
     }
 
+  m_StartBuild = ::CurrentTime();
   std::string output;
   int retVal;
   bool res = cmSystemTools::RunCommand(makeCommand.c_str(), output, 
                                        retVal, buildDirectory.c_str(), 
                                        m_Verbose);
+  m_EndBuild = ::CurrentTime();
   if (! res || retVal )
     {
     std::cerr << "Error(s) when building project" << std::endl;
@@ -519,6 +560,7 @@ void ctest::BuildDirectory()
   cmCTestBuildErrorWarning errorwarning;
   for ( kk =0; kk < markedLines.size(); kk ++ )
     {
+    errorwarning.m_LineNumber = -1;
     bool found = false;
     if ( markedLines[kk] == 1 )
       {
@@ -547,40 +589,55 @@ void ctest::BuildDirectory()
         errorwarning.m_PreContext += lines[jj] + "\n";
         }
       for ( jj = kk+1; 
-            jj < lines.size() && jj < kk + 6 /* && markedLines[jj] == 0*/; 
+            jj < lines.size() && jj < kk + 7 /* && markedLines[jj] == 0*/; 
             jj ++ )
         {
         errorwarning.m_PostContext += lines[jj] + "\n";
         }
       errorsWarnings.push_back(errorwarning);
       }
     }
-  /*
-  this->GenerateDartBuildOutput(std::cout, 
-                                errorsWarnings);
-  */
+  std::string testingDir = m_ToplevelPath + "/Testing/CDart";
+  if ( cmSystemTools::FileExists(testingDir.c_str()) )
+    {
+    if ( !cmSystemTools::FileIsDirectory(testingDir.c_str()) )
+      {
+      std::cerr << "File " << testingDir 
+                << " is in the place of the testing directory"
+                << std::endl;
+      return 1;
+      }
+    }
+  else
+    {
+    if ( !cmSystemTools::MakeDirectory(testingDir.c_str()) )
+      {
+      std::cerr << "Cannot create directory " << testingDir
+                << std::endl;
+      return 1;
+      }
+    }
+  std::string buildxml = testingDir + "/Build.xml";
+  std::ofstream ofs(buildxml.c_str());
+  if( !ofs )
+    {
+    std::cerr << "Cannot create build XML file" << std::endl;
+    return 1;
+    }
+  this->GenerateDartBuildOutput(ofs, errorsWarnings);
+  return 0;
 }
 
 
 void ctest::GenerateDartBuildOutput(std::ostream& os, 
                                     std::vector<cmCTestBuildErrorWarning> ew)
 {
-  time_t tctime = time(0);
-  struct tm *lctime = gmtime(&tctime);
-  char datestring[100];
-  sprintf(datestring, "%4d%02d%02d-%d%d",
-          lctime->tm_year + 1900,
-          lctime->tm_mon,
-          lctime->tm_mday,
-          lctime->tm_hour,
-          lctime->tm_min);
-
   os << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      << "<Site BuildName=\"" << m_DartConfiguration["BuildName"]
-     << "\" BuildStamp=\"" << datestring << "-Experimental\" Name=\""
+     << "\" BuildStamp=\"" << m_CurrentTag << "-Experimental\" Name=\""
      << m_DartConfiguration["Site"] << "\">\n"
      << "<Build>\n"
-     << "  <StartDateTime>" << ::CurrentTime() << "</StartDateTime>\n"
+     << "  <StartDateTime>" << m_StartBuild << "</StartDateTime>\n"
      << "  <BuildCommand>" << m_DartConfiguration["MakeCommand"]
      << "</BuildCommand>" << std::endl;
     
@@ -612,7 +669,7 @@ void ctest::GenerateDartBuildOutput(std::ostream& os,
        << std::endl;
     }
   os << "  <Log Encoding=\"base64\" Compression=\"/bin/gzip\">\n    </Log>\n"
-     << "  <EndDateTime>" << ::CurrentTime() << "</EndDateTime>\n"
+     << "  <EndDateTime>" << m_EndBuild << "</EndDateTime>\n"
      << "</Build>\n"
      << "</Site>" << std::endl;
 }
@@ -783,6 +840,83 @@ void ctest::ProcessDirectory(std::vector<std::string> &passed,
     }
 }
 
+int ctest::TestDirectory()
+{
+  std::vector<std::string> passed;
+  std::vector<std::string> failed;
+  int total;
+
+  m_StartTest = ::CurrentTime();
+  this->ProcessDirectory(passed, failed);
+  m_EndTest = ::CurrentTime();
+
+  total = int(passed.size()) + int(failed.size());
+
+  if (total == 0)
+    {
+    std::cerr << "No tests were found!!!\n";
+    }
+  else
+    {
+    if (passed.size() && (m_UseIncludeRegExp || m_UseExcludeRegExp)) 
+      {
+      std::cerr << "\nThe following tests passed:\n";
+      for(std::vector<std::string>::iterator j = passed.begin();
+          j != passed.end(); ++j)
+        {   
+        std::cerr << "\t" << *j << "\n";
+        }
+      }
+
+    float percent = float(passed.size()) * 100.0f / total;
+    fprintf(stderr,"\n%.0f%% tests passed, %i tests failed out of %i\n",
+            percent, int(failed.size()), total);
+
+    if (failed.size()) 
+      {
+      std::cerr << "\nThe following tests FAILED:\n";
+      for(std::vector<std::string>::iterator j = failed.begin();
+          j != failed.end(); ++j)
+        {   
+        std::cerr << "\t" << *j << "\n";
+        }
+      }
+    }
+
+  if ( m_DartMode )
+    {
+    std::string testingDir = m_ToplevelPath + "/Testing/CDart";
+    if ( cmSystemTools::FileExists(testingDir.c_str()) )
+      {
+      if ( !cmSystemTools::FileIsDirectory(testingDir.c_str()) )
+        {
+        std::cerr << "File " << testingDir << " is in the place of the testing directory"
+                  << std::endl;
+        return 1;
+        }
+      }
+    else
+      {
+      if ( !cmSystemTools::MakeDirectory(testingDir.c_str()) )
+        {
+        std::cerr << "Cannot create directory " << testingDir
+                  << std::endl;
+        return 1;
+        }
+      }
+    std::string testxml = testingDir + "/Test.xml";
+    std::ofstream ofs(testxml.c_str());
+    if( !ofs )
+      {
+      std::cerr << "Cannot create testing XML file" << std::endl;
+      return 1;
+      }
+    this->GenerateDartOutput(ofs);
+    }
+
+  return int(failed.size());
+}
+
 void ctest::GenerateDartOutput(std::ostream& os)
 {
   if ( !m_DartMode )
@@ -795,22 +929,12 @@ void ctest::GenerateDartOutput(std::ostream& os)
     return;
     }
 
-  time_t tctime = time(0);
-  struct tm *lctime = gmtime(&tctime);
-  char datestring[100];
-  sprintf(datestring, "%4d%02d%02d-%d%d",
-          lctime->tm_year + 1900,
-          lctime->tm_mon,
-          lctime->tm_mday,
-          lctime->tm_hour,
-          lctime->tm_min);
-
   os << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      << "<Site BuildName=\"" << m_DartConfiguration["BuildName"]
-     << "\" BuildStamp=\"" << datestring << "-Experimental\" Name=\""
+     << "\" BuildStamp=\"" << m_CurrentTag << "-Experimental\" Name=\""
      << m_DartConfiguration["Site"] << "\">\n"
      << "<Testing>\n"
-     << "  <StartDateTime>" << ::CurrentTime() << "</StartDateTime>\n"
+     << "  <StartDateTime>" << m_StartTest << "</StartDateTime>\n"
      << "  <TestList>\n";
   tm_TestResultsVector::size_type cc;
   for ( cc = 0; cc < m_TestResults.size(); cc ++ )
@@ -850,7 +974,7 @@ void ctest::GenerateDartOutput(std::ostream& os)
        << "  </Test>" << std::endl;
     }
   
-  os << "<EndDateTime>" << ::CurrentTime() << "</EndDateTime>\n"
+  os << "<EndDateTime>" << m_EndTest << "</EndDateTime>\n"
      << "</Testing>\n"
      << "</Site>" << std::endl;
 }
@@ -883,46 +1007,7 @@ int ctest::ProcessTests()
     }
   if ( m_Tests[TEST_TEST] || m_Tests[ALL_TEST] || notest )
     {
-    std::vector<std::string> passed;
-    std::vector<std::string> failed;
-    int total;
-
-    this->ProcessDirectory(passed, failed);
-
-    total = int(passed.size()) + int(failed.size());
-
-    if (total == 0)
-      {
-      std::cerr << "No tests were found!!!\n";
-      }
-    else
-      {
-      if (passed.size() && (m_UseIncludeRegExp || m_UseExcludeRegExp)) 
-        {
-        std::cerr << "\nThe following tests passed:\n";
-        for(std::vector<std::string>::iterator j = passed.begin();
-            j != passed.end(); ++j)
-          {   
-          std::cerr << "\t" << *j << "\n";
-          }
-        }
-
-      float percent = float(passed.size()) * 100.0f / total;
-      fprintf(stderr,"\n%.0f%% tests passed, %i tests failed out of %i\n",
-              percent, int(failed.size()), total);
-
-      if (failed.size()) 
-        {
-        std::cerr << "\nThe following tests FAILED:\n";
-        for(std::vector<std::string>::iterator j = failed.begin();
-            j != failed.end(); ++j)
-          {   
-          std::cerr << "\t" << *j << "\n";
-          }
-        }
-      }
-
-    res += int(failed.size());
+    res += this->TestDirectory();
     }
   if ( m_Tests[COVERAGE_TEST] || m_Tests[ALL_TEST] )
     {