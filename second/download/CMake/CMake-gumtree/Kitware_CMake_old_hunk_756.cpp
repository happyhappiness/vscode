  this->CTest->EndXML(ostr);

  char covLogFilename[1024];

  sprintf(covLogFilename, "CoverageLog-%d.xml", logFileCount);

  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Close file: "

    << covLogFilename << std::endl);

  ostr.Close();

}



