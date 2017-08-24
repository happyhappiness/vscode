@@ -24,7 +24,9 @@
 #include "cmDynamicLoader.h"
 
 #include "cmCTestBuildHandler.h"
+#include "cmCTestCoverageHandler.h"
 #include "cmCTestScriptHandler.h"
+#include "cmCTestTestHandler.h"
 #include "cmCTestUpdateHandler.h"
 #include "cmCTestConfigureHandler.h"
 
@@ -33,15 +35,13 @@
 
 #include <cmsys/RegularExpression.hxx>
 #include <cmsys/Process.h>
-#include <cmsys/Base64.h>
 
 #include <stdlib.h> 
 #include <math.h>
 #include <float.h>
 
 #include <memory> // auto_ptr
 
-#define SAFEDIV(x,y) (((y)!=0)?((x)/(y)):(0))
 #define DEBUGOUT std::cout << __LINE__ << " "; std::cout
 #define DEBUGERR std::cerr << __LINE__ << " "; std::cerr
 
@@ -112,7 +112,7 @@ struct tm* cmCTest::GetNightlyTime(std::string str,
   return lctime;
 }
 
-static std::string CleanString(const std::string& str)
+std::string cmCTest::CleanString(const std::string& str)
 {
   std::string::size_type spos = str.find_first_not_of(" \n\t\r\f\v");
   std::string::size_type epos = str.find_last_not_of(" \n\t\r\f\v");
@@ -142,62 +142,10 @@ std::string cmCTest::CurrentTime()
     strftime(current_time, 1000, "%a %b %d %H:%M:%S %Z %Y", t);
     }
   //std::cout << "Current_Time: " << current_time << std::endl;
-  return cmCTest::MakeXMLSafe(::CleanString(current_time));
+  return cmCTest::MakeXMLSafe(cmCTest::CleanString(current_time));
 }
 
 
-static const char* cmCTestMemCheckResultStrings[] = {
-  "ABR",
-  "ABW",
-  "ABWL",
-  "COR",
-  "EXU",
-  "FFM",
-  "FIM",
-  "FMM",
-  "FMR",
-  "FMW",
-  "FUM",
-  "IPR",
-  "IPW",
-  "MAF",
-  "MLK",
-  "MPK",
-  "NPR",
-  "ODS",
-  "PAR",
-  "PLK",
-  "UMC",
-  "UMR",
-  0
-};
-
-static const char* cmCTestMemCheckResultLongStrings[] = {
-  "Threading Problem",
-  "ABW",
-  "ABWL",
-  "COR",
-  "EXU",
-  "FFM",
-  "FIM",
-  "Mismatched deallocation",
-  "FMR",
-  "FMW",
-  "FUM",
-  "IPR",
-  "IPW",
-  "MAF",
-  "Memory Leak",
-  "Potential Memory Leak",
-  "NPR",
-  "ODS",
-  "Invalid syscall param",
-  "PLK",
-  "Uninitialized Memory Conditional",
-  "Uninitialized Memory Read",
-  0
-};
-
 std::string cmCTest::MakeXMLSafe(const std::string& str)
 {
   cmOStringStream ost;
@@ -263,75 +211,41 @@ std::string cmCTest::MakeURLSafe(const std::string& str)
   return ost.str();
 }
 
-bool TryExecutable(const char *dir, const char *file,
-                   std::string *fullPath, const char *subdir)
-{
-  // try current directory
-  std::string tryPath;
-  if (dir && strcmp(dir,""))
-    {
-    tryPath = dir;
-    tryPath += "/";
-    }
-  
-  if (subdir && strcmp(subdir,""))
-    {
-    tryPath += subdir;
-    tryPath += "/";
-    }
-  
-  tryPath += file;
-  if(cmSystemTools::FileExists(tryPath.c_str()))
-    {
-    *fullPath = cmSystemTools::CollapseFullPath(tryPath.c_str());
-    return true;
-    }
-  tryPath += cmSystemTools::GetExecutableExtension();
-  if(cmSystemTools::FileExists(tryPath.c_str()))
-    {
-    *fullPath = cmSystemTools::CollapseFullPath(tryPath.c_str());
-    return true;
-    }
-  return false;
-}
-
 cmCTest::cmCTest() 
 { 
   m_ForceNewCTestProcess   = false;
   m_TomorrowTag            = false;
   m_BuildNoCMake           = false;
   m_BuildNoClean           = false;
   m_BuildTwoConfig         = false;
-  m_UseIncludeRegExp       = false;
-  m_UseExcludeRegExp       = false;
-  m_UseExcludeRegExpFirst  = false;
   m_Verbose                = false;
   m_DartMode               = false;
   m_ShowOnly               = false;
   m_RunConfigurationScript = false;
   m_TestModel              = cmCTest::EXPERIMENTAL;
   m_InteractiveDebugMode   = true;
   m_TimeOut                = 0;
-  m_CompatibilityMode      = 0;
   int cc; 
   for ( cc=0; cc < cmCTest::LAST_TEST; cc ++ )
     {
     m_Tests[cc] = 0;
     }
   m_ShortDateFormat        = true;
-  m_MaximumPassedTestResultSize  = 100 * 1024;
-  m_MaximumFailedTestResultSize  = 200 * 1024;
 
   this->BuildHandler     = new cmCTestBuildHandler;
+  this->CoverageHandler  = new cmCTestCoverageHandler;
   this->ScriptHandler    = new cmCTestScriptHandler;
+  this->TestHandler      = new cmCTestTestHandler;
   this->UpdateHandler    = new cmCTestUpdateHandler;
   this->ConfigureHandler = new cmCTestConfigureHandler;
 }
 
 cmCTest::~cmCTest() 
 { 
   delete this->BuildHandler;
+  delete this->CoverageHandler;
   delete this->ScriptHandler;
+  delete this->TestHandler;
   delete this->UpdateHandler;
   delete this->ConfigureHandler;
 }
@@ -453,7 +367,7 @@ void cmCTest::UpdateCTestConfiguration()
     buffer[0] = 0;
     fin.getline(buffer, 1023);
     buffer[1023] = 0;
-    std::string line = ::CleanString(buffer);
+    std::string line = cmCTest::CleanString(buffer);
     if(line.size() == 0)
       {
       continue;
@@ -464,7 +378,7 @@ void cmCTest::UpdateCTestConfiguration()
       buffer[0] = 0;
       fin.getline(buffer, 1023);
       buffer[1023] = 0;
-      line += ::CleanString(buffer);
+      line += cmCTest::CleanString(buffer);
       }
     if ( line[0] == '#' )
       {
@@ -476,7 +390,7 @@ void cmCTest::UpdateCTestConfiguration()
       continue;
       }
     std::string key = line.substr(0, cpos);
-    std::string value = ::CleanString(line.substr(cpos+1, line.npos));
+    std::string value = cmCTest::CleanString(line.substr(cpos+1, line.npos));
     m_DartConfiguration[key] = value;
     }
   fin.close();
@@ -558,1398 +472,171 @@ void cmCTest::Finalize()
 {
 }
 
