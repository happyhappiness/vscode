    }

  if ( m_Tests[TEST_TEST] || m_Tests[ALL_TEST] || notest )

    {

    res += this->TestDirectory();

    }

  if ( m_Tests[COVERAGE_TEST] || m_Tests[ALL_TEST] )

    {
