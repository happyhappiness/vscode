void ctest::ProcessDirectory(std::vector<std::string> &passed, 
                             std::vector<std::string> &failed)
{
  // does the DartTestfile.txt exist ?
  if(!cmSystemTools::FileExists("DartTestfile.txt"))
    {
    return;
    }
  
  // parse the file
  std::ifstream fin("DartTestfile.txt");
  if(!fin)
    {
    return;
    }

  int firstTest = 1;
  long line = 0;
  
  cmRegularExpression ireg(this->m_IncludeRegExp.c_str());
  cmRegularExpression ereg(this->m_ExcludeRegExp.c_str());
  cmRegularExpression dartStuff("([\t\n ]*<DartMeasurement.*/DartMeasurement[a-zA-Z]*>[\t ]*[\n]*)");

  bool parseError;
  while ( fin )
    {
    cmListFileFunction lff;
    if(cmListFileCache::ParseFunction(fin, lff, "DartTestfile.txt",
                                      parseError, line))
      {
      const std::string& name = lff.m_Name;
      const std::vector<cmListFileArgument>& args = lff.m_Arguments;
      if (name == "SUBDIRS")
        {
        std::string cwd = cmSystemTools::GetCurrentWorkingDirectory();
        for(std::vector<cmListFileArgument>::const_iterator j = args.begin();
            j != args.end(); ++j)
          {   
          std::string nwd = cwd + "/";
          nwd += j->Value;
          if (cmSystemTools::FileIsDirectory(nwd.c_str()))
            {
            cmSystemTools::ChangeDirectory(nwd.c_str());
            this->ProcessDirectory(passed, failed);
            }
          }
        // return to the original directory
        cmSystemTools::ChangeDirectory(cwd.c_str());
        }
      
      if (name == "ADD_TEST")
        {
        if (this->m_UseExcludeRegExp && 
            this->m_UseExcludeRegExpFirst && 
            ereg.find(args[0].Value.c_str()))
          {
          continue;
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

        if (firstTest)
          {
          std::string nwd = cmSystemTools::GetCurrentWorkingDirectory();
          std::cerr << "Changing directory into " << nwd.c_str() << "\n";
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
        std::string testCommand = this->FindExecutable(args[1].Value.c_str());
        testCommand = cmSystemTools::ConvertToOutputPath(testCommand.c_str());

        // continue if we did not find the executable
        if (testCommand == "")
          {
          std::cerr << "Unable to find executable: " << 
            args[1].Value.c_str() << "\n";
          continue;
          }
        
        // add the arguments
        std::vector<cmListFileArgument>::const_iterator j = args.begin();
        ++j;
        ++j;
        for(;j != args.end(); ++j)
          {   
          testCommand += " ";
          testCommand += cmSystemTools::EscapeSpaces(j->Value.c_str());
          }
        /**
         * Run an executable command and put the stdout in output.
         */
        std::string output;
        int retVal = 0;

        double clock_start, clock_finish;
        clock_start = cmSystemTools::GetTime();

        if ( m_Verbose )
          {
          std::cout << std::endl << "Test command: " << testCommand << std::endl;
          }
        bool res = true;
        if ( !m_ShowOnly )
          {
          res = cmSystemTools::RunCommand(testCommand.c_str(), output, 
                                          retVal, 0, false);
          }
        clock_finish = cmSystemTools::GetTime();

        cres.m_ExecutionTime = (double)(clock_finish - clock_start);
        cres.m_FullCommandLine = testCommand;

        if ( !m_ShowOnly )
          {
          if (!res || retVal != 0)
            {
            fprintf(stderr,"***Failed\n");
            if (output != "")
              {
              if (dartStuff.find(output.c_str()))
                {
                cmSystemTools::ReplaceString(output,
                                             dartStuff.match(1).c_str(),"");
                }
              if (output != "" && m_Verbose)
                {
                std::cerr << output.c_str() << "\n";
                }
              }
            failed.push_back(args[0].Value); 
            }
          else
            {
            fprintf(stderr,"   Passed\n");
            if (output != "")
              {
              if (dartStuff.find(output.c_str()))
                {
                cmSystemTools::ReplaceString(output,
                                             dartStuff.match(1).c_str(),"");
                }
              if (output != "" && m_Verbose)
                {
                std::cerr << output.c_str() << "\n";
                }
              }
            passed.push_back(args[0].Value); 
            }
          }
        cres.m_Output = output;
        cres.m_ReturnValue = retVal;
        std::string nwd = cmSystemTools::GetCurrentWorkingDirectory();
        if ( nwd.size() > m_ToplevelPath.size() )
          {
          nwd = "." + nwd.substr(m_ToplevelPath.size(), nwd.npos);
          }
        cres.m_Path = nwd;
        cres.m_CompletionStatus = "Completed";
        m_TestResults.push_back( cres );
        }
      }
    }
}