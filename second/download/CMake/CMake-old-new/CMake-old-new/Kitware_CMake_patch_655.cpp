@@ -19,529 +19,452 @@
 
 #include "cmCTest.h"
 #include "cmake.h"
+#include "cmSystemTools.h"
+#include "cmGlob.h"
 #include <cmsys/Process.h>
+#include <cmsys/RegularExpression.hxx>
 
 #include <stdlib.h> 
 #include <math.h>
 #include <float.h>
 
 #define SAFEDIV(x,y) (((y)!=0)?((x)/(y)):(0))
 
-
 //----------------------------------------------------------------------
 cmCTestCoverageHandler::cmCTestCoverageHandler()
 {
   m_Verbose = false; 
   m_CTest = 0;
 }
 
-
 //----------------------------------------------------------------------
-//clearly it would be nice if this were broken up into a few smaller
-//functions and commented...
-int cmCTestCoverageHandler::CoverageDirectory(cmCTest *ctest_inst)
+bool cmCTestCoverageHandler::StartLogFile(std::ofstream& covLogFile, int logFileCount)
 {
-  m_CTest = ctest_inst;
-
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
-  std::string start_time = m_CTest->CurrentTime();
-
-  // Find all source files.
-  std::string sourceDirectory = m_CTest->GetDartConfiguration("SourceDirectory");
-  if ( sourceDirectory.size() == 0 )
+  char covLogFilename[1024];
+  sprintf(covLogFilename, "CoverageLog-%d.xml", logFileCount);
+  std::cout << "Open file: " << covLogFilename << std::endl;
+  if (!m_CTest->OpenOutputFile(m_CTest->GetCurrentTag(), 
+      covLogFilename, covLogFile))
     {
-    std::cerr << "Cannot find SourceDirectory key in the DartConfiguration.tcl" << std::endl;
-    return 1;
+    std::cerr << "Cannot open log file: " << covLogFilename << std::endl;
+    return false;
     }
+  std::string local_start_time = m_CTest->CurrentTime();
+  covLogFile << "<CoverageLog>" << std::endl
+    << "\t<StartDateTime>" << local_start_time << "</StartDateTime>" << std::endl;
+  return true;
+}
 
-  std::string coverageCommand = m_CTest->GetDartConfiguration("CoverageCommand");
-  if ( coverageCommand.size() == 0 )
-    {
-    std::cerr << "Coverage command not defined in DartConfiguration.tcl" << std::endl;
-    return 1;
-    }
-  cdirs.push_back(sourceDirectory);
-  while ( !done ) 
+//----------------------------------------------------------------------
+void cmCTestCoverageHandler::StopLogFile(std::ofstream& ostr, int logFileCount)
+{
+  std::string local_end_time = m_CTest->CurrentTime();
+  ostr << "\t<EndDateTime>" << local_end_time << "</EndDateTime>" << std::endl
+    << "</CoverageLog>" << std::endl;
+  char covLogFilename[1024];
+  sprintf(covLogFilename, "CoverageLog-%d.xml", logFileCount);
+  std::cout << "Close file: " << covLogFilename << std::endl;
+  ostr.close();
+}
+
+//----------------------------------------------------------------------
+bool cmCTestCoverageHandler::ShouldIDoCoverage(const char* file, const char* srcDir,
+  const char* binDir, bool verbose)
+{
+  std::string fSrcDir = cmSystemTools::CollapseFullPath(srcDir);
+  std::string fBinDir = cmSystemTools::CollapseFullPath(binDir);
+  std::string fFile = cmSystemTools::CollapseFullPath(file);
+  bool sourceSubDir = cmSystemTools::IsSubDirectory(fFile.c_str(), fSrcDir.c_str());
+  bool buildSubDir = cmSystemTools::IsSubDirectory(fFile.c_str(), fBinDir.c_str());
+  // Always check parent directory of the file.
+  std::string fileDir = cmSystemTools::GetFilenamePath(fFile.c_str());
+  std::string checkDir;
+
+  // We also need to check the binary/source directory pair.
+  if ( sourceSubDir && buildSubDir )
     {
-    if ( cdirs.size() <= 0 )
+    if ( fSrcDir.size() > fBinDir.size() )
       {
-      break;
+      checkDir = fSrcDir;
       }
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
+    else
       {
-      for ( cc = 0; cc < cfiles.size(); cc ++ )
-        {
-        if ( cfiles[cc] != "." && cfiles[cc] != ".." )
-          {
-          cdirs.push_back(cfiles[cc]);
-          }
-        }
+      checkDir = fBinDir;
       }
     }
-
-  // find all binary files
-  cdirs.push_back(cmSystemTools::GetCurrentWorkingDirectory());
-  while ( !done ) 
+  else if ( sourceSubDir )
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
-      {
-      for ( cc = 0; cc < cfiles.size(); cc ++ )
-        {
-        if ( cfiles[cc] != "." && cfiles[cc] != ".." )
-          {
-          cdirs.push_back(cfiles[cc]);
-          }
-        }
-      }
+    checkDir = fSrcDir;
     }
