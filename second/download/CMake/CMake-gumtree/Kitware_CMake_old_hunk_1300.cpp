  m_CTest = 0;
}


//----------------------------------------------------------------------
//clearly it would be nice if this were broken up into a few smaller
//functions and commented...
int cmCTestUpdateHandler::ProcessHandler()
{
  int count = 0;
  std::string::size_type cc, kk;
  std::string cvsCommand = m_CTest->GetDartConfiguration("CVSCommand");
  if ( cvsCommand.size() == 0 )
    {
    std::cerr << "Cannot find CVSCommand key in the DartConfiguration.tcl" << std::endl;
    return -1;
    }
  std::string cvsOptions = m_CTest->GetDartConfiguration("CVSUpdateOptions");
  if ( cvsOptions.size() == 0 )
    {
    std::cerr << "Cannot find CVSUpdateOptions key in the DartConfiguration.tcl" << std::endl;
    return -1;
    }

  std::string sourceDirectory = m_CTest->GetDartConfiguration("SourceDirectory");
  if ( sourceDirectory.size() == 0 )
    {
    std::cerr << "Cannot find SourceDirectory  key in the DartConfiguration.tcl" << std::endl;
    return -1;
    }

  std::string extra_update_opts;
  if ( m_CTest->GetTestModel() == cmCTest::NIGHTLY )
    {
    struct tm* t = cmCTest::GetNightlyTime(m_CTest->GetDartConfiguration("NightlyStartTime"),
      m_Verbose, m_CTest->GetTomorrowTag());
    char current_time[1024];
    sprintf(current_time, "%04d-%02d-%02d %02d:%02d:%02d UTC",
      t->tm_year + 1900,
      t->tm_mon + 1,
      t->tm_mday,
      t->tm_hour,
      t->tm_min,
      t->tm_sec);
    std::string today_update_date = current_time;
   
    extra_update_opts += "-D \"" + today_update_date +"\"";
    //std::cout << "Update: " << extra_update_opts << std::endl;
    }

  std::string command = cvsCommand + " -z3 update " + cvsOptions +
    " " + extra_update_opts;
  cmGeneratedFileStream os; 
  if ( !m_CTest->OpenOutputFile(m_CTest->GetCurrentTag(), "Update.xml", os, true) )
    {
