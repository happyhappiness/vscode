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