-
-  std::map<std::string, std::string>::iterator sit;
-  for ( sit = allbinaryfiles.begin(); sit != allbinaryfiles.end(); sit ++ )
+  else if ( buildSubDir )
     {
-    const std::string& fname = sit->second;
-    //std::cout << "File: " << fname << std::endl;
-    if ( strcmp(fname.substr(fname.size()-3, 3).c_str(), ".da") == 0 )
-      {
-      files.push_back(fname);
-      }
+    checkDir = fBinDir;
     }
-  
-  if ( files.size() == 0 )
+  std::string ndc
+    = cmSystemTools::FileExistsInParentDirectories(".NoDartCoverage",
+      fFile.c_str(), checkDir.c_str());
+  if ( ndc.size() )
     {
-    std::cerr << "Cannot find any coverage information files (.da)" << std::endl;
-    return 1;
+    if ( verbose )
+      {
+      std::cout << "Found: " << ndc.c_str() << " so skip coverage of " << file << std::endl;
+      }
+    return false;
     }
 
-  std::ofstream log; 
-  if (!m_CTest->OpenOutputFile("Temporary", "Coverage.log", log))
+  // By now checkDir should be set to parent directory of the file.
+  // Get the relative path to the file an apply it to the opposite directory.
+  // If it is the same as fileDir, then ignore, otherwise check.
+  std::string relPath = cmSystemTools::RelativePath(checkDir.c_str(),
+    fFile.c_str());
+  if ( checkDir == fSrcDir )
     {
-    std::cerr << "Cannot open log file" << std::endl;
-    return 1;
+    checkDir = fBinDir;
     }
-  log.close();
-  if (!m_CTest->OpenOutputFile(m_CTest->GetCurrentTag(), "Coverage.xml", log))
+  else
     {
-    std::cerr << "Cannot open log file" << std::endl;
-    return 1;
+    checkDir = fSrcDir;
     }
+  fFile = checkDir + "/" + relPath;
+  fFile = cmSystemTools::GetFilenamePath(fFile.c_str());
 
-  std::string opath = m_CTest->GetToplevelPath() + "/Testing/Temporary/Coverage";
-  cmSystemTools::MakeDirectory(opath.c_str());
-  cfiles.clear();
-  cmCTest::tm_VectorOfStrings ncfiles;
-  cmCTest::tm_VectorOfStrings missing_files;
-
-  for ( cc = 0; cc < files.size(); cc ++ )
+  if ( fileDir == fFile )
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
-    if ( !m_CTest->GetShowOnly() )
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
-      {
-      std::cerr << "Run gcov on " << files[cc] << std::flush;
-      std::cerr << " [" << command << "]" << std::endl;
-      std::cerr << " - fail" << std::endl;
-      }
+    // This is in-source build, so we trust the previous check.
+    return true;
     }
