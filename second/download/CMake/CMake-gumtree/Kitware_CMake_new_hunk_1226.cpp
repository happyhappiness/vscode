  std::string extra_update_opts;
  if ( m_CTest->GetTestModel() == cmCTest::NIGHTLY )
    {
    struct tm* t = m_CTest->GetNightlyTime(m_CTest->GetCTestConfiguration("NightlyStartTime"),
      m_CTest->GetTomorrowTag());
    char current_time[1024];
    sprintf(current_time, "%04d-%02d-%02d %02d:%02d:%02d",
      t->tm_year + 1900,
