  std::string extra_update_opts;

  if ( m_TestModel == cmCTest::NIGHTLY )

    {

    struct tm* t = ::GetNightlyTime(m_DartConfiguration["NightlyStartTime"]);

    char current_time[1024];

    sprintf(current_time, "%04d-%02d-%02d %02d:%02d:%02d UTC",

      t->tm_year + 1900,