-  
-  files.clear();
-  std::map<std::string, cmCTest::tm_VectorOfStrings > sourcefiles;
-  for ( cc = 0; cc < cfiles.size(); cc ++ )
+
+  ndc = cmSystemTools::FileExistsInParentDirectories(".NoDartCoverage",
+    fFile.c_str(), checkDir.c_str());
+  if ( ndc.size() )
     {
-    std::string& fname = cfiles[cc];
-    //    std::cout << "File: " << fname << std::endl;
-    if ( strcmp(fname.substr(fname.size()-5, 5).c_str(), ".gcov") == 0 )
+    if ( verbose )
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
+      std::cout << "Found: " << ndc.c_str() << " so skip coverage of: " << file << std::endl;
       }
+    return false;
     }
-  // for ( cc = 0; cc < files.size(); cc ++ )
-  //     {
-  //     std::cout << "File: " << files[cc] << std::endl;
-  //     }
-  if ( missing_files.size() > 0 )
+  // Ok, nothing in source tree, nothing in binary tree
+  return true;
+}
+
+//----------------------------------------------------------------------
+//clearly it would be nice if this were broken up into a few smaller
+//functions and commented...
+int cmCTestCoverageHandler::CoverageDirectory(cmCTest *ctest_inst)
+{
+  m_CTest = ctest_inst;
+
+  int error = 0;
+
+  std::string sourceDir = m_CTest->GetDartConfiguration("SourceDirectory");
+  std::string binaryDir = m_CTest->GetDartConfiguration("BuildDirectory");
+  std::string gcovCommand = m_CTest->GetDartConfiguration("CoverageCommand");
+
+  cmSystemTools::ConvertToUnixSlashes(sourceDir);
+  cmSystemTools::ConvertToUnixSlashes(binaryDir);
+
+  std::string asfGlob = sourceDir + "/*";
+  std::string abfGlob = binaryDir + "/*";
+  std::string daGlob = binaryDir + "/*.da";
+  std::string gcovOutputRex = "[0-9]+\\.[0-9]+% of [0-9]+ (source |)lines executed in file (.*)$";
+  std::string gcovOutputRex2 = "^Creating (.*\\.gcov)\\.";
+
+  std::cout << "Performing coverage" << std::endl;
+  double elapsed_time_start = cmSystemTools::GetTime();
+
+  std::string coverage_start_time = m_CTest->CurrentTime();
+
+  std::string testingDir = m_CTest->GetToplevelPath() + "/Testing";
+  std::string tempDir = testingDir + "/CoverageInfo";
+  std::string currentDirectory = cmSystemTools::GetCurrentWorkingDirectory();
+  cmSystemTools::MakeDirectory(tempDir.c_str());
+  cmSystemTools::ChangeDirectory(tempDir.c_str());
+
+  cmGlob gl;
+  gl.RecurseOn();
+  gl.FindFiles(daGlob);
+  std::vector<std::string> files = gl.GetFiles();
+  std::vector<std::string>::iterator it;
+
+  if ( files.size() == 0 )
     {
-    std::cout << "---------------------------------------------------------------" << std::endl;
-    std::cout << "The following files were missing:" << std::endl;
-    for ( cc = 0; cc < missing_files.size(); cc ++ )
-      {
-      std::cout << "File: " << missing_files[cc] << std::endl;
-      }
-    std::cout << "---------------------------------------------------------------" << std::endl;
+    std::cerr << " Cannot find any coverage files." << std::endl;
+    // No coverage files is a valid thing, so the exit code is 0
+    return 0;
     }
 
-  std::map<std::string, cmCTest::tm_VectorOfStrings >::iterator it;
-  cmCTestCoverageHandler::tm_CoverageMap coverageresults;
+  // Regular expressions for output of gcov
+  cmsys::RegularExpression re(gcovOutputRex.c_str());
+  cmsys::RegularExpression re2(gcovOutputRex2.c_str());
 
-  m_CTest->StartXML(log);
-  log << "<Coverage>\n"
-      << "\t<StartDateTime>" << start_time << "</StartDateTime>" << std::endl;
+  typedef std::vector<int> singleFileCoverageVector;
+  typedef std::map<std::string, singleFileCoverageVector> totalCoverageMap;
 
-  int total_tested = 0;
-  int total_untested = 0;
+  totalCoverageMap totalCoverage;
 
-  for ( it = sourcefiles.begin(); it != sourcefiles.end(); it ++ )
+  std::string cfile = "";
+  for ( it = files.begin(); it != files.end(); ++ it )
     {
-    //std::cerr << "Source file: " << it->first << std::endl;
-    cmCTest::tm_VectorOfStrings &gfiles = it->second;
-
-    for ( cc = 0; cc < gfiles.size(); cc ++ )
+    std::string fileDir = cmSystemTools::GetFilenamePath(it->c_str());
+    std::string command = "\"" + gcovCommand + "\" -l -o \"" + fileDir + "\" \"" + *it + "\"";
+    if ( m_Verbose )
       {
-      int do_coverage = 1;
-      std::string coverage_dir = cmSystemTools::GetFilenamePath(gfiles[cc].c_str());
-      std::string builDir = m_CTest->GetDartConfiguration("BuildDirectory");
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
-      cmCTestCoverageHandler::cmCTestCoverage& cov = coverageresults[it->first];
-      std::vector<int>& covlines = cov.m_Lines; 
-      if ( cov.m_FullPath == "" )
+      std::cout << command.c_str() << std::endl;
+      }
+    std::string output = "";
+    int retVal = 0;
+    int res = cmSystemTools::RunSingleCommand(command.c_str(), &output, 
+      &retVal, tempDir.c_str(),
+      false, 0 /*m_TimeOut*/);
+    if ( ! res )
+      {
+      std::cerr << "Problem running coverage on file: " << it->c_str() << std::endl;
+      error ++;
+      continue;
+      }
+    if ( retVal != 0 )
+      {
+      std::cerr << "Coverage command returned: " << retVal << " while processing: " << it->c_str() << std::endl;
+      }
+    std::vector<cmStdString> lines;
+    std::vector<cmStdString>::iterator line;
+    cmSystemTools::Split(output.c_str(), lines);
+    for ( line = lines.begin(); line != lines.end(); ++line)
+      {
+      if ( re.find(line->c_str()) )
         {
-        covlines.insert(covlines.begin(), lines.size(), -1);
-        if ( allsourcefiles.find(it->first) != allsourcefiles.end() )
+        cfile = "";
+        std::string file = re.match(2);
+        // Is it in the source dir?
+        if ( file.size() > sourceDir.size() &&
+          file.substr(0, sourceDir.size()) == sourceDir &&
+          file[sourceDir.size()] == '/' )
           {
-          cov.m_FullPath = allsourcefiles[it->first];
-          }
-        else if ( allbinaryfiles.find(it->first) != allbinaryfiles.end() )
-          {
-          cov.m_FullPath = allbinaryfiles[it->first];
-          }
-        cov.m_AbsolutePath = cov.m_FullPath;
-        std::string src_dir = m_CTest->GetDartConfiguration("SourceDirectory");
-        if ( src_dir[src_dir.size()-1] != '/' )
-          {
-          src_dir = src_dir + "/";
+          if ( m_Verbose )
+            {
+            std::cout << "   produced s: " << file << std::endl;
+            }
+          cfile = file;
           }
-        std::string::size_type spos = cov.m_FullPath.find(src_dir);
-        if ( spos == 0 )
+        // Binary dir?
+        if ( file.size() > binaryDir.size() &&
+          file.substr(0, binaryDir.size()) == binaryDir &&
+          file[binaryDir.size()] == '/' )
           {
-          cov.m_FullPath = std::string("./") + cov.m_FullPath.substr(src_dir.size());
+          if ( m_Verbose )
+            {
+            std::cout << "   produce b: " << file << std::endl;
+            }
+          cfile = file;
           }
-        else
+        if ( cfile.empty() )
           {
-          //std::cerr << "Compare -- " << cov.m_FullPath << std::endl;
-          //std::cerr << "        -- " << src_dir << std::endl;
-          cov.m_Show = false;
-          continue;
+          std::cerr << "Something went wrong" << std::endl;
+          std::cerr << "File: [" << file << "]" << std::endl;
+          std::cerr << "s: [" << file.substr(0, sourceDir.size()) << "]" << std::endl;
+          std::cerr << "b: [" << file.substr(0, binaryDir.size()) << "]" << std::endl;
           }
-        cov.m_Show = true;
         }
-      std::string::size_type kk;
-      //      std::cerr << "number of lines " << lines.size() << "\n";
-      for ( kk = 0; kk < lines.size(); kk ++ )
+      else if ( re2.find(line->c_str() ) )
         {
-        std::string& line = lines[kk];
-        //std::cerr << line << "\n";
-        std::string sub1 = line.substr(0, strlen("    #####"));
-        std::string sub2 = line.substr(0, strlen("      ######"));
-        int count = atoi(sub2.c_str());
-        if ( sub1.compare("    #####") == 0 ||
-             sub2.compare("      ######") == 0 )
+        std::string fname = re2.match(1);
+        if ( cfile.size() )
           {
-          if ( covlines[kk] == -1 )
+          singleFileCoverageVector* vec = &totalCoverage[cfile];
+          if ( m_Verbose )
             {
-            covlines[kk] = 0;
+            std::cout << "   in file: " << fname << std::endl;
             }
-          cov.m_UnTested ++;
-          //std::cout << "Untested - ";
-          }
-        else if ( count > 0 )
-          {
-          if ( covlines[kk] == -1 )
+          singleFileCoverageVector cov;
+          std::ifstream ifile(fname.c_str());
+          if ( ! ifile )
+            {
+            std::cerr << "Cannot open file: " << fname << std::endl;
+            }
+          else
             {
-            covlines[kk] = 0;
+            long cnt = -1;
+            std::string nl;
+            while ( cmSystemTools::GetLineFromStream(ifile, nl) )
+              {
+              cnt ++;
+              if ( vec->size() <= static_cast<singleFileCoverageVector::size_type>(cnt) )
+                {
+                vec->push_back(-1);
+                }
+
+              //TODO: Handle gcov 3.0 non-coverage lines
+
+              // Skip empty lines
+              if ( !nl.size() )
+                {
+                continue;
+                }
+
+              // Skip unused lines
+              if ( nl[0] == '\t' || nl.size() < 12 )
+                {
+                continue;
+                }
+
+              std::string prefix = nl.substr(0, 12);
+              int cov = atoi(prefix.c_str());
+              (*vec)[cnt] += cov;
+              }
             }
-          cov.m_Tested ++;
-          covlines[kk] ++;
-          //std::cout << "Tested[" << count << "] - ";
           }
-
-        //std::cout << line << std::endl;
+        }
+      else
+        {
+        std::cerr << "Unknown line: " << line->c_str() << std::endl;
+        error ++;
         }
       }
     }
 
-  //std::cerr << "Finalizing" << std::endl;
-  cmCTestCoverageHandler::tm_CoverageMap::iterator cit;
-  int ccount = 0;
-  std::ofstream cfileoutput; 
-  int cfileoutputcount = 0;
-  char cfileoutputname[100];
-  std::string local_start_time = m_CTest->CurrentTime();
-  std::string local_end_time;
-  for ( cit = coverageresults.begin(); cit != coverageresults.end(); cit ++ )
+  std::ofstream covSumFile;
+  std::ofstream covLogFile;
+
+  if (!m_CTest->OpenOutputFile(m_CTest->GetCurrentTag(), 
+      "Coverage.xml", covSumFile))
     {
-    cmCTestCoverageHandler::cmCTestCoverage &cov = cit->second;
-    if ( !cov.m_Show )
-      {
-      continue;
-      }
+    std::cerr << "Cannot open coverage summary file: Coverage.xml" << std::endl;
+    return 1;
+    }
+
+  m_CTest->StartXML(covSumFile);
+  // Produce output xml files
 
-    // Check if we should ignore the directory, if we find a NoDartCoverage
-    // file in it or any of its parents
-    int do_coverage = 1;
-    std::string coverage_dir = cmSystemTools::GetFilenamePath(cov.m_AbsolutePath.c_str());
-    do
+  covSumFile << "<Coverage>" << std::endl
+    << "\t<StartDateTime>" << coverage_start_time << "</StartDateTime>" << std::endl;
+  int logFileCount = 0;
+  if ( !this->StartLogFile(covLogFile, logFileCount) )
+    {
+    return 1;
+    }
+  totalCoverageMap::iterator fileIterator;
+  int cnt = 0;
+  long total_tested = 0;
+  long total_untested = 0;
+  std::string fullSourceDir = sourceDir + "/";
+  std::string fullBinaryDir = binaryDir + "/";
+  for ( fileIterator = totalCoverage.begin();
+    fileIterator != totalCoverage.end();
+    ++fileIterator )
+    {
+    if ( cnt == 100 )
       {
-      std::string coverage_file = coverage_dir + "/.NoDartCoverage";
-      if ( cmSystemTools::FileExists(coverage_file.c_str()) )
+      cnt = 0;
+      this->StopLogFile(covLogFile, logFileCount);
+      logFileCount ++;
+      if ( !this->StartLogFile(covLogFile, logFileCount) )
         {
-        do_coverage = 0;
-        break;
-        }
-      // is there a parent directory we can check
-      std::string::size_type pos = coverage_dir.rfind('/');
-      // if we could not find the directory return 0
-      if(pos == std::string::npos)
-        {
-        break;
+        return 1;
         }
-      coverage_dir = coverage_dir.substr(0, pos);
+      }
+    const std::string fullFileName = fileIterator->first;
+    const std::string fileName = cmSystemTools::GetFilenameName(fullFileName.c_str());
+    std::string fullFilePath = cmSystemTools::GetFilenamePath(fullFileName.c_str());
+    if ( m_Verbose )
+      {
+      std::cerr << "Process file: " << fullFileName << std::endl;
+      }
+
+    cmSystemTools::ConvertToUnixSlashes(fullFilePath);
 
+    if ( !cmSystemTools::FileExists(fullFileName.c_str()) )
+      {
+      std::cerr << "Cannot find file: " << fullFileName.c_str() << std::endl;
+      continue;
       }
-    while (coverage_dir.size() >= sourceDirectory.size());
 
-    if (!do_coverage)
+    bool shouldIDoCoverage
+      = this->ShouldIDoCoverage(fullFileName.c_str(),
+        sourceDir.c_str(), binaryDir.c_str(), m_Verbose);
+    if ( !shouldIDoCoverage )
       {
       if ( m_Verbose )
         {
-        std::cout << "Ignore file: " << cov.m_FullPath.c_str() << std::endl;
+        std::cerr << ".NoDartCoverage found, so skip coverage check for: "
+          << fullFileName.c_str()
+          << std::endl;
         }
       continue;
       }
-    
-    if ( ccount == 100 )
+
+    const singleFileCoverageVector& fcov = fileIterator->second;
+    covLogFile << "\t<File Name=\""
+      << m_CTest->MakeXMLSafe(fileName.c_str())
+      << "\" FullPath=\"" << m_CTest->MakeXMLSafe(fileIterator->first) << "\">" << std::endl
+      << "\t\t<Report>" << std::endl;
+
+    std::ifstream ifs(fullFileName.c_str());
+    if ( !ifs)
       {
-      local_end_time = m_CTest->CurrentTime();
-      cfileoutput << "\t<EndDateTime>" << local_end_time << "</EndDateTime>\n"
-        << "</CoverageLog>" << std::endl;
-      m_CTest->EndXML(cfileoutput);
-      cfileoutput.close();
-      std::cout << "Close file: " << cfileoutputname << std::endl;
-      ccount = 0;
+      std::cerr << "Cannot open source file: " << fullFileName.c_str() << std::endl;
+      error ++;
+      continue;
       }
-    if ( ccount == 0 )
+
+    int tested = 0;
+    int untested = 0;
+
+    singleFileCoverageVector::size_type cc;
+    std::string line;
+    for ( cc= 0; cc < fcov.size(); cc ++ )
       {
-      sprintf(cfileoutputname, "CoverageLog-%d.xml", cfileoutputcount++);
-      std::cout << "Open file: " << cfileoutputname << std::endl;
-      if (!m_CTest->OpenOutputFile(m_CTest->GetCurrentTag(), 
-                                   cfileoutputname, cfileoutput))
+      if ( !cmSystemTools::GetLineFromStream(ifs, line) )
         {
-        std::cerr << "Cannot open log file: " << cfileoutputname << std::endl;
-        return 1;
+        std::cerr << "Problem reading source file: " << fullFileName.c_str() << " line:" << cc << std::endl;
+        error ++;
+        break;
         }
-      local_start_time = m_CTest->CurrentTime();
-      m_CTest->StartXML(cfileoutput);
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
+      covLogFile << "\t\t<Line Number=\"" << cc << "\" Count=\"" << fcov[cc] << "\">"
+        << m_CTest->MakeXMLSafe(line.c_str()) << "</Line>" << std::endl;
+      if ( fcov[cc] == 0 )
         {
-        cov.m_UnTested ++;
+        untested ++;
         }
-      else if ( cov.m_Lines[cc] > 0 )
+      else if ( fcov[cc] > 0 )
         {
-        cov.m_Tested ++;
+        tested ++;
         }
       }
-
-    std::ifstream ifile(cov.m_AbsolutePath.c_str());
-    if ( !ifile )
+    if ( cmSystemTools::GetLineFromStream(ifs, line) )
       {
-      std::cerr << "Cannot open file: " << cov.m_FullPath.c_str() << std::endl;
+      std::cerr << "Looks like there are more lines in the file: " << line << std::endl;
       }
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
     float cper = 0;
     float cmet = 0;
-    if ( total_tested + total_untested > 0 && (cov.m_Tested + cov.m_UnTested) > 0)
+    if ( tested + untested > 0 )
       {
-      cper = (100 * SAFEDIV(static_cast<float>(cov.m_Tested),
-        static_cast<float>(cov.m_Tested + cov.m_UnTested)));
-      cmet = ( SAFEDIV(static_cast<float>(cov.m_Tested + 10),
-        static_cast<float>(cov.m_Tested + cov.m_UnTested + 10)));
+      cper = (100 * SAFEDIV(static_cast<float>(tested),
+          static_cast<float>(tested + untested)));
+      cmet = ( SAFEDIV(static_cast<float>(tested + 10),
+          static_cast<float>(tested + untested + 10)));
       }
-
-    log << "\t<File Name=\"" << cit->first << "\" FullPath=\"" << cov.m_FullPath
+    total_tested += tested;
+    total_untested += untested;
+    covLogFile << "\t\t</Report>" << std::endl
+      << "\t</File>" << std::endl;
+    covSumFile << "\t<File Name=\"" << m_CTest->MakeXMLSafe(fileName)
+      << "\" FullPath=\"" << m_CTest->MakeXMLSafe(fullFileName)
       << "\" Covered=\"" << (cmet>0?"true":"false") << "\">\n"
-      << "\t\t<LOCTested>" << cov.m_Tested << "</LOCTested>\n"
-      << "\t\t<LOCUnTested>" << cov.m_UnTested << "</LOCUnTested>\n"
+      << "\t\t<LOCTested>" << tested << "</LOCTested>\n"
+      << "\t\t<LOCUnTested>" << untested << "</LOCUnTested>\n"
       << "\t\t<PercentCoverage>";
-    log.setf(std::ios::fixed, std::ios::floatfield);
-    log.precision(2);
-    log << (cper) << "</PercentCoverage>\n"
+    covSumFile.setf(std::ios::fixed, std::ios::floatfield);
+    covSumFile.precision(2);
+    covSumFile << (cper) << "</PercentCoverage>\n"
       << "\t\t<CoverageMetric>";
-    log.setf(std::ios::fixed, std::ios::floatfield);
-    log.precision(2);
-    log << (cmet) << "</CoverageMetric>\n"
+    covSumFile.setf(std::ios::fixed, std::ios::floatfield);
+    covSumFile.precision(2);
+    covSumFile << (cmet) << "</CoverageMetric>\n"
       << "\t</File>" << std::endl;
-    ccount ++;
-    }
-  
-  if ( ccount > 0 )
-    {
-    local_end_time = m_CTest->CurrentTime();
-    cfileoutput << "\t<EndDateTime>" << local_end_time << "</EndDateTime>\n"
-                << "</CoverageLog>" << std::endl;
-    m_CTest->EndXML(cfileoutput);
-    cfileoutput.close();
+    cnt ++;
     }
+  this->StopLogFile(covLogFile, logFileCount);
 
   int total_lines = total_tested + total_untested;
   float percent_coverage = 100 * SAFEDIV(static_cast<float>(total_tested),
@@ -553,29 +476,30 @@ int cmCTestCoverageHandler::CoverageDirectory(cmCTest *ctest_inst)
 
   std::string end_time = m_CTest->CurrentTime();
 
-  log << "\t<LOCTested>" << total_tested << "</LOCTested>\n"
-      << "\t<LOCUntested>" << total_untested << "</LOCUntested>\n"
-      << "\t<LOC>" << total_lines << "</LOC>\n"
-      << "\t<PercentCoverage>";
-  log.setf(std::ios::fixed, std::ios::floatfield);
-  log.precision(2);
-  log << (percent_coverage)<< "</PercentCoverage>\n"
-      << "\t<EndDateTime>" << end_time << "</EndDateTime>\n";
-  log << "<ElapsedMinutes>" << 
+  covSumFile << "\t<LOCTested>" << total_tested << "</LOCTested>\n"
+    << "\t<LOCUntested>" << total_untested << "</LOCUntested>\n"
+    << "\t<LOC>" << total_lines << "</LOC>\n"
+    << "\t<PercentCoverage>";
+  covSumFile.setf(std::ios::fixed, std::ios::floatfield);
+  covSumFile.precision(2);
+  covSumFile << (percent_coverage)<< "</PercentCoverage>\n"
+    << "\t<EndDateTime>" << end_time << "</EndDateTime>\n";
+  covSumFile << "<ElapsedMinutes>" << 
     static_cast<int>((cmSystemTools::GetTime() - elapsed_time_start)/6)/10.0
-      << "</ElapsedMinutes>"
-      << "</Coverage>" << std::endl;
-  m_CTest->EndXML(log);
+    << "</ElapsedMinutes>"
+    << "</Coverage>" << std::endl;
+  m_CTest->EndXML(covSumFile);
 
   std::cout << "\tCovered LOC:         " << total_tested << std::endl
-            << "\tNot covered LOC:     " << total_untested << std::endl
-            << "\tTotal LOC:           " << total_lines << std::endl
-            << "\tPercentage Coverage: ";
+    << "\tNot covered LOC:     " << total_untested << std::endl
+    << "\tTotal LOC:           " << total_lines << std::endl
+    << "\tPercentage Coverage: ";
 
   std::cout.setf(std::ios::fixed, std::ios::floatfield);
   std::cout.precision(2);
   std::cout << (percent_coverage) << "%" << std::endl;
 
+  cmSystemTools::ChangeDirectory(currentDirectory.c_str());
 
-  return 1;
+  return error;
 }