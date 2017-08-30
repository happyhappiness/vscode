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

