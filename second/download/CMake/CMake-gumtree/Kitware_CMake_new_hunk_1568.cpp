      cmCTestLog(this, DEBUG, "TestModel: " << m_TestModel << std::endl);
      if ( m_TestModel == cmCTest::NIGHTLY )
        {
        lctime = this->GetNightlyTime(this->GetCTestConfiguration("NightlyStartTime"), m_TomorrowTag);
        }
      char datestring[100];
      sprintf(datestring, "%04d%02d%02d-%02d%02d",
