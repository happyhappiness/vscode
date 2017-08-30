      }
    if ( tag.size() == 0 || m_Tests[cmCTest::START_TEST] || m_Tests[ALL_TEST])
      {
      //std::cout << "TestModel: " << this->GetTestModelString() << std::endl;
      //std::cout << "TestModel: " << m_TestModel << std::endl;
      if ( m_TestModel == cmCTest::NIGHTLY )
        {
        lctime = ::GetNightlyTime(m_DartConfiguration["NightlyStartTime"]);
        }
      char datestring[100];
      sprintf(datestring, "%04d%02d%02d-%02d%02d",
              lctime->tm_year + 1900,
