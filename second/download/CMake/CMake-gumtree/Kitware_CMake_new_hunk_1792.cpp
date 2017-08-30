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
           mon != lctime->tm_mon ||
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
              lctime->tm_mon,
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

bool ctest::SetTest(const char* ttype)
