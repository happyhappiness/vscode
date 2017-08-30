{

  char covLogFilename[1024];

  sprintf(covLogFilename, "CoverageLog-%d", logFileCount);

  cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Open file: "

    << covLogFilename << std::endl, this->Quiet);

  if(!this->StartResultingXML(cmCTest::PartCoverage,

                              covLogFilename, covLogFile))

    {

