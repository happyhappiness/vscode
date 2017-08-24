  else
    {
    updateType = this->DetermineType(updateCommand.c_str(),
      this->CTest->GetCTestConfiguration("UpdateType").c_str());
    }

  cmCTestLog(this->CTest, HANDLER_OUTPUT, "   Use "
    << cmCTestUpdateHandlerUpdateToString(updateType) << " repository type"
    << std::endl;);

  // And update options
  std::string updateOptions
    = this->CTest->GetCTestConfiguration("UpdateOptions");
  if ( updateOptions.empty() )
    {
    switch (updateType)
      {
    case cmCTestUpdateHandler::e_CVS:
      updateOptions = this->CTest->GetCTestConfiguration("CVSUpdateOptions");
      if ( updateOptions.empty() )
        {
        updateOptions = "-dP";
        }
      break;
    case cmCTestUpdateHandler::e_SVN:
      updateOptions = this->CTest->GetCTestConfiguration("SVNUpdateOptions");
      break;
      }
    }

  // Get update time
  std::string extra_update_opts;
  if ( this->CTest->GetTestModel() == cmCTest::NIGHTLY )
    {
    struct tm* t = this->CTest->GetNightlyTime(
      this->CTest->GetCTestConfiguration("NightlyStartTime"),
      this->CTest->GetTomorrowTag());
    char current_time[1024];
    sprintf(current_time, "%04d-%02d-%02d %02d:%02d:%02d",
      t->tm_year + 1900,
