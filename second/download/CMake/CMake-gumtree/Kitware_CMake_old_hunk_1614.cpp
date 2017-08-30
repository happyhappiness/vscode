    return false;
    }
  std::string local_start_time = m_CTest->CurrentTime();
  covLogFile << "<CoverageLog>" << std::endl
    << "\t<StartDateTime>" << local_start_time << "</StartDateTime>" << std::endl;
  return true;
}

//----------------------------------------------------------------------
void cmCTestCoverageHandler::StopLogFile(std::ofstream& ostr, int logFileCount)
{
  std::string local_end_time = m_CTest->CurrentTime();
  ostr << "\t<EndDateTime>" << local_end_time << "</EndDateTime>" << std::endl
    << "</CoverageLog>" << std::endl;
  char covLogFilename[1024];
  sprintf(covLogFilename, "CoverageLog-%d.xml", logFileCount);
  std::cout << "Close file: " << covLogFilename << std::endl;
