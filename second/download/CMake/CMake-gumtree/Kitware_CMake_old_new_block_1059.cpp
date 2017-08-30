{
  const std::string& testname = it->Name;
  std::vector<std::string>& args = it->Args;
  cmCTestTestResult cres;
  cres.Properties = &*it;
  cres.ExecutionTime = 0;
  cres.ReturnValue = -1;
  cres.Status = cmCTestTestHandler::NOT_RUN;
  cres.TestCount = cnt;  
  cres.Name = testname;
  cres.Path = it->Directory.c_str();
  
  cmCTestLog(this->CTest, HANDLER_OUTPUT, std::setw(3) << cnt << "/");
  cmCTestLog(this->CTest, HANDLER_OUTPUT, std::setw(3) << tmsize << " ");
  if ( this->MemCheck )
    {
    cmCTestLog(this->CTest, HANDLER_OUTPUT, "Memory Check");
    }
  else
    {
    cmCTestLog(this->CTest, HANDLER_OUTPUT, "Testing");
    }
  cmCTestLog(this->CTest, HANDLER_OUTPUT, " ");
  const int maxTestNameWidth = this->CTest->GetMaxTestNameWidth();
  std::string outname = testname + " ";
  outname.resize(maxTestNameWidth, '.');
  *this->LogFile << cnt << "/" << tmsize << " Testing: " << testname
                 << std::endl;
  
  if ( this->CTest->GetShowOnly() )
    {
    cmCTestLog(this->CTest, HANDLER_OUTPUT, outname.c_str() << std::endl);
    }
  else
    {
    cmCTestLog(this->CTest, HANDLER_OUTPUT, outname.c_str());
    }
  
  cmCTestLog(this->CTest, DEBUG, "Testing " << args[0].c_str() << " ... ");
  // find the test executable
  std::string actualCommand = this->FindTheExecutable(args[1].c_str());
  std::string testCommand
    = cmSystemTools::ConvertToOutputPath(actualCommand.c_str());
  
  // continue if we did not find the executable
  if (testCommand == "")
    {
    *this->LogFile << "Unable to find executable: " << args[1].c_str()
                   << std::endl;
    cmCTestLog(this->CTest, ERROR_MESSAGE, "Unable to find executable: "
               << args[1].c_str() << std::endl);
    cres.Output = "Unable to find executable: " + args[1];
    if ( !this->CTest->GetShowOnly() )
      {
      cres.FullCommandLine = actualCommand;
      this->TestResults.push_back( cres );
      failed.push_back(testname);
      return;
      }
    }
  
  // add the arguments
  std::vector<std::string>::const_iterator j = args.begin();
  ++j; // skip test name
  ++j; // skip command as it is in actualCommand
  std::vector<const char*> arguments;
  this->GenerateTestCommand(arguments);
  arguments.push_back(actualCommand.c_str());
  for(;j != args.end(); ++j)
    {
    testCommand += " ";
    testCommand += cmSystemTools::EscapeSpaces(j->c_str());
    arguments.push_back(j->c_str());
    }
  arguments.push_back(0);
  
  /**
   * Run an executable command and put the stdout in output.
   */
  std::string output;
  int retVal = 0;
  
  
  cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, std::endl
             << (this->MemCheck?"MemCheck":"Test") 
             << " command: " << testCommand
             << std::endl);
  *this->LogFile << cnt << "/" << tmsize
                 << " Test: " << testname.c_str() << std::endl;
  *this->LogFile << "Command: ";
  std::vector<cmStdString>::size_type ll;
  for ( ll = 0; ll < arguments.size()-1; ll ++ )
    {
    *this->LogFile << "\"" << arguments[ll] << "\" ";
    }
  *this->LogFile
    << std::endl
    << "Directory: " << it->Directory << std::endl
    << "\"" << testname.c_str() << "\" start time: "
    << this->CTest->CurrentTime() << std::endl
    << "Output:" << std::endl
    << "----------------------------------------------------------"
    << std::endl;
  int res = 0;
  double clock_start, clock_finish;
  clock_start = cmSystemTools::GetTime();
  
  if ( !this->CTest->GetShowOnly() )
    {
    res = this->CTest->RunTest(arguments, &output, &retVal, this->LogFile,
                               it->Timeout, &it->Environment);
    }

  clock_finish = cmSystemTools::GetTime();  

  if ( this->LogFile )
    {
    double ttime = clock_finish - clock_start;
    int hours = static_cast<int>(ttime / (60 * 60));
    int minutes = static_cast<int>(ttime / 60) % 60;
    int seconds = static_cast<int>(ttime) % 60;
    char buffer[100];
    sprintf(buffer, "%02d:%02d:%02d", hours, minutes, seconds);
    *this->LogFile
      << "----------------------------------------------------------"
      << std::endl
      << "\"" << testname.c_str() << "\" end time: "
      << this->CTest->CurrentTime() << std::endl
      << "\"" << testname.c_str() << "\" time elapsed: "
      << buffer << std::endl
      << "----------------------------------------------------------"
      << std::endl << std::endl;
    }
  
  cres.ExecutionTime = (double)(clock_finish - clock_start);
  cres.FullCommandLine = testCommand;
  std::string reason;
  if ( !this->CTest->GetShowOnly() )
    {
    bool testFailed = false;
    std::vector<std::pair<cmsys::RegularExpression,
      std::string> >::iterator passIt;
    bool forceFail = false;
    if ( it->RequiredRegularExpressions.size() > 0 )
      {
      bool found = false;
      for ( passIt = it->RequiredRegularExpressions.begin();
            passIt != it->RequiredRegularExpressions.end();
            ++ passIt )
        {
        if ( passIt->first.find(output.c_str()) )
          {
          found = true;
          reason = "Required regular expression found.";
          }
        }
      if ( !found )
        { 
        reason = "Required regular expression not found.";
        forceFail = true;
        }
      reason +=  "Regex=["; 
      for ( passIt = it->RequiredRegularExpressions.begin();
            passIt != it->RequiredRegularExpressions.end();
            ++ passIt )
        {
        reason += passIt->second;
        reason += "\n";
        }
      reason += "]";
      }
    if ( it->ErrorRegularExpressions.size() > 0 )
      {
      for ( passIt = it->ErrorRegularExpressions.begin();
            passIt != it->ErrorRegularExpressions.end();
            ++ passIt )
        {
        if ( passIt->first.find(output.c_str()) )
          {
          reason = "Error regular expression found in output.";
          reason += " Regex=[";
          reason += passIt->second;
          reason += "]";
          forceFail = true;
          }
        }
      }
    
    if (res == cmsysProcess_State_Exited &&
        (retVal == 0 || it->RequiredRegularExpressions.size()) &&
        !forceFail)
      {
      cmCTestLog(this->CTest, HANDLER_OUTPUT,   "   Passed");
      if ( it->WillFail )
        {
        cmCTestLog(this->CTest, HANDLER_OUTPUT,   " - But it should fail!");
        cres.Status = cmCTestTestHandler::FAILED;
        testFailed = true;
        }
      else
        {
        cres.Status = cmCTestTestHandler::COMPLETED;
        }
      cmCTestLog(this->CTest, HANDLER_OUTPUT, std::endl);
      }
    else
      {
      testFailed = true;
      
      cres.Status = cmCTestTestHandler::FAILED;
      if ( res == cmsysProcess_State_Expired )
        {
        cmCTestLog(this->CTest, HANDLER_OUTPUT, "***Timeout" << std::endl);
        cres.Status = cmCTestTestHandler::TIMEOUT;
        }
      else if ( res == cmsysProcess_State_Exception )
        {
        cmCTestLog(this->CTest, HANDLER_OUTPUT, "***Exception: ");
        switch ( retVal )
          {
          case cmsysProcess_Exception_Fault:
            cmCTestLog(this->CTest, HANDLER_OUTPUT, "SegFault");
            cres.Status = cmCTestTestHandler::SEGFAULT;
            break;
          case cmsysProcess_Exception_Illegal:
            cmCTestLog(this->CTest, HANDLER_OUTPUT, "Illegal");
            cres.Status = cmCTestTestHandler::ILLEGAL;
            break;
          case cmsysProcess_Exception_Interrupt:
            cmCTestLog(this->CTest, HANDLER_OUTPUT, "Interrupt");
            cres.Status = cmCTestTestHandler::INTERRUPT;
            break;
          case cmsysProcess_Exception_Numerical:
            cmCTestLog(this->CTest, HANDLER_OUTPUT, "Numerical");
            cres.Status = cmCTestTestHandler::NUMERICAL;
            break;
          default:
            cmCTestLog(this->CTest, HANDLER_OUTPUT, "Other");
            cres.Status = cmCTestTestHandler::OTHER_FAULT;
          }
        cmCTestLog(this->CTest, HANDLER_OUTPUT, std::endl);
        }
      else if ( res == cmsysProcess_State_Error )
        {
        cmCTestLog(this->CTest, HANDLER_OUTPUT, "***Bad command " << res
                   << std::endl);
        cres.Status = cmCTestTestHandler::BAD_COMMAND;
        }
      else
        {
        // Force fail will also be here?
        cmCTestLog(this->CTest, HANDLER_OUTPUT, "***Failed " << reason);
        if ( it->WillFail )
          {
          cres.Status = cmCTestTestHandler::COMPLETED;
          cmCTestLog(this->CTest, HANDLER_OUTPUT, " - supposed to fail");
          testFailed = false;
          }
        cmCTestLog(this->CTest, HANDLER_OUTPUT, std::endl);
        }
      }
    if ( testFailed )
      {
      failed.push_back(testname);
      }
    else
      {
      passed.push_back(testname);
      }
    if (!output.empty() && output.find("<DartMeasurement") != output.npos)
      {
      if (this->DartStuff.find(output.c_str()))
        {
        std::string dartString = this->DartStuff.match(1);
        // keep searching and replacing until none are left
        while (this->DartStuff1.find(output.c_str()))
          {
          // replace the exact match for the string
          cmSystemTools::ReplaceString(output,
                                       this->DartStuff1.match(1).c_str(), "");
          }
        cres.RegressionImages
          = this->GenerateRegressionImages(dartString);
        }
      }
    }

  // if this is doing MemCheck then all the output needs to be put into
  // Output since that it what is parsed to by cmCTestMemCheckHandler
  if(!this->MemCheck)
    {
    if ( cres.Status == cmCTestTestHandler::COMPLETED )
      {
      this->CleanTestOutput(output, static_cast<size_t>
                            (this->CustomMaximumPassedTestOutputSize));
      }
    else
      {
      this->CleanTestOutput(output, static_cast<size_t>
                            (this->CustomMaximumFailedTestOutputSize));
      }
    }
  cres.Reason = reason;
  cres.Output = output;
  cres.ReturnValue = retVal;
  cres.CompletionStatus = "Completed";
  this->TestResults.push_back( cres );
}