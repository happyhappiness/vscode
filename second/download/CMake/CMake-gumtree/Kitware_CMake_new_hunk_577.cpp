      << covLogFilename << std::endl);
    return false;
    }
  return true;
}

//----------------------------------------------------------------------
void cmCTestCoverageHandler::EndCoverageLogFile(cmGeneratedFileStream& ostr,
  int logFileCount)
{
  char covLogFilename[1024];
  sprintf(covLogFilename, "CoverageLog-%d.xml", logFileCount);
  cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Close file: "
