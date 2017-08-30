    }



  int firstTest = 1;

  long line = 0;



#define SPACE_REGEX "[ \t\r\n]"

  

  cmsys::RegularExpression ireg(this->m_IncludeRegExp.c_str());

  cmsys::RegularExpression ereg(this->m_ExcludeRegExp.c_str());

  cmsys::RegularExpression dartStuff("(<DartMeasurement.*/DartMeasurement[a-zA-Z]*>)");



  bool parseError;

  while ( fin )

    {

    cmListFileFunction lff;

    if(cmListFileCache::ParseFunction(fin, lff, "DartTestfile.txt",

                                      parseError, line))

      {

      const std::string& name = lff.m_Name;

      const std::vector<cmListFileArgument>& args = lff.m_Arguments;

      if (name == "SUBDIRS")

        {

        std::string cwd = cmSystemTools::GetCurrentWorkingDirectory();

        for(std::vector<cmListFileArgument>::const_iterator j = args.begin();

            j != args.end(); ++j)

          {   

          std::string nwd = cwd + "/";

          nwd += j->Value;

          if (cmSystemTools::FileIsDirectory(nwd.c_str()))

            {

            cmSystemTools::ChangeDirectory(nwd.c_str());

            this->ProcessDirectory(passed, failed);

            }

          }

        // return to the original directory

        cmSystemTools::ChangeDirectory(cwd.c_str());

        }

      

      if (name == "ADD_TEST")

        {

        if (this->m_UseExcludeRegExp && 

            this->m_UseExcludeRegExpFirst && 

            ereg.find(args[0].Value.c_str()))

          {

          continue;

          }

        if (this->m_UseIncludeRegExp && !ireg.find(args[0].Value.c_str()))

          {

          continue;

          }

        if (this->m_UseExcludeRegExp && 

            !this->m_UseExcludeRegExpFirst && 

            ereg.find(args[0].Value.c_str()))

          {

          continue;

          }



        cmCTestTestResult cres;

        cres.m_Status = cmCTest::NOT_RUN;



        if (firstTest)

          {

          std::string nwd = cmSystemTools::GetCurrentWorkingDirectory();

          std::cerr << "Changing directory into " << nwd.c_str() << "\n";

          firstTest = 0;

          }

        cres.m_Name = args[0].Value;

        if ( m_ShowOnly )

          {

          std::cout << args[0].Value << std::endl;

          }

        else

          {

          fprintf(stderr,"Testing %-30s ",args[0].Value.c_str());

          fflush(stderr);

          }

        //std::cerr << "Testing " << args[0] << " ... ";

        // find the test executable

        std::string actualCommand = this->FindTheExecutable(args[1].Value.c_str());

        std::string testCommand = cmSystemTools::ConvertToOutputPath(actualCommand.c_str());



        // continue if we did not find the executable

        if (testCommand == "")

          {

          std::cerr << "Unable to find executable: " << 

            args[1].Value.c_str() << "\n";

          m_TestResults.push_back( cres );

          continue;

          }

        

        // add the arguments

        std::vector<cmListFileArgument>::const_iterator j = args.begin();

        ++j;

        ++j;

        std::vector<const char*> arguments;

        arguments.push_back(actualCommand.c_str());

        for(;j != args.end(); ++j)

          {   

          testCommand += " ";

          testCommand += cmSystemTools::EscapeSpaces(j->Value.c_str());

          arguments.push_back(j->Value.c_str());

          }

        arguments.push_back(0);



        /**

         * Run an executable command and put the stdout in output.

         */

        std::string output;

        int retVal = 0;



        double clock_start, clock_finish;

        clock_start = cmSystemTools::GetTime();



        if ( m_Verbose )

          {

          std::cout << std::endl << "Test command: " << testCommand << std::endl;

          }

        int res = 0;

        if ( !m_ShowOnly )

          {

          res = this->RunTest(arguments, &output, &retVal);

          }

        clock_finish = cmSystemTools::GetTime();



        cres.m_ExecutionTime = (double)(clock_finish - clock_start);

        cres.m_FullCommandLine = testCommand;



        if ( !m_ShowOnly )

          {

          if (res == cmsysProcess_State_Exited && retVal == 0)

            {

            fprintf(stderr,"   Passed\n");

            passed.push_back(args[0].Value); 

            cres.m_Status = cmCTest::COMPLETED;

            }

          else

            {

            cres.m_Status = cmCTest::FAILED;

            if ( res == cmsysProcess_State_Expired )

              {

              fprintf(stderr,"***Timeout\n");

              cres.m_Status = cmCTest::TIMEOUT;

              }

            else if ( res == cmsysProcess_State_Exception )

              {

              fprintf(stderr,"***Exception: ");

              switch ( retVal )

                {

              case cmsysProcess_Exception_Fault:

                fprintf(stderr,"SegFault");

                cres.m_Status = cmCTest::SEGFAULT;

