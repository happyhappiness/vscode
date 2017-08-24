      {
      percent = 99;
      }
    cmCTestLog(m_CTest, HANDLER_OUTPUT, std::endl << std::setprecision(0) << percent << "% tests passed, "
      << failed.size() << " tests failed out of " << total << std::endl);
    //fprintf(stderr,"\n%.0f%% tests passed, %i tests failed out of %i\n",
    //  percent, int(failed.size()), total);

    if (failed.size()) 
      {
      cmGeneratedFileStream ofs;

      cmCTestLog(m_CTest, ERROR, std::endl << "The following tests FAILED:" << std::endl);
      m_CTest->OpenOutputFile("Temporary", "LastTestsFailed.log", ofs);

      std::vector<cmCTestTestHandler::cmCTestTestResult>::iterator ftit;
