}

//----------------------------------------------------------------------
bool cmCTestCoverageHandler::StartLogFile(cmGeneratedFileStream& covLogFile, int logFileCount)
{
  char covLogFilename[1024];
  sprintf(covLogFilename, "CoverageLog-%d.xml", logFileCount);
  std::cout << "Open file: " << covLogFilename << std::endl;
  if (!m_CTest->OpenOutputFile(m_CTest->GetCurrentTag(), 
      covLogFilename, covLogFile, true))
    {
    std::cerr << "Cannot open log file: " << covLogFilename << std::endl;
    return false;
