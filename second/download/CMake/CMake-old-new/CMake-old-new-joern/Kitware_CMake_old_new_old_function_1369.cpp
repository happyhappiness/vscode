int cmCTestScriptHandler::ExtractVariables()
{
  // get some info that should be set
  m_Makefile = m_LocalGenerator->GetMakefile();

  m_SourceDir = m_Makefile->GetSafeDefinition("CTEST_SOURCE_DIRECTORY");
  m_BinaryDir = m_Makefile->GetSafeDefinition("CTEST_BINARY_DIRECTORY");
  m_CTestCmd  = m_Makefile->GetSafeDefinition("CTEST_COMMAND");
  m_Backup    = m_Makefile->IsOn("CTEST_BACKUP_AND_RESTORE");

  // in order to backup and restore we also must have the cvs root
  m_CVSCheckOut = m_Makefile->GetSafeDefinition("CTEST_CVS_CHECKOUT");
  if (m_Backup && m_CVSCheckOut.empty())
    {
    cmSystemTools::Error(
      "Backup was requested without specifying CTEST_CVS_CHECKOUT.");    
    return 3;
    }
  
  // make sure the required info is here
  if (this->m_SourceDir.empty() || 
      this->m_BinaryDir.empty() || 
      this->m_CTestCmd.empty())
    {
    std::string message = "CTEST_SOURCE_DIRECTORY = ";
    message += (!m_SourceDir.empty()) ? m_SourceDir.c_str() : "(Null)";
    message += "\nCTEST_BINARY_DIRECTORY = ";
    message += (!m_BinaryDir.empty()) ? m_BinaryDir.c_str() : "(Null)";
    message += "\nCTEST_COMMAND = ";
    message += (!m_CTestCmd.empty()) ? m_CTestCmd.c_str() : "(Null)";
    cmSystemTools::Error(
      "Some required settings in the configuration file were missing:\n",
      message.c_str());
    return 4;
    }
  
  // if the dashboard root isn't specified then we can compute it from the
  // m_SourceDir
  if (m_Makefile->GetDefinition("CTEST_DASHBOARD_ROOT"))
    {
    m_CTestRoot = m_Makefile->GetDefinition("CTEST_DASHBOARD_ROOT");
    }
  else
    {
    m_CTestRoot = cmSystemTools::GetFilenamePath(m_SourceDir).c_str();
    }

  // the script may override the minimum continuous interval
  if (m_Makefile->GetDefinition("CTEST_CONTINUOUS_MINIMUM_INTERVAL"))
    {
    m_MinimumInterval = 60*
      atof(m_Makefile->GetDefinition("CTEST_CONTINUOUS_MINIMUM_INTERVAL"));
    }
  
  m_CVSCmd = m_Makefile->GetSafeDefinition("CTEST_CVS_COMMAND");
  
  return 0;
}