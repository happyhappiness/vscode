//----------------------------------------------------------------------
void cmCTestCoverageHandler::Initialize()
{
  this->Superclass::Initialize();
}

//----------------------------------------------------------------------
bool cmCTestCoverageHandler::StartCoverageLogFile(cmGeneratedFileStream& covLogFile, int logFileCount)
{
  char covLogFilename[1024];
  sprintf(covLogFilename, "CoverageLog-%d", logFileCount);
  cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Open file: " << covLogFilename << std::endl);
  if (!this->StartResultingXML(covLogFilename, covLogFile) )
    {
    cmCTestLog(m_CTest, ERROR_MESSAGE, "Cannot open log file: " << covLogFilename << std::endl);
    return false;
