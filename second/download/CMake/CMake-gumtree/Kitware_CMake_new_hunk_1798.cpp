         */

        std::string output;

        int retVal;



        clock_t clock_start, clock_finish;

        double clocks_per_sec = (double)CLOCKS_PER_SEC;

        clock_start = clock();



        bool res = cmSystemTools::RunCommand(testCommand.c_str(), output, 

                                             retVal, 0, false);

        clock_finish = clock();



        cres.m_ExecutionTime = (double)(clock_finish - clock_start) / clocks_per_sec;

        cres.m_FullCommandLine = testCommand;



        if (!res || retVal != 0)

          {

          fprintf(stderr,"***Failed\n");

          if (output != "")

