int cmCTest::UpdateDirectory()
{
  int count = 0;
  std::string::size_type cc, kk;
  std::string cvsCommand = m_DartConfiguration["CVSCommand"];
  if ( cvsCommand.size() == 0 )
    {
    std::cerr << "Cannot find CVSCommand key in the DartConfiguration.tcl" << std::endl;
    return -1;
    }
  std::string cvsOptions = m_DartConfiguration["CVSUpdateOptions"];
  if ( cvsOptions.size() == 0 )
    {
    std::cerr << "Cannot find CVSUpdateOptions key in the DartConfiguration.tcl" << std::endl;
    return -1;
    }

  std::string sourceDirectory = m_DartConfiguration["SourceDirectory"];
  if ( sourceDirectory.size() == 0 )
    {
    std::cerr << "Cannot find SourceDirectory  key in the DartConfiguration.tcl" << std::endl;
    return -1;
    }

  std::string extra_update_opts;
  if ( m_TestModel == cmCTest::NIGHTLY )
    {
    struct tm* t = ::GetNightlyTime(m_DartConfiguration["NightlyStartTime"],
      m_Verbose,
      m_TomorrowTag);
    char current_time[1024];
    sprintf(current_time, "%04d-%02d-%02d %02d:%02d:%02d UTC",
      t->tm_year + 1900,
      t->tm_mon + 1,
      t->tm_mday,
      t->tm_hour,
      t->tm_min,
      t->tm_sec);
    std::string today_update_date = current_time;
   
    extra_update_opts += "-D \"" + today_update_date +"\"";
    //std::cout << "Update: " << extra_update_opts << std::endl;
    }

  std::string command = cvsCommand + " -z3 update " + cvsOptions +
    " " + extra_update_opts;
  std::ofstream os; 
  if ( !this->OpenOutputFile(m_CurrentTag, "Update.xml", os) )
    {
    std::cerr << "Cannot open log file" << std::endl;
    }
  std::string start_time = this->CurrentTime();
  double elapsed_time_start = cmSystemTools::GetTime();

  std::string goutput;
  int retVal = 0;
  bool res = true;
  std::ofstream ofs;
  if ( !m_ShowOnly )
    {
    res = cmSystemTools::RunSingleCommand(command.c_str(), &goutput, 
      &retVal, sourceDirectory.c_str(),
      m_Verbose, 0 /*m_TimeOut*/);
    if ( this->OpenOutputFile("Temporary", "LastUpdate.log", ofs) )
      {
      ofs << goutput << std::endl;; 
      }
    }
  else
    {
    std::cout << "Update with command: " << command << std::endl;
    }

  os << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
     << "<Update mode=\"Client\" Generator=\"ctest-" << CMake_VERSION_FULL << "\">\n"
     << "\t<Site>" << m_DartConfiguration["Site"] << "</Site>\n"
     << "\t<BuildName>" << m_DartConfiguration["BuildName"]
     << "</BuildName>\n"
     << "\t<BuildStamp>" << m_CurrentTag << "-"
     << this->GetTestModelString() << "</BuildStamp>" << std::endl;
  os << "\t<StartDateTime>" << start_time << "</StartDateTime>\n"
     << "\t<UpdateCommand>" << this->MakeXMLSafe(command)
     << "</UpdateCommand>\n"
     << "\t<UpdateReturnStatus>";
  int failed = 0;
  if ( !res || retVal )
    {
    os << "Update error: ";
    os << this->MakeXMLSafe(goutput);
    std::cerr << "Update with command: " << command << " failed" << std::endl;
    failed = 1;
    }
  os << "</UpdateReturnStatus>" << std::endl;
  if ( !failed )
    {

    std::vector<cmStdString> lines;
    cmSystemTools::Split(goutput.c_str(), lines);
    std::cout << "Updated; gathering version information" << std::endl;
    cmsys::RegularExpression date_author("^date: +([^;]+); +author: +([^;]+); +state: +[^;]+;");
    cmsys::RegularExpression revision("^revision +([^ ]*) *$");
    cmsys::RegularExpression end_of_file("^=============================================================================$");
    cmsys::RegularExpression end_of_comment("^----------------------------$");
    std::string current_path = "<no-path>";
    bool first_file = true;

    cmCTest::AuthorsToUpdatesMap authors_files_map;
    int num_updated = 0;
    int num_modified = 0;
    int num_conflicting = 0;
    for ( cc= 0 ; cc < lines.size(); cc ++ )
      {
      const char* line = lines[cc].c_str();
      char mod = line[0];
      if ( line[1] == ' ' && mod != '?' )
        {
        if ( mod != 'M' && mod != 'C' )
          {
          count ++;
          }
        const char* file = line + 2;
        //std::cout << "Line" << cc << ": " << mod << " - " << file << std::endl;
        std::string logcommand = cvsCommand + " -z3 log -N " + file;
        //std::cout << "Do log: " << logcommand << std::endl;
        std::string output;
        res = cmSystemTools::RunSingleCommand(logcommand.c_str(), &output, 
          &retVal, sourceDirectory.c_str(),
          m_Verbose, 0 /*m_TimeOut*/);
        if ( ofs )
          {
          ofs << output << std::endl;
          }
        if ( res && retVal == 0)
          {
          //std::cout << output << std::endl;
          std::vector<cmStdString> ulines;
          cmSystemTools::Split(output.c_str(), ulines);
          std::string::size_type sline = 0;
          std::string srevision1 = "Unknown";
          std::string sdate1     = "Unknown";
          std::string sauthor1   = "Unknown";
          std::string semail1    = "Unknown";
          std::string comment1   = "";
          std::string srevision2 = "Unknown";
          std::string sdate2     = "Unknown";
          std::string sauthor2   = "Unknown";
          std::string comment2   = "";
          std::string semail2    = "Unknown";
          bool have_first = false;
          bool have_second = false;
          for ( kk = 0; kk < ulines.size(); kk ++ )
            {
            const char* clp = ulines[kk].c_str();
            if ( !have_second && !sline && revision.find(clp) )
              {
              if ( !have_first )
                {
                srevision1 = revision.match(1);
                }
              else
                {
                srevision2 = revision.match(1);
                }
              }
            else if ( !have_second && !sline && date_author.find(clp) )
              {
              sline = kk + 1;
              if ( !have_first )
                {
                sdate1 = date_author.match(1);
                sauthor1 = date_author.match(2);
                }
              else
                {
                sdate2 = date_author.match(1);
                sauthor2 = date_author.match(2);
                }
              }
            else if ( sline && end_of_comment.find(clp) || end_of_file.find(clp))
              {
              if ( !have_first )
                {
                have_first = true;
                }
              else if ( !have_second )
                {
                have_second = true;
                }
              sline = 0;
              }
            else if ( sline )
              {
              if ( !have_first )
                {
                comment1 += clp;
                comment1 += "\n";
                }
              else
                {
                comment2 += clp;
                comment2 += "\n";
                }
              }
            }
          if ( mod == 'M' )
            {
            comment1 = "Locally modified file\n";
            }
          if ( mod == 'C' )
            {
            comment1 = "Conflict while updating\n";
            }
          std::string path = cmSystemTools::GetFilenamePath(file);
          std::string fname = cmSystemTools::GetFilenameName(file);
          if ( path != current_path )
            {
            if ( !first_file )
              {
              os << "\t</Directory>" << std::endl;
              }
            else
              {
              first_file = false;
              }
            os << "\t<Directory>\n"
              << "\t\t<Name>" << path << "</Name>" << std::endl;
            }
          if ( mod == 'C' )
            {
            num_conflicting ++;
            os << "\t<Conflicting>" << std::endl;
            }
          else if ( mod == 'M' )
            {
            num_modified ++;
            os << "\t<Modified>" << std::endl;
            }
          else
            {
            num_updated ++;
            os << "\t<Updated>" << std::endl;
            }
          if ( srevision2 == "Unknown" )
            {
            srevision2 = srevision1;
            }
          os << "\t\t<File Directory=\"" << path << "\">" << fname 
            << "</File>\n"
            << "\t\t<Directory>" << path << "</Directory>\n"
            << "\t\t<FullName>" << file << "</FullName>\n"
            << "\t\t<CheckinDate>" << sdate1 << "</CheckinDate>\n"
            << "\t\t<Author>" << sauthor1 << "</Author>\n"
            << "\t\t<Email>" << semail1 << "</Email>\n"
            << "\t\t<Log>" << this->MakeXMLSafe(comment1) << "</Log>\n"
            << "\t\t<Revision>" << srevision1 << "</Revision>\n"
            << "\t\t<PriorRevision>" << srevision2 << "</PriorRevision>"
            << std::endl;
          if ( srevision2 != srevision1 )
            {
            os
              << "\t\t<Revisions>\n"
              << "\t\t\t<Revision>" << srevision1 << "</Revision>\n"
              << "\t\t\t<PreviousRevision>" << srevision2 << "</PreviousRevision>\n"
              << "\t\t\t<Author>" << sauthor1<< "</Author>\n"
              << "\t\t\t<Date>" << sdate1 << "</Date>\n"
              << "\t\t\t<Comment>" << this->MakeXMLSafe(comment1) << "</Comment>\n"
              << "\t\t\t<Email>" << semail1 << "</Email>\n"
              << "\t\t</Revisions>\n"
              << "\t\t<Revisions>\n"
              << "\t\t\t<Revision>" << srevision2 << "</Revision>\n"
              << "\t\t\t<PreviousRevision>" << srevision2 << "</PreviousRevision>\n"
              << "\t\t\t<Author>" << sauthor2<< "</Author>\n"
              << "\t\t\t<Date>" << sdate2 << "</Date>\n"
              << "\t\t\t<Comment>" << this->MakeXMLSafe(comment2) << "</Comment>\n"
              << "\t\t\t<Email>" << semail2 << "</Email>\n"
              << "\t\t</Revisions>" << std::endl;
            }
          if ( mod == 'C' )
            {
            os << "\t</Conflicting>" << std::endl;
            }
          else if ( mod == 'M' )
            {
            os << "\t</Modified>" << std::endl;
            }
          else
            {
            os << "\t</Updated>" << std::endl;
            }
          cmCTest::UpdateFiles *u = &authors_files_map[sauthor1];
          cmCTest::StringPair p;
          p.first = path;
          p.second = fname;
          u->push_back(p);

          current_path = path;
          }
        }
      }
    if ( num_updated )
      {
      std::cout << "Found " << num_updated << " updated files" << std::endl;
      }
    if ( num_modified )
      {
      std::cout << "Found " << num_modified << " locally modified files" 
        << std::endl;
      }
    if ( num_conflicting )
      {
      std::cout << "Found " << num_conflicting << " conflicting files" 
        << std::endl;
      }
    if ( !first_file )
      {
      os << "\t</Directory>" << std::endl;
      }

    cmCTest::AuthorsToUpdatesMap::iterator it;
    for ( it = authors_files_map.begin();
      it != authors_files_map.end();
      it ++ )
      {
      os << "\t<Author>\n"
        << "\t\t<Name>" << it->first << "</Name>" << std::endl;
      cmCTest::UpdateFiles *u = &(it->second);
      for ( cc = 0; cc < u->size(); cc ++ )
        {
        os << "\t\t<File Directory=\"" << (*u)[cc].first << "\">"
          << (*u)[cc].second << "</File>" << std::endl;
        }
      os << "\t</Author>" << std::endl;
      }
    }

  //std::cout << "End" << std::endl;
  std::string end_time = this->CurrentTime();
  os << "\t<EndDateTime>" << end_time << "</EndDateTime>\n"
     << "<ElapsedMinutes>" << 
    static_cast<int>((cmSystemTools::GetTime() - elapsed_time_start)/6)/10.0 
     << "</ElapsedMinutes>"
     << "</Update>" << std::endl;
  
  if ( ofs )
    {
    ofs.close();
    }

  if (! res || retVal )
    {
    std::cerr << "Error(s) when updating the project" << std::endl;
    std::cerr << "Output: " << goutput << std::endl;
    return -1;
    }
  return count;
}