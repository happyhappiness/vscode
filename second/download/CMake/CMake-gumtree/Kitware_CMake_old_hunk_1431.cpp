          {
          std::cout << std::endl << "Test command: " << testCommand << std::endl;
          }
        bool res = cmSystemTools::RunCommand(testCommand.c_str(), output, 
                                             retVal, 0, false);
        clock_finish = cmSystemTools::GetTime();

        cres.m_ExecutionTime = (double)(clock_finish - clock_start);
        cres.m_FullCommandLine = testCommand;

        if (!res || retVal != 0)
          {
          fprintf(stderr,"***Failed\n");
          if (output != "")
            {
            if (dartStuff.find(output.c_str()))
              {
              cmSystemTools::ReplaceString(output,
                                           dartStuff.match(1).c_str(),"");
              }
            if (output != "" && m_Verbose)
              {
              std::cerr << output.c_str() << "\n";
              }
            }
          failed.push_back(args[0].Value); 
          }
        else
          {
          fprintf(stderr,"   Passed\n");
          if (output != "")
            {
            if (dartStuff.find(output.c_str()))
              {
              cmSystemTools::ReplaceString(output,
                                           dartStuff.match(1).c_str(),"");
              }
            if (output != "" && m_Verbose)
              {
              std::cerr << output.c_str() << "\n";
              }
            }
          passed.push_back(args[0].Value); 
          }
        cres.m_Output = output;
        cres.m_ReturnValue = retVal;
