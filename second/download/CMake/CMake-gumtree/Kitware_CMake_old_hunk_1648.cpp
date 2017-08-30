        cres.m_Status = cmCTest::FAILED;

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

            fprintf(stderr,"Illegal");

            cres.m_Status = cmCTest::ILLEGAL;

            break;

          case cmsysProcess_Exception_Interrupt:

            fprintf(stderr,"Interrupt");

            cres.m_Status = cmCTest::INTERRUPT;

            break;

          case cmsysProcess_Exception_Numerical:

            fprintf(stderr,"Numerical");

            cres.m_Status = cmCTest::NUMERICAL;

            break;

          default:

            fprintf(stderr,"Other");

            cres.m_Status = cmCTest::OTHER_FAULT;

            }

          fprintf(stderr,"\n");

          }

        else if ( res == cmsysProcess_State_Error )

          {

          fprintf(stderr,"***Bad command %d\n", res);

          cres.m_Status = cmCTest::BAD_COMMAND;

          }

        else

          {

          fprintf(stderr,"***Failed\n");

          }

        failed.push_back(testname);

        }

