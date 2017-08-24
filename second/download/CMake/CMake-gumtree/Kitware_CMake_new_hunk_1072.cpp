  sprintf(covLogFilename, "CoverageLog-%d", logFileCount);
  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Open file: "
    << covLogFilename << std::endl);
  if(!this->StartResultingXML(cmCTest::PartCoverage,
                              covLogFilename, covLogFile))
    {
    cmCTestLog(this->CTest, ERROR_MESSAGE, "Cannot open log file: "
      << covLogFilename << std::endl);
