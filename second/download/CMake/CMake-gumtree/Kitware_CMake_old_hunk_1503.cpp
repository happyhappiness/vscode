    int retVal = 0;





    cmCTestLog(m_CTest, HANDLER_VERBOSE_OUTPUT, std::endl

      << (m_MemCheck?"MemCheck":"Test") << " command: " << testCommand

      << std::endl);

    *m_LogFile << cnt << "/" << tmsize

      << " Test: " << testname.c_str() << std::endl;

    *m_LogFile << "Command: ";

    std::vector<cmStdString>::size_type ll;

    for ( ll = 0; ll < arguments.size()-1; ll ++ )

      {

      *m_LogFile << "\"" << arguments[ll] << "\" ";

      }

    *m_LogFile

      << std::endl

      << "Directory: " << it->m_Directory << std::endl

      << "\"" << testname.c_str() << "\" start time: "

      << m_CTest->CurrentTime() << std::endl

      << "Output:" << std::endl

      << "----------------------------------------------------------"

      << std::endl;

    int res = 0;

    double clock_start, clock_finish;

    clock_start = cmSystemTools::GetTime();



    if ( !m_CTest->GetShowOnly() )

      {

      res = m_CTest->RunTest(arguments, &output, &retVal, m_LogFile);

      }



    clock_finish = cmSystemTools::GetTime();



    if ( m_LogFile )

      {

      double ttime = clock_finish - clock_start;

      int hours = static_cast<int>(ttime / (60 * 60));

      int minutes = static_cast<int>(ttime / 60) % 60;

      int seconds = static_cast<int>(ttime) % 60;

      char buffer[100];

      sprintf(buffer, "%02d:%02d:%02d", hours, minutes, seconds);

      *m_LogFile

        << "----------------------------------------------------------"

        << std::endl

        << "\"" << testname.c_str() << "\" end time: "

        << m_CTest->CurrentTime() << std::endl

        << "\"" << testname.c_str() << "\" time elapsed: "

        << buffer << std::endl

        << "----------------------------------------------------------"

        << std::endl << std::endl;

      }



    cres.m_ExecutionTime = (double)(clock_finish - clock_start);

    cres.m_FullCommandLine = testCommand;



    if ( !m_CTest->GetShowOnly() )

      {

      bool testFailed = false;

      std::vector<cmsys::RegularExpression>::iterator passIt;

      bool forceFail = false;

      if ( it->m_RequiredRegularExpressions.size() > 0 )

        {

        bool found = false;

        for ( passIt = it->m_RequiredRegularExpressions.begin();

          passIt != it->m_RequiredRegularExpressions.end();

          ++ passIt )

          {

          if ( passIt->find(output.c_str()) )

