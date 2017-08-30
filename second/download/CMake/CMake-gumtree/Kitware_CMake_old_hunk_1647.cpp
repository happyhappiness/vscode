      {

      if (res == cmsysProcess_State_Exited && retVal == 0)

        {

        fprintf(stderr,"   Passed\n");

        passed.push_back(testname);

        cres.m_Status = cmCTest::COMPLETED;

        }

