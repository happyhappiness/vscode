void cmCTest::ProcessDirectory(std::vector<std::string> &passed, 
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

#define SPACE_REGEX "[ \t\r\n]"
  
  cmsys::RegularExpression ireg(this->m_IncludeRegExp.c_str());
  cmsys::RegularExpression ereg(this->m_ExcludeRegExp.c_str());
  cmsys::RegularExpression dartStuff("(<DartMeasurement.*/DartMeasurement[a-zA-Z]*>)");

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
        cres.m_Status = cmCTest::NOT_RUN;

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
        std::string testCommand = this->FindTheExecutable(args[1].Value.c_str());
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
        int res = 0;
        if ( !m_ShowOnly )
          {
          res = this->RunTest(testCommand.c_str(), &output, &retVal);
          }
        clock_finish = cmSystemTools::GetTime();

        cres.m_ExecutionTime = (double)(clock_finish - clock_start);
        cres.m_FullCommandLine = testCommand;

        if ( !m_ShowOnly )
          {
          if (res == cmsysProcess_State_Exited && retVal )
            {
            fprintf(stderr,"   Passed\n");
            passed.push_back(args[0].Value); 
            }
          else
            {
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
                fprintf(stderr,"SegFault");
                cres.m_Status = cmCTest::ILLEGAL;
                break;
              case cmsysProcess_Exception_Interrupt:
                fprintf(stderr,"SegFault");
                cres.m_Status = cmCTest::INTERRUPT;
                break;
              case cmsysProcess_Exception_Numerical:
                fprintf(stderr,"SegFault");
                cres.m_Status = cmCTest::NUMERICAL;
                break;
              default:
                fprintf(stderr,"Other");
                cres.m_Status = cmCTest::OTHER_FAULT;
                }
              }
            else if ( res == cmsysProcess_State_Error )
              {
              fprintf(stderr,"***Bad command\n");
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
}