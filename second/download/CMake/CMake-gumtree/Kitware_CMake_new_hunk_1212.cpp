void cmCTestCoverageHandler::EndCoverageLogFile(cmGeneratedFileStream& ostr,
  int logFileCount)
{
  std::string local_end_time = this->CTest->CurrentTime();
  ostr << "\t<EndDateTime>" << local_end_time << "</EndDateTime>" << std::endl
    << "</CoverageLog>" << std::endl;
  this->CTest->EndXML(ostr);
  char covLogFilename[1024];
  sprintf(covLogFilename, "CoverageLog-%d.xml", logFileCount);
  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Close file: "
    << covLogFilename << std::endl);
  ostr.Close();
}
