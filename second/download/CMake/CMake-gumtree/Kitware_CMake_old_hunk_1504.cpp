  else
    {
    updateType = this->DetermineType(updateCommand.c_str(),
      m_CTest->GetCTestConfiguration("UpdateType").c_str());
    }

  cmCTestLog(m_CTest, HANDLER_OUTPUT, "   Use "
    << cmCTestUpdateHandlerUpdateToString(updateType) << " repository type"
    << std::endl;);

  // And update options
  std::string updateOptions = m_CTest->GetCTestConfiguration("UpdateOptions");
  if ( updateOptions.empty() )
    {
    switch (updateType)
      {
    case cmCTestUpdateHandler::e_CVS:
      updateOptions = m_CTest->GetCTestConfiguration("CVSUpdateOptions");
      if ( updateOptions.empty() )
        {
        updateOptions = "-dP";
        }
      break;
    case cmCTestUpdateHandler::e_SVN:
      updateOptions = m_CTest->GetCTestConfiguration("SVNUpdateOptions");
      break;
      }
    }

  // Get update time
  std::string extra_update_opts;
  if ( m_CTest->GetTestModel() == cmCTest::NIGHTLY )
    {
    struct tm* t = m_CTest->GetNightlyTime(
      m_CTest->GetCTestConfiguration("NightlyStartTime"),
      m_CTest->GetTomorrowTag());
    char current_time[1024];
    sprintf(current_time, "%04d-%02d-%02d %02d:%02d:%02d",
      t->tm_year + 1900,
