int cmCTest::RunConfigurationDashboard(cmMakefile *mf, 
                                       const char *srcDir, const char *binDir,
                                       const char *ctestRoot,
                                       bool backup, const char *cvsCheckOut,
                                       const char *ctestCmd)
{
  const char *cvsCmd = mf->GetDefinition("CTEST_CVS_COMMAND");
  
  // local variables
  std::string command;
  std::string output;
  int retVal = 0;
  bool res; 

  // make sure the src directory is there, if it isn't then we might be able
  // to check it out from cvs
  if (!cmSystemTools::FileExists(srcDir) && cvsCheckOut)
    {
    // we must now checkout the src dir
    output = "";
    if ( m_Verbose )
      {
      std::cerr << "Run cvs: " << cvsCheckOut << std::endl;
      }
    res = cmSystemTools::RunSingleCommand(cvsCheckOut, &output, 
                                          &retVal, ctestRoot,
                                          m_Verbose, 0 /*m_TimeOut*/);
    if (!res || retVal != 0)
      {
      cmSystemTools::Error("Unable to perform cvs checkout:\n", output.c_str());    
      return 6;
      }
    }
  
  // compute the backup names
  std::string backupSrcDir = srcDir;
  backupSrcDir += "_CMakeBackup";
  std::string backupBinDir = binDir;
  backupBinDir += "_CMakeBackup";

  // backup the binary and src directories if requested
  if (backup)
    {
    // if for some reason those directories exist then first delete them
    if (cmSystemTools::FileExists(backupSrcDir.c_str()))
      {
      cmSystemTools::RemoveADirectory(backupSrcDir.c_str());
      }
    if (cmSystemTools::FileExists(backupBinDir.c_str()))
      {
      cmSystemTools::RemoveADirectory(backupBinDir.c_str());
      }

    // first rename the src and binary directories 
    rename(srcDir, backupSrcDir.c_str());
    rename(binDir, backupBinDir.c_str());

    // we must now checkout the src dir
    output = "";
    if ( m_Verbose )
      {
      std::cerr << "Run cvs: " << cvsCheckOut << std::endl;
      }
    res = cmSystemTools::RunSingleCommand(cvsCheckOut, &output, 
                                          &retVal, ctestRoot,
                                          m_Verbose, 0 /*m_TimeOut*/);
    if (!res || retVal != 0)
      {
      cmSystemTools::Error("Unable to perform cvs checkout:", output.c_str());    
      this->RestoreBackupDirectories(backup, srcDir, binDir,
        backupSrcDir.c_str(), 
        backupBinDir.c_str());
      return 6;
      }
    }

  // clear the binary directory?
  if (mf->IsOn("CTEST_START_WITH_EMPTY_BINARY_DIRECTORY"))
    {
    // try to avoid deleting directories that we shouldn't
    std::string check = binDir;
    check += "/CMakeCache.txt";
    if (cmSystemTools::FileExists(check.c_str()))
      {
      cmSystemTools::RemoveADirectory(binDir);
      }
    }

  // make sure the binary directory exists if it isn;t the srcdir
  if (!cmSystemTools::FileExists(binDir) && strcmp(srcDir, binDir))
    {
    if (!cmSystemTools::MakeDirectory(binDir))
      {
      cmSystemTools::Error("Unable to create the binary directory:\n", binDir);    
      this->RestoreBackupDirectories(backup, srcDir, binDir,
        backupSrcDir.c_str(), 
        backupBinDir.c_str());
      return 7;
      }
    }

  // if the binary directory and the source directory are the same,
  // and we are starting with an empty binary directory, then that means
  // we must check out the source tree
  if (mf->IsOn("CTEST_START_WITH_EMPTY_BINARY_DIRECTORY") &&
      !strcmp(srcDir, binDir))
    {
    // make sure we have the required info
    if (!cvsCheckOut)
      {
      cmSystemTools::Error("You have specified the source and binary directories to be the same (an in source build). You have also specified that the binary directory is to be erased. This means that the source will have to be checked out from CVS. But you have not specified CTEST_CVS_CHECKOUT");    
      return 8;
      }
    
    // we must now checkout the src dir
    output = "";
    if ( m_Verbose )
      {
      std::cerr << "Run cvs: " << cvsCheckOut << std::endl;
      }
    res = cmSystemTools::RunSingleCommand(cvsCheckOut, &output, 
                                          &retVal, ctestRoot,
                                          m_Verbose, 0 /*m_TimeOut*/);
    if (!res || retVal != 0)
      {
      cmSystemTools::Error("Unable to perform cvs checkout:\n", output.c_str());    
      this->RestoreBackupDirectories(backup, srcDir, binDir,
                                     backupSrcDir.c_str(), 
                                     backupBinDir.c_str());
      return 6;
      }
    }
  
  // do an initial cvs update as required
  if (cvsCmd)
    {
    command = cvsCmd;
    char updateVar[40];
    int i;
    for (i = 1; i < 10; ++i)
      {
      sprintf(updateVar,"CTEST_EXTRA_UPDATES_%i",i);
      const char *updateVal = mf->GetDefinition(updateVar);
      if (updateVal)
        {
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
            cmSystemTools::Error("Unable to perform extra cvs updates:\n", output.c_str());
            this->RestoreBackupDirectories(backup, srcDir, binDir,
              backupSrcDir.c_str(), 
              backupBinDir.c_str());
            return 8;
            }
          }
        }
      }
    }

  // put the initial cache into the bin dir
  if (mf->GetDefinition("CTEST_INITIAL_CACHE"))
    {
    const char *initCache = mf->GetDefinition("CTEST_INITIAL_CACHE");
    std::string cacheFile = binDir;
    cacheFile += "/CMakeCache.txt";
    std::ofstream fout(cacheFile.c_str());
    if(!fout)
      {
      this->RestoreBackupDirectories(backup, srcDir, binDir,
        backupSrcDir.c_str(), 
        backupBinDir.c_str());
      return 9;
      }

    fout.write(initCache, strlen(initCache));

    // Make sure the operating system has finished writing the file
    // before closing it.  This will ensure the file is finished before
    // the check below.
    fout.flush();
    fout.close();
    }

  // do an initial cmake to setup the DartConfig file
  const char *cmakeCmd = mf->GetDefinition("CTEST_CMAKE_COMMAND");
  int cmakeFailed = 0;
  std::string cmakeFailedOuput;
  if (cmakeCmd)
    {
    command = cmakeCmd;
    command += " \"";
    command += srcDir;
    output = "";
    command += "\"";
    retVal = 0;
    if ( m_Verbose )
      {
      std::cerr << "Run cmake command: " << command.c_str() << std::endl;
      }
    res = cmSystemTools::RunSingleCommand(command.c_str(), &output, 
      &retVal, binDir,
      m_Verbose, 0 /*m_TimeOut*/);
    if (!res || retVal != 0)
      {
      // even if this fails continue to the next step
      cmakeFailed = 1;
      cmakeFailedOuput = output;
      }
    }

  // run cteste may be more than one command in here
  std::vector<std::string> ctestCommands;
  cmSystemTools::ExpandListArgument(ctestCmd,ctestCommands);
  // for each variable/argument do a putenv
  for (unsigned i = 0; i < ctestCommands.size(); ++i)
    {
    command = ctestCommands[i];
    output = "";
    retVal = 0;
    if ( m_Verbose )
      {
      std::cerr << "Run ctest command: " << command.c_str() << std::endl;
      }
    res = cmSystemTools::RunSingleCommand(command.c_str(), &output, 
                                          &retVal, binDir,
                                          m_Verbose, 0 /*m_TimeOut*/);

    // did something critical fail in ctest
    if (!res || cmakeFailed ||
        retVal & CTEST_BUILD_ERRORS)
      {
      this->RestoreBackupDirectories(backup, srcDir, binDir,
                                     backupSrcDir.c_str(), 
                                     backupBinDir.c_str());
      if (cmakeFailed)
        {
        cmSystemTools::Error("Unable to run cmake:\n", cmakeFailedOuput.c_str());    
        return 10;
        }
      cmSystemTools::Error("Unable to run ctest:\n", output.c_str());    
      if (!res)
        {
        return 11;
        }
      return retVal * 100;
      }
    }
  
  // if all was succesful, delete the backup dirs to free up disk space
  if (backup)
    {
    cmSystemTools::RemoveADirectory(backupSrcDir.c_str());
    cmSystemTools::RemoveADirectory(backupBinDir.c_str());
    }

  return 0;  
}