}



//----------------------------------------------------------------------

bool cmCTestCoverageHandler::StartCoverageLogFile(

  cmGeneratedFileStream& covLogFile, int logFileCount)

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

  return true;

}



//----------------------------------------------------------------------

void cmCTestCoverageHandler::EndCoverageLogFile(cmGeneratedFileStream& ostr,

  int logFileCount)

{

  std::string local_end_time = m_CTest->CurrentTime();

  ostr << "\t<EndDateTime>" << local_end_time << "</EndDateTime>" << std::endl

    << "</CoverageLog>" << std::endl;

  m_CTest->EndXML(ostr);

  char covLogFilename[1024];

  sprintf(covLogFilename, "CoverageLog-%d.xml", logFileCount);

  cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, "Close file: "

    << covLogFilename << std::endl);

  ostr.Close();

}



//----------------------------------------------------------------------

bool cmCTestCoverageHandler::ShouldIDoCoverage(const char* file,

  const char* srcDir,

  const char* binDir)

{

  std::vector<cmsys::RegularExpression>::iterator sit;

