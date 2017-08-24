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