{
      cmCTestLog(this->CTest, HANDLER_OUTPUT, std::endl
                 << static_cast<int>(percent + .5) << "% tests passed, "
                 << failed.size() << " tests failed out of " 
                 << total << std::endl); 
      double totalTestTime = 0;

      for(cmCTestTestHandler::TestResultsVector::size_type cc = 0;
          cc < this->TestResults.size(); cc ++ )
        {
        cmCTestTestResult *result = &this->TestResults[cc];
        totalTestTime += result->ExecutionTime;
        }
      
      char buf[1024];
      sprintf(buf, "%6.2f sec", totalTestTime); 
      cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nTotal Test time = " 
                 <<  buf << "\n" );
      
      }