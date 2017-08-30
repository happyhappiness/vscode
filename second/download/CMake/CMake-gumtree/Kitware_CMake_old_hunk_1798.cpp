         */
        std::string output;
        int retVal;
        if (!cmSystemTools::RunCommand(testCommand.c_str(), output, 
                                       retVal, 0, false) || retVal != 0)
          {
          fprintf(stderr,"***Failed\n");
          if (output != "")
