

        if ( !m_ShowOnly )

          {

          if (res == cmsysProcess_State_Exited && retVal )

            {

            fprintf(stderr,"   Passed\n");

            passed.push_back(args[0].Value); 

            }

          else

            {

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

                break;

              case cmsysProcess_Exception_Illegal:

                fprintf(stderr,"SegFault");

                cres.m_Status = cmCTest::ILLEGAL;

                break;

              case cmsysProcess_Exception_Interrupt:

                fprintf(stderr,"SegFault");

                cres.m_Status = cmCTest::INTERRUPT;

                break;

              case cmsysProcess_Exception_Numerical:

                fprintf(stderr,"SegFault");

                cres.m_Status = cmCTest::NUMERICAL;

                break;

              default:

                fprintf(stderr,"Other");

                cres.m_Status = cmCTest::OTHER_FAULT;

                }

              }

            else if ( res == cmsysProcess_State_Error )

              {

              fprintf(stderr,"***Bad command\n");

              cres.m_Status = cmCTest::BAD_COMMAND;

              }

            else

              {

              fprintf(stderr,"***Failed\n");

              }

            failed.push_back(args[0].Value); 

            }

          if (output != "")

            {

            if (dartStuff.find(output.c_str()))

              {

              std::string dartString = dartStuff.match(1);

              cmSystemTools::ReplaceString(output, dartString.c_str(),"");

              cres.m_RegressionImages = this->GenerateRegressionImages(dartString);

              }

            }

          }

        cres.m_Output = output;

