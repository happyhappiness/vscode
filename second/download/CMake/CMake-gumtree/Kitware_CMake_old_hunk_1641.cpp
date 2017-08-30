{

}



std::string cmCTest::FindTheExecutable(const char *exe)

{

  std::string fullPath = "";

  std::string dir;

  std::string file;



  cmSystemTools::SplitProgramPath(exe, dir, file);

  if(m_ConfigType != "" && 

    ::TryExecutable(dir.c_str(), file.c_str(), &fullPath, 

      m_ConfigType.c_str()))

    {

    return fullPath;

    }



  if (::TryExecutable(dir.c_str(),file.c_str(),&fullPath,"."))

    {

    return fullPath;

    }



  if (::TryExecutable(dir.c_str(),file.c_str(),&fullPath,""))

    {

    return fullPath;

    }



  if ( m_ConfigType == "" )

    {

    // No config type, so try to guess it

    if (::TryExecutable(dir.c_str(),file.c_str(),&fullPath,"Release"))

      {

      return fullPath;

      }



    if (::TryExecutable(dir.c_str(),file.c_str(),&fullPath,"Debug"))

      {

      return fullPath;

      }



    if (::TryExecutable(dir.c_str(),file.c_str(),&fullPath,"MinSizeRel"))

      {

      return fullPath;

      }



    if (::TryExecutable(dir.c_str(),file.c_str(),&fullPath,"RelWithDebInfo"))

      {

      return fullPath;

      }

    }



  // if everything else failed, check the users path

  if (dir != "")

    {

    std::string path = cmSystemTools::FindProgram(file.c_str());

    if (path != "")

      {

      return path;

      }

    }



  if ( m_ConfigType != "" )

    {

    dir += "/";

    dir += m_ConfigType;

    dir += "/";

    dir += file;

    cmSystemTools::Error("config type specified on the command line, but test executable not found.",

      dir.c_str());

    return "";

    }

  return fullPath;

}





 

int cmCTest::CoverageDirectory()

