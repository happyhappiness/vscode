      //std::cout << "TestModel: " << m_TestModel << std::endl;

      if ( m_TestModel == cmCTest::NIGHTLY )

        {

        lctime = ::GetNightlyTime(m_DartConfiguration["NightlyStartTime"]);

        }

      char datestring[100];

      sprintf(datestring, "%04d%02d%02d-%02d%02d",

