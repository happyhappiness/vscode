{
        fprintf(stderr,"Testing %-30s ",args[0].c_str());
        //std::cerr << "Testing " << args[0] << " ... ";
        // find the test executable
        std::string testCommand = this->FindExecutable(args[1].c_str());
        // add the arguments
        std::vector<std::string>::iterator j = args.begin();
        ++j;
        ++j;
        for(;j != args.end(); ++j)
          {   
          testCommand += " ";
          testCommand += *j;
          }
        /**
         * Run an executable command and put the stdout in output.
         */
        std::string output;
        int retVal;
        
        if (!cmSystemTools::RunCommand(testCommand.c_str(), output, 
                                       retVal, false) || retVal != 0)
          {
          std::cerr << " Failed\n";
          if (output != "")
            {
            std::cerr << output.c_str() << "\n";
            }
          failed++;
          }
        else
          {
          std::cerr << " Passed\n";
          if (output != "")
            {
            std::cerr << output.c_str() << "\n";
            }
          passed++;
          }
        }