{

  std::cout << "Performing coverage" << std::endl;

  double elapsed_time_start = cmSystemTools::GetTime();

  cmCTest::tm_VectorOfStrings files;

  cmCTest::tm_VectorOfStrings cfiles;

  cmCTest::tm_VectorOfStrings cdirs;

  bool done = false;

  std::string::size_type cc;

  std::string glob;

  std::map<std::string, std::string> allsourcefiles;

  std::map<std::string, std::string> allbinaryfiles;



  std::string start_time = this->CurrentTime();



  // Find all source files.

  std::string sourceDirectory = m_DartConfiguration["SourceDirectory"];

  if ( sourceDirectory.size() == 0 )

    {

    std::cerr << "Cannot find SourceDirectory key in the DartConfiguration.tcl" << std::endl;

    return 1;

    }



  std::string coverageCommand = m_DartConfiguration["CoverageCommand"];

  if ( coverageCommand.size() == 0 )

    {

    std::cerr << "Coverage command not defined in DartConfiguration.tcl" << std::endl;

    return 1;

    }

  cdirs.push_back(sourceDirectory);

  while ( !done ) 

    {

    if ( cdirs.size() <= 0 )

      {

      break;

      }

    glob = cdirs[cdirs.size()-1] + "/*";

    //std::cout << "Glob: " << glob << std::endl;

    cdirs.pop_back();

    if ( cmSystemTools::SimpleGlob(glob, cfiles, 1) )

      {

      for ( cc = 0; cc < cfiles.size(); cc ++ )

        {

        allsourcefiles[cmSystemTools::GetFilenameName(cfiles[cc])] = cfiles[cc];

        }

      }

    if ( cmSystemTools::SimpleGlob(glob, cfiles, -1) )

      {

      for ( cc = 0; cc < cfiles.size(); cc ++ )

        {

        if ( cfiles[cc] != "." && cfiles[cc] != ".." )

          {

          cdirs.push_back(cfiles[cc]);

          }

        }

      }

    }



  // find all binary files

  cdirs.push_back(cmSystemTools::GetCurrentWorkingDirectory());

  while ( !done ) 

    {

    if ( cdirs.size() <= 0 )

      {

      break;

      }

    glob = cdirs[cdirs.size()-1] + "/*";

    //std::cout << "Glob: " << glob << std::endl;

    cdirs.pop_back();

    if ( cmSystemTools::SimpleGlob(glob, cfiles, 1) )

      {

      for ( cc = 0; cc < cfiles.size(); cc ++ )

        {

        allbinaryfiles[cmSystemTools::GetFilenameName(cfiles[cc])] = cfiles[cc];

        }

      }

    if ( cmSystemTools::SimpleGlob(glob, cfiles, -1) )

      {

      for ( cc = 0; cc < cfiles.size(); cc ++ )

        {

        if ( cfiles[cc] != "." && cfiles[cc] != ".." )

          {

          cdirs.push_back(cfiles[cc]);

          }

        }

      }

    }



  std::map<std::string, std::string>::iterator sit;

  for ( sit = allbinaryfiles.begin(); sit != allbinaryfiles.end(); sit ++ )

    {

    const std::string& fname = sit->second;

    //std::cout << "File: " << fname << std::endl;

    if ( strcmp(fname.substr(fname.size()-3, 3).c_str(), ".da") == 0 )

      {

      files.push_back(fname);

      }

    }

  

  if ( files.size() == 0 )

    {

    std::cerr << "Cannot find any coverage information files (.da)" << std::endl;

    return 1;

    }



  std::ofstream log; 

  if (!this->OpenOutputFile("Temporary", "Coverage.log", log))

    {

    std::cerr << "Cannot open log file" << std::endl;

    return 1;

    }

  log.close();

  if (!this->OpenOutputFile(m_CurrentTag, "Coverage.xml", log))

    {

    std::cerr << "Cannot open log file" << std::endl;

    return 1;

    }



  std::string opath = m_ToplevelPath + "/Testing/Temporary/Coverage";

  cmSystemTools::MakeDirectory(opath.c_str());

  cfiles.clear();

  cmCTest::tm_VectorOfStrings ncfiles;

  cmCTest::tm_VectorOfStrings missing_files;



  for ( cc = 0; cc < files.size(); cc ++ )

    {

    std::string currPath = cmSystemTools::GetFilenamePath(files[cc]);

    std::string command = coverageCommand + " -o \"" + currPath + "\" -l \"" + files[cc] + "\"";

    std::string output;

    int retVal = 0;

    if ( m_Verbose )

      {

      std::cerr << "Run gcov on " << files[cc] << " in directory: " << currPath.c_str() << std::endl;

      }

    //std::cout << "   --- Run [" << command << "]" << std::endl;

    bool res = true;

    if ( !m_ShowOnly )

      {

      res = cmSystemTools::RunSingleCommand(command.c_str(), &output, 

        &retVal, currPath.c_str(),

        m_Verbose, 0 /*m_TimeOut*/);

      }

    if ( res && retVal == 0 )

      {

      //std::cout << " - done" << std::endl;

      glob = currPath + "/*";

      if ( !cmSystemTools::SimpleGlob(glob, ncfiles, 1) )

        {

        std::cerr << "Cannot found any coverage files" << std::endl;

        return 1;

        }

      cfiles.insert(cfiles.end(), ncfiles.begin(), ncfiles.end());

      std::vector<cmStdString> gcovlines;

      cmSystemTools::Split(output.c_str(), gcovlines);

      std::vector<cmStdString>::iterator git;

      const char* message = "Could not open source file";

      for ( git = gcovlines.begin(); git != gcovlines.end(); ++git )

        {

        if ( strncmp(git->c_str(), message, strlen(message) ) == 0 )

          {

          std::cerr << "Problem: " << git->c_str() << std::endl;

          missing_files.push_back(git->c_str() + strlen(message));

          }

        }

      }

    else

      {

      std::cerr << "Run gcov on " << files[cc] << std::flush;

      std::cerr << " [" << command << "]" << std::endl;

      std::cerr << " - fail" << std::endl;

      }

    }

  

  files.clear();

  std::map<std::string, cmCTest::tm_VectorOfStrings > sourcefiles;

  for ( cc = 0; cc < cfiles.size(); cc ++ )

    {

    std::string& fname = cfiles[cc];

    //    std::cout << "File: " << fname << std::endl;

    if ( strcmp(fname.substr(fname.size()-5, 5).c_str(), ".gcov") == 0 )

      {

      files.push_back(fname);

      std::string::size_type pos = fname.find(".da.");

      std::string::size_type pos2 = fname.find(".da##");

      if(pos2 != fname.npos)

        {

        pos = pos2+1;

        }

      if ( pos != fname.npos )

        {

        pos += 4;

        std::string::size_type epos = fname.size() - pos - strlen(".gcov");

        std::string nf = fname.substr(pos, epos);

        //std::cout << "Substring: " << nf << std::endl;

        if ( allsourcefiles.find(nf) != allsourcefiles.end() || 

             allbinaryfiles.find(nf) != allbinaryfiles.end() )

          {

          cmCTest::tm_VectorOfStrings &cvec = sourcefiles[nf];

          cvec.push_back(fname);

          }

        }

      }

    }

  // for ( cc = 0; cc < files.size(); cc ++ )

  //     {

  //     std::cout << "File: " << files[cc] << std::endl;

  //     }

  if ( missing_files.size() > 0 )

    {

    std::cout << "---------------------------------------------------------------" << std::endl;

    std::cout << "The following files were missing:" << std::endl;

    for ( cc = 0; cc < missing_files.size(); cc ++ )

      {

      std::cout << "File: " << missing_files[cc] << std::endl;

      }

    std::cout << "---------------------------------------------------------------" << std::endl;

    }



  std::map<std::string, cmCTest::tm_VectorOfStrings >::iterator it;

  cmCTest::tm_CoverageMap coverageresults;



  this->StartXML(log);

  log << "<Coverage>\n"

      << "\t<StartDateTime>" << start_time << "</StartDateTime>" << std::endl;



  int total_tested = 0;

  int total_untested = 0;



  for ( it = sourcefiles.begin(); it != sourcefiles.end(); it ++ )

    {

    //std::cerr << "Source file: " << it->first << std::endl;

    cmCTest::tm_VectorOfStrings &gfiles = it->second;



    for ( cc = 0; cc < gfiles.size(); cc ++ )

      {

      int do_coverage = 1;

      std::string coverage_dir = cmSystemTools::GetFilenamePath(gfiles[cc].c_str());

      std::string builDir = m_DartConfiguration["BuildDirectory"];

      do

        {

        std::string coverage_file = coverage_dir + "/.NoDartCoverage";

        if ( cmSystemTools::FileExists(coverage_file.c_str()) )

          {

          do_coverage = 0;

          break;

          }

        // is there a parent directory we can check

        std::string::size_type pos = coverage_dir.rfind('/');

        // if we could not find the directory return 0

        if(pos == std::string::npos)

          {

          break;

          }

        coverage_dir = coverage_dir.substr(0, pos);

        }

      while (coverage_dir.size() >= builDir.size());

      if ( !do_coverage )

        {

        continue;

        }

      //std::cout << "\t" << gfiles[cc] << std::endl;

      std::ifstream ifile(gfiles[cc].c_str());

      if ( !ifile )

        {

        std::cerr << "Cannot open file: " << gfiles[cc].c_str() << std::endl;

        }



      ifile.seekg (0, std::ios::end);

      int length = ifile.tellg();

      ifile.seekg (0, std::ios::beg);

      char *buffer = new char [ length + 1 ];

      ifile.read(buffer, length);

      buffer [length] = 0;

      //std::cout << "Read: " << buffer << std::endl;

      std::vector<cmStdString> lines;

      cmSystemTools::Split(buffer, lines);

      delete [] buffer;

      cmCTest::cmCTestCoverage& cov = coverageresults[it->first];

      std::vector<int>& covlines = cov.m_Lines; 

      if ( cov.m_FullPath == "" )

        {

        covlines.insert(covlines.begin(), lines.size(), -1);

        if ( allsourcefiles.find(it->first) != allsourcefiles.end() )

          {

          cov.m_FullPath = allsourcefiles[it->first];

          }

        else if ( allbinaryfiles.find(it->first) != allbinaryfiles.end() )

          {

          cov.m_FullPath = allbinaryfiles[it->first];

          }

        cov.m_AbsolutePath = cov.m_FullPath;

        std::string src_dir = m_DartConfiguration["SourceDirectory"];

        if ( src_dir[src_dir.size()-1] != '/' )

          {

          src_dir = src_dir + "/";

          }

        std::string::size_type spos = cov.m_FullPath.find(src_dir);

        if ( spos == 0 )

          {

          cov.m_FullPath = std::string("./") + cov.m_FullPath.substr(src_dir.size());

          }

        else

          {

          //std::cerr << "Compare -- " << cov.m_FullPath << std::endl;

          //std::cerr << "        -- " << src_dir << std::endl;

          cov.m_Show = false;

          continue;

          }

        cov.m_Show = true;

        }

      std::string::size_type kk;

      //      std::cerr << "number of lines " << lines.size() << "\n";

      for ( kk = 0; kk < lines.size(); kk ++ )

        {

        std::string& line = lines[kk];

        //std::cerr << line << "\n";

        std::string sub1 = line.substr(0, strlen("    #####"));

        std::string sub2 = line.substr(0, strlen("      ######"));

        int count = atoi(sub2.c_str());

        if ( sub1.compare("    #####") == 0 ||

             sub2.compare("      ######") == 0 )

          {

          if ( covlines[kk] == -1 )

            {

            covlines[kk] = 0;

            }

          cov.m_UnTested ++;

          //std::cout << "Untested - ";

          }

        else if ( count > 0 )

          {

          if ( covlines[kk] == -1 )

            {

            covlines[kk] = 0;

            }

          cov.m_Tested ++;

          covlines[kk] ++;

          //std::cout << "Tested[" << count << "] - ";

          }



        //std::cout << line << std::endl;

        }

      }

    }



  //std::cerr << "Finalizing" << std::endl;

  cmCTest::tm_CoverageMap::iterator cit;

  int ccount = 0;

  std::ofstream cfileoutput; 

  int cfileoutputcount = 0;

  char cfileoutputname[100];

  std::string local_start_time = this->CurrentTime();

  std::string local_end_time;

  for ( cit = coverageresults.begin(); cit != coverageresults.end(); cit ++ )

    {

    cmCTest::cmCTestCoverage &cov = cit->second;

    if ( !cov.m_Show )

      {

      continue;

      }



    // Check if we should ignore the directory, if we find a NoDartCoverage

    // file in it or any of its parents

    int do_coverage = 1;

    std::string coverage_dir = cmSystemTools::GetFilenamePath(cov.m_AbsolutePath.c_str());

    do

      {

      std::string coverage_file = coverage_dir + "/.NoDartCoverage";

      if ( cmSystemTools::FileExists(coverage_file.c_str()) )

        {

        do_coverage = 0;

        break;

        }

      // is there a parent directory we can check

      std::string::size_type pos = coverage_dir.rfind('/');

      // if we could not find the directory return 0

      if(pos == std::string::npos)

        {

        break;

        }

      coverage_dir = coverage_dir.substr(0, pos);



      }

    while (coverage_dir.size() >= sourceDirectory.size());



    if (!do_coverage)

      {

      if ( m_Verbose )

        {

        std::cout << "Ignore file: " << cov.m_FullPath.c_str() << std::endl;

        }

      continue;

      }

    

    if ( ccount == 100 )

      {

      local_end_time = this->CurrentTime();

      cfileoutput << "\t<EndDateTime>" << local_end_time << "</EndDateTime>\n"

        << "</CoverageLog>" << std::endl;

      this->EndXML(cfileoutput);

      cfileoutput.close();

      std::cout << "Close file: " << cfileoutputname << std::endl;

      ccount = 0;

      }

    if ( ccount == 0 )

      {

      sprintf(cfileoutputname, "CoverageLog-%d.xml", cfileoutputcount++);

      std::cout << "Open file: " << cfileoutputname << std::endl;

      if (!this->OpenOutputFile(m_CurrentTag, cfileoutputname, cfileoutput))

        {

        std::cerr << "Cannot open log file: " << cfileoutputname << std::endl;

        return 1;

        }

      local_start_time = this->CurrentTime();

      this->StartXML(cfileoutput);

      cfileoutput << "<CoverageLog>\n"

        << "\t<StartDateTime>" << local_start_time << "</StartDateTime>" << std::endl;

      }



    //std::cerr << "Final process of Source file: " << cit->first << std::endl;

    cov.m_UnTested = 0;

    cov.m_Tested = 0;

    for ( cc = 0; cc < cov.m_Lines.size(); cc ++ )

      {

      if ( cov.m_Lines[cc] == 0 )

        {

        cov.m_UnTested ++;

        }

      else if ( cov.m_Lines[cc] > 0 )

        {

        cov.m_Tested ++;

        }

      }



    std::ifstream ifile(cov.m_AbsolutePath.c_str());

    if ( !ifile )

      {

      std::cerr << "Cannot open file: " << cov.m_FullPath.c_str() << std::endl;

      }

    ifile.seekg (0, std::ios::end);

    int length = ifile.tellg();

    ifile.seekg (0, std::ios::beg);

    char *buffer = new char [ length + 1 ];

    ifile.read(buffer, length);

    buffer [length] = 0;

    //std::cout << "Read: " << buffer << std::endl;

    std::vector<cmStdString> lines;

    cmSystemTools::Split(buffer, lines);

    delete [] buffer;



    cfileoutput << "\t<File Name=\"" << cit->first << "\" FullPath=\""

      << cov.m_FullPath << "\">\n"

      << "\t\t<Report>" << std::endl;

    for ( cc = 0; cc < lines.size(); cc ++ )

      {

      cfileoutput << "\t\t<Line Number=\"" 

        << static_cast<int>(cc) << "\" Count=\""

        << cov.m_Lines[cc] << "\">"

        << cmCTest::MakeXMLSafe(lines[cc]) << "</Line>" << std::endl;

      }

    cfileoutput << "\t\t</Report>\n"

      << "\t</File>" << std::endl;





    total_tested += cov.m_Tested;

    total_untested += cov.m_UnTested;

    float cper = 0;

    float cmet = 0;

    if ( total_tested + total_untested > 0 && (cov.m_Tested + cov.m_UnTested) > 0)

      {

      cper = (100 * SAFEDIV(static_cast<float>(cov.m_Tested),

        static_cast<float>(cov.m_Tested + cov.m_UnTested)));

      cmet = ( SAFEDIV(static_cast<float>(cov.m_Tested + 10),

        static_cast<float>(cov.m_Tested + cov.m_UnTested + 10)));

      }



    log << "\t<File Name=\"" << cit->first << "\" FullPath=\"" << cov.m_FullPath

      << "\" Covered=\"" << (cmet>0?"true":"false") << "\">\n"

      << "\t\t<LOCTested>" << cov.m_Tested << "</LOCTested>\n"

      << "\t\t<LOCUnTested>" << cov.m_UnTested << "</LOCUnTested>\n"

      << "\t\t<PercentCoverage>";

    log.setf(std::ios::fixed, std::ios::floatfield);

    log.precision(2);

    log << (cper) << "</PercentCoverage>\n"

      << "\t\t<CoverageMetric>";

    log.setf(std::ios::fixed, std::ios::floatfield);

    log.precision(2);

    log << (cmet) << "</CoverageMetric>\n"

      << "\t</File>" << std::endl;

    ccount ++;

    }

  

  if ( ccount > 0 )

    {

    local_end_time = this->CurrentTime();

    cfileoutput << "\t<EndDateTime>" << local_end_time << "</EndDateTime>\n"

                << "</CoverageLog>" << std::endl;

    this->EndXML(cfileoutput);

    cfileoutput.close();

    }



  int total_lines = total_tested + total_untested;

  float percent_coverage = 100 * SAFEDIV(static_cast<float>(total_tested),

    static_cast<float>(total_lines));

  if ( total_lines == 0 )

    {

    percent_coverage = 0;

    }



  std::string end_time = this->CurrentTime();



  log << "\t<LOCTested>" << total_tested << "</LOCTested>\n"

      << "\t<LOCUntested>" << total_untested << "</LOCUntested>\n"

      << "\t<LOC>" << total_lines << "</LOC>\n"

      << "\t<PercentCoverage>";

  log.setf(std::ios::fixed, std::ios::floatfield);

  log.precision(2);

  log << (percent_coverage)<< "</PercentCoverage>\n"

      << "\t<EndDateTime>" << end_time << "</EndDateTime>\n";

  log << "<ElapsedMinutes>" << 

    static_cast<int>((cmSystemTools::GetTime() - elapsed_time_start)/6)/10.0

      << "</ElapsedMinutes>"

      << "</Coverage>" << std::endl;

  this->EndXML(log);



  std::cout << "\tCovered LOC:         " << total_tested << std::endl

            << "\tNot covered LOC:     " << total_untested << std::endl

            << "\tTotal LOC:           " << total_lines << std::endl

            << "\tPercentage Coverage: ";



  std::cout.setf(std::ios::fixed, std::ios::floatfield);

  std::cout.precision(2);

  std::cout << (percent_coverage) << "%" << std::endl;





  return 1;

}



