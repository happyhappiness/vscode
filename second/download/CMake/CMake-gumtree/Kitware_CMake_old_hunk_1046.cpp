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
