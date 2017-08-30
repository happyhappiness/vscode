    }
}

int ctest::TestDirectory()
{
  std::vector<std::string> passed;
  std::vector<std::string> failed;
  int total;

  m_StartTest = ::CurrentTime();
  this->ProcessDirectory(passed, failed);
  m_EndTest = ::CurrentTime();

  total = int(passed.size()) + int(failed.size());

  if (total == 0)
    {
    std::cerr << "No tests were found!!!\n";
    }
  else
    {
    if (passed.size() && (m_UseIncludeRegExp || m_UseExcludeRegExp)) 
      {
      std::cerr << "\nThe following tests passed:\n";
      for(std::vector<std::string>::iterator j = passed.begin();
          j != passed.end(); ++j)
        {   
        std::cerr << "\t" << *j << "\n";
        }
      }

    float percent = float(passed.size()) * 100.0f / total;
    fprintf(stderr,"\n%.0f%% tests passed, %i tests failed out of %i\n",
            percent, int(failed.size()), total);

    if (failed.size()) 
      {
      std::cerr << "\nThe following tests FAILED:\n";
      for(std::vector<std::string>::iterator j = failed.begin();
          j != failed.end(); ++j)
        {   
        std::cerr << "\t" << *j << "\n";
        }
      }
    }

  if ( m_DartMode )
    {
    std::string testingDir = m_ToplevelPath + "/Testing/CDart";
    if ( cmSystemTools::FileExists(testingDir.c_str()) )
      {
      if ( !cmSystemTools::FileIsDirectory(testingDir.c_str()) )
        {
        std::cerr << "File " << testingDir << " is in the place of the testing directory"
                  << std::endl;
        return 1;
        }
      }
    else
      {
      if ( !cmSystemTools::MakeDirectory(testingDir.c_str()) )
        {
        std::cerr << "Cannot create directory " << testingDir
                  << std::endl;
        return 1;
        }
      }
    std::string testxml = testingDir + "/Test.xml";
    std::ofstream ofs(testxml.c_str());
    if( !ofs )
      {
      std::cerr << "Cannot create testing XML file" << std::endl;
      return 1;
      }
    this->GenerateDartOutput(ofs);
    }

  return int(failed.size());
}

void ctest::GenerateDartOutput(std::ostream& os)
{
  if ( !m_DartMode )