bool cmCTest::OpenOutputFile(const std::string& path, 

                     const std::string& name, std::ofstream& stream)

{

  std::string testingDir = m_ToplevelPath + "/Testing";

  if ( path.size() > 0 )

    {

    testingDir += "/" + path;

    }

  if ( cmSystemTools::FileExists(testingDir.c_str()) )

    {

    if ( !cmSystemTools::FileIsDirectory(testingDir.c_str()) )

      {

      std::cerr << "File " << testingDir 

                << " is in the place of the testing directory"

                << std::endl;

      return false;

      }

    }

  else

    {

    if ( !cmSystemTools::MakeDirectory(testingDir.c_str()) )

      {

      std::cerr << "Cannot create directory " << testingDir

                << std::endl;

      return false;

      }

    }

  std::string filename = testingDir + "/" + name;

  stream.open(filename.c_str());

  if( !stream )

    {

    std::cerr << "Problem opening file: " << filename << std::endl;

    return false;

    }

  return true;

}



void cmCTest::GetListOfTests(tm_ListOfTests* testlist, bool memcheck)

{

  // does the DartTestfile.txt exist ?

  if(!cmSystemTools::FileExists("DartTestfile.txt"))

    {

    return;

    }



  // parse the file

  std::ifstream fin("DartTestfile.txt");

  if(!fin)

    {

    return;

    }



  cmsys::RegularExpression ireg(this->m_IncludeRegExp.c_str());

  cmsys::RegularExpression ereg(this->m_ExcludeRegExp.c_str());



  cmListFileCache cache;

  cmListFile* listFile = cache.GetFileCache("DartTestfile.txt", false);

  for(std::vector<cmListFileFunction>::const_iterator f =

    listFile->m_Functions.begin(); f != listFile->m_Functions.end(); ++f)

    {

    const cmListFileFunction& lff = *f;

    const std::string& name = lff.m_Name;

    const tm_VectorOfListFileArgs& args = lff.m_Arguments;

    if (name == "SUBDIRS")

      {

      std::string cwd = cmSystemTools::GetCurrentWorkingDirectory();

      for(tm_VectorOfListFileArgs::const_iterator j = args.begin();

        j != args.end(); ++j)

        {

        std::string nwd = cwd + "/";

        nwd += j->Value;

        if (cmSystemTools::FileIsDirectory(nwd.c_str()))

          {

          cmSystemTools::ChangeDirectory(nwd.c_str());

          this->GetListOfTests(testlist, memcheck);

          }

        }

      // return to the original directory

      cmSystemTools::ChangeDirectory(cwd.c_str());

      }



    if (name == "ADD_TEST")

      {

      const std::string& testname = args[0].Value;

      if (this->m_UseExcludeRegExp &&

        this->m_UseExcludeRegExpFirst &&

        ereg.find(testname.c_str()))

        {

        continue;

        }

      if ( memcheck )

        {

        tm_VectorOfStrings::iterator it;

        bool found = false;

        for ( it = m_CustomMemCheckIgnore.begin(); 

          it != m_CustomMemCheckIgnore.end(); ++ it )

          {

          if ( *it == testname )

            {

            found = true;

            break;

            }

          }

        if ( found )

          {

          if ( m_Verbose )

            {

            std::cout << "Ignore memcheck: " << *it << std::endl;

            }

          continue;

          }

        }

      else

        {

        tm_VectorOfStrings::iterator it;

        bool found = false;

        for ( it = m_CustomTestsIgnore.begin(); 

          it != m_CustomTestsIgnore.end(); ++ it )

          {

          if ( *it == testname )

            {

            found = true;

            break;

            }

          }

        if ( found )

          {

          if ( m_Verbose )

            {

            std::cout << "Ignore test: " << *it << std::endl;

            }

          continue;

          }

        }





      if (this->m_UseIncludeRegExp && !ireg.find(testname.c_str()))

        {

        continue;

        }

      if (this->m_UseExcludeRegExp &&

        !this->m_UseExcludeRegExpFirst &&

        ereg.find(testname.c_str()))

        {

        continue;

        }



      cmCTestTestProperties test;

      test.m_Name = testname;

      test.m_Args = args;

      test.m_Directory = cmSystemTools::GetCurrentWorkingDirectory();

      testlist->push_back(test);

      }

    }

}



