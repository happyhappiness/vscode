void cmCTest::ProcessDirectory(cmCTest::tm_VectorOfStrings &passed, 
                             cmCTest::tm_VectorOfStrings &failed,
                             bool memcheck)
{
  std::string current_dir = cmSystemTools::GetCurrentWorkingDirectory();
  cmsys::RegularExpression dartStuff("(<DartMeasurement.*/DartMeasurement[a-zA-Z]*>)");
  tm_ListOfTests testlist;
  this->GetListOfTests(&testlist, memcheck);
  tm_ListOfTests::size_type tmsize = testlist.size();

  std::ofstream ofs;
  std::ofstream *olog = 0;
  if ( !m_ShowOnly && tmsize > 0 && 
    this->OpenOutputFile("Temporary", 
      (memcheck?"LastMemCheck.log":"LastTest.log"), ofs) )
    {
    olog = &ofs;
    }

  m_StartTest = this->CurrentTime();
  double elapsed_time_start = cmSystemTools::GetTime();

  if ( olog )
    {
    *olog << "Start testing: " << m_StartTest << std::endl
      << "----------------------------------------------------------"
      << std::endl;
    }

  // expand the test list
  this->ExpandTestsToRunInformation((int)tmsize);
  
  int cnt = 0;
  tm_ListOfTests::iterator it;
  std::string last_directory = "";
  for ( it = testlist.begin(); it != testlist.end(); it ++ )
    {
    cnt ++;
    const std::string& testname = it->m_Name;
    tm_VectorOfListFileArgs& args = it->m_Args;
    cmCTestTestResult cres;
    cres.m_Status = cmCTest::NOT_RUN;
    cres.m_TestCount = cnt;

    if (!(last_directory == it->m_Directory))
      {
      if ( m_Verbose )
        {
        std::cerr << "Changing directory into " 
          << it->m_Directory.c_str() << "\n";
        }
      last_directory = it->m_Directory;
      cmSystemTools::ChangeDirectory(it->m_Directory.c_str());
      }
    cres.m_Name = testname;
    if(m_TestsToRun.size() && 
       std::find(m_TestsToRun.begin(), m_TestsToRun.end(), cnt) == m_TestsToRun.end())
      {
      continue;
      }

    if ( m_ShowOnly )
      {
      std::cerr.width(3);
      std::cerr.setf(std::ios_base::right);
      std::cerr << cnt << "/";
      std::cerr.width(3);
      std::cerr << tmsize << " Testing ";
      std::string outname = testname;
      outname.resize(30, ' ');
      std::cerr << outname.c_str() << "\n";
     }
    else
      {
      std::cerr.width(3);
      std::cerr << cnt << "/";
      std::cerr.width(3);
      std::cerr << tmsize << " Testing ";
      std::string outname = testname;
      outname.resize(30, ' ');
      std::cerr << outname.c_str();
      std::cerr.flush();
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
      if ( !m_ShowOnly )
        {
        m_TestResults.push_back( cres ); 
        failed.push_back(testname);
        continue;
        }
      }

    // add the arguments
    tm_VectorOfListFileArgs::const_iterator j = args.begin();
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


    if ( m_Verbose )
      {
      std::cout << std::endl << (memcheck?"MemCheck":"Test") << " command: " << testCommand << std::endl;
      if ( memcheck )
        {
        std::cout << "Memory check command: " << memcheckcommand << std::endl;
        }
      }
    if ( olog )
      {
      *olog << cnt << "/" << tmsize 
        << " Test: " << testname.c_str() << std::endl;
      *olog << "Command: ";
      tm_VectorOfStrings::size_type ll;
      for ( ll = 0; ll < arguments.size()-1; ll ++ )
        {
        *olog << "\"" << arguments[ll] << "\" ";
        }
      *olog 
        << std::endl 
        << "Directory: " << it->m_Directory << std::endl 
        << "\"" << testname.c_str() << "\" start time: " 
        << this->CurrentTime() << std::endl
        << "Output:" << std::endl 
        << "----------------------------------------------------------"
        << std::endl;
      }
    int res = 0;
    double clock_start, clock_finish;
    clock_start = cmSystemTools::GetTime();

    if ( !m_ShowOnly )
      {
      res = this->RunTest(arguments, &output, &retVal, olog);
      }

    clock_finish = cmSystemTools::GetTime();

    if ( olog )
      {
      double ttime = clock_finish - clock_start;
      int hours = static_cast<int>(ttime / (60 * 60));
      int minutes = static_cast<int>(ttime / 60) % 60;
      int seconds = static_cast<int>(ttime) % 60;
      char buffer[100];
      sprintf(buffer, "%02d:%02d:%02d", hours, minutes, seconds);
      *olog 
        << "----------------------------------------------------------"
        << std::endl
        << "\"" << testname.c_str() << "\" end time: " 
        << this->CurrentTime() << std::endl
        << "\"" << testname.c_str() << "\" time elapsed: " 
        << buffer << std::endl
        << "----------------------------------------------------------"
        << std::endl << std::endl;
      }

    cres.m_ExecutionTime = (double)(clock_finish - clock_start);
    cres.m_FullCommandLine = testCommand;

    if ( !m_ShowOnly )
      {
      if (res == cmsysProcess_State_Exited && retVal == 0)
        {
        std::cerr <<   "   Passed\n";
        passed.push_back(testname);
        cres.m_Status = cmCTest::COMPLETED;
        }
      else
        {
        cres.m_Status = cmCTest::FAILED;
        if ( res == cmsysProcess_State_Expired )
          {
          std::cerr << "***Timeout\n";
          cres.m_Status = cmCTest::TIMEOUT;
          }
        else if ( res == cmsysProcess_State_Exception )
          {
          std::cerr << "***Exception: ";
          switch ( retVal )
            {
          case cmsysProcess_Exception_Fault:
            std::cerr << "SegFault";
            cres.m_Status = cmCTest::SEGFAULT;
            break;
          case cmsysProcess_Exception_Illegal:
            std::cerr << "Illegal";
            cres.m_Status = cmCTest::ILLEGAL;
            break;
          case cmsysProcess_Exception_Interrupt:
            std::cerr << "Interrupt";
            cres.m_Status = cmCTest::INTERRUPT;
            break;
          case cmsysProcess_Exception_Numerical:
            std::cerr << "Numerical";
            cres.m_Status = cmCTest::NUMERICAL;
            break;
          default:
            std::cerr << "Other";
            cres.m_Status = cmCTest::OTHER_FAULT;
            }
           std::cerr << "\n";
          }
        else if ( res == cmsysProcess_State_Error )
          {
          std::cerr << "***Bad command " << res << "\n";
          cres.m_Status = cmCTest::BAD_COMMAND;
          }
        else
          {
          std::cerr << "***Failed\n";
          }
        failed.push_back(testname);
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
    std::string nwd = it->m_Directory;
    if ( nwd.size() > m_ToplevelPath.size() )
      {
      nwd = "." + nwd.substr(m_ToplevelPath.size(), nwd.npos);
      }
    cmSystemTools::ReplaceString(nwd, "\\", "/");
    cres.m_Path = nwd;
    cres.m_CompletionStatus = "Completed";
    m_TestResults.push_back( cres );
    }

  m_EndTest = this->CurrentTime();
  m_ElapsedTestingTime = cmSystemTools::GetTime() - elapsed_time_start;
  if ( olog )
    {
    *olog << "End testing: " << m_EndTest << std::endl;
    }
  cmSystemTools::ChangeDirectory(current_dir.c_str());
}