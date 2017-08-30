{

  char covLogFilename[1024];

  sprintf(covLogFilename, "CoverageLog-%d", logFileCount);

  cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Open file: " << covLogFilename

    << std::endl);

  if (!this->StartResultingXML(covLogFilename, covLogFile) )

    {

    cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot open log file: "

      << covLogFilename << std::endl);

    return false;

    }

  std::string local_start_time = m_CTest->CurrentTime();

  m_CTest->StartXML(covLogFile);

  covLogFile << "<CoverageLog>" << std::endl

    << "\t<StartDateTime>" << local_start_time << "</StartDateTime>"

    << std::endl;