void cmCTest::ProcessDirectory(cmCTest::tm_VectorOfStrings &passed, 

                             cmCTest::tm_VectorOfStrings &failed,

                             bool memcheck)

{

  std::string current_dir = cmSystemTools::GetCurrentWorkingDirectory();

  cmsys::RegularExpression dartStuff("(<DartMeasurement.*/DartMeasurement[a-zA-Z]*>)");

  tm_ListOfTests testlist;

  this->GetListOfTests(&testlist, memcheck);

  tm_ListOfTests::size_type tmsize = testlist.size();



  std::ofstream ofs;

  std::ofstream *olog = 0;

  if ( !m_ShowOnly && tmsize > 0 && 

    this->OpenOutputFile("Temporary", 

      (memcheck?"LastMemCheck.log":"LastTest.log"), ofs) )

    {

    olog = &ofs;

    }



  m_StartTest = this->CurrentTime();

  double elapsed_time_start = cmSystemTools::GetTime();



  if ( olog )

    {

    *olog << "Start testing: " << m_StartTest << std::endl

      << "----------------------------------------------------------"

      << std::endl;

    }



  // expand the test list

  this->ExpandTestsToRunInformation((int)tmsize);

  

  int cnt = 0;

  tm_ListOfTests::iterator it;

  std::string last_directory = "";

  for ( it = testlist.begin(); it != testlist.end(); it ++ )

    {

    cnt ++;

    const std::string& testname = it->m_Name;

    tm_VectorOfListFileArgs& args = it->m_Args;

    cmCTestTestResult cres;

    cres.m_Status = cmCTest::NOT_RUN;

    cres.m_TestCount = cnt;



    if (!(last_directory == it->m_Directory))

      {

      if ( m_Verbose )

        {

        std::cerr << "Changing directory into " 

          << it->m_Directory.c_str() << "\n";

        }

      last_directory = it->m_Directory;

      cmSystemTools::ChangeDirectory(it->m_Directory.c_str());

      }

    cres.m_Name = testname;

    if(m_TestsToRun.size() && 

       std::find(m_TestsToRun.begin(), m_TestsToRun.end(), cnt) == m_TestsToRun.end())

      {

      continue;

      }



    if ( m_ShowOnly )

      {

      std::cerr.width(3);

      std::cerr << cnt << "/";

      std::cerr.width(3);

      std::cerr << tmsize << " Testing ";

      std::string outname = testname;

      outname.resize(30, ' ');

      std::cerr << outname.c_str() << "\n";

     }

    else

      {

      std::cerr.width(3);

      std::cerr << cnt << "/";

      std::cerr.width(3);

      std::cerr << tmsize << " Testing ";

      std::string outname = testname;

      outname.resize(30, ' ');

      std::cerr << outname.c_str();

      std::cerr.flush();

      }

    

    //std::cerr << "Testing " << args[0] << " ... ";

    // find the test executable

    std::string actualCommand = this->FindTheExecutable(args[1].Value.c_str());

    std::string testCommand = cmSystemTools::ConvertToOutputPath(actualCommand.c_str());

    std::string memcheckcommand = "";



    // continue if we did not find the executable

    if (testCommand == "")

      {

      std::cerr << "Unable to find executable: " <<

        args[1].Value.c_str() << "\n";

      if ( !m_ShowOnly )

        {

        m_TestResults.push_back( cres ); 

        failed.push_back(testname);

        continue;

        }

      }



    // add the arguments

    tm_VectorOfListFileArgs::const_iterator j = args.begin();

    ++j;

    ++j;

    std::vector<const char*> arguments;

    if ( memcheck )

      {

      cmCTest::tm_VectorOfStrings::size_type pp;

      arguments.push_back(m_MemoryTester.c_str());

      memcheckcommand = m_MemoryTester;

      for ( pp = 0; pp < m_MemoryTesterOptionsParsed.size(); pp ++ )

        {

        arguments.push_back(m_MemoryTesterOptionsParsed[pp].c_str());

        memcheckcommand += " ";

        memcheckcommand += cmSystemTools::EscapeSpaces(m_MemoryTesterOptionsParsed[pp].c_str());

        }

      }

    arguments.push_back(actualCommand.c_str());

    for(;j != args.end(); ++j)

      {

      testCommand += " ";

      testCommand += cmSystemTools::EscapeSpaces(j->Value.c_str());

      arguments.push_back(j->Value.c_str());

      }

    arguments.push_back(0);



    /**

     * Run an executable command and put the stdout in output.

     */

    std::string output;

    int retVal = 0;





    if ( m_Verbose )

      {

      std::cout << std::endl << (memcheck?"MemCheck":"Test") << " command: " << testCommand << std::endl;

      if ( memcheck )

        {

        std::cout << "Memory check command: " << memcheckcommand << std::endl;

        }

      }

    if ( olog )

      {

      *olog << cnt << "/" << tmsize 

        << " Test: " << testname.c_str() << std::endl;

      *olog << "Command: ";

      tm_VectorOfStrings::size_type ll;

      for ( ll = 0; ll < arguments.size()-1; ll ++ )

        {

        *olog << "\"" << arguments[ll] << "\" ";

        }

      *olog 

        << std::endl 

        << "Directory: " << it->m_Directory << std::endl 

        << "\"" << testname.c_str() << "\" start time: " 

        << this->CurrentTime() << std::endl

        << "Output:" << std::endl 

        << "----------------------------------------------------------"

        << std::endl;

      }

    int res = 0;

    double clock_start, clock_finish;

    clock_start = cmSystemTools::GetTime();



    if ( !m_ShowOnly )

      {

      res = this->RunTest(arguments, &output, &retVal, olog);

      }



    clock_finish = cmSystemTools::GetTime();



    if ( olog )

      {

      double ttime = clock_finish - clock_start;

      int hours = static_cast<int>(ttime / (60 * 60));

      int minutes = static_cast<int>(ttime / 60) % 60;

      int seconds = static_cast<int>(ttime) % 60;

      char buffer[100];

      sprintf(buffer, "%02d:%02d:%02d", hours, minutes, seconds);

      *olog 

        << "----------------------------------------------------------"

        << std::endl

        << "\"" << testname.c_str() << "\" end time: " 

        << this->CurrentTime() << std::endl

        << "\"" << testname.c_str() << "\" time elapsed: " 

        << buffer << std::endl

        << "----------------------------------------------------------"

        << std::endl << std::endl;

      }



    cres.m_ExecutionTime = (double)(clock_finish - clock_start);

    cres.m_FullCommandLine = testCommand;



    if ( !m_ShowOnly )

      {

      if (res == cmsysProcess_State_Exited && retVal == 0)

        {

        std::cerr <<   "   Passed\n";

        passed.push_back(testname);

        cres.m_Status = cmCTest::COMPLETED;

        }

      else

        {

        cres.m_Status = cmCTest::FAILED;

        if ( res == cmsysProcess_State_Expired )

          {

          std::cerr << "***Timeout\n";

          cres.m_Status = cmCTest::TIMEOUT;

          }

        else if ( res == cmsysProcess_State_Exception )

          {

          std::cerr << "***Exception: ";

          switch ( retVal )

            {

          case cmsysProcess_Exception_Fault:

            std::cerr << "SegFault";

            cres.m_Status = cmCTest::SEGFAULT;

            break;

          case cmsysProcess_Exception_Illegal:

            std::cerr << "Illegal";

            cres.m_Status = cmCTest::ILLEGAL;

            break;

          case cmsysProcess_Exception_Interrupt:

            std::cerr << "Interrupt";

            cres.m_Status = cmCTest::INTERRUPT;

            break;

          case cmsysProcess_Exception_Numerical:

            std::cerr << "Numerical";

            cres.m_Status = cmCTest::NUMERICAL;

            break;

          default:

            std::cerr << "Other";

            cres.m_Status = cmCTest::OTHER_FAULT;

            }

           std::cerr << "\n";

          }

        else if ( res == cmsysProcess_State_Error )

          {

          std::cerr << "***Bad command " << res << "\n";

          cres.m_Status = cmCTest::BAD_COMMAND;

          }

        else

          {

          std::cerr << "***Failed\n";

          }

        failed.push_back(testname);

        }

      if (output != "")

        {

        if (dartStuff.find(output.c_str()))

          {

          std::string dartString = dartStuff.match(1);

          cmSystemTools::ReplaceString(output, dartString.c_str(),"");

          cres.m_RegressionImages = this->GenerateRegressionImages(dartString);

          }

        }

      }

    cres.m_Output = output;

    cres.m_ReturnValue = retVal;

    std::string nwd = it->m_Directory;

    if ( nwd.size() > m_ToplevelPath.size() )

      {

      nwd = "." + nwd.substr(m_ToplevelPath.size(), nwd.npos);

      }

    cmSystemTools::ReplaceString(nwd, "\\", "/");

    cres.m_Path = nwd;

    cres.m_CompletionStatus = "Completed";

    m_TestResults.push_back( cres );

    }



  m_EndTest = this->CurrentTime();

  m_ElapsedTestingTime = cmSystemTools::GetTime() - elapsed_time_start;

  if ( olog )

    {

    *olog << "End testing: " << m_EndTest << std::endl;

    }

  cmSystemTools::ChangeDirectory(current_dir.c_str());

}



