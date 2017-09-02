bool cmQtAutomoc::GenerateMoc(const std::string& sourceFile,
                              const std::string& mocFileName)
{
  const std::string mocFilePath = this->Builddir + mocFileName;
  int sourceNewerThanMoc = 0;
  bool success = cmsys::SystemTools::FileTimeCompare(sourceFile.c_str(),
                                                     mocFilePath.c_str(),
                                                     &sourceNewerThanMoc);
  if (this->GenerateAll || !success || sourceNewerThanMoc >= 0)
    {
    // make sure the directory for the resulting moc file exists
    std::string mocDir = mocFilePath.substr(0, mocFilePath.rfind('/'));
    if (!cmsys::SystemTools::FileExists(mocDir.c_str(), false))
      {
      cmsys::SystemTools::MakeDirectory(mocDir.c_str());
      }

    std::string msg = "Generating ";
    msg += mocFileName;
    cmSystemTools::MakefileColorEcho(cmsysTerminal_Color_ForegroundBlue
                                           |cmsysTerminal_Color_ForegroundBold,
                                     msg.c_str(), true, this->ColorOutput);

    std::vector<cmStdString> command;
    command.push_back(this->MocExecutable);
    for (std::list<std::string>::const_iterator it = this->MocIncludes.begin();
         it != this->MocIncludes.end();
         ++it)
      {
      command.push_back(*it);
      }
    for(std::list<std::string>::const_iterator it=this->MocDefinitions.begin();
        it != this->MocDefinitions.end();
        ++it)
      {
      command.push_back(*it);
      }
#ifdef _WIN32
    command.push_back("-DWIN32");
#endif
    command.push_back("-o");
    command.push_back(mocFilePath);
    command.push_back(sourceFile);

    if (this->Verbose)
      {
      for(int i=0; i<command.size(); i++)
        {
        std::cout << command[i] << " ";
        }
      std::cout << std::endl;
      }

    std::string output;
    int retVal = 0;
    bool result = cmSystemTools::RunSingleCommand(command, &output, &retVal);
    if (!result || retVal)
      {
      std::cerr << "AUTOMOC: process for " << mocFilePath << " failed:\n"
                << output << std::endl;
      this->RunMocFailed = true;
      cmSystemTools::RemoveFile(mocFilePath.c_str());
      }
    return true;
    }
  return false;
}