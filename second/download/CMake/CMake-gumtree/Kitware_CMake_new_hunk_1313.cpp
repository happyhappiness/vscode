      }

    }

  cres.Reason = reason;

  if ( this->LogFile )

    {

    bool pass = true;

    const char* reasonType = "Test Pass Reason";

    if(cres.Status != cmCTestTestHandler::COMPLETED &&

       cres.Status != cmCTestTestHandler::NOT_RUN)

      {

      reasonType = "Test Fail Reason";

      pass = false;

      }

    double ttime = clock_finish - clock_start;

    int hours = static_cast<int>(ttime / (60 * 60));

    int minutes = static_cast<int>(ttime / 60) % 60;

    int seconds = static_cast<int>(ttime) % 60;

    char buffer[100];

    sprintf(buffer, "%02d:%02d:%02d", hours, minutes, seconds);

    *this->LogFile

      << "----------------------------------------------------------"

      << std::endl;

    if(cres.Reason.size())

      {

      *this->LogFile << reasonType << ":\n" << cres.Reason << "\n";

      }

    else 

      {

      if(pass)

        {

        *this->LogFile << "Test Passed.\n";

        }

      else

        {

        *this->LogFile << "Test Failed.\n";

        }

      }

    *this->LogFile << "\"" << testname.c_str() << "\" end time: "

      << this->CTest->CurrentTime() << std::endl

      << "\"" << testname.c_str() << "\" time elapsed: "

      << buffer << std::endl

      << "----------------------------------------------------------"

      << std::endl << std::endl;

    }

  cres.Output = output;

  cres.ReturnValue = retVal;

  cres.CompletionStatus = "Completed";
