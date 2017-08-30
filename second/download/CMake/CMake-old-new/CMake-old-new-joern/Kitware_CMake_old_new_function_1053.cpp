bool cmCTestRunTest::EndTest()
{
  //restore the old environment
  if (this->ModifyEnv)
    {
    cmSystemTools::RestoreEnv(this->OrigEnv);
    }
  this->WriteLogOutputTop();
  std::string reason;
  bool passed = true;
  int res = this->TestProcess->GetProcessStatus();
  int retVal = this->TestProcess->GetExitValue();
  if ( !this->CTest->GetShowOnly() )
    {
    std::vector<std::pair<cmsys::RegularExpression,
      std::string> >::iterator passIt;
    bool forceFail = false;
    if ( this->TestProperties->RequiredRegularExpressions.size() > 0 )
      {
      bool found = false;
      for ( passIt = this->TestProperties->RequiredRegularExpressions.begin();
            passIt != this->TestProperties->RequiredRegularExpressions.end();
            ++ passIt )
        {
        if ( passIt->first.find(this->ProcessOutput.c_str()) )
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
      for ( passIt = this->TestProperties->RequiredRegularExpressions.begin();
            passIt != this->TestProperties->RequiredRegularExpressions.end();
            ++ passIt )
        {
        reason += passIt->second;
        reason += "\n";
        }
      reason += "]";
      }
    if ( this->TestProperties->ErrorRegularExpressions.size() > 0 )
      {
      for ( passIt = this->TestProperties->ErrorRegularExpressions.begin();
            passIt != this->TestProperties->ErrorRegularExpressions.end();
            ++ passIt )
        {
        if ( passIt->first.find(this->ProcessOutput.c_str()) )
          {
          reason = "Error regular expression found in output.";
          reason += " Regex=[";
          reason += passIt->second;
          reason += "]";
          forceFail = true;
          }
        }
      }
    if (res == cmsysProcess_State_Exited)
      {
      bool success = 
        !forceFail &&  (retVal == 0 || 
        this->TestProperties->RequiredRegularExpressions.size());
      if((success && !this->TestProperties->WillFail) 
        || (!success && this->TestProperties->WillFail))
        {
        this->TestResult.Status = cmCTestTestHandler::COMPLETED;
        cmCTestLog(this->CTest, HANDLER_OUTPUT, "   Passed  " );
        }
      else
        {
        this->TestResult.Status = cmCTestTestHandler::FAILED;
        cmCTestLog(this->CTest, HANDLER_OUTPUT, "***Failed  " << reason );
        }
      }
    else if ( res == cmsysProcess_State_Expired )
      {
      cmCTestLog(this->CTest, HANDLER_OUTPUT, "***Timeout");
      this->TestResult.Status = cmCTestTestHandler::TIMEOUT;
      }
    else if ( res == cmsysProcess_State_Exception )
      {
      cmCTestLog(this->CTest, HANDLER_OUTPUT, "***Exception: ");
      switch ( retVal )
        {
        case cmsysProcess_Exception_Fault:
          cmCTestLog(this->CTest, HANDLER_OUTPUT, "SegFault");
          this->TestResult.Status = cmCTestTestHandler::SEGFAULT;
          break;
        case cmsysProcess_Exception_Illegal:
          cmCTestLog(this->CTest, HANDLER_OUTPUT, "Illegal");
          this->TestResult.Status = cmCTestTestHandler::ILLEGAL;
          break;
        case cmsysProcess_Exception_Interrupt:
          cmCTestLog(this->CTest, HANDLER_OUTPUT, "Interrupt");
          this->TestResult.Status = cmCTestTestHandler::INTERRUPT;
          break;
        case cmsysProcess_Exception_Numerical:
          cmCTestLog(this->CTest, HANDLER_OUTPUT, "Numerical");
          this->TestResult.Status = cmCTestTestHandler::NUMERICAL;
          break;
        default:
          cmCTestLog(this->CTest, HANDLER_OUTPUT, "Other");
          this->TestResult.Status = cmCTestTestHandler::OTHER_FAULT;
        }
      }
    else // if ( res == cmsysProcess_State_Error )
      {
      cmCTestLog(this->CTest, HANDLER_OUTPUT, "***Bad command " << res );
      this->TestResult.Status = cmCTestTestHandler::BAD_COMMAND;
      }

    passed = this->TestResult.Status == cmCTestTestHandler::COMPLETED;

    char buf[1024];
    sprintf(buf, "%6.2f sec", this->TestProcess->GetTotalTime());
    cmCTestLog(this->CTest, HANDLER_OUTPUT, buf << "\n" );
    if ( this->TestHandler->LogFile )
      {
      *this->TestHandler->LogFile << "Test time = " << buf << std::endl;
      }
    this->DartProcessing();
    } 
  // if this is doing MemCheck then all the output needs to be put into
  // Output since that is what is parsed by cmCTestMemCheckHandler
  if(!this->TestHandler->MemCheck)
    {
    if ( this->TestResult.Status == cmCTestTestHandler::COMPLETED )
      {
      this->TestHandler->CleanTestOutput(this->ProcessOutput, 
          static_cast<size_t>
          (this->TestHandler->CustomMaximumPassedTestOutputSize));
      }
    else
      {
      this->TestHandler->CleanTestOutput(this->ProcessOutput,
          static_cast<size_t>
          (this->TestHandler->CustomMaximumFailedTestOutputSize));
      }
    }
  this->TestResult.Reason = reason;
  if ( this->TestHandler->LogFile )
    {
    bool pass = true;
    const char* reasonType = "Test Pass Reason";
    if(this->TestResult.Status != cmCTestTestHandler::COMPLETED &&
       this->TestResult.Status != cmCTestTestHandler::NOT_RUN)
      {
      reasonType = "Test Fail Reason";
      pass = false;
      }
    double ttime = this->TestProcess->GetTotalTime();
    int hours = static_cast<int>(ttime / (60 * 60));
    int minutes = static_cast<int>(ttime / 60) % 60;
    int seconds = static_cast<int>(ttime) % 60;
    char buffer[100];
    sprintf(buffer, "%02d:%02d:%02d", hours, minutes, seconds);
    *this->TestHandler->LogFile
      << "----------------------------------------------------------"
      << std::endl;
    if(this->TestResult.Reason.size())
      {
      *this->TestHandler->LogFile << reasonType << ":\n" 
        << this->TestResult.Reason << "\n";
      }
    else 
      {
      if(pass)
        {
        *this->TestHandler->LogFile << "Test Passed.\n";
        }
      else
        {
        *this->TestHandler->LogFile << "Test Failed.\n";
        }
      }
    *this->TestHandler->LogFile << "\"" << this->TestProperties->Name.c_str()
      << "\" end time: " << this->CTest->CurrentTime() << std::endl
      << "\"" << this->TestProperties->Name.c_str() << "\" time elapsed: "
      << buffer << std::endl
      << "----------------------------------------------------------"
      << std::endl << std::endl;
    }
  this->TestResult.Output = this->ProcessOutput;
  this->TestResult.ReturnValue = this->TestProcess->GetExitValue();
  this->TestResult.CompletionStatus = "Completed";
  this->TestResult.ExecutionTime = this->TestProcess->GetTotalTime();
  this->TestHandler->TestResults.push_back( this->TestResult );

  delete this->TestProcess;
  return passed;
}