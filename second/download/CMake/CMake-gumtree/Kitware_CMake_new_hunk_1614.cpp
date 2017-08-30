    return false;

    }

  std::string local_start_time = m_CTest->CurrentTime();

  m_CTest->StartXML(covLogFile);

  covLogFile << "<CoverageLog>" << std::endl

    << "\t<StartDateTime>" << local_start_time << "</StartDateTime>" << std::endl;

  return true;

}



//----------------------------------------------------------------------

void cmCTestCoverageHandler::EndLogFile(std::ofstream& ostr, int logFileCount)

{

  std::string local_end_time = m_CTest->CurrentTime();

  ostr << "\t<EndDateTime>" << local_end_time << "</EndDateTime>" << std::endl

    << "</CoverageLog>" << std::endl;

  m_CTest->EndXML(ostr);

  char covLogFilename[1024];

  sprintf(covLogFilename, "CoverageLog-%d.xml", logFileCount);

  std::cout << "Close file: " << covLogFilename << std::endl;

