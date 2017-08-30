            }

          else

            {

            cres.m_Status = cmCTest::FAILED;

            if ( res == cmsysProcess_State_Expired )

              {

              fprintf(stderr,"***Timeout\n");

