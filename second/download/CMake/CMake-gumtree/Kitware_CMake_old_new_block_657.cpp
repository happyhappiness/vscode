{
    if (m_Verbose && passed.size() && 
      (m_UseIncludeRegExp || m_UseExcludeRegExp)) 
      {
      std::cerr << "\nThe following tests passed:\n";
      for(std::vector<cmStdString>::iterator j = passed.begin();
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
      cmGeneratedFileStream ofs;

      std::cerr << "\nThe following tests FAILED:\n";
      m_CTest->OpenOutputFile("Temporary", "LastTestsFailed.log", ofs);

      std::vector<cmCTestTestHandler::cmCTestTestResult>::iterator ftit;
      for(ftit = m_TestResults.begin();
        ftit != m_TestResults.end(); ++ftit)
        {
        if ( ftit->m_Status != cmCTestTestHandler::COMPLETED )
          {
          ofs << ftit->m_TestCount << ":" << ftit->m_Name << std::endl;
          fprintf(stderr, "\t%3d - %s (%s)\n", ftit->m_TestCount, ftit->m_Name.c_str(),
            this->GetTestStatus(ftit->m_Status));
          }
        }

      }
    }