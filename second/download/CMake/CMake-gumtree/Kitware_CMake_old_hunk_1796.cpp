    }
  if ( m_Tests[TEST_TEST] || m_Tests[ALL_TEST] || notest )
    {
    std::vector<std::string> passed;
    std::vector<std::string> failed;
    int total;

    this->ProcessDirectory(passed, failed);

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

    res += int(failed.size());
    }
  if ( m_Tests[COVERAGE_TEST] || m_Tests[ALL_TEST] )
    {