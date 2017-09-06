int cmCTest::CoverageDirectory()
{
  std::cout << "Performing coverage" << std::endl;
  std::vector<std::string> files;
  std::vector<std::string> cfiles;
  std::vector<std::string> cdirs;
  bool done = false;
  std::string::size_type cc;
  std::string glob;
  std::map<std::string, std::string> allsourcefiles;
  std::map<std::string, std::string> allbinaryfiles;

  std::string start_time = ::CurrentTime();

  // Find all source files.
  std::string sourceDirectory = m_DartConfiguration["SourceDirectory"];
  if ( sourceDirectory.size() == 0 )
    {
    std::cerr << "Cannot find SourceDirectory  key in the DartConfiguration.tcl" << std::endl;
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
    std::cout << "Cannot find any coverage information files (.da)" << std::endl;
    return 1;
    }

  std::ofstream log; 
  if (!this->OpenOutputFile("Temporary", "Coverage.log", log))
    {
    std::cout << "Cannot open log file" << std::endl;
    return 1;
    }
  log.close();
  if (!this->OpenOutputFile(m_CurrentTag, "Coverage.xml", log))
    {
    std::cout << "Cannot open log file" << std::endl;
    return 1;
    }

  std::string opath = m_ToplevelPath + "/Testing/Temporary/Coverage";
  cmSystemTools::MakeDirectory(opath.c_str());
  
  for ( cc = 0; cc < files.size(); cc ++ )
    {
    std::string command = "gcov -l \"" + files[cc] + "\"";
    std::string output;
    int retVal = 0;
    //std::cout << "Run gcov on " << files[cc] << std::flush;
    //std::cout << "   --- Run [" << command << "]" << std::endl;
    bool res = true;
    if ( !m_ShowOnly )
      {
      res = cmSystemTools::RunCommand(command.c_str(), output, 
                                      retVal, opath.c_str(),
                                      m_Verbose);
      }
    if ( res && retVal == 0 )
      {
      //std::cout << " - done" << std::endl;
      }
    else
      {
      //std::cout << " - fail" << std::endl;
      }
    }
  
  files.clear();
  glob = opath + "/*";
  if ( !cmSystemTools::SimpleGlob(glob, cfiles, 1) )
    {
    std::cout << "Cannot found any coverage files" << std::endl;
    return 1;
    }
  std::map<std::string, std::vector<std::string> > sourcefiles;
  for ( cc = 0; cc < cfiles.size(); cc ++ )
    {
    std::string& fname = cfiles[cc];
    //std::cout << "File: " << fname << std::endl;
    if ( strcmp(fname.substr(fname.size()-5, 5).c_str(), ".gcov") == 0 )
      {
      files.push_back(fname);
      std::string::size_type pos = fname.find(".da.");
      if ( pos != fname.npos )
        {
        pos += 4;
        std::string::size_type epos = fname.size() - pos - strlen(".gcov");
        std::string nf = fname.substr(pos, epos);
        //std::cout << "Substring: " << nf << std::endl;
        if ( allsourcefiles.find(nf) != allsourcefiles.end() || 
             allbinaryfiles.find(nf) != allbinaryfiles.end() )
          {
          std::vector<std::string> &cvec = sourcefiles[nf];
          cvec.push_back(fname);
          }
        }
      }
    }
  for ( cc = 0; cc < files.size(); cc ++ )
    {
    //std::cout << "File: " << files[cc] << std::endl;
    }

  std::map<std::string, std::vector<std::string> >::iterator it;
  cmCTest::tm_CoverageMap coverageresults;

  log << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
      << "<Site BuildName=\"" << m_DartConfiguration["BuildName"]
      << "\" BuildStamp=\"" << m_CurrentTag << "-"
      << this->GetTestModelString() << "\" Name=\""
      << m_DartConfiguration["Site"] << "\">\n"
      << "<Coverage>\n"
      << "\t<StartDateTime>" << start_time << "</StartDateTime>" << std::endl;

  int total_tested = 0;
  int total_untested = 0;

  for ( it = sourcefiles.begin(); it != sourcefiles.end(); it ++ )
    {
    //std::cerr << "Source file: " << it->first << std::endl;
    std::vector<std::string> &gfiles = it->second;
    for ( cc = 0; cc < gfiles.size(); cc ++ )
      {
      //std::cout << "\t" << gfiles[cc] << std::endl;
      std::ifstream ifile(gfiles[cc].c_str());
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
        std::string src_dir = m_DartConfiguration["SourceDirectory"];
        std::string::size_type spos = cov.m_FullPath.find(src_dir);
        if ( spos == 0 )
          {
          cov.m_FullPath = std::string(".") + cov.m_FullPath.substr(src_dir.size());
          }
        else
          {
          std::cerr << "Compare -- " << cov.m_FullPath << std::endl;
          std::cerr << "        -- " << src_dir << std::endl;
          }
        }
      for ( cc = 0; cc < lines.size(); cc ++ )
        {
        std::string& line = lines[cc];
        std::string sub = line.substr(0, strlen("      ######"));
        int count = atoi(sub.c_str());
        if ( sub.compare("      ######") == 0 )
          {
          if ( covlines[cc] == -1 )
            {
            covlines[cc] = 0;
            }
          cov.m_UnTested ++;
          //std::cout << "Untested - ";
          }
        else if ( count > 0 )
          {
          if ( covlines[cc] == -1 )
            {
            covlines[cc] = 0;
            }
          cov.m_Tested ++;
          covlines[cc] += count;
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
  std::string local_start_time = ::CurrentTime();
  std::string local_end_time;
  for ( cit = coverageresults.begin(); cit != coverageresults.end(); cit ++ )
    {
    if ( ccount == 100 )
      {
      local_end_time = ::CurrentTime();
      cfileoutput << "\t<EndDateTime>" << local_end_time << "</EndDateTime>\n"
        << "</CoverageLog>\n"
        << "</Site>" << std::endl;
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
        std::cout << "Cannot open log file: " << cfileoutputname << std::endl;
        return 1;
        }
      local_start_time = ::CurrentTime();
      cfileoutput << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        << "<Site BuildName=\"" << m_DartConfiguration["BuildName"]
        << "\" BuildStamp=\"" << m_CurrentTag << "-"
        << this->GetTestModelString() << "\" Site=\""
        << m_DartConfiguration["Site"] << "\">\n"
        << "<CoverageLog>\n"
        << "\t<StartDateTime>" << local_start_time << "</StartDateTime>" << std::endl;
      }

    //std::cerr << "Final process of Source file: " << cit->first << std::endl;
    cmCTest::cmCTestCoverage &cov = cit->second;


    std::ifstream ifile(cov.m_FullPath.c_str());
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
      << cov.m_FullPath << std::endl << "\">\n"
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
    if ( total_tested + total_untested > 0 )
      {
      cper = (100 * static_cast<float>(cov.m_Tested)/
        static_cast<float>(cov.m_Tested + cov.m_UnTested));
      cmet = ( static_cast<float>(cov.m_Tested + 10) /
        static_cast<float>(cov.m_Tested + cov.m_UnTested + 10));
      }
    log << "\t<File Name=\"" << cit->first << "\" FullPath=\"" << cov.m_FullPath
      << "\" Covered=\"" << (cmet>0?"true":"false") << "\">\n"
      << "\t\t<LOCTested>" << cov.m_Tested << "</LOCTested>\n"
      << "\t\t<LOCUnTested>" << cov.m_UnTested << "</LOCUnTested>\n"
      << "\t\t<PercentCoverage>" << cper << "</PercentCoverage>\n"
      << "\t\t<CoverageMetric>" << cmet << "</CoverageMetric>\n"
      << "\t</File>" << std::endl;
    ccount ++;
    }
  
  if ( ccount > 0 )
    {
    local_end_time = ::CurrentTime();
    cfileoutput << "\t<EndDateTime>" << local_end_time << "</EndDateTime>\n"
                << "</CoverageLog>\n"
                << "</Site>" << std::endl;
    cfileoutput.close();
    }

  int total_lines = total_tested + total_untested;
  float percent_coverage = 100 * static_cast<float>(total_tested) / 
    static_cast<float>(total_lines);
  if ( total_lines == 0 )
    {
    percent_coverage = 0;
    }

  std::string end_time = ::CurrentTime();

  log << "\t<LOCTested>" << total_tested << "</LOCTested>\n"
      << "\t<LOCUntested>" << total_untested << "</LOCUntested>\n"
      << "\t<LOC>" << total_lines << "</LOC>\n"
      << "\t<PercentCoverage>" << percent_coverage << "</PercentCoverage>\n"
      << "\t<EndDateTime>" << end_time << "</EndDateTime>\n"
      << "</Coverage>\n"
      << "</Site>" << std::endl;

  std::cout << "\tCovered LOC:         " << total_tested << std::endl
            << "\tNot covered LOC:     " << total_untested << std::endl
            << "\tTotal LOC:           " << total_lines << std::endl
            << "\tPercentage Coverage: " << percent_coverage << "%" << std::endl;


  return 1;
}