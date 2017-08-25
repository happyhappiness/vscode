{
  char covLogFilename[1024];
  sprintf(covLogFilename, "CoverageLog-%d.xml", logFileCount);
  cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Open file: " << covLogFilename << std::endl);
  if (!m_CTest->OpenOutputFile(m_CTest->GetCurrentTag(), 
      covLogFilename, covLogFile, true))
    {
    cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot open log file: " << covLogFilename << std::endl);
    return false;
    }
  std::string local_start_time = m_CTest->CurrentTime();
  m_CTest->StartXML(covLogFile);
  covLogFile << "<CoverageLog>" << std::endl
    << "\t<StartDateTime>" << local_start_time << "</StartDateTime>" << std::endl;
  return true;
}