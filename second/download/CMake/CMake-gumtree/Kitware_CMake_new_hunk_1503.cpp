    int retVal = 0;





    cmCTestLog(this->CTest, HANDLER_VERBOSE_OUTPUT, std::endl

      << (this->MemCheck?"MemCheck":"Test") << " command: " << testCommand

      << std::endl);

    *this->LogFile << cnt << "/" << tmsize

      << " Test: " << testname.c_str() << std::endl;

    *this->LogFile << "Command: ";

    std::vector<cmStdString>::size_type ll;

    for ( ll = 0; ll < arguments.size()-1; ll ++ )

      {

      *this->LogFile << "\"" << arguments[ll] << "\" ";

      }

    *this->LogFile

      << std::endl

      << "Directory: " << it->Directory << std::endl

      << "\"" << testname.c_str() << "\" start time: "

      << this->CTest->CurrentTime() << std::endl

      << "Output:" << std::endl

      << "----------------------------------------------------------"

      << std::endl;

    int res = 0;

    double clock_start, clock_finish;

    clock_start = cmSystemTools::GetTime();



    if ( !this->CTest->GetShowOnly() )

      {

      res = this->CTest->RunTest(arguments, &output, &retVal, this->LogFile);

      }



    clock_finish = cmSystemTools::GetTime();



    if ( this->LogFile )

      {

      double ttime = clock_finish - clock_start;

      int hours = static_cast<int>(ttime / (60 * 60));

      int minutes = static_cast<int>(ttime / 60) % 60;

      int seconds = static_cast<int>(ttime) % 60;

      char buffer[100];

      sprintf(buffer, "%02d:%02d:%02d", hours, minutes, seconds);

      *this->LogFile

        << "----------------------------------------------------------"

        << std::endl

        << "\"" << testname.c_str() << "\" end time: "

        << this->CTest->CurrentTime() << std::endl

        << "\"" << testname.c_str() << "\" time elapsed: "

        << buffer << std::endl

        << "----------------------------------------------------------"

        << std::endl << std::endl;

      }



    cres.ExecutionTime = (double)(clock_finish - clock_start);

    cres.FullCommandLine = testCommand;



    if ( !this->CTest->GetShowOnly() )

      {

      bool testFailed = false;

      std::vector<cmsys::RegularExpression>::iterator passIt;

      bool forceFail = false;

      if ( it->RequiredRegularExpressions.size() > 0 )

        {

        bool found = false;

        for ( passIt = it->RequiredRegularExpressions.begin();

          passIt != it->RequiredRegularExpressions.end();

          ++ passIt )

          {

          if ( passIt->find(output.c_str()) )

