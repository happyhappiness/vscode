    passed = this->TestResult.Status == cmCTestTestHandler::COMPLETED;

    char buf[1024];
    sprintf(buf, "%6.2f sec", this->TestResult.ExecutionTime);
    cmCTestLog(this->CTest, HANDLER_OUTPUT, buf << "\n" );
    if ( this->TestHandler->LogFile )
      {
      *this->TestHandler->LogFile << "\nTest time = " << buf << std::endl;
      }
    this->DartProcessing(output);
    } 

  // if this is doing MemCheck then all the output needs to be put into
  // Output since that is what is parsed by cmCTestMemCheckHandler
  if(!this->TestHandler->MemCheck)
    {
    if ( this->TestResult.Status == cmCTestTestHandler::COMPLETED )
      {
      this->TestHandler->CleanTestOutput(output, static_cast<size_t>
                     (this->TestHandler->CustomMaximumPassedTestOutputSize));
      }
    else
      {
      this->TestHandler->CleanTestOutput(output, static_cast<size_t>
                     (this->TestHandler->CustomMaximumFailedTestOutputSize));
      }
    }
  this->TestResult.Reason = reason;
