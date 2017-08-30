      std::string tagmode;

      if ( cmSystemTools::GetLineFromStream(tfin, tagmode) )

        {

        if ( tagmode.size() > 4 && !( m_Tests[cmCTest::START_TEST] || m_Tests[ALL_TEST] ))

          {

          m_TestModel = cmCTest::GetTestModelFromString(tagmode.c_str());

          }

        }

      tfin.close();

      }

    if ( tag.size() == 0 || new_tag || m_Tests[cmCTest::START_TEST] || m_Tests[ALL_TEST])

      {

      cmCTestLog(this, DEBUG, "TestModel: " << this->GetTestModelString() << std::endl);

      cmCTestLog(this, DEBUG, "TestModel: " << m_TestModel << std::endl);

      if ( m_TestModel == cmCTest::NIGHTLY )

        {

        lctime = this->GetNightlyTime(this->GetCTestConfiguration("NightlyStartTime"), m_TomorrowTag);

        }

      char datestring[100];

      sprintf(datestring, "%04d%02d%02d-%02d%02d",

