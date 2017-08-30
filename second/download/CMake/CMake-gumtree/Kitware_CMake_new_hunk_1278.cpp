        this->TestResult.Status = cmCTestTestHandler::OTHER_FAULT;

      }

    }

  passed = this->TestResult.Status == cmCTestTestHandler::COMPLETED;

  char buf[1024];

  sprintf(buf, "%6.2f sec", this->TestProcess->GetTotalTime());

