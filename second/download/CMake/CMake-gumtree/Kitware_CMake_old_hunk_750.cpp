      << covLogFilename << std::endl);

    return false;

    }

  std::string local_start_time = this->CTest->CurrentTime();

  this->CTest->StartXML(covLogFile, this->AppendXML);

  covLogFile << "<CoverageLog>" << std::endl

             << "\t<StartDateTime>" << local_start_time << "</StartDateTime>"

             << "\t<StartTime>"

             << static_cast<unsigned int>(cmSystemTools::GetTime())

             << "</StartTime>"

    << std::endl;

  return true;

}



//----------------------------------------------------------------------

void cmCTestCoverageHandler::EndCoverageLogFile(cmGeneratedFileStream& ostr,

  int logFileCount)

{

  std::string local_end_time = this->CTest->CurrentTime();

  ostr << "\t<EndDateTime>" << local_end_time << "</EndDateTime>" << std::endl

       << "\t<EndTime>" <<

       static_cast<unsigned int>(cmSystemTools::GetTime())

       << "</EndTime>" << std::endl

    << "</CoverageLog>" << std::endl;

  this->CTest->EndXML(ostr);

  char covLogFilename[1024];

  sprintf(covLogFilename, "CoverageLog-%d.xml", logFileCount);

  cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Close file: "

