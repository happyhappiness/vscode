        cmCTestTestResult *result = &this->TestResults[cc];
        totalTestTime += result->ExecutionTime;
        }
      
      char buf[1024];
      sprintf(buf, "%6.2f sec", totalTestTime); 
      cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nTotal Test time = " 
