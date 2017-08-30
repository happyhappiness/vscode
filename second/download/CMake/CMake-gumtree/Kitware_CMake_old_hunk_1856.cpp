        if (!cmSystemTools::RunCommand(testCommand.c_str(), output, 
                                       retVal, false) || retVal != 0)
          {
          std::cerr << " Failed\n";
          if (output != "")
            {
            std::cerr << output.c_str() << "\n";
