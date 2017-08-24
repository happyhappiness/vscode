@@ -22,10 +22,8 @@
 #include <cmsys/Directory.hxx>
 #include "cmListFileCache.h"
 
-#ifdef HAVE_CURL
-# include "cmCTestSubmit.h"
-# include "curl/curl.h"
-#endif
+#include "cmCTestSubmit.h"
+#include "curl/curl.h"
 
 #include <cmsys/RegularExpression.hxx>
 #include <cmsys/Process.h>
@@ -38,7 +36,6 @@
 
 #define SAFEDIV(x,y) (((y)!=0)?((x)/(y)):(0))
 
-#ifdef HAVE_CURL
 static struct tm* GetNightlyTime(std::string str)
 {
   struct tm* lctime;
@@ -66,7 +63,6 @@ static struct tm* GetNightlyTime(std::string str)
   lctime = gmtime(&ntime);
   return lctime;
 }
-#endif
 
 static std::string CleanString(std::string str)
 {
@@ -175,6 +171,32 @@ static const char* cmCTestWarningExceptions[] = {
   0
 };
 
+static const char* cmCTestMemCheckResultStrings[] = {
+  "ABR",
+  "ABW",
+  "ABWL",
+  "COR",
+  "EXU",
+  "FFM",
+  "FIM",
+  "FMM",
+  "FMR",
+  "FMW",
+  "FUM",
+  "IPR",
+  "IPW",
+  "MAF",
+  "MLK",
+  "MPK",
+  "NPR",
+  "ODS",
+  "PAR",
+  "PLK",
+  "UMC",
+  "UMR",
+  0
+};
+
 std::string cmCTest::MakeXMLSafe(const std::string& str)
 {
   cmOStringStream ost;
@@ -271,6 +293,7 @@ cmCTest::cmCTest()
   m_RunConfigurationScript = false;
   m_TestModel              = cmCTest::EXPERIMENTAL;
   m_TimeOut                = 0;
+  m_CompatibilityMode      = 1;
   int cc; 
   for ( cc=0; cc < cmCTest::LAST_TEST; cc ++ )
     {
@@ -369,14 +392,12 @@ void cmCTest::Initialize()
       }
     if ( tag.size() == 0 || m_Tests[cmCTest::START_TEST] || m_Tests[ALL_TEST])
       {
-#ifdef HAVE_CURL
       //std::cout << "TestModel: " << this->GetTestModelString() << std::endl;
       //std::cout << "TestModel: " << m_TestModel << std::endl;
       if ( m_TestModel == cmCTest::NIGHTLY )
         {
         lctime = ::GetNightlyTime(m_DartConfiguration["NightlyStartTime"]);
         }
-#endif
       char datestring[100];
       sprintf(datestring, "%04d%02d%02d-%02d%02d",
               lctime->tm_year + 1900,
@@ -427,9 +448,9 @@ bool cmCTest::SetTest(const char* ttype)
     {
     m_Tests[cmCTest::COVERAGE_TEST] = 1;
     }
-  else if ( cmSystemTools::LowerCase(ttype) == "purify" )
+  else if ( cmSystemTools::LowerCase(ttype) == "memcheck" )
     {
-    m_Tests[cmCTest::PURIFY_TEST] = 1;
+    m_Tests[cmCTest::MEMCHECK_TEST] = 1;
     }
   else if ( cmSystemTools::LowerCase(ttype) == "submit" )
     {
@@ -543,7 +564,6 @@ int cmCTest::UpdateDirectory()
     }
 
   std::string extra_update_opts;
-#ifdef HAVE_CURL
   if ( m_TestModel == cmCTest::NIGHTLY )
     {
     struct tm* t = ::GetNightlyTime(m_DartConfiguration["NightlyStartTime"]);
@@ -560,7 +580,6 @@ int cmCTest::UpdateDirectory()
     extra_update_opts += "-D \"" + today_update_date +"\"";
     //std::cout << "Update: " << extra_update_opts << std::endl;
     }
-#endif
 
   std::string command = cvsCommand + " -z3 update " + cvsOptions +
     " " + extra_update_opts;
@@ -597,8 +616,8 @@ int cmCTest::UpdateDirectory()
      << "\t<BuildName>" << m_DartConfiguration["BuildName"]
      << "</BuildName>\n"
      << "\t<BuildStamp>" << m_CurrentTag << "-"
-     << this->GetTestModelString() << "</BuildStamp>\n"
-     << "\t<StartDateTime>" << start_time << "</StartDateTime>\n"
+     << this->GetTestModelString() << "</BuildStamp>" << std::endl;
+  os << "\t<StartDateTime>" << start_time << "</StartDateTime>\n"
      << "\t<UpdateCommand>" << command << "</UpdateCommand>\n"
      << "\t<UpdateReturnStatus>";
   if ( retVal )
@@ -904,12 +923,8 @@ int cmCTest::ConfigureDirectory()
     
     if ( os )
       {
-      os << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
-         << "<Site BuildName=\"" << m_DartConfiguration["BuildName"]
-         << "\" BuildStamp=\"" << m_CurrentTag << "-"
-         << this->GetTestModelString() << "\" Name=\""
-         << m_DartConfiguration["Site"] << "\">\n"
-         << "<Configure>\n"
+      this->StartXML(os);
+      os << "<Configure>\n"
          << "\t<StartDateTime>" << start_time << "</StartDateTime>" << std::endl;
       if ( res == cmsysProcess_State_Exited && retVal )
         {
@@ -921,8 +936,8 @@ int cmCTest::ConfigureDirectory()
       std::string end_time = ::CurrentTime();
       os << "\t<ConfigureStatus>" << retVal << "</ConfigureStatus>\n"
          << "\t<EndDateTime>" << end_time << "</EndDateTime>\n"
-         << "</Configure>\n"
-         << "</Site>" << std::endl;
+         << "</Configure>" << std::endl;
+      this->EndXML(os);
       }    
     }
   else
@@ -999,7 +1014,7 @@ int cmCTest::BuildDirectory()
   for ( cc = 0; cmCTestErrorMatches[cc]; cc ++ )
     {
     cmsys::RegularExpression re(cmCTestErrorMatches[cc]);
-    std::vector<std::string>::size_type kk;
+    cmCTest::tm_VectorOfStrings::size_type kk;
     for ( kk = 0; kk < lines.size(); kk ++ )
       {
       if ( re.find(lines[kk]) )
@@ -1012,7 +1027,7 @@ int cmCTest::BuildDirectory()
   for ( cc = 0; cmCTestWarningMatches[cc]; cc ++ )
     {
     cmsys::RegularExpression re(cmCTestWarningMatches[cc]);
-    std::vector<std::string>::size_type kk;
+    cmCTest::tm_VectorOfStrings::size_type kk;
     for ( kk = 0; kk < lines.size(); kk ++ )
       {
       if ( re.find(lines[kk]) )
@@ -1128,9 +1143,9 @@ int cmCTest::BuildDirectory()
 int cmCTest::CoverageDirectory()
 {
   std::cout << "Performing coverage" << std::endl;
-  std::vector<std::string> files;
-  std::vector<std::string> cfiles;
-  std::vector<std::string> cdirs;
+  cmCTest::tm_VectorOfStrings files;
+  cmCTest::tm_VectorOfStrings cfiles;
+  cmCTest::tm_VectorOfStrings cdirs;
   bool done = false;
   std::string::size_type cc;
   std::string glob;
@@ -1279,7 +1294,7 @@ int cmCTest::CoverageDirectory()
     std::cout << "Cannot found any coverage files" << std::endl;
     return 1;
     }
-  std::map<std::string, std::vector<std::string> > sourcefiles;
+  std::map<std::string, cmCTest::tm_VectorOfStrings > sourcefiles;
   for ( cc = 0; cc < cfiles.size(); cc ++ )
     {
     std::string& fname = cfiles[cc];
@@ -1302,7 +1317,7 @@ int cmCTest::CoverageDirectory()
         if ( allsourcefiles.find(nf) != allsourcefiles.end() || 
              allbinaryfiles.find(nf) != allbinaryfiles.end() )
           {
-          std::vector<std::string> &cvec = sourcefiles[nf];
+          cmCTest::tm_VectorOfStrings &cvec = sourcefiles[nf];
           cvec.push_back(fname);
           }
         }
@@ -1313,24 +1328,21 @@ int cmCTest::CoverageDirectory()
   //     std::cout << "File: " << files[cc] << std::endl;
   //     }
 
-  std::map<std::string, std::vector<std::string> >::iterator it;
+  std::map<std::string, cmCTest::tm_VectorOfStrings >::iterator it;
   cmCTest::tm_CoverageMap coverageresults;
 
-  log << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
-      << "<Site BuildName=\"" << m_DartConfiguration["BuildName"]
-      << "\" BuildStamp=\"" << m_CurrentTag << "-"
-      << this->GetTestModelString() << "\" Name=\""
-      << m_DartConfiguration["Site"] << "\">\n"
-      << "<Coverage>\n"
+  this->StartXML(log);
+  log << "<Coverage>\n"
       << "\t<StartDateTime>" << start_time << "</StartDateTime>" << std::endl;
 
   int total_tested = 0;
   int total_untested = 0;
 
   for ( it = sourcefiles.begin(); it != sourcefiles.end(); it ++ )
     {
-      //    std::cerr << "Source file: " << it->first << std::endl;
-    std::vector<std::string> &gfiles = it->second;
+    //std::cerr << "Source file: " << it->first << std::endl;
+    cmCTest::tm_VectorOfStrings &gfiles = it->second;
+
     for ( cc = 0; cc < gfiles.size(); cc ++ )
       {
       //std::cout << "\t" << gfiles[cc] << std::endl;
@@ -1435,8 +1447,8 @@ int cmCTest::CoverageDirectory()
       {
       local_end_time = ::CurrentTime();
       cfileoutput << "\t<EndDateTime>" << local_end_time << "</EndDateTime>\n"
-        << "</CoverageLog>\n"
-        << "</Site>" << std::endl;
+        << "</CoverageLog>" << std::endl;
+      this->EndXML(cfileoutput);
       cfileoutput.close();
       std::cout << "Close file: " << cfileoutputname << std::endl;
       ccount = 0;
@@ -1451,12 +1463,8 @@ int cmCTest::CoverageDirectory()
         return 1;
         }
       local_start_time = ::CurrentTime();
-      cfileoutput << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
-        << "<Site BuildName=\"" << m_DartConfiguration["BuildName"]
-        << "\" BuildStamp=\"" << m_CurrentTag << "-"
-        << this->GetTestModelString() << "\" Site=\""
-        << m_DartConfiguration["Site"] << "\">\n"
-        << "<CoverageLog>\n"
+      this->StartXML(cfileoutput);
+      cfileoutput << "<CoverageLog>\n"
         << "\t<StartDateTime>" << local_start_time << "</StartDateTime>" << std::endl;
       }
 
@@ -1524,8 +1532,8 @@ int cmCTest::CoverageDirectory()
     {
     local_end_time = ::CurrentTime();
     cfileoutput << "\t<EndDateTime>" << local_end_time << "</EndDateTime>\n"
-                << "</CoverageLog>\n"
-                << "</Site>" << std::endl;
+                << "</CoverageLog>" << std::endl;
+    this->EndXML(cfileoutput);
     cfileoutput.close();
     }
 
@@ -1547,8 +1555,8 @@ int cmCTest::CoverageDirectory()
   log.precision(2);
   log << (percent_coverage)<< "</PercentCoverage>\n"
       << "\t<EndDateTime>" << end_time << "</EndDateTime>\n"
-      << "</Coverage>\n"
-      << "</Site>" << std::endl;
+      << "</Coverage>" << std::endl;
+  this->EndXML(log);
 
   std::cout << "\tCovered LOC:         " << total_tested << std::endl
             << "\tNot covered LOC:     " << total_untested << std::endl
@@ -1603,12 +1611,8 @@ bool cmCTest::OpenOutputFile(const std::string& path,
 void cmCTest::GenerateDartBuildOutput(std::ostream& os, 
                                     std::vector<cmCTestBuildErrorWarning> ew)
 {
-  os << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
-     << "<Site BuildName=\"" << m_DartConfiguration["BuildName"]
-     << "\" BuildStamp=\"" << m_CurrentTag << "-"
-     << this->GetTestModelString() << "\" Name=\""
-     << m_DartConfiguration["Site"] << "\">\n"
-     << "<Build>\n"
+  this->StartXML(os);
+  os << "<Build>\n"
      << "\t<StartDateTime>" << m_StartBuild << "</StartDateTime>\n"
      << "<BuildCommand>" 
      << this->MakeXMLSafe(m_DartConfiguration["MakeCommand"])
@@ -1647,12 +1651,13 @@ void cmCTest::GenerateDartBuildOutput(std::ostream& os,
     }
   os << "\t<Log Encoding=\"base64\" Compression=\"/bin/gzip\">\n\t</Log>\n"
      << "\t<EndDateTime>" << m_EndBuild << "</EndDateTime>\n"
-     << "</Build>\n"
-     << "</Site>" << std::endl;
+     << "</Build>" << std::endl;
+  this->EndXML(os);
 }
   
-void cmCTest::ProcessDirectory(std::vector<std::string> &passed, 
-                             std::vector<std::string> &failed)
+void cmCTest::ProcessDirectory(cmCTest::tm_VectorOfStrings &passed, 
+                             cmCTest::tm_VectorOfStrings &failed,
+                             bool memcheck)
 {
   // does the DartTestfile.txt exist ?
   if(!cmSystemTools::FileExists("DartTestfile.txt"))
@@ -1692,7 +1697,7 @@ void cmCTest::ProcessDirectory(std::vector<std::string> &passed,
         if (cmSystemTools::FileIsDirectory(nwd.c_str()))
           {
           cmSystemTools::ChangeDirectory(nwd.c_str());
-          this->ProcessDirectory(passed, failed);
+          this->ProcessDirectory(passed, failed, memcheck);
           }
         }
       // return to the original directory
@@ -1724,7 +1729,10 @@ void cmCTest::ProcessDirectory(std::vector<std::string> &passed,
       if (firstTest)
         {
         std::string nwd = cmSystemTools::GetCurrentWorkingDirectory();
-        std::cerr << "Changing directory into " << nwd.c_str() << "\n";
+        if ( m_Verbose )
+          {
+          std::cerr << "Changing directory into " << nwd.c_str() << "\n";
+          }
         firstTest = 0;
         }
       cres.m_Name = args[0].Value;
@@ -1756,6 +1764,15 @@ void cmCTest::ProcessDirectory(std::vector<std::string> &passed,
       ++j;
       ++j;
       std::vector<const char*> arguments;
+      if ( memcheck )
+        {
+        cmCTest::tm_VectorOfStrings::size_type pp;
+        arguments.push_back(m_MemoryTester.c_str());
+        for ( pp = 0; pp < m_MemoryTesterOptionsParsed.size(); pp ++ )
+          {
+          arguments.push_back(m_MemoryTesterOptionsParsed[pp].c_str());
+          }
+        }
       arguments.push_back(actualCommand.c_str());
       for(;j != args.end(); ++j)
         {
@@ -1867,15 +1884,97 @@ void cmCTest::ProcessDirectory(std::vector<std::string> &passed,
     }
 }
 
-int cmCTest::TestDirectory()
+bool cmCTest::InitializeMemoryChecking()
+{
+  if ( cmSystemTools::FileExists(m_DartConfiguration["MemoryCheckCommand"].c_str()) )
+    {
+    m_MemoryTester 
+      = cmSystemTools::ConvertToOutputPath(m_DartConfiguration["MemoryCheckCommand"].c_str());
+    }
+  else if ( cmSystemTools::FileExists(m_DartConfiguration["PurifyCommand"].c_str()) )
+    {
+    m_MemoryTester 
+      = cmSystemTools::ConvertToOutputPath(m_DartConfiguration["PurifyCommand"].c_str());
+    }
+  else if ( cmSystemTools::FileExists(m_DartConfiguration["ValgrindCommand"].c_str()) )
+    {
+    m_MemoryTester 
+      = cmSystemTools::ConvertToOutputPath(m_DartConfiguration["ValgrindCommand"].c_str());
+    }
+  else
+    {
+    std::cout << "Memory checker (MemoryCheckCommand) not set, or cannot find the specified program." 
+      << std::endl;
+    return false;
+    }
+
+  if ( m_DartConfiguration["MemoryCheckCommandOptions"].size() )
+    {
+    m_MemoryTesterOptions = m_DartConfiguration["MemoryCheckCommandOptions"];
+    }
+  else if ( m_DartConfiguration["ValgrindCommandOptions"].size() )
+    {
+    m_MemoryTesterOptions = m_DartConfiguration["ValgrindCommandOptions"];
+    }
+
+  m_MemoryTesterOutputFile = m_ToplevelPath + "/Testing/Temporary/MemoryChecker.log";
+  m_MemoryTesterOutputFile = cmSystemTools::EscapeSpaces(m_MemoryTesterOutputFile.c_str());
+
+  if ( m_MemoryTester.find("valgrind") )
+    {
+    m_MemoryTesterStyle = cmCTest::VALGRIND;
+    if ( !m_MemoryTesterOptions.size() )
+      {
+      m_MemoryTesterOptions = "-q --skin=memcheck --leak-check=yes --show-reachable=yes --workaround-gcc296-bugs=yes --num-callers=100";
+      }
+    }
+  else if ( m_MemoryTester.find("purify") )
+    {
+    m_MemoryTesterStyle = cmCTest::PURIFY;
+#ifdef _WIN32
+    m_MemoryTesterOptions += " /SAVETEXTDATA=" + m_MemoryTesterOutputFile;
+#else
+    m_MemoryTesterOptions += " -log-file=" + m_MemoryTesterOutputFile;
+#endif
+    }
+  else if ( m_MemoryTester.find("boundschecker") )
+    {
+    m_MemoryTesterStyle = cmCTest::BOUNDS_CHECKER;
+    std::cout << "Bounds checker not yet implemented" << std::endl;
+    return false;
+    }
+  else
+    {
+    std::cout << "Do not understand memory checker: " << m_MemoryTester.c_str() << std::endl;
+    return false;
+    }
+
+  m_MemoryTesterOptionsParsed = cmSystemTools::ParseArguments(m_MemoryTesterOptions.c_str());
+  cmCTest::tm_VectorOfStrings::size_type cc;
+  for ( cc = 0; cmCTestMemCheckResultStrings[cc]; cc ++ )
+    {
+    m_MemoryTesterGlobalResults[cc] = 0;
+    }
+  return true;
+}
+
+int cmCTest::TestDirectory(bool memcheck)
 {
-  std::cout << "Test project" << std::endl;
-  std::vector<std::string> passed;
-  std::vector<std::string> failed;
+  std::cout << (memcheck ? "Memory check" : "Test") << " project" << std::endl;
+  if ( memcheck )
+    {
+    if ( !this->InitializeMemoryChecking() )
+      {
+      return 1;
+      }
+    }
+
+  cmCTest::tm_VectorOfStrings passed;
+  cmCTest::tm_VectorOfStrings failed;
   int total;
 
   m_StartTest = ::CurrentTime();
-  this->ProcessDirectory(passed, failed);
+  this->ProcessDirectory(passed, failed, memcheck);
   m_EndTest = ::CurrentTime();
 
   total = int(passed.size()) + int(failed.size());
@@ -1892,7 +1991,7 @@ int cmCTest::TestDirectory()
     if (passed.size() && (m_UseIncludeRegExp || m_UseExcludeRegExp)) 
       {
       std::cerr << "\nThe following tests passed:\n";
-      for(std::vector<std::string>::iterator j = passed.begin();
+      for(cmCTest::tm_VectorOfStrings::iterator j = passed.begin();
           j != passed.end(); ++j)
         {   
         std::cerr << "\t" << *j << "\n";
@@ -1906,7 +2005,7 @@ int cmCTest::TestDirectory()
     if (failed.size()) 
       {
       std::cerr << "\nThe following tests FAILED:\n";
-      for(std::vector<std::string>::iterator j = failed.begin();
+      for(cmCTest::tm_VectorOfStrings::iterator j = failed.begin();
           j != failed.end(); ++j)
         {   
         std::cerr << "\t" << *j << "\n";
@@ -1917,21 +2016,29 @@ int cmCTest::TestDirectory()
   if ( m_DartMode )
     {
     std::ofstream ofs;
-    if( !this->OpenOutputFile(m_CurrentTag, "Test.xml", ofs) )
+    if( !this->OpenOutputFile(m_CurrentTag, 
+        (memcheck ? (m_CompatibilityMode?"Purify.xml":"MemCheck.xml") : "Test.xml"), ofs) )
       {
-      std::cerr << "Cannot create testing XML file" << std::endl;
+      std::cerr << "Cannot create " << (memcheck ? "memory check" : "testing")
+        << " XML file" << std::endl;
       return 1;
       }
-    this->GenerateDartTestOutput(ofs);
+    if ( memcheck )
+      {
+      this->GenerateDartMemCheckOutput(ofs);
+      }
+    else
+      {
+      this->GenerateDartTestOutput(ofs);
+      }
     }
 
   return int(failed.size());
 }
 
 int cmCTest::SubmitResults()
 {
-#ifdef HAVE_CURL
-  std::vector<std::string> files;
+  cmCTest::tm_VectorOfStrings files;
   std::string prefix = this->GetSubmitResultsPrefix();
   // TODO:
   // Check if test is enabled
@@ -1954,7 +2061,7 @@ int cmCTest::SubmitResults()
   if ( this->CTestFileExists("Coverage.xml") )
     {
     files.push_back("Coverage.xml");
-    std::vector<std::string> gfiles;
+    cmCTest::tm_VectorOfStrings gfiles;
     std::string gpath = m_ToplevelPath + "/Testing/" + m_CurrentTag;
     std::string::size_type glen = gpath.size() + 1;
     gpath = gpath + "/CoverageLog*";
@@ -1974,6 +2081,10 @@ int cmCTest::SubmitResults()
       std::cout << "Problem globbing" << std::endl;
       }
     }
+  if ( this->CTestFileExists("MemCheck.xml") )
+    {
+    files.push_back("MemCheck.xml");
+    }
   if ( this->CTestFileExists("Purify.xml") )
     {
     files.push_back("Purify.xml");
@@ -2035,7 +2146,6 @@ int cmCTest::SubmitResults()
     std::cout << "SCP submit not yet implemented" << std::endl;
     }
                           
-#endif
   return 0;
 }
 
@@ -2055,19 +2165,105 @@ std::string cmCTest::GetSubmitResultsPrefix()
   return name;
 }
 
+void cmCTest::GenerateDartMemCheckOutput(std::ostream& os)
+{
+  if ( !m_DartMode )
+    {
+    return;
+    }
+
+  this->StartXML(os);
+  if ( m_CompatibilityMode )
+    {
+    os << "<Purify>" << std::endl;
+    }
+  else
+    {
+    os << "<MemCheck>" << std::endl;
+    }
+  os << "\t<StartDateTime>" << m_StartTest << "</StartDateTime>\n"
+     << "\t<TestList>\n";
+  tm_TestResultsVector::size_type cc;
+  for ( cc = 0; cc < m_TestResults.size(); cc ++ )
+    {
+    cmCTestTestResult *result = &m_TestResults[cc];
+    os << "\t\t<Test>" << this->MakeXMLSafe(result->m_Path) 
+       << "/" << this->MakeXMLSafe(result->m_Name)
+       << "</Test>" << std::endl;
+    }
+  os << "\t</TestList>\n";
+  for ( cc = 0; cc < m_TestResults.size(); cc ++ )
+    {
+    cmCTestTestResult *result = &m_TestResults[cc];
+    std::string memcheckstr;
+    int memcheckresults[cmCTest::NO_MEMORY_FAULT];
+    int kk;
+    this->ProcessMemCheckOutput(result->m_Output, memcheckstr, memcheckresults);
+    os << "\t<Test Status=\"";
+    if ( result->m_Status == cmCTest::COMPLETED )
+      {
+      os << "passed";
+      }
+    else if ( result->m_Status == cmCTest::NOT_RUN )
+      {
+      os << "notrun";
+      }
+    else
+      {
+      os << "failed";
+      }
+    os << "\">\n"
+      << "\t\t<Name>" << this->MakeXMLSafe(result->m_Name) << "</Name>\n"
+      << "\t\t<Path>" << this->MakeXMLSafe(result->m_Path) << "</Path>\n"
+      << "\t\t<FullName>" << this->MakeXMLSafe(result->m_Path) 
+      << "/" << this->MakeXMLSafe(result->m_Name) << "</FullName>\n"
+      << "\t\t<FullCommandLine>" 
+      << this->MakeXMLSafe(result->m_FullCommandLine) 
+      << "</FullCommandLine>\n"
+      << "\t\t<Results>" << std::endl;
+    for ( kk = 0; cmCTestMemCheckResultStrings[kk]; kk ++ )
+      {
+      os << "\t\t\t<" << cmCTestMemCheckResultStrings[kk] << ">"
+        << memcheckresults[kk] 
+        << "</" << cmCTestMemCheckResultStrings[kk] << ">" << std::endl;
+      m_MemoryTesterGlobalResults[kk] += memcheckresults[kk];
+      }
+    os 
+      << "\t\t</Results>\n"
+      << "\t<Log>\n" << cmCTest::MakeXMLSafe(memcheckstr) << std::endl
+      << "\t</Log>\n"
+      << "\t</Test>" << std::endl;
+    }
+  
+  os << "\t<EndDateTime>" << m_EndTest << "</EndDateTime>" << std::endl;
+  if ( m_CompatibilityMode )
+    {
+    os << "</Purify>" << std::endl;
+    }
+  else
+    {
+    os << "</MemCheck>" << std::endl;
+    }
+  this->EndXML(os);
+
+
+  std::cerr << "Memory checking results:" << std::endl;
+  for ( cc = 0; cmCTestMemCheckResultStrings[cc]; cc ++ )
+    {
+    std::cerr << "\t\t" << cmCTestMemCheckResultStrings[cc] << " - " 
+      << m_MemoryTesterGlobalResults[cc] << std::endl;
+    }
+}
+
 void cmCTest::GenerateDartTestOutput(std::ostream& os)
 {
   if ( !m_DartMode )
     {
     return;
     }
 
-  os << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
-     << "<Site BuildName=\"" << m_DartConfiguration["BuildName"]
-     << "\" BuildStamp=\"" << m_CurrentTag << "-"
-     << this->GetTestModelString() << "\" Name=\""
-     << m_DartConfiguration["Site"] << "\">\n"
-     << "<Testing>\n"
+  this->StartXML(os);
+  os << "<Testing>\n"
      << "\t<StartDateTime>" << m_StartTest << "</StartDateTime>\n"
      << "\t<TestList>\n";
   tm_TestResultsVector::size_type cc;
@@ -2132,8 +2328,8 @@ void cmCTest::GenerateDartTestOutput(std::ostream& os)
     }
   
   os << "\t<EndDateTime>" << m_EndTest << "</EndDateTime>\n"
-     << "</Testing>\n"
-     << "</Site>" << std::endl;
+     << "</Testing>" << std::endl;
+  this->EndXML(os);
 }
 
 int cmCTest::ProcessTests()
@@ -2173,23 +2369,19 @@ int cmCTest::ProcessTests()
     }
   if ( m_Tests[TEST_TEST] || m_Tests[ALL_TEST] || notest )
     {
-    res += this->TestDirectory();
+    res += this->TestDirectory(false);
     }
   if ( m_Tests[COVERAGE_TEST] || m_Tests[ALL_TEST] )
     {
     this->CoverageDirectory();
     }
-  if ( m_Tests[PURIFY_TEST] || m_Tests[ALL_TEST] )
+  if ( m_Tests[MEMCHECK_TEST] || m_Tests[ALL_TEST] )
     {
-    std::cerr << "Purify test is not yet implemented" << std::endl;
+    res += this->TestDirectory(true);
     }
   if ( m_Tests[SUBMIT_TEST] || m_Tests[ALL_TEST] )
     {
-#ifdef HAVE_CURL
     this->SubmitResults();
-#else
-    std::cerr << "Submit test is not yet implemented" << std::endl;
-#endif
     }
   return res;
 }
@@ -2763,3 +2955,100 @@ int cmCTest::RunConfigurationScript()
 
   return 0;  
 }
+
+void cmCTest::StartXML(ostream& ostr)
+{
+  ostr << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
+    << "<Site BuildName=\"" << m_DartConfiguration["BuildName"]
+    << "\" BuildStamp=\"" << m_CurrentTag << "-"
+    << this->GetTestModelString() << "\" Name=\""
+    << m_DartConfiguration["Site"] << "\">" << std::endl;
+}
+
+void cmCTest::EndXML(ostream& ostr)
+{
+  ostr << "</Site>" << std::endl;
+}
+
+bool cmCTest::ProcessMemCheckValgrindOutput(const std::string& str, std::string& log, int* results)
+{
+  std::vector<cmStdString> lines;
+  cmSystemTools::Split(str.c_str(), lines);
+
+
+  std::string::size_type cc;
+
+  cmOStringStream ostr;
+  log = "";
+
+  cmsys::RegularExpression valgrindLine("^==[0-9][0-9]*==");
+
+  cmsys::RegularExpression vgFIM("== .*Invalid free\\(\\) / delete / delete\\[\\]");
+  cmsys::RegularExpression vgFMM("== .*Mismatched free\\(\\) / delete / delete \\[\\]");
+  cmsys::RegularExpression vgMLK("== .*[0-9][0-9]* bytes in [0-9][0-9]* blocks are definitely lost in loss record [0-9][0-9]* of [0-9]");
+  cmsys::RegularExpression vgPAR("== .*Syscall param .* contains unaddressable byte\\(s\\)");
+  cmsys::RegularExpression vgMPK1("== .*[0-9][0-9]* bytes in [0-9][0-9]* blocks are possibly lost in loss record [0-9][0-9]* of [0-9]");
+  cmsys::RegularExpression vgMPK2("== .*[0-9][0-9]* bytes in [0-9][0-9]* blocks are still reachable in loss record [0-9][0-9]* of [0-9]");
+  cmsys::RegularExpression vgUMC("== .*Conditional jump or move depends on uninitialised value\\(s\\)");
+  cmsys::RegularExpression vgUMR1("== .*Use of uninitialised value of size [0-9][0-9]*");
+  cmsys::RegularExpression vgUMR2("== .*Invalid read of size [0-9][0-9]*");
+  cmsys::RegularExpression vgUMR3("== .*Jump to the invalid address ");
+  cmsys::RegularExpression vgUMR4("== .*Syscall param .* contains uninitialised or unaddressable byte\\(s\\)");
+  cmsys::RegularExpression vgIPW("== .*Invalid write of size [0-9]");
+
+  for ( cc = 0; cc < lines.size(); cc ++ )
+    {
+    if ( valgrindLine.find(lines[cc]) )
+      {
+           if ( vgFIM.find(lines[cc]) )  { results[cmCTest::FIM] ++; ostr << "FIM"; }
+      else if ( vgFMM.find(lines[cc]) )  { results[cmCTest::FMM] ++; ostr << "FMM"; }
+      else if ( vgMLK.find(lines[cc]) )  { results[cmCTest::MLK] ++; ostr << "MLK"; }
+      else if ( vgPAR.find(lines[cc]) )  { results[cmCTest::PAR] ++; ostr << "PAR"; }
+      else if ( vgMPK1.find(lines[cc]) ) { results[cmCTest::MPK] ++; ostr << "MPK"; }
+      else if ( vgMPK2.find(lines[cc]) ) { results[cmCTest::MPK] ++; ostr << "MPK"; }
+      else if ( vgUMC.find(lines[cc]) )  { results[cmCTest::UMC] ++; ostr << "UMC"; }
+      else if ( vgUMR1.find(lines[cc]) ) { results[cmCTest::UMR] ++; ostr << "UMR"; }
+      else if ( vgUMR2.find(lines[cc]) ) { results[cmCTest::UMR] ++; ostr << "UMR"; }
+      else if ( vgUMR3.find(lines[cc]) ) { results[cmCTest::UMR] ++; ostr << "UMR"; }
+      else if ( vgUMR4.find(lines[cc]) ) { results[cmCTest::UMR] ++; ostr << "UMR"; }
+      else if ( vgIPW.find(lines[cc]) )  { results[cmCTest::IPW] ++; ostr << "IPW"; }
+
+      ostr << lines[cc] << std::endl;
+      }
+    }
+  log = ostr.str();
+  return true;
+}
+
+bool cmCTest::ProcessMemCheckOutput(const std::string& str, std::string& log, int* results)
+{
+  std::string::size_type cc;
+  for ( cc = 0; cc < cmCTest::NO_MEMORY_FAULT; cc ++ )
+    {
+    results[cc] = 0;
+    }
+
+  if ( m_MemoryTesterStyle == cmCTest::VALGRIND )
+    {
+    return ProcessMemCheckValgrindOutput(str, log, results);
+    }
+  else if ( m_MemoryTesterStyle == cmCTest::PURIFY )
+    {
+    log.append("\nMemory checking style used was: ");
+    log.append("Purify");
+    }
+  else if ( m_MemoryTesterStyle == cmCTest::BOUNDS_CHECKER )
+    {
+    log.append("\nMemory checking style used was: ");
+    log.append("Bounds Checker");
+    }
+  else
+    {
+    log.append("\nMemory checking style used was: ");
+    log.append("None that I know");
+    log = str;
+    }
+
+
+  return true;
+}