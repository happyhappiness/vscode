int ctest::ProcessTests()
{
  int res = 0;
  bool notest = true;
  int cc;

  for ( cc = 0; cc < LAST_TEST; cc ++ )
    {
    if ( m_Tests[cc] )
      {
      notest = false;
      break;
      }
    }
  if ( m_Tests[UPDATE_TEST] || m_Tests[ALL_TEST] )
    {
    this->UpdateDirectory();
    }
  if ( m_Tests[CONFIGURE_TEST] || m_Tests[ALL_TEST] )
    {
    this->ConfigureDirectory();
    }
  if ( m_Tests[BUILD_TEST] || m_Tests[ALL_TEST] )
    {
    this->BuildDirectory();
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
    std::cerr << "Coverage test is not yet implemented" << std::endl;
    }
  if ( m_Tests[PURIFY_TEST] || m_Tests[ALL_TEST] )
    {
    std::cerr << "Purify test is not yet implemented" << std::endl;
    }
  return res;
}