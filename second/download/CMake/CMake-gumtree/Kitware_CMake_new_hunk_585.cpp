  this->CTest->EndXML(ostr);
  char covLogFilename[1024];
  sprintf(covLogFilename, "CoverageLog-%d.xml", logFileCount);
  cmCTestOptionalLog(this->CTest, HANDLER_VERBOSE_OUTPUT, "Close file: "
    << covLogFilename << std::endl, this->Quiet);
  ostr.Close();
}

