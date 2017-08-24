      {
      if (res == cmsysProcess_State_Exited && retVal == 0)
        {
        std::cerr <<   "   Passed\n";
        passed.push_back(testname);
        cres.m_Status = cmCTest::COMPLETED;
        }
