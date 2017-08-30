{

  char covLogFilename[1024];

  sprintf(covLogFilename, "CoverageLog-%d", logFileCount);

  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Open file: "

    << covLogFilename << std::endl);

  if(!this->StartResultingXML(cmCTest::PartCoverage,

                              covLogFilename, covLogFile))

    {

