int cmCTestScriptHandler::PerformExtraUpdates()
{
  std::string command;
  std::string output;
  int retVal;
  bool res; 

  // do an initial cvs update as required
  command = m_CVSCmd;
  char updateVar[40];
  int i;
  for (i = 1; i < 10; ++i)
    {
    sprintf(updateVar,"CTEST_EXTRA_UPDATES_%i",i);
    const char *updateVal = m_Makefile->GetDefinition(updateVar);
    if (updateVal)
      {
      if (m_CVSCmd.empty())
        {
        cmSystemTools::Error(updateVar, " specified without specifying CTEST_CVS_COMMAND.");
        this->RestoreBackupDirectories();
        return 12;
        }
      std::vector<std::string> cvsArgs;
      cmSystemTools::ExpandListArgument(updateVal,cvsArgs);
      if (cvsArgs.size() == 2)
        {
        std::string fullCommand = command;
        fullCommand += " update ";
        fullCommand += cvsArgs[1];
        output = "";
        retVal = 0;
        if ( m_Verbose )
          {
          std::cerr << "Run CVS: " << fullCommand.c_str() << std::endl;
          }
        res = cmSystemTools::RunSingleCommand(fullCommand.c_str(), &output, 
          &retVal, cvsArgs[0].c_str(),
          m_Verbose, 0 /*m_TimeOut*/);
        if (!res || retVal != 0)
          {
          cmSystemTools::Error("Unable to perform extra cvs updates:\n", 
            output.c_str());
          this->RestoreBackupDirectories();
          return 8;
          }
        }
      }
    }
  return 0;
}