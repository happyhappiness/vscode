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
