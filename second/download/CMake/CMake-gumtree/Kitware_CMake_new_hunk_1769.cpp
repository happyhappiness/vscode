          std::cerr << "Changing directory into " << nwd.c_str() << "\n";

          firstTest = 0;

          }

        cres.m_Name = args[0].Value;

        fprintf(stderr,"Testing %-30s ",args[0].Value.c_str());

        fflush(stderr);

        //std::cerr << "Testing " << args[0] << " ... ";

        // find the test executable

        std::string testCommand = this->FindExecutable(args[1].Value.c_str());

        testCommand = cmSystemTools::ConvertToOutputPath(testCommand.c_str());



        // continue if we did not find the executable

        if (testCommand == "")

          {

          std::cerr << "Unable to find executable: " << 

            args[1].Value.c_str() << "\n";

          continue;

          }

        

        // add the arguments

        std::vector<cmListFileArgument>::const_iterator j = args.begin();

        ++j;

        ++j;

        for(;j != args.end(); ++j)

          {   

          testCommand += " ";

          testCommand += cmSystemTools::EscapeSpaces(j->Value.c_str());

          }

        /**

         * Run an executable command and put the stdout in output.

