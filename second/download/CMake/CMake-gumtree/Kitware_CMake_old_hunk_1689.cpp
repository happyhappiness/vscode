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

