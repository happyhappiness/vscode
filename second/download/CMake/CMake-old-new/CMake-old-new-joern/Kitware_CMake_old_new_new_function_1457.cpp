void cmCTest::Initialize()
{
  m_ToplevelPath = cmSystemTools::GetCurrentWorkingDirectory();
  // parse the dart test file
  std::ifstream fin("DartConfiguration.tcl");
  if(!fin)
    {
    return;
    }

  char buffer[1024];
  while ( fin )
    {
    buffer[0] = 0;
    fin.getline(buffer, 1023);
    buffer[1023] = 0;
    std::string line = ::CleanString(buffer);
    if(line.size() == 0)
      {
      continue;
      }
    while ( fin && (line[line.size()-1] == '\\') )
      {
      line = line.substr(0, line.size()-1);
      buffer[0] = 0;
      fin.getline(buffer, 1023);
      buffer[1023] = 0;
      line += ::CleanString(buffer);
      }
    if ( line[0] == '#' )
      {
      continue;
      }
    std::string::size_type cpos = line.find_first_of(":");
    if ( cpos == line.npos )
      {
      continue;
      }
    std::string key = line.substr(0, cpos);
    std::string value = ::CleanString(line.substr(cpos+1, line.npos));
    m_DartConfiguration[key] = value;
    }
  fin.close();
  if ( m_DartMode )
    {
    std::string testingDir = m_ToplevelPath + "/Testing/CDart";
    if ( cmSystemTools::FileExists(testingDir.c_str()) )
      {
      if ( !cmSystemTools::FileIsDirectory(testingDir.c_str()) )
        {
        std::cerr << "File " << testingDir << " is in the place of the testing directory"
                  << std::endl;
        return;
        }
      }
    else
      {
      if ( !cmSystemTools::MakeDirectory(testingDir.c_str()) )
        {
        std::cerr << "Cannot create directory " << testingDir
                  << std::endl;
        return;
        }
      }
    std::string tagfile = testingDir + "/TAG";
    std::ifstream tfin(tagfile.c_str());
    std::string tag;
    time_t tctime = time(0);
    struct tm *lctime = gmtime(&tctime);
    if ( tfin )
      {
      tfin >> tag;
      tfin.close();
      int year = 0;
      int mon = 0;
      int day = 0;
      int hour = 0;
      int min = 0;
      sscanf(tag.c_str(), "%04d%02d%02d-%02d%02d",
             &year, &mon, &day, &hour, &min);
      if ( year != lctime->tm_year + 1900 ||
           mon != lctime->tm_mon+1 ||
           day != lctime->tm_mday )
        {
        tag = "";
        }

      }
    if ( tag.size() == 0 )
      {
      char datestring[100];
      sprintf(datestring, "%04d%02d%02d-%02d%02d",
              lctime->tm_year + 1900,
              lctime->tm_mon+1,
              lctime->tm_mday,
              lctime->tm_hour,
              lctime->tm_min);
      tag = datestring;
      std::ofstream ofs(tagfile.c_str());
      if ( ofs )
        {
        ofs << tag << std::endl;
        }
      ofs.close();
      std::cout << "Create new tag: " << tag << std::endl;
      }
    m_CurrentTag = tag;
    }
}