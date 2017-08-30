      sprintf(buf, "%6.2f sec", totalTestTime); 
      cmCTestLog(this->CTest, HANDLER_OUTPUT, "\nTotal Test time = " 
                 <<  buf << "\n" );
      
      }

    if (failed.size())
