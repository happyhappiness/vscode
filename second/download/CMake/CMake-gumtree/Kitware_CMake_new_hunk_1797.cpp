          {

          continue;

          }



        cmCTestTestResult cres;



        if (firstTest)

          {

          std::string nwd = cmSystemTools::GetCurrentWorkingDirectory();

          std::cerr << "Changing directory into " << nwd.c_str() << "\n";

          firstTest = 0;

          }

        cres.m_Name = args[0];

        fprintf(stderr,"Testing %-30s ",args[0].c_str());

        fflush(stderr);

        //std::cerr << "Testing " << args[0] << " ... ";

        // find the test executable

        std::string testCommand = 

          cmSystemTools::EscapeSpaces(this->FindExecutable(args[1].c_str()).c_str());

        // continue if we did not find the executable

        if (testCommand == "")

          {

