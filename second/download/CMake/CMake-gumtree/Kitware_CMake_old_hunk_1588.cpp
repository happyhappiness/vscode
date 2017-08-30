  m_CTest->EndXML(ostr);
  char covLogFilename[1024];
  sprintf(covLogFilename, "CoverageLog-%d.xml", logFileCount);
  std::cout << "Close file: " << covLogFilename << std::endl;
  ostr.close();
}

//----------------------------------------------------------------------
bool cmCTestCoverageHandler::ShouldIDoCoverage(const char* file, const char* srcDir,
  const char* binDir, bool verbose)
{
  std::string fSrcDir = cmSystemTools::CollapseFullPath(srcDir);
  std::string fBinDir = cmSystemTools::CollapseFullPath(binDir);