bool cmCTest::InitializeMemoryChecking()

{

  // Setup the command

  if ( cmSystemTools::FileExists(m_DartConfiguration["MemoryCheckCommand"].c_str()) )

    {

    m_MemoryTester 

      = cmSystemTools::ConvertToOutputPath(m_DartConfiguration["MemoryCheckCommand"].c_str());

    }

  else if ( cmSystemTools::FileExists(m_DartConfiguration["PurifyCommand"].c_str()) )

    {

    m_MemoryTester 

      = cmSystemTools::ConvertToOutputPath(m_DartConfiguration["PurifyCommand"].c_str());

    }

  else if ( cmSystemTools::FileExists(m_DartConfiguration["ValgrindCommand"].c_str()) )

    {

    m_MemoryTester 

      = cmSystemTools::ConvertToOutputPath(m_DartConfiguration["ValgrindCommand"].c_str());

    }

  else

    {

    std::cerr << "Memory checker (MemoryCheckCommand) not set, or cannot find the specified program." 

      << std::endl;

    return false;

    }



  if ( m_MemoryTester[0] == '\"' && m_MemoryTester[m_MemoryTester.size()-1] == '\"' )

    {

    m_MemoryTester = m_MemoryTester.substr(1, m_MemoryTester.size()-2);

    }



  // Setup the options

  if ( m_DartConfiguration["MemoryCheckCommandOptions"].size() )

    {

    m_MemoryTesterOptions = m_DartConfiguration["MemoryCheckCommandOptions"];

    }

  else if ( m_DartConfiguration["ValgrindCommandOptions"].size() )

    {

    m_MemoryTesterOptions = m_DartConfiguration["ValgrindCommandOptions"];

    }



  m_MemoryTesterOutputFile = m_ToplevelPath + "/Testing/Temporary/MemoryChecker.log";

  m_MemoryTesterOutputFile = cmSystemTools::EscapeSpaces(m_MemoryTesterOutputFile.c_str());



  if ( m_MemoryTester.find("valgrind") != std::string::npos )

    {

    m_MemoryTesterStyle = cmCTest::VALGRIND;

    if ( !m_MemoryTesterOptions.size() )

      {

      m_MemoryTesterOptions = "-q --skin=memcheck --leak-check=yes --show-reachable=yes --workaround-gcc296-bugs=yes --num-callers=100";

      }

    if ( m_DartConfiguration["MemoryCheckSuppressionFile"].size() )

      {

      if ( !cmSystemTools::FileExists(m_DartConfiguration["MemoryCheckSuppressionFile"].c_str()) )

        {

        std::cerr << "Cannot find memory checker suppression file: " 

          << m_DartConfiguration["MemoryCheckSuppressionFile"].c_str() << std::endl;

        return false;

        }

      m_MemoryTesterOptions += " --suppressions=" + cmSystemTools::EscapeSpaces(m_DartConfiguration["MemoryCheckSuppressionFile"].c_str()) + "";

      }

    }

  else if ( m_MemoryTester.find("purify") != std::string::npos )

    {

    m_MemoryTesterStyle = cmCTest::PURIFY;

#ifdef _WIN32

    m_MemoryTesterOptions += " /SAVETEXTDATA=" + m_MemoryTesterOutputFile;

#else

    m_MemoryTesterOptions += " -log-file=" + m_MemoryTesterOutputFile;

#endif

    }

  else if ( m_MemoryTester.find("boundschecker") != std::string::npos )

    {

    m_MemoryTesterStyle = cmCTest::BOUNDS_CHECKER;

    std::cerr << "Bounds checker not yet implemented" << std::endl;

    return false;

    }

  else

    {

    std::cerr << "Do not understand memory checker: " << m_MemoryTester.c_str() << std::endl;

    return false;

    }



  m_MemoryTesterOptionsParsed = cmSystemTools::ParseArguments(m_MemoryTesterOptions.c_str());

  cmCTest::tm_VectorOfStrings::size_type cc;

  for ( cc = 0; cmCTestMemCheckResultStrings[cc]; cc ++ )

    {

    m_MemoryTesterGlobalResults[cc] = 0;

    }

  return true;

}



