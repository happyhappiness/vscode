        }


      if (this->m_UseIncludeRegExp && !ireg.find(args[0].Value.c_str()))
        {
        continue;
        }
      if (this->m_UseExcludeRegExp &&
        !this->m_UseExcludeRegExpFirst &&
        ereg.find(args[0].Value.c_str()))
        {
        continue;
        }

      cmCTestTestResult cres;
      cres.m_Status = cmCTest::NOT_RUN;

      if (firstTest)
        {
        std::string nwd = cmSystemTools::GetCurrentWorkingDirectory();
        if ( m_Verbose )
          {
          std::cerr << "Changing directory into " << nwd.c_str() << "\n";
          }
        firstTest = 0;
        }
      cres.m_Name = args[0].Value;
      if ( m_ShowOnly )
        {
        std::cout << args[0].Value << std::endl;
        }
      else
        {
        fprintf(stderr,"Testing %-30s ",args[0].Value.c_str());
        fflush(stderr);
        }
      //std::cerr << "Testing " << args[0] << " ... ";
      // find the test executable
      std::string actualCommand = this->FindTheExecutable(args[1].Value.c_str());
      std::string testCommand = cmSystemTools::ConvertToOutputPath(actualCommand.c_str());
      std::string memcheckcommand = "";

      // continue if we did not find the executable
      if (testCommand == "")
        {
        std::cerr << "Unable to find executable: " <<
          args[1].Value.c_str() << "\n";
        m_TestResults.push_back( cres ); 
        failed.push_back(args[0].Value);
        continue;
        }

      // add the arguments
      std::vector<cmListFileArgument>::const_iterator j = args.begin();
      ++j;
      ++j;
      std::vector<const char*> arguments;
      if ( memcheck )
        {
        cmCTest::tm_VectorOfStrings::size_type pp;
        arguments.push_back(m_MemoryTester.c_str());
        memcheckcommand = m_MemoryTester;
        for ( pp = 0; pp < m_MemoryTesterOptionsParsed.size(); pp ++ )
          {
          arguments.push_back(m_MemoryTesterOptionsParsed[pp].c_str());
          memcheckcommand += " ";
          memcheckcommand += cmSystemTools::EscapeSpaces(m_MemoryTesterOptionsParsed[pp].c_str());
          }
        }
      arguments.push_back(actualCommand.c_str());
      for(;j != args.end(); ++j)
        {
        testCommand += " ";
        testCommand += cmSystemTools::EscapeSpaces(j->Value.c_str());
        arguments.push_back(j->Value.c_str());
        }
      arguments.push_back(0);

      /**
       * Run an executable command and put the stdout in output.
       */
      std::string output;
      int retVal = 0;

      double clock_start, clock_finish;
      clock_start = cmSystemTools::GetTime();

      if ( m_Verbose )
        {
        std::cout << std::endl << (memcheck?"MemCheck":"Test") << " command: " << testCommand << std::endl;
        if ( memcheck )
          {
          std::cout << "Memory check command: " << memcheckcommand << std::endl;
          }
        }
      if ( logfile )
        {
        *logfile << "Command: ";
        tm_VectorOfStrings::size_type ll;
        for ( ll = 0; ll < arguments.size()-1; ll ++ )
          {
          *logfile << "\"" << arguments[ll] << "\" ";
          }
        *logfile 
          << std::endl 
          << "Directory: " << cmSystemTools::GetCurrentWorkingDirectory() << std::endl 
          << "Output:" << std::endl 
          << "----------------------------------------------------------"
          << std::endl;
        }
      int res = 0;
      if ( !m_ShowOnly )
        {
        res = this->RunTest(arguments, &output, &retVal, logfile);
        }
      if ( logfile )
        {
        *logfile 
          << "----------------------------------------------------------"
          << std::endl << std::endl;
        }
      
      clock_finish = cmSystemTools::GetTime();

      cres.m_ExecutionTime = (double)(clock_finish - clock_start);
      cres.m_FullCommandLine = testCommand;

      if ( !m_ShowOnly )
        {
        if (res == cmsysProcess_State_Exited && retVal == 0)
          {
          fprintf(stderr,"   Passed\n");
          passed.push_back(args[0].Value);
          cres.m_Status = cmCTest::COMPLETED;
          }
        else
          {
          cres.m_Status = cmCTest::FAILED;
          if ( res == cmsysProcess_State_Expired )
            {
            fprintf(stderr,"***Timeout\n");
            cres.m_Status = cmCTest::TIMEOUT;
            }
          else if ( res == cmsysProcess_State_Exception )
            {
            fprintf(stderr,"***Exception: ");
            switch ( retVal )
              {
            case cmsysProcess_Exception_Fault:
              fprintf(stderr,"SegFault");
              cres.m_Status = cmCTest::SEGFAULT;
              break;
            case cmsysProcess_Exception_Illegal:
              fprintf(stderr,"Illegal");
              cres.m_Status = cmCTest::ILLEGAL;
              break;
            case cmsysProcess_Exception_Interrupt:
              fprintf(stderr,"Interrupt");
              cres.m_Status = cmCTest::INTERRUPT;
              break;
            case cmsysProcess_Exception_Numerical:
              fprintf(stderr,"Numerical");
              cres.m_Status = cmCTest::NUMERICAL;
              break;
            default:
              fprintf(stderr,"Other");
              cres.m_Status = cmCTest::OTHER_FAULT;
              }
            fprintf(stderr,"\n");
            }
          else if ( res == cmsysProcess_State_Error )
            {
            fprintf(stderr,"***Bad command %d\n", res);
            cres.m_Status = cmCTest::BAD_COMMAND;
            }
          else
            {
            fprintf(stderr,"***Failed\n");
            }
          failed.push_back(args[0].Value);
          }
        if (output != "")
          {
          if (dartStuff.find(output.c_str()))
            {
            std::string dartString = dartStuff.match(1);
            cmSystemTools::ReplaceString(output, dartString.c_str(),"");
            cres.m_RegressionImages = this->GenerateRegressionImages(dartString);
            }
          }
        }
      cres.m_Output = output;
      cres.m_ReturnValue = retVal;
      std::string nwd = cmSystemTools::GetCurrentWorkingDirectory();
      if ( nwd.size() > m_ToplevelPath.size() )
        {
        nwd = "." + nwd.substr(m_ToplevelPath.size(), nwd.npos);
        }
      cmSystemTools::ReplaceString(nwd, "\\", "/");
      cres.m_Path = nwd;
      cres.m_CompletionStatus = "Completed";
      m_TestResults.push_back( cres );
      }
    }
}

