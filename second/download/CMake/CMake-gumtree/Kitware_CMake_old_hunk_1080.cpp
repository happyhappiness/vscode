      {
      percent = 99;
      }
    cmCTestLog(this->CTest, HANDLER_OUTPUT, std::endl
      << static_cast<int>(percent + .5) << "% tests passed, "
      << failed.size() << " tests failed out of " << total << std::endl);
    //fprintf(stderr,"\n%.0f%% tests passed, %i tests failed out of %i\n",
    //  percent, int(failed.size()), total);

    if (failed.size())
      {
      cmGeneratedFileStream ofs;

      cmCTestLog(this->CTest, ERROR_MESSAGE, std::endl
        << "The following tests FAILED:" << std::endl);
      this->StartLogFile("TestsFailed", ofs);

      std::vector<cmCTestTestHandler::cmCTestTestResult>::iterator ftit;
      for(ftit = this->TestResults.begin();
        ftit != this->TestResults.end(); ++ftit)
        {
        if ( ftit->Status != cmCTestTestHandler::COMPLETED )
          {
          ofs << ftit->TestCount << ":" << ftit->Name << std::endl;
          cmCTestLog(this->CTest, HANDLER_OUTPUT, "\t" << std::setw(3)
            << ftit->TestCount << " - " << ftit->Name.c_str() << " ("
            << this->GetTestStatus(ftit->Status) << ")" << std::endl);
          }
        }

      }
    }