int cmCTest::TestDirectory(bool memcheck)

{

  m_TestResults.clear();

  std::cout << (memcheck ? "Memory check" : "Test") << " project" << std::endl;

  if ( memcheck )

    {

    if ( !this->InitializeMemoryChecking() )

      {

      return 1;

      }

    }



  if ( memcheck )

    {

    if ( !this->ExecuteCommands(m_CustomPreMemCheck) )

      {

      std::cerr << "Problem executing pre-memcheck command(s)." << std::endl;

      return 1;

      }

    }

  else

    {

    if ( !this->ExecuteCommands(m_CustomPreTest) )

      {

      std::cerr << "Problem executing pre-test command(s)." << std::endl;

      return 1;

      }

    }



  cmCTest::tm_VectorOfStrings passed;

  cmCTest::tm_VectorOfStrings failed;

  int total;



  this->ProcessDirectory(passed, failed, memcheck);



  total = int(passed.size()) + int(failed.size());



  if (total == 0)

    {

    if ( !m_ShowOnly )

      {

      std::cerr << "No tests were found!!!\n";

      }

    }

  else

    {

    if (m_Verbose && passed.size() && 

      (m_UseIncludeRegExp || m_UseExcludeRegExp)) 

      {

      std::cerr << "\nThe following tests passed:\n";

      for(cmCTest::tm_VectorOfStrings::iterator j = passed.begin();

        j != passed.end(); ++j)

        {   

        std::cerr << "\t" << *j << "\n";

        }

      }



    float percent = float(passed.size()) * 100.0f / total;

    if ( failed.size() > 0 &&  percent > 99)

      {

      percent = 99;

      }

    fprintf(stderr,"\n%.0f%% tests passed, %i tests failed out of %i\n",

      percent, int(failed.size()), total);



    if (failed.size()) 

      {

      std::ofstream ofs;



      std::cerr << "\nThe following tests FAILED:\n";

      this->OpenOutputFile("Temporary", "LastTestsFailed.log", ofs);



      std::vector<cmCTest::cmCTestTestResult>::iterator ftit;

      for(ftit = m_TestResults.begin();

        ftit != m_TestResults.end(); ++ftit)

        {

        if ( ftit->m_Status != cmCTest::COMPLETED )

          {

          ofs << ftit->m_TestCount << ":" << ftit->m_Name << std::endl;

          fprintf(stderr, "\t%3d - %s (%s)\n", ftit->m_TestCount, ftit->m_Name.c_str(),

            this->GetTestStatus(ftit->m_Status));

          }

        }



      }

    }



  if ( m_DartMode )

    {

    std::ofstream xmlfile;

    if( !this->OpenOutputFile(m_CurrentTag, 

        (memcheck ? (m_CompatibilityMode?"Purify.xml":"DynamicAnalysis.xml") : "Test.xml"), xmlfile) )

      {

      std::cerr << "Cannot create " << (memcheck ? "memory check" : "testing")

        << " XML file" << std::endl;

      return 1;

      }

    if ( memcheck )

      {

      this->GenerateDartMemCheckOutput(xmlfile);

      }

    else

      {

      this->GenerateDartTestOutput(xmlfile);

      }

    }



  if ( memcheck )

    {

    if ( !this->ExecuteCommands(m_CustomPostMemCheck) )

      {

      std::cerr << "Problem executing post-memcheck command(s)." << std::endl;

      return 1;

      }

    }

  else

    {

    if ( !this->ExecuteCommands(m_CustomPostTest) )

      {

      std::cerr << "Problem executing post-test command(s)." << std::endl;

      return 1;

      }

    }



  return int(failed.size());

}



