            }

          else if ( res == cmsysProcess_State_Error )

            {

            fprintf(stderr,"***Bad command %d\n", res);

            cres.m_Status = cmCTest::BAD_COMMAND;

            }

          else

