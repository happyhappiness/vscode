      {

      percent = 99;

      }

    cmCTestLog(m_CTest, HANDLER_OUTPUT, std::endl

      << static_cast<int>(percent + .5) << "% tests passed, "

      << failed.size() << " tests failed out of " << total << std::endl);

    //fprintf(stderr,"\n%.0f%% tests passed, %i tests failed out of %i\n",

    //  percent, int(failed.size()), total);



    if (failed.size())

      {

      cmGeneratedFileStream ofs;



      cmCTestLog(m_CTest, ERROR_MESSAGE, std::endl

        << "The following tests FAILED:" << std::endl);

      this->StartLogFile("TestsFailed", ofs);



      std::vector<cmCTestTestHandler::cmCTestTestResult>::iterator ftit;

