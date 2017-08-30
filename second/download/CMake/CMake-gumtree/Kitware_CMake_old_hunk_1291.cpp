               << static_cast<int>(percent + .5) << "% tests passed, "
               << failed.size() << " tests failed out of " 
               << total << std::endl); 
    double totalTestTime = 0;

    for(cmCTestTestHandler::TestResultsVector::size_type cc = 0;
        cc < this->TestResults.size(); cc ++ )
      {
      cmCTestTestResult *result = &this->TestResults[cc];
      totalTestTime += result->ExecutionTime;
      }
    
    char realBuf[1024];
    sprintf(realBuf, "%6.2f sec", (double)(clock_finish - clock_start));
    cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nTotal Test time (real) = "
               << realBuf << "\n" );

    char totalBuf[1024];
    sprintf(totalBuf, "%6.2f sec", totalTestTime); 
    cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nTotal Test time (parallel) = "
               <<  totalBuf << "\n" );

    if (failed.size())
      {
      cmGeneratedFileStream ofs;