-std::string cmCTest::FindTheExecutable(const char *exe)
-{
-  std::string fullPath = "";
-  std::string dir;
-  std::string file;
-
-  cmSystemTools::SplitProgramPath(exe, dir, file);
-  if(m_ConfigType != "" && 
-    ::TryExecutable(dir.c_str(), file.c_str(), &fullPath, 
-      m_ConfigType.c_str()))
-    {
-    return fullPath;
-    }
-
-  if (::TryExecutable(dir.c_str(),file.c_str(),&fullPath,"."))
-    {
-    return fullPath;
-    }
+ 
 
-  if (::TryExecutable(dir.c_str(),file.c_str(),&fullPath,""))
+bool cmCTest::OpenOutputFile(const std::string& path, 
+                     const std::string& name, std::ofstream& stream)
+{
+  std::string testingDir = m_ToplevelPath + "/Testing";
+  if ( path.size() > 0 )
     {
-    return fullPath;
+    testingDir += "/" + path;
     }
-
-  if ( m_ConfigType == "" )
+  if ( cmSystemTools::FileExists(testingDir.c_str()) )
     {
-    // No config type, so try to guess it
-    if (::TryExecutable(dir.c_str(),file.c_str(),&fullPath,"Release"))
-      {
-      return fullPath;
-      }
-
-    if (::TryExecutable(dir.c_str(),file.c_str(),&fullPath,"Debug"))
-      {
-      return fullPath;
-      }
-
-    if (::TryExecutable(dir.c_str(),file.c_str(),&fullPath,"MinSizeRel"))
-      {
-      return fullPath;
-      }
-
-    if (::TryExecutable(dir.c_str(),file.c_str(),&fullPath,"RelWithDebInfo"))
+    if ( !cmSystemTools::FileIsDirectory(testingDir.c_str()) )
       {
-      return fullPath;
+      std::cerr << "File " << testingDir 
+                << " is in the place of the testing directory"
+                << std::endl;
+      return false;
       }
     }
-
-  // if everything else failed, check the users path
-  if (dir != "")
+  else
     {
-    std::string path = cmSystemTools::FindProgram(file.c_str());
-    if (path != "")
+    if ( !cmSystemTools::MakeDirectory(testingDir.c_str()) )
       {
-      return path;
+      std::cerr << "Cannot create directory " << testingDir
+                << std::endl;
+      return false;
       }
     }
-
-  if ( m_ConfigType != "" )
+  std::string filename = testingDir + "/" + name;
+  stream.open(filename.c_str());
+  if( !stream )
     {
-    dir += "/";
-    dir += m_ConfigType;
-    dir += "/";
-    dir += file;
-    cmSystemTools::Error("config type specified on the command line, but test executable not found.",
-      dir.c_str());
-    return "";
+    std::cerr << "Problem opening file: " << filename << std::endl;
+    return false;
     }
-  return fullPath;
+  return true;
 }
 
-
- 
-int cmCTest::CoverageDirectory()
+int cmCTest::SubmitResults()
 {
-  std::cout << "Performing coverage" << std::endl;
-  double elapsed_time_start = cmSystemTools::GetTime();
-  cmCTest::tm_VectorOfStrings files;
-  cmCTest::tm_VectorOfStrings cfiles;
-  cmCTest::tm_VectorOfStrings cdirs;
-  bool done = false;
-  std::string::size_type cc;
-  std::string glob;
-  std::map<std::string, std::string> allsourcefiles;
-  std::map<std::string, std::string> allbinaryfiles;
-
-  std::string start_time = this->CurrentTime();
+  std::ofstream ofs;
+  this->OpenOutputFile("Temporary", "LastSubmit.log", ofs);
 
-  // Find all source files.
-  std::string sourceDirectory = m_DartConfiguration["SourceDirectory"];
-  if ( sourceDirectory.size() == 0 )
+  cmCTest::tm_VectorOfStrings files;
+  std::string prefix = this->GetSubmitResultsPrefix();
+  // TODO:
+  // Check if test is enabled
+  if ( this->CTestFileExists("Update.xml") )
     {
-    std::cerr << "Cannot find SourceDirectory key in the DartConfiguration.tcl" << std::endl;
-    return 1;
+    files.push_back("Update.xml");
     }
-
-  std::string coverageCommand = m_DartConfiguration["CoverageCommand"];
-  if ( coverageCommand.size() == 0 )
+  if ( this->CTestFileExists("Configure.xml") )
     {
-    std::cerr << "Coverage command not defined in DartConfiguration.tcl" << std::endl;
-    return 1;
+    files.push_back("Configure.xml");
     }
-  cdirs.push_back(sourceDirectory);
-  while ( !done ) 
+  if ( this->CTestFileExists("Build.xml") )
     {
-    if ( cdirs.size() <= 0 )
-      {
-      break;
-      }
-    glob = cdirs[cdirs.size()-1] + "/*";
-    //std::cout << "Glob: " << glob << std::endl;
-    cdirs.pop_back();
-    if ( cmSystemTools::SimpleGlob(glob, cfiles, 1) )
-      {
-      for ( cc = 0; cc < cfiles.size(); cc ++ )
-        {
-        allsourcefiles[cmSystemTools::GetFilenameName(cfiles[cc])] = cfiles[cc];
-        }
-      }
-    if ( cmSystemTools::SimpleGlob(glob, cfiles, -1) )
-      {
-      for ( cc = 0; cc < cfiles.size(); cc ++ )
-        {
-        if ( cfiles[cc] != "." && cfiles[cc] != ".." )
-          {
-          cdirs.push_back(cfiles[cc]);
-          }
-        }
-      }
+    files.push_back("Build.xml");
     }
-
-  // find all binary files
-  cdirs.push_back(cmSystemTools::GetCurrentWorkingDirectory());
-  while ( !done ) 
+  if ( this->CTestFileExists("Test.xml") )
     {
-    if ( cdirs.size() <= 0 )
-      {
-      break;
-      }
-    glob = cdirs[cdirs.size()-1] + "/*";
-    //std::cout << "Glob: " << glob << std::endl;
-    cdirs.pop_back();
-    if ( cmSystemTools::SimpleGlob(glob, cfiles, 1) )
-      {
-      for ( cc = 0; cc < cfiles.size(); cc ++ )
-        {
-        allbinaryfiles[cmSystemTools::GetFilenameName(cfiles[cc])] = cfiles[cc];
-        }
-      }
-    if ( cmSystemTools::SimpleGlob(glob, cfiles, -1) )
+    files.push_back("Test.xml");
+    }
+  if ( this->CTestFileExists("Coverage.xml") )
+    {
+    files.push_back("Coverage.xml");
+    cmCTest::tm_VectorOfStrings gfiles;
+    std::string gpath = m_ToplevelPath + "/Testing/" + m_CurrentTag;
+    std::string::size_type glen = gpath.size() + 1;
+    gpath = gpath + "/CoverageLog*";
+    //std::cout << "Globbing for: " << gpath.c_str() << std::endl;
+    if ( cmSystemTools::SimpleGlob(gpath, gfiles, 1) )
       {
-      for ( cc = 0; cc < cfiles.size(); cc ++ )
+      size_t cc;
+      for ( cc = 0; cc < gfiles.size(); cc ++ )
         {
-        if ( cfiles[cc] != "." && cfiles[cc] != ".." )
-          {
-          cdirs.push_back(cfiles[cc]);
-          }
+        gfiles[cc] = gfiles[cc].substr(glen);
+        //std::cout << "Glob file: " << gfiles[cc].c_str() << std::endl;
+        files.push_back(gfiles[cc]);
         }
       }
-    }
-
-  std::map<std::string, std::string>::iterator sit;
-  for ( sit = allbinaryfiles.begin(); sit != allbinaryfiles.end(); sit ++ )
-    {
-    const std::string& fname = sit->second;
-    //std::cout << "File: " << fname << std::endl;
-    if ( strcmp(fname.substr(fname.size()-3, 3).c_str(), ".da") == 0 )
+    else
       {
-      files.push_back(fname);
+      std::cerr << "Problem globbing" << std::endl;
       }
     }
-  
-  if ( files.size() == 0 )
+  if ( this->CTestFileExists("DynamicAnalysis.xml") )
     {
-    std::cerr << "Cannot find any coverage information files (.da)" << std::endl;
-    return 1;
+    files.push_back("DynamicAnalysis.xml");
     }
-
-  std::ofstream log; 
-  if (!this->OpenOutputFile("Temporary", "Coverage.log", log))
+  if ( this->CTestFileExists("Purify.xml") )
     {
-    std::cerr << "Cannot open log file" << std::endl;
-    return 1;
+    files.push_back("Purify.xml");
     }
-  log.close();
-  if (!this->OpenOutputFile(m_CurrentTag, "Coverage.xml", log))
+  if ( this->CTestFileExists("Notes.xml") )
     {
-    std::cerr << "Cannot open log file" << std::endl;
-    return 1;
+    files.push_back("Notes.xml");
     }
 
-  std::string opath = m_ToplevelPath + "/Testing/Temporary/Coverage";
-  cmSystemTools::MakeDirectory(opath.c_str());
-  cfiles.clear();
-  cmCTest::tm_VectorOfStrings ncfiles;
-  cmCTest::tm_VectorOfStrings missing_files;
-
-  for ( cc = 0; cc < files.size(); cc ++ )
+  if ( ofs )
     {
-    std::string currPath = cmSystemTools::GetFilenamePath(files[cc]);
-    std::string command = coverageCommand + " -o \"" + currPath + "\" -l \"" + files[cc] + "\"";
-    std::string output;
-    int retVal = 0;
-    if ( m_Verbose )
-      {
-      std::cerr << "Run gcov on " << files[cc] << " in directory: " << currPath.c_str() << std::endl;
-      }
-    //std::cout << "   --- Run [" << command << "]" << std::endl;
-    bool res = true;
-    if ( !m_ShowOnly )
-      {
-      res = cmSystemTools::RunSingleCommand(command.c_str(), &output, 
-        &retVal, currPath.c_str(),
-        m_Verbose, 0 /*m_TimeOut*/);
-      }
-    if ( res && retVal == 0 )
-      {
-      //std::cout << " - done" << std::endl;
-      glob = currPath + "/*";
-      if ( !cmSystemTools::SimpleGlob(glob, ncfiles, 1) )
-        {
-        std::cerr << "Cannot found any coverage files" << std::endl;
-        return 1;
-        }
-      cfiles.insert(cfiles.end(), ncfiles.begin(), ncfiles.end());
-      std::vector<cmStdString> gcovlines;
-      cmSystemTools::Split(output.c_str(), gcovlines);
-      std::vector<cmStdString>::iterator git;
-      const char* message = "Could not open source file";
-      for ( git = gcovlines.begin(); git != gcovlines.end(); ++git )
-        {
-        if ( strncmp(git->c_str(), message, strlen(message) ) == 0 )
-          {
-          std::cerr << "Problem: " << git->c_str() << std::endl;
-          missing_files.push_back(git->c_str() + strlen(message));
-          }
-        }
-      }
-    else
+    ofs << "Upload files:" << std::endl;
+    int cnt = 0;
+    cmCTest::tm_VectorOfStrings::iterator it;
+    for ( it = files.begin(); it != files.end(); ++ it )
       {
-      std::cerr << "Run gcov on " << files[cc] << std::flush;
-      std::cerr << " [" << command << "]" << std::endl;
-      std::cerr << " - fail" << std::endl;
+      ofs << cnt << "\t" << it->c_str() << std::endl;
+      cnt ++;
       }
     }
-  
-  files.clear();
-  std::map<std::string, cmCTest::tm_VectorOfStrings > sourcefiles;
-  for ( cc = 0; cc < cfiles.size(); cc ++ )
+  std::cout << "Submit files (using " << m_DartConfiguration["DropMethod"] << ")"
+    << std::endl;
+  cmCTestSubmit submit;
+  submit.SetVerbose(m_Verbose);
+  submit.SetLogFile(&ofs);
+  if ( m_DartConfiguration["DropMethod"] == "" ||
+    m_DartConfiguration["DropMethod"] ==  "ftp" )
     {
-    std::string& fname = cfiles[cc];
-    //    std::cout << "File: " << fname << std::endl;
-    if ( strcmp(fname.substr(fname.size()-5, 5).c_str(), ".gcov") == 0 )
+    ofs << "Using drop method: FTP" << std::endl;
+    std::cout << "  Using FTP submit method" << std::endl;
+    std::string url = "ftp://";
+    url += cmCTest::MakeURLSafe(m_DartConfiguration["DropSiteUser"]) + ":" + 
+      cmCTest::MakeURLSafe(m_DartConfiguration["DropSitePassword"]) + "@" + 
+      m_DartConfiguration["DropSite"] + 
+      cmCTest::MakeURLSafe(m_DartConfiguration["DropLocation"]);
+    if ( !submit.SubmitUsingFTP(m_ToplevelPath+"/Testing/"+m_CurrentTag, 
+        files, prefix, url) )
       {
-      files.push_back(fname);
-      std::string::size_type pos = fname.find(".da.");
-      std::string::size_type pos2 = fname.find(".da##");
-      if(pos2 != fname.npos)
-        {
-        pos = pos2+1;
-        }
-      if ( pos != fname.npos )
-        {
-        pos += 4;
-        std::string::size_type epos = fname.size() - pos - strlen(".gcov");
-        std::string nf = fname.substr(pos, epos);
-        //std::cout << "Substring: " << nf << std::endl;
-        if ( allsourcefiles.find(nf) != allsourcefiles.end() || 
-             allbinaryfiles.find(nf) != allbinaryfiles.end() )
-          {
-          cmCTest::tm_VectorOfStrings &cvec = sourcefiles[nf];
-          cvec.push_back(fname);
-          }
-        }
+      std::cerr << "  Problems when submitting via FTP" << std::endl;
+      ofs << "  Problems when submitting via FTP" << std::endl;
+      return 0;
       }
-    }
-  // for ( cc = 0; cc < files.size(); cc ++ )
-  //     {
-  //     std::cout << "File: " << files[cc] << std::endl;
-  //     }
-  if ( missing_files.size() > 0 )
-    {
-    std::cout << "---------------------------------------------------------------" << std::endl;
-    std::cout << "The following files were missing:" << std::endl;
-    for ( cc = 0; cc < missing_files.size(); cc ++ )
+    if ( !submit.TriggerUsingHTTP(files, prefix, m_DartConfiguration["TriggerSite"]) )
       {
-      std::cout << "File: " << missing_files[cc] << std::endl;
+      std::cerr << "  Problems when triggering via HTTP" << std::endl;
+      ofs << "  Problems when triggering via HTTP" << std::endl;
+      return 0;
       }
-    std::cout << "---------------------------------------------------------------" << std::endl;
+    std::cout << "  Submission successfull" << std::endl;
+    ofs << "  Submission succesfull" << std::endl;
+    return 1;
     }
-
-  std::map<std::string, cmCTest::tm_VectorOfStrings >::iterator it;
-  cmCTest::tm_CoverageMap coverageresults;
-
-  this->StartXML(log);
-  log << "<Coverage>\n"
-      << "\t<StartDateTime>" << start_time << "</StartDateTime>" << std::endl;
-
-  int total_tested = 0;
-  int total_untested = 0;
-
-  for ( it = sourcefiles.begin(); it != sourcefiles.end(); it ++ )
+  else if ( m_DartConfiguration["DropMethod"] == "http" )
     {
-    //std::cerr << "Source file: " << it->first << std::endl;
-    cmCTest::tm_VectorOfStrings &gfiles = it->second;
-
-    for ( cc = 0; cc < gfiles.size(); cc ++ )
+    ofs << "Using drop method: HTTP" << std::endl;
+    std::cout << "  Using HTTP submit method" << std::endl;
+    std::string url = "http://";
+    if ( m_DartConfiguration["DropSiteUser"].size() > 0 )
       {
-      int do_coverage = 1;
-      std::string coverage_dir = cmSystemTools::GetFilenamePath(gfiles[cc].c_str());
-      std::string builDir = m_DartConfiguration["BuildDirectory"];
-      do
-        {
-        std::string coverage_file = coverage_dir + "/.NoDartCoverage";
-        if ( cmSystemTools::FileExists(coverage_file.c_str()) )
-          {
-          do_coverage = 0;
-          break;
-          }
-        // is there a parent directory we can check
-        std::string::size_type pos = coverage_dir.rfind('/');
-        // if we could not find the directory return 0
-        if(pos == std::string::npos)
-          {
-          break;
-          }
-        coverage_dir = coverage_dir.substr(0, pos);
-        }
-      while (coverage_dir.size() >= builDir.size());
-      if ( !do_coverage )
-        {
-        continue;
-        }
-      //std::cout << "\t" << gfiles[cc] << std::endl;
-      std::ifstream ifile(gfiles[cc].c_str());
-      if ( !ifile )
-        {
-        std::cerr << "Cannot open file: " << gfiles[cc].c_str() << std::endl;
-        }
-
-      ifile.seekg (0, std::ios::end);
-      int length = ifile.tellg();
-      ifile.seekg (0, std::ios::beg);
-      char *buffer = new char [ length + 1 ];
-      ifile.read(buffer, length);
-      buffer [length] = 0;
-      //std::cout << "Read: " << buffer << std::endl;
-      std::vector<cmStdString> lines;
-      cmSystemTools::Split(buffer, lines);
-      delete [] buffer;
-      cmCTest::cmCTestCoverage& cov = coverageresults[it->first];
-      std::vector<int>& covlines = cov.m_Lines; 
-      if ( cov.m_FullPath == "" )
-        {
-        covlines.insert(covlines.begin(), lines.size(), -1);
-        if ( allsourcefiles.find(it->first) != allsourcefiles.end() )
-          {
-          cov.m_FullPath = allsourcefiles[it->first];
-          }
-        else if ( allbinaryfiles.find(it->first) != allbinaryfiles.end() )
-          {
-          cov.m_FullPath = allbinaryfiles[it->first];
-          }
-        cov.m_AbsolutePath = cov.m_FullPath;
-        std::string src_dir = m_DartConfiguration["SourceDirectory"];
-        if ( src_dir[src_dir.size()-1] != '/' )
-          {
-          src_dir = src_dir + "/";
-          }
-        std::string::size_type spos = cov.m_FullPath.find(src_dir);
-        if ( spos == 0 )
-          {
-          cov.m_FullPath = std::string("./") + cov.m_FullPath.substr(src_dir.size());
-          }
-        else
-          {
-          //std::cerr << "Compare -- " << cov.m_FullPath << std::endl;
-          //std::cerr << "        -- " << src_dir << std::endl;
-          cov.m_Show = false;
-          continue;
-          }
-        cov.m_Show = true;
-        }
-      std::string::size_type kk;
-      //      std::cerr << "number of lines " << lines.size() << "\n";
-      for ( kk = 0; kk < lines.size(); kk ++ )
+      url += m_DartConfiguration["DropSiteUser"];
+      if ( m_DartConfiguration["DropSitePassword"].size() > 0 )
         {
-        std::string& line = lines[kk];
-        //std::cerr << line << "\n";
-        std::string sub1 = line.substr(0, strlen("    #####"));
-        std::string sub2 = line.substr(0, strlen("      ######"));
-        int count = atoi(sub2.c_str());
-        if ( sub1.compare("    #####") == 0 ||
-             sub2.compare("      ######") == 0 )
-          {
-          if ( covlines[kk] == -1 )
-            {
-            covlines[kk] = 0;
-            }
-          cov.m_UnTested ++;
-          //std::cout << "Untested - ";
-          }
-        else if ( count > 0 )
-          {
-          if ( covlines[kk] == -1 )
-            {
-            covlines[kk] = 0;
-            }
-          cov.m_Tested ++;
-          covlines[kk] ++;
-          //std::cout << "Tested[" << count << "] - ";
-          }
-
-        //std::cout << line << std::endl;
+        url += ":" + m_DartConfiguration["DropSitePassword"];
         }
+      url += "@";
       }
-    }
-
-  //std::cerr << "Finalizing" << std::endl;
-  cmCTest::tm_CoverageMap::iterator cit;
-  int ccount = 0;
-  std::ofstream cfileoutput; 
-  int cfileoutputcount = 0;
-  char cfileoutputname[100];
-  std::string local_start_time = this->CurrentTime();
-  std::string local_end_time;
-  for ( cit = coverageresults.begin(); cit != coverageresults.end(); cit ++ )
-    {
-    cmCTest::cmCTestCoverage &cov = cit->second;
-    if ( !cov.m_Show )
+    url += m_DartConfiguration["DropSite"] + m_DartConfiguration["DropLocation"];
+    if ( !submit.SubmitUsingHTTP(m_ToplevelPath+"/Testing/"+m_CurrentTag, files, prefix, url) )
       {
-      continue;
+      std::cerr << "  Problems when submitting via HTTP" << std::endl;
+      ofs << "  Problems when submitting via HTTP" << std::endl;
+      return 0;
       }
-
-    // Check if we should ignore the directory, if we find a NoDartCoverage
-    // file in it or any of its parents
-    int do_coverage = 1;
-    std::string coverage_dir = cmSystemTools::GetFilenamePath(cov.m_AbsolutePath.c_str());
-    do
-      {
-      std::string coverage_file = coverage_dir + "/.NoDartCoverage";
-      if ( cmSystemTools::FileExists(coverage_file.c_str()) )
-        {
-        do_coverage = 0;
-        break;
-        }
-      // is there a parent directory we can check
-      std::string::size_type pos = coverage_dir.rfind('/');
-      // if we could not find the directory return 0
-      if(pos == std::string::npos)
-        {
-        break;
-        }
-      coverage_dir = coverage_dir.substr(0, pos);
-
-      }
-    while (coverage_dir.size() >= sourceDirectory.size());
-
-    if (!do_coverage)
-      {
-      if ( m_Verbose )
-        {
-        std::cout << "Ignore file: " << cov.m_FullPath.c_str() << std::endl;
-        }
-      continue;
-      }
-    
-    if ( ccount == 100 )
-      {
-      local_end_time = this->CurrentTime();
-      cfileoutput << "\t<EndDateTime>" << local_end_time << "</EndDateTime>\n"
-        << "</CoverageLog>" << std::endl;
-      this->EndXML(cfileoutput);
-      cfileoutput.close();
-      std::cout << "Close file: " << cfileoutputname << std::endl;
-      ccount = 0;
-      }
-    if ( ccount == 0 )
-      {
-      sprintf(cfileoutputname, "CoverageLog-%d.xml", cfileoutputcount++);
-      std::cout << "Open file: " << cfileoutputname << std::endl;
-      if (!this->OpenOutputFile(m_CurrentTag, cfileoutputname, cfileoutput))
-        {
-        std::cerr << "Cannot open log file: " << cfileoutputname << std::endl;
-        return 1;
-        }
-      local_start_time = this->CurrentTime();
-      this->StartXML(cfileoutput);
-      cfileoutput << "<CoverageLog>\n"
-        << "\t<StartDateTime>" << local_start_time << "</StartDateTime>" << std::endl;
-      }
-
-    //std::cerr << "Final process of Source file: " << cit->first << std::endl;
-    cov.m_UnTested = 0;
-    cov.m_Tested = 0;
-    for ( cc = 0; cc < cov.m_Lines.size(); cc ++ )
-      {
-      if ( cov.m_Lines[cc] == 0 )
-        {
-        cov.m_UnTested ++;
-        }
-      else if ( cov.m_Lines[cc] > 0 )
-        {
-        cov.m_Tested ++;
-        }
-      }
-
-    std::ifstream ifile(cov.m_AbsolutePath.c_str());
-    if ( !ifile )
-      {
-      std::cerr << "Cannot open file: " << cov.m_FullPath.c_str() << std::endl;
-      }
-    ifile.seekg (0, std::ios::end);
-    int length = ifile.tellg();
-    ifile.seekg (0, std::ios::beg);
-    char *buffer = new char [ length + 1 ];
-    ifile.read(buffer, length);
-    buffer [length] = 0;
-    //std::cout << "Read: " << buffer << std::endl;
-    std::vector<cmStdString> lines;
-    cmSystemTools::Split(buffer, lines);
-    delete [] buffer;
-
-    cfileoutput << "\t<File Name=\"" << cit->first << "\" FullPath=\""
-      << cov.m_FullPath << "\">\n"
-      << "\t\t<Report>" << std::endl;
-    for ( cc = 0; cc < lines.size(); cc ++ )
-      {
-      cfileoutput << "\t\t<Line Number=\"" 
-        << static_cast<int>(cc) << "\" Count=\""
-        << cov.m_Lines[cc] << "\">"
-        << cmCTest::MakeXMLSafe(lines[cc]) << "</Line>" << std::endl;
-      }
-    cfileoutput << "\t\t</Report>\n"
-      << "\t</File>" << std::endl;
-
-
-    total_tested += cov.m_Tested;
-    total_untested += cov.m_UnTested;
-    float cper = 0;
-    float cmet = 0;
-    if ( total_tested + total_untested > 0 && (cov.m_Tested + cov.m_UnTested) > 0)
-      {
-      cper = (100 * SAFEDIV(static_cast<float>(cov.m_Tested),
-        static_cast<float>(cov.m_Tested + cov.m_UnTested)));
-      cmet = ( SAFEDIV(static_cast<float>(cov.m_Tested + 10),
-        static_cast<float>(cov.m_Tested + cov.m_UnTested + 10)));
-      }
-
-    log << "\t<File Name=\"" << cit->first << "\" FullPath=\"" << cov.m_FullPath
-      << "\" Covered=\"" << (cmet>0?"true":"false") << "\">\n"
-      << "\t\t<LOCTested>" << cov.m_Tested << "</LOCTested>\n"
-      << "\t\t<LOCUnTested>" << cov.m_UnTested << "</LOCUnTested>\n"
-      << "\t\t<PercentCoverage>";
-    log.setf(std::ios::fixed, std::ios::floatfield);
-    log.precision(2);
-    log << (cper) << "</PercentCoverage>\n"
-      << "\t\t<CoverageMetric>";
-    log.setf(std::ios::fixed, std::ios::floatfield);
-    log.precision(2);
-    log << (cmet) << "</CoverageMetric>\n"
-      << "\t</File>" << std::endl;
-    ccount ++;
-    }
-  
-  if ( ccount > 0 )
-    {
-    local_end_time = this->CurrentTime();
-    cfileoutput << "\t<EndDateTime>" << local_end_time << "</EndDateTime>\n"
-                << "</CoverageLog>" << std::endl;
-    this->EndXML(cfileoutput);
-    cfileoutput.close();
-    }
-
-  int total_lines = total_tested + total_untested;
-  float percent_coverage = 100 * SAFEDIV(static_cast<float>(total_tested),
-    static_cast<float>(total_lines));
-  if ( total_lines == 0 )
-    {
-    percent_coverage = 0;
-    }
-
-  std::string end_time = this->CurrentTime();
-
-  log << "\t<LOCTested>" << total_tested << "</LOCTested>\n"
-      << "\t<LOCUntested>" << total_untested << "</LOCUntested>\n"
-      << "\t<LOC>" << total_lines << "</LOC>\n"
-      << "\t<PercentCoverage>";
-  log.setf(std::ios::fixed, std::ios::floatfield);
-  log.precision(2);
-  log << (percent_coverage)<< "</PercentCoverage>\n"
-      << "\t<EndDateTime>" << end_time << "</EndDateTime>\n";
-  log << "<ElapsedMinutes>" << 
-    static_cast<int>((cmSystemTools::GetTime() - elapsed_time_start)/6)/10.0
-      << "</ElapsedMinutes>"
-      << "</Coverage>" << std::endl;
-  this->EndXML(log);
-
-  std::cout << "\tCovered LOC:         " << total_tested << std::endl
-            << "\tNot covered LOC:     " << total_untested << std::endl
-            << "\tTotal LOC:           " << total_lines << std::endl
-            << "\tPercentage Coverage: ";
-
-  std::cout.setf(std::ios::fixed, std::ios::floatfield);
-  std::cout.precision(2);
-  std::cout << (percent_coverage) << "%" << std::endl;
-
-
-  return 1;
-}
-
-bool cmCTest::OpenOutputFile(const std::string& path, 
-                     const std::string& name, std::ofstream& stream)
-{
-  std::string testingDir = m_ToplevelPath + "/Testing";
-  if ( path.size() > 0 )
-    {
-    testingDir += "/" + path;
-    }
-  if ( cmSystemTools::FileExists(testingDir.c_str()) )
-    {
-    if ( !cmSystemTools::FileIsDirectory(testingDir.c_str()) )
-      {
-      std::cerr << "File " << testingDir 
-                << " is in the place of the testing directory"
-                << std::endl;
-      return false;
-      }
-    }
-  else
-    {
-    if ( !cmSystemTools::MakeDirectory(testingDir.c_str()) )
-      {
-      std::cerr << "Cannot create directory " << testingDir
-                << std::endl;
-      return false;
-      }
-    }
-  std::string filename = testingDir + "/" + name;
-  stream.open(filename.c_str());
-  if( !stream )
-    {
-    std::cerr << "Problem opening file: " << filename << std::endl;
-    return false;
-    }
-  return true;
-}
-
-void cmCTest::GetListOfTests(tm_ListOfTests* testlist, bool memcheck)
-{
-  // does the DartTestfile.txt exist ?
-  if(!cmSystemTools::FileExists("DartTestfile.txt"))
-    {
-    return;
-    }
-
-  // parse the file
-  std::ifstream fin("DartTestfile.txt");
-  if(!fin)
-    {
-    return;
-    }
-
-  cmsys::RegularExpression ireg(this->m_IncludeRegExp.c_str());
-  cmsys::RegularExpression ereg(this->m_ExcludeRegExp.c_str());
-
-  cmListFileCache cache;
-  cmListFile* listFile = cache.GetFileCache("DartTestfile.txt", false);
-  for(std::vector<cmListFileFunction>::const_iterator f =
-    listFile->m_Functions.begin(); f != listFile->m_Functions.end(); ++f)
-    {
-    const cmListFileFunction& lff = *f;
-    const std::string& name = lff.m_Name;
-    const tm_VectorOfListFileArgs& args = lff.m_Arguments;
-    if (name == "SUBDIRS")
-      {
-      std::string cwd = cmSystemTools::GetCurrentWorkingDirectory();
-      for(tm_VectorOfListFileArgs::const_iterator j = args.begin();
-        j != args.end(); ++j)
-        {
-        std::string nwd = cwd + "/";
-        nwd += j->Value;
-        if (cmSystemTools::FileIsDirectory(nwd.c_str()))
-          {
-          cmSystemTools::ChangeDirectory(nwd.c_str());
-          this->GetListOfTests(testlist, memcheck);
-          }
-        }
-      // return to the original directory
-      cmSystemTools::ChangeDirectory(cwd.c_str());
-      }
-
-    if (name == "ADD_TEST")
-      {
-      const std::string& testname = args[0].Value;
-      if (this->m_UseExcludeRegExp &&
-        this->m_UseExcludeRegExpFirst &&
-        ereg.find(testname.c_str()))
-        {
-        continue;
-        }
-      if ( memcheck )
-        {
-        tm_VectorOfStrings::iterator it;
-        bool found = false;
-        for ( it = m_CustomMemCheckIgnore.begin(); 
-          it != m_CustomMemCheckIgnore.end(); ++ it )
-          {
-          if ( *it == testname )
-            {
-            found = true;
-            break;
-            }
-          }
-        if ( found )
-          {
-          if ( m_Verbose )
-            {
-            std::cout << "Ignore memcheck: " << *it << std::endl;
-            }
-          continue;
-          }
-        }
-      else
-        {
-        tm_VectorOfStrings::iterator it;
-        bool found = false;
-        for ( it = m_CustomTestsIgnore.begin(); 
-          it != m_CustomTestsIgnore.end(); ++ it )
-          {
-          if ( *it == testname )
-            {
-            found = true;
-            break;
-            }
-          }
-        if ( found )
-          {
-          if ( m_Verbose )
-            {
-            std::cout << "Ignore test: " << *it << std::endl;
-            }
-          continue;
-          }
-        }
-
-
-      if (this->m_UseIncludeRegExp && !ireg.find(testname.c_str()))
-        {
-        continue;
-        }
-      if (this->m_UseExcludeRegExp &&
-        !this->m_UseExcludeRegExpFirst &&
-        ereg.find(testname.c_str()))
-        {
-        continue;
-        }
-
-      cmCTestTestProperties test;
-      test.m_Name = testname;
-      test.m_Args = args;
-      test.m_Directory = cmSystemTools::GetCurrentWorkingDirectory();
-      testlist->push_back(test);
-      }
-    }
-}
-
-void cmCTest::ProcessDirectory(cmCTest::tm_VectorOfStrings &passed, 
-                             cmCTest::tm_VectorOfStrings &failed,
-                             bool memcheck)
-{
-  std::string current_dir = cmSystemTools::GetCurrentWorkingDirectory();
-  cmsys::RegularExpression dartStuff("(<DartMeasurement.*/DartMeasurement[a-zA-Z]*>)");
-  tm_ListOfTests testlist;
-  this->GetListOfTests(&testlist, memcheck);
-  tm_ListOfTests::size_type tmsize = testlist.size();
-
-  std::ofstream ofs;
-  std::ofstream *olog = 0;
-  if ( !m_ShowOnly && tmsize > 0 && 
-    this->OpenOutputFile("Temporary", 
-      (memcheck?"LastMemCheck.log":"LastTest.log"), ofs) )
-    {
-    olog = &ofs;
-    }
-
-  m_StartTest = this->CurrentTime();
-  double elapsed_time_start = cmSystemTools::GetTime();
-
-  if ( olog )
-    {
-    *olog << "Start testing: " << m_StartTest << std::endl
-      << "----------------------------------------------------------"
-      << std::endl;
-    }
-
-  // expand the test list
-  this->ExpandTestsToRunInformation((int)tmsize);
-  
-  int cnt = 0;
-  tm_ListOfTests::iterator it;
-  std::string last_directory = "";
-  for ( it = testlist.begin(); it != testlist.end(); it ++ )
-    {
-    cnt ++;
-    const std::string& testname = it->m_Name;
-    tm_VectorOfListFileArgs& args = it->m_Args;
-    cmCTestTestResult cres;
-    cres.m_Status = cmCTest::NOT_RUN;
-    cres.m_TestCount = cnt;
-
-    if (!(last_directory == it->m_Directory))
-      {
-      if ( m_Verbose )
-        {
-        std::cerr << "Changing directory into " 
-          << it->m_Directory.c_str() << "\n";
-        }
-      last_directory = it->m_Directory;
-      cmSystemTools::ChangeDirectory(it->m_Directory.c_str());
-      }
-    cres.m_Name = testname;
-    if(m_TestsToRun.size() && 
-       std::find(m_TestsToRun.begin(), m_TestsToRun.end(), cnt) == m_TestsToRun.end())
-      {
-      continue;
-      }
-
-    if ( m_ShowOnly )
-      {
-      std::cerr.width(3);
-      std::cerr << cnt << "/";
-      std::cerr.width(3);
-      std::cerr << tmsize << " Testing ";
-      std::string outname = testname;
-      outname.resize(30, ' ');
-      std::cerr << outname.c_str() << "\n";
-     }
-    else
-      {
-      std::cerr.width(3);
-      std::cerr << cnt << "/";
-      std::cerr.width(3);
-      std::cerr << tmsize << " Testing ";
-      std::string outname = testname;
-      outname.resize(30, ' ');
-      std::cerr << outname.c_str();
-      std::cerr.flush();
-      }
-    
-    //std::cerr << "Testing " << args[0] << " ... ";
-    // find the test executable
-    std::string actualCommand = this->FindTheExecutable(args[1].Value.c_str());
-    std::string testCommand = cmSystemTools::ConvertToOutputPath(actualCommand.c_str());
-    std::string memcheckcommand = "";
-
-    // continue if we did not find the executable
-    if (testCommand == "")
-      {
-      std::cerr << "Unable to find executable: " <<
-        args[1].Value.c_str() << "\n";
-      if ( !m_ShowOnly )
-        {
-        m_TestResults.push_back( cres ); 
-        failed.push_back(testname);
-        continue;
-        }
-      }
-
-    // add the arguments
-    tm_VectorOfListFileArgs::const_iterator j = args.begin();
-    ++j;
-    ++j;
-    std::vector<const char*> arguments;
-    if ( memcheck )
-      {
-      cmCTest::tm_VectorOfStrings::size_type pp;
-      arguments.push_back(m_MemoryTester.c_str());
-      memcheckcommand = m_MemoryTester;
-      for ( pp = 0; pp < m_MemoryTesterOptionsParsed.size(); pp ++ )
-        {
-        arguments.push_back(m_MemoryTesterOptionsParsed[pp].c_str());
-        memcheckcommand += " ";
-        memcheckcommand += cmSystemTools::EscapeSpaces(m_MemoryTesterOptionsParsed[pp].c_str());
-        }
-      }
-    arguments.push_back(actualCommand.c_str());
-    for(;j != args.end(); ++j)
-      {
-      testCommand += " ";
-      testCommand += cmSystemTools::EscapeSpaces(j->Value.c_str());
-      arguments.push_back(j->Value.c_str());
-      }
-    arguments.push_back(0);
-
-    /**
-     * Run an executable command and put the stdout in output.
-     */
-    std::string output;
-    int retVal = 0;
-
-
-    if ( m_Verbose )
-      {
-      std::cout << std::endl << (memcheck?"MemCheck":"Test") << " command: " << testCommand << std::endl;
-      if ( memcheck )
-        {
-        std::cout << "Memory check command: " << memcheckcommand << std::endl;
-        }
-      }
-    if ( olog )
-      {
-      *olog << cnt << "/" << tmsize 
-        << " Test: " << testname.c_str() << std::endl;
-      *olog << "Command: ";
-      tm_VectorOfStrings::size_type ll;
-      for ( ll = 0; ll < arguments.size()-1; ll ++ )
-        {
-        *olog << "\"" << arguments[ll] << "\" ";
-        }
-      *olog 
-        << std::endl 
-        << "Directory: " << it->m_Directory << std::endl 
-        << "\"" << testname.c_str() << "\" start time: " 
-        << this->CurrentTime() << std::endl
-        << "Output:" << std::endl 
-        << "----------------------------------------------------------"
-        << std::endl;
-      }
-    int res = 0;
-    double clock_start, clock_finish;
-    clock_start = cmSystemTools::GetTime();
-
-    if ( !m_ShowOnly )
-      {
-      res = this->RunTest(arguments, &output, &retVal, olog);
-      }
-
-    clock_finish = cmSystemTools::GetTime();
-
-    if ( olog )
-      {
-      double ttime = clock_finish - clock_start;
-      int hours = static_cast<int>(ttime / (60 * 60));
-      int minutes = static_cast<int>(ttime / 60) % 60;
-      int seconds = static_cast<int>(ttime) % 60;
-      char buffer[100];
-      sprintf(buffer, "%02d:%02d:%02d", hours, minutes, seconds);
-      *olog 
-        << "----------------------------------------------------------"
-        << std::endl
-        << "\"" << testname.c_str() << "\" end time: " 
-        << this->CurrentTime() << std::endl
-        << "\"" << testname.c_str() << "\" time elapsed: " 
-        << buffer << std::endl
-        << "----------------------------------------------------------"
-        << std::endl << std::endl;
-      }
-
-    cres.m_ExecutionTime = (double)(clock_finish - clock_start);
-    cres.m_FullCommandLine = testCommand;
-
-    if ( !m_ShowOnly )
-      {
-      if (res == cmsysProcess_State_Exited && retVal == 0)
-        {
-        std::cerr <<   "   Passed\n";
-        passed.push_back(testname);
-        cres.m_Status = cmCTest::COMPLETED;
-        }
-      else
-        {
-        cres.m_Status = cmCTest::FAILED;
-        if ( res == cmsysProcess_State_Expired )
-          {
-          std::cerr << "***Timeout\n";
-          cres.m_Status = cmCTest::TIMEOUT;
-          }
-        else if ( res == cmsysProcess_State_Exception )
-          {
-          std::cerr << "***Exception: ";
-          switch ( retVal )
-            {
-          case cmsysProcess_Exception_Fault:
-            std::cerr << "SegFault";
-            cres.m_Status = cmCTest::SEGFAULT;
-            break;
-          case cmsysProcess_Exception_Illegal:
-            std::cerr << "Illegal";
-            cres.m_Status = cmCTest::ILLEGAL;
-            break;
-          case cmsysProcess_Exception_Interrupt:
-            std::cerr << "Interrupt";
-            cres.m_Status = cmCTest::INTERRUPT;
-            break;
-          case cmsysProcess_Exception_Numerical:
-            std::cerr << "Numerical";
-            cres.m_Status = cmCTest::NUMERICAL;
-            break;
-          default:
-            std::cerr << "Other";
-            cres.m_Status = cmCTest::OTHER_FAULT;
-            }
-           std::cerr << "\n";
-          }
-        else if ( res == cmsysProcess_State_Error )
-          {
-          std::cerr << "***Bad command " << res << "\n";
-          cres.m_Status = cmCTest::BAD_COMMAND;
-          }
-        else
-          {
-          std::cerr << "***Failed\n";
-          }
-        failed.push_back(testname);
-        }
-      if (output != "")
-        {
-        if (dartStuff.find(output.c_str()))
-          {
-          std::string dartString = dartStuff.match(1);
-          cmSystemTools::ReplaceString(output, dartString.c_str(),"");
-          cres.m_RegressionImages = this->GenerateRegressionImages(dartString);
-          }
-        }
-      }
-    cres.m_Output = output;
-    cres.m_ReturnValue = retVal;
-    std::string nwd = it->m_Directory;
-    if ( nwd.size() > m_ToplevelPath.size() )
-      {
-      nwd = "." + nwd.substr(m_ToplevelPath.size(), nwd.npos);
-      }
-    cmSystemTools::ReplaceString(nwd, "\\", "/");
-    cres.m_Path = nwd;
-    cres.m_CompletionStatus = "Completed";
-    m_TestResults.push_back( cres );
-    }
-
-  m_EndTest = this->CurrentTime();
-  m_ElapsedTestingTime = cmSystemTools::GetTime() - elapsed_time_start;
-  if ( olog )
-    {
-    *olog << "End testing: " << m_EndTest << std::endl;
-    }
-  cmSystemTools::ChangeDirectory(current_dir.c_str());
-}
-
-bool cmCTest::InitializeMemoryChecking()
-{
-  // Setup the command
-  if ( cmSystemTools::FileExists(m_DartConfiguration["MemoryCheckCommand"].c_str()) )
-    {
-    m_MemoryTester 
-      = cmSystemTools::ConvertToOutputPath(m_DartConfiguration["MemoryCheckCommand"].c_str());
-    }
-  else if ( cmSystemTools::FileExists(m_DartConfiguration["PurifyCommand"].c_str()) )
-    {
-    m_MemoryTester 
-      = cmSystemTools::ConvertToOutputPath(m_DartConfiguration["PurifyCommand"].c_str());
-    }
-  else if ( cmSystemTools::FileExists(m_DartConfiguration["ValgrindCommand"].c_str()) )
-    {
-    m_MemoryTester 
-      = cmSystemTools::ConvertToOutputPath(m_DartConfiguration["ValgrindCommand"].c_str());
-    }
-  else
-    {
-    std::cerr << "Memory checker (MemoryCheckCommand) not set, or cannot find the specified program." 
-      << std::endl;
-    return false;
-    }
-
-  if ( m_MemoryTester[0] == '\"' && m_MemoryTester[m_MemoryTester.size()-1] == '\"' )
-    {
-    m_MemoryTester = m_MemoryTester.substr(1, m_MemoryTester.size()-2);
-    }
-
-  // Setup the options
-  if ( m_DartConfiguration["MemoryCheckCommandOptions"].size() )
-    {
-    m_MemoryTesterOptions = m_DartConfiguration["MemoryCheckCommandOptions"];
-    }
-  else if ( m_DartConfiguration["ValgrindCommandOptions"].size() )
-    {
-    m_MemoryTesterOptions = m_DartConfiguration["ValgrindCommandOptions"];
-    }
-
-  m_MemoryTesterOutputFile = m_ToplevelPath + "/Testing/Temporary/MemoryChecker.log";
-  m_MemoryTesterOutputFile = cmSystemTools::EscapeSpaces(m_MemoryTesterOutputFile.c_str());
-
-  if ( m_MemoryTester.find("valgrind") != std::string::npos )
-    {
-    m_MemoryTesterStyle = cmCTest::VALGRIND;
-    if ( !m_MemoryTesterOptions.size() )
-      {
-      m_MemoryTesterOptions = "-q --skin=memcheck --leak-check=yes --show-reachable=yes --workaround-gcc296-bugs=yes --num-callers=100";
-      }
-    if ( m_DartConfiguration["MemoryCheckSuppressionFile"].size() )
-      {
-      if ( !cmSystemTools::FileExists(m_DartConfiguration["MemoryCheckSuppressionFile"].c_str()) )
-        {
-        std::cerr << "Cannot find memory checker suppression file: " 
-          << m_DartConfiguration["MemoryCheckSuppressionFile"].c_str() << std::endl;
-        return false;
-        }
-      m_MemoryTesterOptions += " --suppressions=" + cmSystemTools::EscapeSpaces(m_DartConfiguration["MemoryCheckSuppressionFile"].c_str()) + "";
-      }
-    }
-  else if ( m_MemoryTester.find("purify") != std::string::npos )
-    {
-    m_MemoryTesterStyle = cmCTest::PURIFY;
-#ifdef _WIN32
-    m_MemoryTesterOptions += " /SAVETEXTDATA=" + m_MemoryTesterOutputFile;
-#else
-    m_MemoryTesterOptions += " -log-file=" + m_MemoryTesterOutputFile;
-#endif
-    }
-  else if ( m_MemoryTester.find("boundschecker") != std::string::npos )
-    {
-    m_MemoryTesterStyle = cmCTest::BOUNDS_CHECKER;
-    std::cerr << "Bounds checker not yet implemented" << std::endl;
-    return false;
-    }
-  else
-    {
-    std::cerr << "Do not understand memory checker: " << m_MemoryTester.c_str() << std::endl;
-    return false;
-    }
-
-  m_MemoryTesterOptionsParsed = cmSystemTools::ParseArguments(m_MemoryTesterOptions.c_str());
-  cmCTest::tm_VectorOfStrings::size_type cc;
-  for ( cc = 0; cmCTestMemCheckResultStrings[cc]; cc ++ )
-    {
-    m_MemoryTesterGlobalResults[cc] = 0;
-    }
-  return true;
-}
-
-int cmCTest::TestDirectory(bool memcheck)
-{
-  m_TestResults.clear();
-  std::cout << (memcheck ? "Memory check" : "Test") << " project" << std::endl;
-  if ( memcheck )
-    {
-    if ( !this->InitializeMemoryChecking() )
-      {
-      return 1;
-      }
-    }
-
-  if ( memcheck )
-    {
-    if ( !this->ExecuteCommands(m_CustomPreMemCheck) )
-      {
-      std::cerr << "Problem executing pre-memcheck command(s)." << std::endl;
-      return 1;
-      }
-    }
-  else
-    {
-    if ( !this->ExecuteCommands(m_CustomPreTest) )
-      {
-      std::cerr << "Problem executing pre-test command(s)." << std::endl;
-      return 1;
-      }
-    }
-
-  cmCTest::tm_VectorOfStrings passed;
-  cmCTest::tm_VectorOfStrings failed;
-  int total;
-
-  this->ProcessDirectory(passed, failed, memcheck);
-
-  total = int(passed.size()) + int(failed.size());
-
-  if (total == 0)
-    {
-    if ( !m_ShowOnly )
-      {
-      std::cerr << "No tests were found!!!\n";
-      }
-    }
-  else
-    {
-    if (m_Verbose && passed.size() && 
-      (m_UseIncludeRegExp || m_UseExcludeRegExp)) 
-      {
-      std::cerr << "\nThe following tests passed:\n";
-      for(cmCTest::tm_VectorOfStrings::iterator j = passed.begin();
-        j != passed.end(); ++j)
-        {   
-        std::cerr << "\t" << *j << "\n";
-        }
-      }
-
-    float percent = float(passed.size()) * 100.0f / total;
-    if ( failed.size() > 0 &&  percent > 99)
-      {
-      percent = 99;
-      }
-    fprintf(stderr,"\n%.0f%% tests passed, %i tests failed out of %i\n",
-      percent, int(failed.size()), total);
-
-    if (failed.size()) 
-      {
-      std::ofstream ofs;
-
-      std::cerr << "\nThe following tests FAILED:\n";
-      this->OpenOutputFile("Temporary", "LastTestsFailed.log", ofs);
-
-      std::vector<cmCTest::cmCTestTestResult>::iterator ftit;
-      for(ftit = m_TestResults.begin();
-        ftit != m_TestResults.end(); ++ftit)
-        {
-        if ( ftit->m_Status != cmCTest::COMPLETED )
-          {
-          ofs << ftit->m_TestCount << ":" << ftit->m_Name << std::endl;
-          fprintf(stderr, "\t%3d - %s (%s)\n", ftit->m_TestCount, ftit->m_Name.c_str(),
-            this->GetTestStatus(ftit->m_Status));
-          }
-        }
-
-      }
-    }
-
-  if ( m_DartMode )
-    {
-    std::ofstream xmlfile;
-    if( !this->OpenOutputFile(m_CurrentTag, 
-        (memcheck ? (m_CompatibilityMode?"Purify.xml":"DynamicAnalysis.xml") : "Test.xml"), xmlfile) )
-      {
-      std::cerr << "Cannot create " << (memcheck ? "memory check" : "testing")
-        << " XML file" << std::endl;
-      return 1;
-      }
-    if ( memcheck )
-      {
-      this->GenerateDartMemCheckOutput(xmlfile);
-      }
-    else
-      {
-      this->GenerateDartTestOutput(xmlfile);
-      }
-    }
-
-  if ( memcheck )
-    {
-    if ( !this->ExecuteCommands(m_CustomPostMemCheck) )
-      {
-      std::cerr << "Problem executing post-memcheck command(s)." << std::endl;
-      return 1;
-      }
-    }
-  else
-    {
-    if ( !this->ExecuteCommands(m_CustomPostTest) )
-      {
-      std::cerr << "Problem executing post-test command(s)." << std::endl;
-      return 1;
-      }
-    }
-
-  return int(failed.size());
-}
-
-int cmCTest::SubmitResults()
-{
-  std::ofstream ofs;
-  this->OpenOutputFile("Temporary", "LastSubmit.log", ofs);
-
-  cmCTest::tm_VectorOfStrings files;
-  std::string prefix = this->GetSubmitResultsPrefix();
-  // TODO:
-  // Check if test is enabled
-  if ( this->CTestFileExists("Update.xml") )
-    {
-    files.push_back("Update.xml");
-    }
-  if ( this->CTestFileExists("Configure.xml") )
-    {
-    files.push_back("Configure.xml");
-    }
-  if ( this->CTestFileExists("Build.xml") )
-    {
-    files.push_back("Build.xml");
-    }
-  if ( this->CTestFileExists("Test.xml") )
-    {
-    files.push_back("Test.xml");
-    }
-  if ( this->CTestFileExists("Coverage.xml") )
-    {
-    files.push_back("Coverage.xml");
-    cmCTest::tm_VectorOfStrings gfiles;
-    std::string gpath = m_ToplevelPath + "/Testing/" + m_CurrentTag;
-    std::string::size_type glen = gpath.size() + 1;
-    gpath = gpath + "/CoverageLog*";
-    //std::cout << "Globbing for: " << gpath.c_str() << std::endl;
-    if ( cmSystemTools::SimpleGlob(gpath, gfiles, 1) )
-      {
-      size_t cc;
-      for ( cc = 0; cc < gfiles.size(); cc ++ )
-        {
-        gfiles[cc] = gfiles[cc].substr(glen);
-        //std::cout << "Glob file: " << gfiles[cc].c_str() << std::endl;
-        files.push_back(gfiles[cc]);
-        }
-      }
-    else
-      {
-      std::cerr << "Problem globbing" << std::endl;
-      }
-    }
-  if ( this->CTestFileExists("DynamicAnalysis.xml") )
-    {
-    files.push_back("DynamicAnalysis.xml");
-    }
-  if ( this->CTestFileExists("Purify.xml") )
-    {
-    files.push_back("Purify.xml");
-    }
-  if ( this->CTestFileExists("Notes.xml") )
-    {
-    files.push_back("Notes.xml");
-    }
-
-  if ( ofs )
-    {
-    ofs << "Upload files:" << std::endl;
-    int cnt = 0;
-    cmCTest::tm_VectorOfStrings::iterator it;
-    for ( it = files.begin(); it != files.end(); ++ it )
-      {
-      ofs << cnt << "\t" << it->c_str() << std::endl;
-      cnt ++;
-      }
-    }
-  std::cout << "Submit files (using " << m_DartConfiguration["DropMethod"] << ")"
-    << std::endl;
-  cmCTestSubmit submit;
-  submit.SetVerbose(m_Verbose);
-  submit.SetLogFile(&ofs);
-  if ( m_DartConfiguration["DropMethod"] == "" ||
-    m_DartConfiguration["DropMethod"] ==  "ftp" )
-    {
-    ofs << "Using drop method: FTP" << std::endl;
-    std::cout << "  Using FTP submit method" << std::endl;
-    std::string url = "ftp://";
-    url += cmCTest::MakeURLSafe(m_DartConfiguration["DropSiteUser"]) + ":" + 
-      cmCTest::MakeURLSafe(m_DartConfiguration["DropSitePassword"]) + "@" + 
-      m_DartConfiguration["DropSite"] + 
-      cmCTest::MakeURLSafe(m_DartConfiguration["DropLocation"]);
-    if ( !submit.SubmitUsingFTP(m_ToplevelPath+"/Testing/"+m_CurrentTag, 
-        files, prefix, url) )
-      {
-      std::cerr << "  Problems when submitting via FTP" << std::endl;
-      ofs << "  Problems when submitting via FTP" << std::endl;
-      return 0;
-      }
-    if ( !submit.TriggerUsingHTTP(files, prefix, m_DartConfiguration["TriggerSite"]) )
-      {
-      std::cerr << "  Problems when triggering via HTTP" << std::endl;
-      ofs << "  Problems when triggering via HTTP" << std::endl;
-      return 0;
-      }
-    std::cout << "  Submission successfull" << std::endl;
-    ofs << "  Submission succesfull" << std::endl;
-    return 1;
-    }
-  else if ( m_DartConfiguration["DropMethod"] == "http" )
-    {
-    ofs << "Using drop method: HTTP" << std::endl;
-    std::cout << "  Using HTTP submit method" << std::endl;
-    std::string url = "http://";
-    if ( m_DartConfiguration["DropSiteUser"].size() > 0 )
-      {
-      url += m_DartConfiguration["DropSiteUser"];
-      if ( m_DartConfiguration["DropSitePassword"].size() > 0 )
-        {
-        url += ":" + m_DartConfiguration["DropSitePassword"];
-        }
-      url += "@";
-      }
-    url += m_DartConfiguration["DropSite"] + m_DartConfiguration["DropLocation"];
-    if ( !submit.SubmitUsingHTTP(m_ToplevelPath+"/Testing/"+m_CurrentTag, files, prefix, url) )
-      {
-      std::cerr << "  Problems when submitting via HTTP" << std::endl;
-      ofs << "  Problems when submitting via HTTP" << std::endl;
-      return 0;
-      }
-    if ( !submit.TriggerUsingHTTP(files, prefix, m_DartConfiguration["TriggerSite"]) )
+    if ( !submit.TriggerUsingHTTP(files, prefix, m_DartConfiguration["TriggerSite"]) )
       {
       std::cerr << "  Problems when triggering via HTTP" << std::endl;
       ofs << "  Problems when triggering via HTTP" << std::endl;
@@ -1961,295 +648,45 @@ int cmCTest::SubmitResults()
     }
   else
     {
-    std::string url;
-    if ( m_DartConfiguration["DropSiteUser"].size() > 0 )
-      {
-      url += m_DartConfiguration["DropSiteUser"] + "@";
-      }
-    url += m_DartConfiguration["DropSite"] + ":" + m_DartConfiguration["DropLocation"];
-    
-    if ( !submit.SubmitUsingSCP(m_DartConfiguration["ScpCommand"],
-        m_ToplevelPath+"/Testing/"+m_CurrentTag, files, prefix, url) )
-      {
-      std::cerr << "  Problems when submitting via SCP" << std::endl;
-      ofs << "  Problems when submitting via SCP" << std::endl;
-      return 0;
-      }
-    std::cout << "  Submission successfull" << std::endl;
-    ofs << "  Submission succesfull" << std::endl;
-    }
-
-  return 0;
-}
-
-bool cmCTest::CTestFileExists(const std::string& filename)
-{
-  std::string testingDir = m_ToplevelPath + "/Testing/" + m_CurrentTag + "/" +
-    filename;
-  return cmSystemTools::FileExists(testingDir.c_str());
-}
-
-std::string cmCTest::GetSubmitResultsPrefix()
-{
-  std::string name = m_DartConfiguration["Site"] +
-    "___" + m_DartConfiguration["BuildName"] +
-    "___" + m_CurrentTag + "-" +
-    this->GetTestModelString() + "___XML___";
-  return name;
-}
-
-void cmCTest::GenerateDartMemCheckOutput(std::ostream& os)
-{
-  if ( !m_DartMode )
-    {
-    return;
-    }
-
-  this->StartXML(os);
-  if ( m_CompatibilityMode )
-    {
-    os << "<Purify>" << std::endl;
-    }
-  else
-    {
-    os << "<DynamicAnalysis Checker=\"";
-    switch ( m_MemoryTesterStyle )
-      {
-    case cmCTest::VALGRIND:
-      os << "Valgrind";
-      break;
-    case cmCTest::PURIFY:
-      os << "Purify";
-      break;
-    case cmCTest::BOUNDS_CHECKER:
-      os << "BoundsChecker";
-      break;
-    default:
-      os << "Unknown";
-      }
-    os << "\">" << std::endl;
-    }
-  os << "\t<StartDateTime>" << m_StartTest << "</StartDateTime>\n"
-    << "\t<TestList>\n";
-  tm_TestResultsVector::size_type cc;
-  for ( cc = 0; cc < m_TestResults.size(); cc ++ )
-    {
-    cmCTestTestResult *result = &m_TestResults[cc];
-    os << "\t\t<Test>" << this->MakeXMLSafe(result->m_Path) 
-      << "/" << this->MakeXMLSafe(result->m_Name)
-      << "</Test>" << std::endl;
-    }
-  os << "\t</TestList>\n";
-  std::cout << "-- Processing memory checking output: ";
-  unsigned int total = m_TestResults.size();
-  unsigned int step = total / 10;
-  unsigned int current = 0;
-  for ( cc = 0; cc < m_TestResults.size(); cc ++ )
-    {
-    cmCTestTestResult *result = &m_TestResults[cc];
-    std::string memcheckstr;
-    int memcheckresults[cmCTest::NO_MEMORY_FAULT];
-    int kk;
-    bool res = this->ProcessMemCheckOutput(result->m_Output, memcheckstr, memcheckresults);
-    if ( res && result->m_Status == cmCTest::COMPLETED )
-      {
-      continue;
-      }
-    os << "\t<Test Status=\"";
-    if ( result->m_Status == cmCTest::COMPLETED )
-      {
-      os << "passed";
-      }
-    else if ( result->m_Status == cmCTest::NOT_RUN )
-      {
-      os << "notrun";
-      }
-    else
-      {
-      os << "failed";
-      }
-    os << "\">\n"
-      << "\t\t<Name>" << this->MakeXMLSafe(result->m_Name) << "</Name>\n"
-      << "\t\t<Path>" << this->MakeXMLSafe(result->m_Path) << "</Path>\n"
-      << "\t\t<FullName>" << this->MakeXMLSafe(result->m_Path) 
-      << "/" << this->MakeXMLSafe(result->m_Name) << "</FullName>\n"
-      << "\t\t<FullCommandLine>" 
-      << this->MakeXMLSafe(result->m_FullCommandLine) 
-      << "</FullCommandLine>\n"
-      << "\t\t<Results>" << std::endl;
-    if ( m_CompatibilityMode )
-      {
-      for ( kk = 0; cmCTestMemCheckResultStrings[kk]; kk ++ )
-        {
-        os << "\t\t\t<" << cmCTestMemCheckResultStrings[kk] << ">"
-          << memcheckresults[kk] 
-          << "</" << cmCTestMemCheckResultStrings[kk] << ">" << std::endl;
-        m_MemoryTesterGlobalResults[kk] += memcheckresults[kk];
-        }
-      }
-    else
-      {
-      for ( kk = 0; cmCTestMemCheckResultLongStrings[kk]; kk ++ )
-        {
-        if ( memcheckresults[kk] )
-          {
-          os << "\t\t\t<Defect type=\"" << cmCTestMemCheckResultLongStrings[kk] << "\">"
-            << memcheckresults[kk] 
-            << "</Defect>" << std::endl;
-          }
-        m_MemoryTesterGlobalResults[kk] += memcheckresults[kk];
-        }
-      }
-    os 
-      << "\t\t</Results>\n"
-      << "\t<Log>\n" << memcheckstr << std::endl
-      << "\t</Log>\n"
-      << "\t</Test>" << std::endl;
-    if ( current < cc )
-      {
-      std::cout << "#";
-      std::cout.flush();
-      current += step;
-      }
-    }
-  std::cout << std::endl;
-  std::cerr << "Memory checking results:" << std::endl;
-  os << "\t<DefectList>" << std::endl;
-  for ( cc = 0; cmCTestMemCheckResultStrings[cc]; cc ++ )
-    {
-    if ( m_MemoryTesterGlobalResults[cc] )
-      {
-      std::cerr.width(35);
-      std::cerr << cmCTestMemCheckResultLongStrings[cc] << " - " 
-        << m_MemoryTesterGlobalResults[cc] << std::endl;
-      if ( !m_CompatibilityMode )
-        {
-        os << "\t\t<Defect Type=\"" << cmCTestMemCheckResultLongStrings[cc] << "\"/>" << std::endl;
-        }
-      }
-    }
-  os << "\t</DefectList>" << std::endl;
-
-  os << "\t<EndDateTime>" << m_EndTest << "</EndDateTime>" << std::endl;
-  os << "<ElapsedMinutes>" 
-     << static_cast<int>(m_ElapsedTestingTime/6)/10.0 
-     << "</ElapsedMinutes>\n";
-  
-  if ( m_CompatibilityMode )
-    {
-    os << "</Purify>" << std::endl;
-    }
-  else
-    {
-    os << "</DynamicAnalysis>" << std::endl;
-    }
-  this->EndXML(os);
-
-
-}
-
-void cmCTest::GenerateDartTestOutput(std::ostream& os)
-{
-  if ( !m_DartMode )
-    {
-    return;
-    }
-
-  this->StartXML(os);
-  os << "<Testing>\n"
-    << "\t<StartDateTime>" << m_StartTest << "</StartDateTime>\n"
-    << "\t<TestList>\n";
-  tm_TestResultsVector::size_type cc;
-  for ( cc = 0; cc < m_TestResults.size(); cc ++ )
-    {
-    cmCTestTestResult *result = &m_TestResults[cc];
-    os << "\t\t<Test>" << this->MakeXMLSafe(result->m_Path) 
-      << "/" << this->MakeXMLSafe(result->m_Name)
-      << "</Test>" << std::endl;
-    }
-  os << "\t</TestList>\n";
-  for ( cc = 0; cc < m_TestResults.size(); cc ++ )
-    {
-    cmCTestTestResult *result = &m_TestResults[cc];
-    os << "\t<Test Status=\"";
-    if ( result->m_Status == cmCTest::COMPLETED )
-      {
-      os << "passed";
-      }
-    else if ( result->m_Status == cmCTest::NOT_RUN )
-      {
-      os << "notrun";
-      }
-    else
-      {
-      os << "failed";
-      }
-    os << "\">\n"
-      << "\t\t<Name>" << this->MakeXMLSafe(result->m_Name) << "</Name>\n"
-      << "\t\t<Path>" << this->MakeXMLSafe(result->m_Path) << "</Path>\n"
-      << "\t\t<FullName>" << this->MakeXMLSafe(result->m_Path) 
-      << "/" << this->MakeXMLSafe(result->m_Name) << "</FullName>\n"
-      << "\t\t<FullCommandLine>" 
-      << this->MakeXMLSafe(result->m_FullCommandLine) 
-      << "</FullCommandLine>\n"
-      << "\t\t<Results>" << std::endl;
-    if ( result->m_Status != cmCTest::NOT_RUN )
-      {
-      if ( result->m_Status != cmCTest::COMPLETED || result->m_ReturnValue )
-        {
-        os << "\t\t\t<NamedMeasurement type=\"text/string\" name=\"Exit Code\"><Value>"
-          << this->GetTestStatus(result->m_Status) << "</Value></NamedMeasurement>\n"
-          << "\t\t\t<NamedMeasurement type=\"text/string\" name=\"Exit Value\"><Value>"
-          << result->m_ReturnValue << "</Value></NamedMeasurement>" << std::endl;
-        }
-      os << result->m_RegressionImages;
-      os << "\t\t\t<NamedMeasurement type=\"numeric/double\" "
-        << "name=\"Execution Time\"><Value>"
-        << result->m_ExecutionTime << "</Value></NamedMeasurement>\n";
-      os 
-        << "\t\t\t<NamedMeasurement type=\"text/string\" "
-        << "name=\"Completion Status\"><Value>"
-        << result->m_CompletionStatus << "</Value></NamedMeasurement>\n";
-      }
-    os 
-      << "\t\t\t<Measurement>\n"
-      << "\t\t\t\t<Value>";
-    size_t truncate = result->m_Output.size();
-    if ( result->m_Status == cmCTest::COMPLETED )
-      {
-      if ( result->m_Output.size() > m_MaximumPassedTestResultSize )
-        {
-        truncate = m_MaximumPassedTestResultSize;
-        }
-      }
-    else
+    std::string url;
+    if ( m_DartConfiguration["DropSiteUser"].size() > 0 )
       {
-      if ( result->m_Output.size() > m_MaximumFailedTestResultSize )
-        {
-        truncate = m_MaximumFailedTestResultSize;
-        }
+      url += m_DartConfiguration["DropSiteUser"] + "@";
       }
-    os << this->MakeXMLSafe(result->m_Output.substr(0, truncate));
-    if ( truncate < result->m_Output.size() )
+    url += m_DartConfiguration["DropSite"] + ":" + m_DartConfiguration["DropLocation"];
+    
+    if ( !submit.SubmitUsingSCP(m_DartConfiguration["ScpCommand"],
+        m_ToplevelPath+"/Testing/"+m_CurrentTag, files, prefix, url) )
       {
-      os << "...\n\nThe output was stirpped because it excedes maximum allowed size: "
-        << truncate << std::endl;
+      std::cerr << "  Problems when submitting via SCP" << std::endl;
+      ofs << "  Problems when submitting via SCP" << std::endl;
+      return 0;
       }
-    os
-      << "</Value>\n"
-      << "\t\t\t</Measurement>\n"
-      << "\t\t</Results>\n"
-      << "\t</Test>" << std::endl;
+    std::cout << "  Submission successfull" << std::endl;
+    ofs << "  Submission succesfull" << std::endl;
     }
 
-  os << "\t<EndDateTime>" << m_EndTest << "</EndDateTime>\n"
-     << "<ElapsedMinutes>" 
-     << static_cast<int>(m_ElapsedTestingTime/6)/10.0
-     << "</ElapsedMinutes>"
-    << "</Testing>" << std::endl;
-  this->EndXML(os);
+  return 0;
+}
+
+bool cmCTest::CTestFileExists(const std::string& filename)
+{
+  std::string testingDir = m_ToplevelPath + "/Testing/" + m_CurrentTag + "/" +
+    filename;
+  return cmSystemTools::FileExists(testingDir.c_str());
+}
+
+std::string cmCTest::GetSubmitResultsPrefix()
+{
+  std::string name = m_DartConfiguration["Site"] +
+    "___" + m_DartConfiguration["BuildName"] +
+    "___" + m_CurrentTag + "-" +
+    this->GetTestModelString() + "___XML___";
+  return name;
 }
 
+
+
 int cmCTest::ProcessTests()
 {
   int res = 0;
@@ -2295,20 +732,20 @@ int cmCTest::ProcessTests()
   if ( m_Tests[TEST_TEST] || m_Tests[ALL_TEST] || notest )
     {
     this->UpdateCTestConfiguration();
-    if (this->TestDirectory(false))
+    if (this->TestHandler->TestDirectory(this,false))
       {
       res |= cmCTest::TEST_ERRORS;
       }
     }
   if ( m_Tests[COVERAGE_TEST] || m_Tests[ALL_TEST] )
     {
     this->UpdateCTestConfiguration();
-    this->CoverageDirectory();
+    this->CoverageHandler->CoverageDirectory(this);
     }
   if ( m_Tests[MEMCHECK_TEST] || m_Tests[ALL_TEST] )
     {
     this->UpdateCTestConfiguration();
-    if (this->TestDirectory(true))
+    if (this->TestHandler->TestDirectory(this,true))
       {
       res |= cmCTest::MEMORY_ERRORS;
       }
@@ -2384,164 +821,6 @@ int cmCTest::GetTestModelFromString(const char* str)
   return cmCTest::EXPERIMENTAL;
 }
 
-#define SPACE_REGEX "[ \t\r\n]"
-
-std::string cmCTest::GenerateRegressionImages(const std::string& xml)
-{
-  cmsys::RegularExpression twoattributes(
-    "<DartMeasurement" 
-    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
-    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
-    SPACE_REGEX "*>([^<]*)</DartMeasurement>");
-  cmsys::RegularExpression threeattributes(
-    "<DartMeasurement" 
-    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
-    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
-    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
-    SPACE_REGEX "*>([^<]*)</DartMeasurement>");
-  cmsys::RegularExpression fourattributes(
-    "<DartMeasurement" 
-    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
-    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
-    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
-    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
-    SPACE_REGEX "*>([^<]*)</DartMeasurement>");
-  cmsys::RegularExpression measurementfile(
-    "<DartMeasurementFile" 
-    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
-    SPACE_REGEX "*(name|type|encoding|compression)=\"([^\"]*)\"" 
-    SPACE_REGEX "*>([^<]*)</DartMeasurementFile>");
-
-  cmOStringStream ostr;
-  bool done = false;
-  std::string cxml = xml;
-  while ( ! done )
-    {
-    if ( twoattributes.find(cxml) )
-      {
-      ostr
-        << "\t\t\t<NamedMeasurement" 
-        << " " << twoattributes.match(1) << "=\"" << twoattributes.match(2) << "\""
-        << " " << twoattributes.match(3) << "=\"" << twoattributes.match(4) << "\""
-        << "><Value>" << twoattributes.match(5) 
-        << "</Value></NamedMeasurement>" 
-        << std::endl;
-      cxml.erase(twoattributes.start(), twoattributes.end() - twoattributes.start());
-      }
-    else if ( threeattributes.find(cxml) )
-      {
-      ostr
-        << "\t\t\t<NamedMeasurement" 
-        << " " << threeattributes.match(1) << "=\"" << threeattributes.match(2) << "\""
-        << " " << threeattributes.match(3) << "=\"" << threeattributes.match(4) << "\""
-        << " " << threeattributes.match(5) << "=\"" << threeattributes.match(6) << "\""
-        << "><Value>" << threeattributes.match(7) 
-        << "</Value></NamedMeasurement>" 
-        << std::endl;
-      cxml.erase(threeattributes.start(), threeattributes.end() - threeattributes.start());
-      }
-    else if ( fourattributes.find(cxml) )
-      {
-      ostr
-        << "\t\t\t<NamedMeasurement" 
-        << " " << fourattributes.match(1) << "=\"" << fourattributes.match(2) << "\""
-        << " " << fourattributes.match(3) << "=\"" << fourattributes.match(4) << "\""
-        << " " << fourattributes.match(5) << "=\"" << fourattributes.match(6) << "\""
-        << " " << fourattributes.match(7) << "=\"" << fourattributes.match(8) << "\""
-        << "><Value>" << fourattributes.match(9) 
-        << "</Value></NamedMeasurement>" 
-        << std::endl;
-      cxml.erase(fourattributes.start(), fourattributes.end() - fourattributes.start());
-      }
-    else if ( measurementfile.find(cxml) )
-      {
-      const std::string& filename = ::CleanString(measurementfile.match(5));
-      if ( cmSystemTools::FileExists(filename.c_str()) )
-        {
-        long len = cmSystemTools::FileLength(filename.c_str());
-        if ( len == 0 )
-          {
-          std::string k1 = measurementfile.match(1);
-          std::string v1 = measurementfile.match(2);
-          std::string k2 = measurementfile.match(3);
-          std::string v2 = measurementfile.match(4);
-          if ( cmSystemTools::LowerCase(k1) == "type" )
-            {
-            v1 = "text/string";
-            }
-          if ( cmSystemTools::LowerCase(k2) == "type" )
-            {
-            v2 = "text/string";
-            }          
-          
-          ostr
-            << "\t\t\t<NamedMeasurement" 
-            << " " << k1 << "=\"" << v1 << "\""
-            << " " << k2 << "=\"" << v2 << "\""
-            << " encoding=\"none\""
-            << "><Value>Image " << filename.c_str() 
-            << " is empty</Value></NamedMeasurement>";
-          }
-        else
-          {
-          std::ifstream ifs(filename.c_str(), std::ios::in 
-#ifdef _WIN32
-                            | std::ios::binary
-#endif
-            );
-          unsigned char *file_buffer = new unsigned char [ len + 1 ];
-          ifs.read(reinterpret_cast<char*>(file_buffer), len);
-          unsigned char *encoded_buffer = new unsigned char [ static_cast<int>(len * 1.5 + 5) ];
-          
-          unsigned long rlen = cmsysBase64_Encode(file_buffer, len, encoded_buffer, 1);
-          unsigned long cc;
-          
-          ostr
-            << "\t\t\t<NamedMeasurement" 
-          << " " << measurementfile.match(1) << "=\"" << measurementfile.match(2) << "\""
-            << " " << measurementfile.match(3) << "=\"" << measurementfile.match(4) << "\""
-            << " encoding=\"base64\""
-            << ">" << std::endl << "\t\t\t\t<Value>";
-          for ( cc = 0; cc < rlen; cc ++ )
-            {
-            ostr << encoded_buffer[cc];
-            if ( cc % 60 == 0 && cc )
-              {
-              ostr << std::endl;
-              }
-            }
-          ostr
-            << "</Value>" << std::endl << "\t\t\t</NamedMeasurement>" 
-            << std::endl;
-          delete [] file_buffer;
-          delete [] encoded_buffer;
-          }
-        }
-      else
-        {
-        int idx = 4;
-        if ( measurementfile.match(1) == "name" )
-          {
-          idx = 2;
-          }
-        ostr
-          << "\t\t\t<NamedMeasurement" 
-          << " name=\"" << measurementfile.match(idx) << "\""
-          << " text=\"text/string\""
-          << "><Value>File " << filename.c_str() << " not found</Value></NamedMeasurement>" 
-          << std::endl;
-        std::cout << "File \"" << filename.c_str() << "\" not found." << std::endl;
-        }
-      cxml.erase(measurementfile.start(), measurementfile.end() - measurementfile.start());
-      }
-    else
-      {
-      done = true;
-      }
-    }
-  return ostr.str();
-}
-
 int cmCTest::RunMakeCommand(const char* command, std::string* output,
   int* retVal, const char* dir, bool verbose, int timeout, std::ofstream& ofs)
 {
@@ -2653,10 +932,12 @@ int cmCTest::RunMakeCommand(const char* command, std::string* output,
   return result;
 }
 
-int cmCTest::RunTest(std::vector<const char*> argv, std::string* output, int *retVal,
-  std::ostream* log)
+int cmCTest::RunTest(std::vector<const char*> argv, 
+                     std::string* output, int *retVal,
+                     std::ostream* log)
 {
-  if(cmSystemTools::SameFile(argv[0], m_CTestSelf.c_str()) && !m_ForceNewCTestProcess)
+  if(cmSystemTools::SameFile(argv[0], m_CTestSelf.c_str()) && 
+     !m_ForceNewCTestProcess)
     {
     cmCTest inst;
     inst.m_ConfigType = m_ConfigType;
@@ -2769,28 +1050,6 @@ int cmCTest::RunTest(std::vector<const char*> argv, std::string* output, int *re
   return result;
 }
 
-const char* cmCTest::GetTestStatus(int status)
-{
-  static const char statuses[][100] = {
-    "Not Run",
-    "Timeout",
-    "SEGFAULT",
-    "ILLEGAL",
-    "INTERRUPT",
-    "NUMERICAL",
-    "OTHER_FAULT",
-    "Failed",
-    "BAD_COMMAND",
-    "Completed"
-  };
-
-  if ( status < cmCTest::NOT_RUN || status > cmCTest::COMPLETED )
-    {
-    return "No Status";
-    }
-  return statuses[status];
-}
-
 void cmCTest::StartXML(std::ostream& ostr)
 {
   ostr << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
@@ -2806,180 +1065,6 @@ void cmCTest::EndXML(std::ostream& ostr)
   ostr << "</Site>" << std::endl;
 }
 
-bool cmCTest::ProcessMemCheckPurifyOutput(const std::string&, std::string& log, 
-  int* results)
-{
-  if ( !cmSystemTools::FileExists(m_MemoryTesterOutputFile.c_str()) )
-    {
-    log = "Cannot find Purify output file: " + m_MemoryTesterOutputFile;
-    std::cerr << log.c_str() << std::endl;
-    return false;
-    }
-
-  std::ifstream ifs(m_MemoryTesterOutputFile.c_str());
-  if ( !ifs )
-    {
-    log = "Cannot read Purify output file: " + m_MemoryTesterOutputFile;
-    std::cerr << log.c_str() << std::endl;
-    return false;
-    }
-
-  cmOStringStream ostr;
-  log = "";
-
-  cmsys::RegularExpression pfW("^\\[[WEI]\\] ([A-Z][A-Z][A-Z][A-Z]*): ");
-
-  int defects = 0;
-
-  std::string line;
-  while ( cmSystemTools::GetLineFromStream(ifs, line) )
-    {
-    int failure = cmCTest::NO_MEMORY_FAULT;
-    if ( pfW.find(line) )
-      {
-      int cc;
-      for ( cc = 0; cc < cmCTest::NO_MEMORY_FAULT; cc ++ )
-        {
-        if ( pfW.match(1) == cmCTestMemCheckResultStrings[cc] )
-          {
-          failure = cc;
-          break;
-          }
-        }
-      if ( cc == cmCTest::NO_MEMORY_FAULT )
-        {
-        std::cerr<< "Unknown Purify memory fault: " << pfW.match(1) << std::endl;
-        ostr << "*** Unknown Purify memory fault: " << pfW.match(1) << std::endl;
-        }
-      }
-    if ( failure != NO_MEMORY_FAULT )
-      {
-      ostr << "<b>" << cmCTestMemCheckResultStrings[failure] << "</b> ";
-      results[failure] ++;
-      defects ++;
-      }
-    ostr << cmCTest::MakeXMLSafe(line) << std::endl;
-    }
-
-  log = ostr.str();
-  if ( defects )
-    {
-    return false;
-    }
-  return true;
-}
-
-bool cmCTest::ProcessMemCheckValgrindOutput(const std::string& str, std::string& log, 
-  int* results)
-{
-  std::vector<cmStdString> lines;
-  cmSystemTools::Split(str.c_str(), lines);
- 
-  std::string::size_type cc;
-
-  cmOStringStream ostr;
-  log = "";
-
-  int defects = 0;
-
-  cmsys::RegularExpression valgrindLine("^==[0-9][0-9]*==");
-
-  cmsys::RegularExpression vgFIM(
-    "== .*Invalid free\\(\\) / delete / delete\\[\\]");
-  cmsys::RegularExpression vgFMM(
-    "== .*Mismatched free\\(\\) / delete / delete \\[\\]");
-  cmsys::RegularExpression vgMLK(
-    "== .*[0-9][0-9]* bytes in [0-9][0-9]* blocks are definitely lost"
-    " in loss record [0-9][0-9]* of [0-9]");
-  cmsys::RegularExpression vgPAR(
-    "== .*Syscall param .* contains unaddressable byte\\(s\\)");
-  cmsys::RegularExpression vgMPK1(
-    "== .*[0-9][0-9]* bytes in [0-9][0-9]* blocks are possibly lost in"
-    " loss record [0-9][0-9]* of [0-9]");
-  cmsys::RegularExpression vgMPK2(
-    "== .*[0-9][0-9]* bytes in [0-9][0-9]* blocks are still reachable"
-    " in loss record [0-9][0-9]* of [0-9]");
-  cmsys::RegularExpression vgUMC(
-    "== .*Conditional jump or move depends on uninitialised value\\(s\\)");
-  cmsys::RegularExpression vgUMR1("== .*Use of uninitialised value of size [0-9][0-9]*");
-  cmsys::RegularExpression vgUMR2("== .*Invalid read of size [0-9][0-9]*");
-  cmsys::RegularExpression vgUMR3("== .*Jump to the invalid address ");
-  cmsys::RegularExpression vgUMR4(
-    "== .*Syscall param .* contains uninitialised or unaddressable byte\\(s\\)");
-  cmsys::RegularExpression vgIPW("== .*Invalid write of size [0-9]");
-  cmsys::RegularExpression vgABR("== .*pthread_mutex_unlock: mutex is locked by a different thread");
-
-  //double sttime = cmSystemTools::GetTime();
-  //std::cout << "Start test: " << lines.size() << std::endl;
-  for ( cc = 0; cc < lines.size(); cc ++ )
-    {
-    if ( valgrindLine.find(lines[cc]) )
-      {
-      int failure = cmCTest::NO_MEMORY_FAULT;
-      if ( vgFIM.find(lines[cc]) ) { failure = cmCTest::FIM; }
-      else if ( vgFMM.find(lines[cc]) ) { failure = cmCTest::FMM; }
-      else if ( vgMLK.find(lines[cc]) ) { failure = cmCTest::MLK; }
-      else if ( vgPAR.find(lines[cc]) ) { failure = cmCTest::PAR; }
-      else if ( vgMPK1.find(lines[cc]) ){ failure = cmCTest::MPK; }
-      else if ( vgMPK2.find(lines[cc]) ){ failure = cmCTest::MPK; }
-      else if ( vgUMC.find(lines[cc]) ) { failure = cmCTest::UMC; }
-      else if ( vgUMR1.find(lines[cc]) ){ failure = cmCTest::UMR; }
-      else if ( vgUMR2.find(lines[cc]) ){ failure = cmCTest::UMR; }
-      else if ( vgUMR3.find(lines[cc]) ){ failure = cmCTest::UMR; }
-      else if ( vgUMR4.find(lines[cc]) ){ failure = cmCTest::UMR; }
-      else if ( vgIPW.find(lines[cc]) ) { failure = cmCTest::IPW; }
-      else if ( vgABR.find(lines[cc]) ) { failure = cmCTest::ABR; }
-
-      if ( failure != cmCTest::NO_MEMORY_FAULT )
-        {
-        ostr << "<b>" << cmCTestMemCheckResultStrings[failure] << "</b> ";
-        results[failure] ++;
-        defects ++;
-        }
-      ostr << cmCTest::MakeXMLSafe(lines[cc]) << std::endl;
-      }
-    }
-  //std::cout << "End test (elapsed: " << (cmSystemTools::GetTime() - sttime) << std::endl;
-  log = ostr.str();
-  if ( defects )
-    {
-    return false;
-    }
-  return true;
-}
-
-bool cmCTest::ProcessMemCheckOutput(const std::string& str, std::string& log, int* results)
-{
-  std::string::size_type cc;
-  for ( cc = 0; cc < cmCTest::NO_MEMORY_FAULT; cc ++ )
-    {
-    results[cc] = 0;
-    }
-
-  if ( m_MemoryTesterStyle == cmCTest::VALGRIND )
-    {
-    return this->ProcessMemCheckValgrindOutput(str, log, results);
-    }
-  else if ( m_MemoryTesterStyle == cmCTest::PURIFY )
-    {
-    return this->ProcessMemCheckPurifyOutput(str, log, results);
-    }
-  else if ( m_MemoryTesterStyle == cmCTest::BOUNDS_CHECKER )
-    {
-    log.append("\nMemory checking style used was: ");
-    log.append("Bounds Checker");
-    }
-  else
-    {
-    log.append("\nMemory checking style used was: ");
-    log.append("None that I know");
-    log = str;
-    }
-
-
-  return true;
-}
-
 int cmCTest::GenerateDartNotesOutput(std::ostream& os, const cmCTest::tm_VectorOfStrings& files)
 {
   cmCTest::tm_VectorOfStrings::const_iterator it;
@@ -3078,9 +1163,11 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
       {
       this->m_Verbose = true;
       this->BuildHandler->SetVerbose(this->m_Verbose);
+      this->ConfigureHandler->SetVerbose(this->m_Verbose);
+      this->CoverageHandler->SetVerbose(this->m_Verbose);
       this->ScriptHandler->SetVerbose(this->m_Verbose);
+      this->TestHandler->SetVerbose(this->m_Verbose);
       this->UpdateHandler->SetVerbose(this->m_Verbose);
-      this->ConfigureHandler->SetVerbose(this->m_Verbose);
       }
 
     if( arg.find("-N",0) == 0 || arg.find("--show-only",0) == 0 )
@@ -3108,10 +1195,6 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
       i++;
       m_InteractiveDebugMode = cmSystemTools::IsOn(args[i].c_str());
       }
-    if( arg.find("--compatibility-mode",0) == 0 )
-      {
-      m_CompatibilityMode = true;
-      }
     if( arg.find("-D",0) == 0 && i < args.size() - 1 )
       {
       this->m_DartMode = true;
@@ -3366,21 +1449,20 @@ int cmCTest::Run(std::vector<std::string>const& args, std::string* output)
     if(arg.find("-I",0) == 0 && i < args.size() - 1)
       {
       i++;
-      this->SetTestsToRunInformation(args[i].c_str());
+      this->TestHandler->SetTestsToRunInformation(args[i].c_str());
       }
     if(arg.find("-R",0) == 0 && i < args.size() - 1)
       {
-      this->m_UseIncludeRegExp = true;
+      this->TestHandler->UseIncludeRegExp();
       i++;
-      this->m_IncludeRegExp  = args[i];
+      this->TestHandler->SetIncludeRegExp(args[i].c_str());
       }
 
     if(arg.find("-E",0) == 0 && i < args.size() - 1)
       {
-      this->m_UseExcludeRegExp = true;
+      this->TestHandler->UseExcludeRegExp();
       i++;
-      this->m_ExcludeRegExp  = args[i];
-      this->m_UseExcludeRegExpFirst = this->m_UseIncludeRegExp ? false : true;
+      this->TestHandler->SetExcludeRegExp(args[i].c_str());
       }
 
     if(arg.find("-A",0) == 0 && i < args.size() - 1)
@@ -4016,34 +2098,8 @@ int cmCTest::ReadCustomConfigurationFileTree(const char* dir)
     }
 
   this->BuildHandler->PopulateCustomVectors(mf);
+  this->TestHandler->PopulateCustomVectors(mf);
   
-  this->PopulateCustomVector(mf, "CTEST_CUSTOM_TESTS_IGNORE", m_CustomTestsIgnore);
-  this->PopulateCustomVector(mf, "CTEST_CUSTOM_MEMCHECK_IGNORE", m_CustomMemCheckIgnore);
-
-  this->PopulateCustomVector(mf, "CTEST_CUSTOM_PRE_TEST", m_CustomPreTest);
-  this->PopulateCustomVector(mf, "CTEST_CUSTOM_POST_TEST", m_CustomPostTest);
-  this->PopulateCustomVector(mf, "CTEST_CUSTOM_PRE_MEMCHECK", m_CustomPreMemCheck);
-  this->PopulateCustomVector(mf, "CTEST_CUSTOM_POST_MEMCHECK", m_CustomPostMemCheck);
-
-  const char* maxstr = mf->GetDefinition("CTEST_CUSTOM_PASSED_TEST_STRING_MAXLEN");
-  if ( maxstr )
-    {
-    long val = atoi(maxstr);
-    if ( val > 0 )
-      {
-      m_MaximumPassedTestResultSize = val;
-      }
-    }
-  maxstr = mf->GetDefinition("CTEST_CUSTOM_FAILED_TEST_STRING_MAXLEN");
-  if ( maxstr )
-    {
-    long val = atoi(maxstr);
-    if ( val > 0 )
-      {
-      m_MaximumFailedTestResultSize = val;
-      }
-    }
-
   return 1;
 }
 
@@ -4068,204 +2124,33 @@ void cmCTest::PopulateCustomVector(cmMakefile* mf, const char* def, tm_VectorOfS
     }
 }
 
-int cmCTest::ExecuteCommands(tm_VectorOfStrings& vec)
-{
-  tm_VectorOfStrings::iterator it;
-  for ( it = vec.begin(); it != vec.end(); ++it )
-    {
-    int retVal = 0;
-    if ( m_Verbose )
-      {
-      std::cout << "Run command: " << *it << std::endl;
-      }
-    if ( !cmSystemTools::RunSingleCommand(it->c_str(), 0, &retVal, 0, true /*m_Verbose*/) || 
-      retVal != 0 )
-      {
-      std::cerr << "Problem running command: " << *it << std::endl;
-      return 0;
-      }
-    }
-  return 1;
-}
-
-
-// get the next number in a string with numbers separated by ,
-// pos is the start of the search and pos2 is the end of the search
-// pos becomes pos2 after a call to GetNextNumber.   
-// -1 is returned at the end of the list.
-inline int GetNextNumber(std::string const& in, 
-                         int& val,
-                         std::string::size_type& pos,
-                         std::string::size_type& pos2)
-{
-  pos2 = in.find(',', pos);
-  if(pos2 != in.npos)
-    {
-    if(pos2-pos == 0)
-      {
-      val = -1;
-      }
-    else
-      {
-      val = atoi(in.substr(pos, pos2-pos).c_str());
-      }
-    pos = pos2+1;
-    return 1;
-    }
-  else
-    {
-    if(in.size()-pos == 0)
-      {
-       val = -1;
-      }
-    else
-      {
-      val = atoi(in.substr(pos, in.size()-pos).c_str());
-      }
-    return 0;
-    }
-}
-
-// get the next number in a string with numbers separated by ,
-// pos is the start of the search and pos2 is the end of the search
-// pos becomes pos2 after a call to GetNextNumber.   
-// -1 is returned at the end of the list.
-inline int GetNextRealNumber(std::string const& in, 
-                             double& val,
-                             std::string::size_type& pos,
-                             std::string::size_type& pos2)
+std::string cmCTest::GetDartConfiguration(const char *name)
 {
-  pos2 = in.find(',', pos);
-  if(pos2 != in.npos)
-    {
-    if(pos2-pos == 0)
-      {
-      val = -1;
-      }
-    else
-      {
-      val = atof(in.substr(pos, pos2-pos).c_str());
-      }
-    pos = pos2+1;
-    return 1;
-    }
-  else
-    {
-    if(in.size()-pos == 0)
-      {
-       val = -1;
-      }
-    else
-      {
-      val = atof(in.substr(pos, in.size()-pos).c_str());
-      }
-    return 0;
-    }
+  return m_DartConfiguration[name];
 }
 
-                         
-void cmCTest::SetTestsToRunInformation(const char* in)
+  
+std::string cmCTest::GetCurrentTag()
 {
-  this->TestsToRunString = in;
-  // if the argument is a file, then read it and use the contents as the string
-  if(cmSystemTools::FileExists(in))
-    {
-    std::ifstream fin(in);
-    unsigned long filelen = cmSystemTools::FileLength(in);
-    char* buff = new char[filelen+1];
-    fin.getline(buff, filelen);
-    buff[fin.gcount()] = 0;
-    this->TestsToRunString = buff;
-    }
+  return m_CurrentTag;
 }
 
-void cmCTest::ExpandTestsToRunInformation(int numTests)
+std::string cmCTest::GetToplevelPath()
 {
-  if (this->TestsToRunString.empty())
-    {
-    return;
-    }
-  
-  int start;
-  int end = -1;
-  double stride = -1;
-  std::string::size_type pos = 0;
-  std::string::size_type pos2;
-  // read start
-  if(GetNextNumber(this->TestsToRunString, start, pos, pos2))
-    {
-    // read end
-    if(GetNextNumber(this->TestsToRunString, end, pos, pos2))
-      {
-      // read stride
-      if(GetNextRealNumber(this->TestsToRunString, stride, pos, pos2))
-        {
-        int val =0;
-        // now read specific numbers
-        while(GetNextNumber(this->TestsToRunString, val, pos, pos2))
-          {
-          m_TestsToRun.push_back(val);
-          }
-        m_TestsToRun.push_back(val);
-        }
-      }
-    }
-
-  // if start is not specified then we assume we start at 1
-  if(start == -1)
-    {
-    start = 1;
-    }
-
-  // if end isnot specified then we assume we end with the last test
-  if(end == -1)
-    {
-    end = numTests;
-    }
-  
-  // if the stride wasn't specified then it defaults to 1
-  if(stride == -1)
-    {
-    stride = 1;
-    }
-
-  // if we have a range then add it
-  if(end != -1 && start != -1 && stride > 0)
-    {
-    int i = 0;
-    while (i*stride + start <= end)
-      {
-      m_TestsToRun.push_back(static_cast<int>(i*stride+start));
-      ++i;
-      }
-    }
-
-  // sort the array
-  std::sort(m_TestsToRun.begin(), m_TestsToRun.end(), std::less<int>());
-  // remove duplicates
-  std::vector<int>::iterator new_end = 
-    std::unique(m_TestsToRun.begin(), m_TestsToRun.end());
-  m_TestsToRun.erase(new_end, m_TestsToRun.end());
-  std::cout << "Running tests: ";
-  for(unsigned int i =0; i < m_TestsToRun.size(); ++i)
-    {
-    std::cout << m_TestsToRun[i] << " ";
-    }
-  std::cout << "\n";
+  return m_ToplevelPath;
 }
 
-std::string cmCTest::GetDartConfiguration(const char *name)
+std::string cmCTest::GetConfigType()
 {
-  return m_DartConfiguration[name];
+  return m_ConfigType;
 }
 
-  
-std::string cmCTest::GetCurrentTag()
+bool cmCTest::GetShowOnly()
 {
-  return m_CurrentTag;
+  return m_ShowOnly;
 }
 
-bool cmCTest::GetShowOnly()
+bool cmCTest::GetProduceXML()
 {
-  return m_ShowOnly;
+  return m_DartMode;
 }