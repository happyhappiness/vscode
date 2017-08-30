         */

        std::string output;

        int retVal;



        if (!cmSystemTools::RunCommand(testCommand.c_str(), output, 

                                       retVal, false) || retVal != 0)

          {

          fprintf(stderr,"***Failed\n");

          if (output != "")

            {

            if (dartStuff.find(output.c_str()))

              {

              cmSystemTools::ReplaceString(output,

                                           dartStuff.match(1).c_str(),"");

              }

            if (output != "")

              {

              std::cerr << output.c_str() << "\n";

              }

            }

          failed++;

          }