int cmCTest::SubmitResults()

{

  std::ofstream ofs;

  this->OpenOutputFile("Temporary", "LastSubmit.log", ofs);



  cmCTest::tm_VectorOfStrings files;

  std::string prefix = this->GetSubmitResultsPrefix();

  // TODO:

  // Check if test is enabled

  if ( this->CTestFileExists("Update.xml") )

    {

    files.push_back("Update.xml");

    }

  if ( this->CTestFileExists("Configure.xml") )

    {

    files.push_back("Configure.xml");

    }

  if ( this->CTestFileExists("Build.xml") )

    {

    files.push_back("Build.xml");

    }

  if ( this->CTestFileExists("Test.xml") )

    {

    files.push_back("Test.xml");

    }

  if ( this->CTestFileExists("Coverage.xml") )

    {

    files.push_back("Coverage.xml");

    cmCTest::tm_VectorOfStrings gfiles;

    std::string gpath = m_ToplevelPath + "/Testing/" + m_CurrentTag;

    std::string::size_type glen = gpath.size() + 1;

    gpath = gpath + "/CoverageLog*";

    //std::cout << "Globbing for: " << gpath.c_str() << std::endl;

    if ( cmSystemTools::SimpleGlob(gpath, gfiles, 1) )

      {

      size_t cc;

      for ( cc = 0; cc < gfiles.size(); cc ++ )

        {

        gfiles[cc] = gfiles[cc].substr(glen);

        //std::cout << "Glob file: " << gfiles[cc].c_str() << std::endl;

        files.push_back(gfiles[cc]);

        }

      }

    else

      {

      std::cerr << "Problem globbing" << std::endl;

      }

    }

  if ( this->CTestFileExists("DynamicAnalysis.xml") )

    {

    files.push_back("DynamicAnalysis.xml");

    }

  if ( this->CTestFileExists("Purify.xml") )

    {

    files.push_back("Purify.xml");

    }

  if ( this->CTestFileExists("Notes.xml") )

    {

    files.push_back("Notes.xml");

    }



  if ( ofs )

    {

    ofs << "Upload files:" << std::endl;

    int cnt = 0;

    cmCTest::tm_VectorOfStrings::iterator it;

    for ( it = files.begin(); it != files.end(); ++ it )

      {

      ofs << cnt << "\t" << it->c_str() << std::endl;

      cnt ++;

      }

    }

  std::cout << "Submit files (using " << m_DartConfiguration["DropMethod"] << ")"

    << std::endl;

  cmCTestSubmit submit;

  submit.SetVerbose(m_Verbose);

  submit.SetLogFile(&ofs);

  if ( m_DartConfiguration["DropMethod"] == "" ||

    m_DartConfiguration["DropMethod"] ==  "ftp" )

    {

    ofs << "Using drop method: FTP" << std::endl;

    std::cout << "  Using FTP submit method" << std::endl;

    std::string url = "ftp://";

    url += cmCTest::MakeURLSafe(m_DartConfiguration["DropSiteUser"]) + ":" + 

      cmCTest::MakeURLSafe(m_DartConfiguration["DropSitePassword"]) + "@" + 

      m_DartConfiguration["DropSite"] + 

      cmCTest::MakeURLSafe(m_DartConfiguration["DropLocation"]);

    if ( !submit.SubmitUsingFTP(m_ToplevelPath+"/Testing/"+m_CurrentTag, 

        files, prefix, url) )

      {

      std::cerr << "  Problems when submitting via FTP" << std::endl;

      ofs << "  Problems when submitting via FTP" << std::endl;

      return 0;

      }

    if ( !submit.TriggerUsingHTTP(files, prefix, m_DartConfiguration["TriggerSite"]) )

      {

      std::cerr << "  Problems when triggering via HTTP" << std::endl;

      ofs << "  Problems when triggering via HTTP" << std::endl;

      return 0;

      }

    std::cout << "  Submission successfull" << std::endl;

    ofs << "  Submission succesfull" << std::endl;

    return 1;

    }

  else if ( m_DartConfiguration["DropMethod"] == "http" )

    {

    ofs << "Using drop method: HTTP" << std::endl;

    std::cout << "  Using HTTP submit method" << std::endl;

    std::string url = "http://";

    if ( m_DartConfiguration["DropSiteUser"].size() > 0 )

      {

      url += m_DartConfiguration["DropSiteUser"];

      if ( m_DartConfiguration["DropSitePassword"].size() > 0 )

        {

        url += ":" + m_DartConfiguration["DropSitePassword"];

        }

      url += "@";

      }

    url += m_DartConfiguration["DropSite"] + m_DartConfiguration["DropLocation"];

    if ( !submit.SubmitUsingHTTP(m_ToplevelPath+"/Testing/"+m_CurrentTag, files, prefix, url) )

      {

      std::cerr << "  Problems when submitting via HTTP" << std::endl;

      ofs << "  Problems when submitting via HTTP" << std::endl;

      return 0;

      }

    if ( !submit.TriggerUsingHTTP(files, prefix, m_DartConfiguration["TriggerSite"]) )

      {

      std::cerr << "  Problems when triggering via HTTP" << std::endl;

      ofs << "  Problems when triggering via HTTP" << std::endl;

