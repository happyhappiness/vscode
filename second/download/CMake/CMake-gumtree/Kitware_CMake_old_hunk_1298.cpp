        cmCTestTestResult *result = &this->TestResults[cc];
        totalTestTime += result->ExecutionTime;
        }
      this->PrintLabelSummary();
      char buf[1024];
      sprintf(buf, "%6.2f sec", totalTestTime); 
      cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nTotal Test time = " 
                 <<  buf << "\n" );
      if ( this->LogFile )
        {
        *this->LogFile << "\nTotal Test time = " << buf << std::endl;
        }
      }

    if (failed.size())
