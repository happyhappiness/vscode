  m_CTest = 0;
}

//----------------------------------------------------------------------
int cmCTestUpdateHandler::DetermineType(const char* cmd, const char* type)
{
  if ( type && *type )
    {
    std::string stype = cmSystemTools::LowerCase(type);
    if ( stype.find("cvs") != std::string::npos )
      {
      return cmCTestUpdateHandler::e_CVS;
      }
    if ( stype.find("svn") != std::string::npos )
      {
      return cmCTestUpdateHandler::e_SVN;
      }
    }
  else
    {
    std::string stype = cmSystemTools::LowerCase(cmd);
    if ( stype.find("cvs") != std::string::npos )
      {
      return cmCTestUpdateHandler::e_CVS;
      }
    if ( stype.find("svn") != std::string::npos )
      {
      return cmCTestUpdateHandler::e_SVN;
      }
    }
  return cmCTestUpdateHandler::e_CVS;
}

//----------------------------------------------------------------------
//clearly it would be nice if this were broken up into a few smaller
//functions and commented...
int cmCTestUpdateHandler::ProcessHandler()
{
  int count = 0;
  int updateType = e_CVS;
  std::string::size_type cc, kk;


  // Get source dir
  std::string sourceDirectory = m_CTest->GetDartConfiguration("SourceDirectory");
  if ( sourceDirectory.empty() )
    {
    std::cerr << "Cannot find SourceDirectory  key in the DartConfiguration.tcl" << std::endl;
    return -1;
    }

  std::cout << "Updating the repository: " << sourceDirectory.c_str() << std::endl;

  // Get update command
  std::string updateCommand = m_CTest->GetDartConfiguration("UpdateCommand");
  if ( updateCommand.empty() )
    {
    updateCommand = m_CTest->GetDartConfiguration("CVSCommand");
    if ( updateCommand.empty() )
      {
      updateCommand = m_CTest->GetDartConfiguration("SVNCommand");
      if ( updateCommand.empty() )
        {
        std::cerr << "Cannot find CVSCommand, SVNCommand, or UpdateCommand key in the DartConfiguration.tcl" << std::endl;
        return -1;
        }
      else
        {
        updateType = e_SVN;
        }
      }
    else
      {
      updateType = e_CVS;
      }
    }
  else
    {
    updateType = this->DetermineType(updateCommand.c_str(), m_CTest->GetDartConfiguration("UpdateType").c_str());
    }

  // And update options
  std::string updateOptions = m_CTest->GetDartConfiguration("UpdateOptions");
  if ( updateOptions.empty() )
    {
    switch (updateType)
      {
    case cmCTestUpdateHandler::e_CVS:
      updateOptions = m_CTest->GetDartConfiguration("CVSUpdateOptions");
      break;
    case cmCTestUpdateHandler::e_SVN:
      updateOptions = m_CTest->GetDartConfiguration("SVNUpdateOptions");
      break;
      }
    }

  // Get update time
  std::string extra_update_opts;
  if ( m_CTest->GetTestModel() == cmCTest::NIGHTLY )
    {
    struct tm* t = cmCTest::GetNightlyTime(m_CTest->GetDartConfiguration("NightlyStartTime"),
      m_Verbose, m_CTest->GetTomorrowTag());
    char current_time[1024];
    sprintf(current_time, "%04d-%02d-%02d %02d:%02d:%02d",
      t->tm_year + 1900,
      t->tm_mon + 1,
      t->tm_mday,
      t->tm_hour,
      t->tm_min,
      t->tm_sec);
    std::string today_update_date = current_time;

    // TODO: SVN
    switch ( updateType )
      {
    case cmCTestUpdateHandler::e_CVS:
      extra_update_opts += "-D \"" + today_update_date +" UTC\"";
      break;
    case cmCTestUpdateHandler::e_SVN:
      extra_update_opts += "-r \"{" + today_update_date +" +0000}\"";
      break;
      }
    }

  // First, check what the current state of repository is
  std::string command = "";
  switch( updateType )
    {
  case cmCTestUpdateHandler::e_CVS:
    // TODO: CVS - for now just leave empty
    break;
  case cmCTestUpdateHandler::e_SVN:
    command = updateCommand + " info";
    break;
    }

  cmGeneratedFileStream ofs;
  if ( !m_CTest->GetShowOnly() )
    {
    m_CTest->OpenOutputFile("Temporary", "LastUpdate.log", ofs);
    }

  // CVS variables
  // SVN variables
  int svn_current_revision = 0;
  int svn_latest_revision = 0;
  int svn_use_status = 0;

  std::string goutput;
  int retVal = 0;
  bool res = true;

  if ( !command.empty() )
    {
    if ( m_Verbose )
      {
      std::cout << "* Get repository information: " << command.c_str() << std::endl;
      }
    if ( !m_CTest->GetShowOnly() )
      {
      res = cmSystemTools::RunSingleCommand(command.c_str(), &goutput, 
        &retVal, sourceDirectory.c_str(),
        m_Verbose, 0 /*m_TimeOut*/);
      if ( ofs )
        {
        ofs << "--- Update information ---" << std::endl;
        ofs << goutput << std::endl;
        }
      switch ( updateType )
        {
      case cmCTestUpdateHandler::e_CVS:
        // TODO: CVS - for now just leave empty
        break;
      case cmCTestUpdateHandler::e_SVN:
          {
          cmsys::RegularExpression current_revision_regex("Revision: ([0-9]+)");
          if ( current_revision_regex.find(goutput.c_str()) )
            {
            std::string currentRevisionString = current_revision_regex.match(1);
            svn_current_revision = atoi(currentRevisionString.c_str());
            std::cout << "   Old revision of repository is: " << svn_current_revision << std::endl;
            }
          }
        break;
        }
      }
    else
      {
      std::cout << "Update with command: " << command << std::endl;
      }
    }


  command = "";
  switch( updateType )
    {
  case cmCTestUpdateHandler::e_CVS:
    command = updateCommand + " -z3 update " + updateOptions +
      " " + extra_update_opts;
    break;
  case cmCTestUpdateHandler::e_SVN:
    command = updateCommand + " update " + updateOptions +
      " " + extra_update_opts;
    }
  cmGeneratedFileStream os; 
  if ( !m_CTest->OpenOutputFile(m_CTest->GetCurrentTag(), "Update.xml", os, true) )
    {
