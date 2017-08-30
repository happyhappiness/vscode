        totalTestTime += result->ExecutionTime;
        }
      
      char realBuf[1024];
      sprintf(realBuf, "%6.2f sec", (double)(clock_finish - clock_start));
      cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nTotal Test time (real) = "
                 << realBuf << "\n" );

      char totalBuf[1024];
      sprintf(totalBuf, "%6.2f sec", totalTestTime); 
      cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nTotal Test time (parallel) = " 
                 <<  totalBuf << "\n" );
      
      }

