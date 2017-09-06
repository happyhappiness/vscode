int cmCTestScriptHandler::ExtractVariables()
{
  // get some info that should be set
  m_Makefile = m_LocalGenerator->GetMakefile();

  // Temporary variables
  const char* minInterval;
  const char* contDuration;

  m_SourceDir   = m_Makefile->GetSafeDefinition("CTEST_SOURCE_DIRECTORY");
  m_BinaryDir   = m_Makefile->GetSafeDefinition("CTEST_BINARY_DIRECTORY");
  m_CTestCmd    = m_Makefile->GetSafeDefinition("CTEST_COMMAND");
  m_CVSCheckOut = m_Makefile->GetSafeDefinition("CTEST_CVS_CHECKOUT");
  m_CTestRoot   = m_Makefile->GetSafeDefinition("CTEST_DASHBOARD_ROOT");
  m_CVSCmd      = m_Makefile->GetSafeDefinition("CTEST_CVS_COMMAND");
  m_CTestEnv    = m_Makefile->GetSafeDefinition("CTEST_ENVIRONMENT");
  m_InitCache   = m_Makefile->GetSafeDefinition("CTEST_INITIAL_CACHE");
  m_CMakeCmd    = m_Makefile->GetSafeDefinition("CTEST_CMAKE_COMMAND");
  m_CMOutFile   = m_Makefile->GetSafeDefinition("CTEST_CMAKE_OUTPUT_FILE_NAME");

  m_Backup      = m_Makefile->IsOn("CTEST_BACKUP_AND_RESTORE");
  m_EmptyBinDir = m_Makefile->IsOn("CTEST_START_WITH_EMPTY_BINARY_DIRECTORY");
  m_EmptyBinDirOnce = m_Makefile->IsOn("CTEST_START_WITH_EMPTY_BINARY_DIRECTORY_ONCE");

  minInterval   = m_Makefile->GetDefinition("CTEST_CONTINUOUS_MINIMUM_INTERVAL");
  contDuration  = m_Makefile->GetDefinition("CTEST_CONTINUOUS_DURATION");

  char updateVar[40];
  int i;
  for (i = 1; i < 10; ++i)
    {
    sprintf(updateVar,"CTEST_EXTRA_UPDATES_%i",i);
    const char *updateVal = m_Makefile->GetDefinition(updateVar);
    if ( updateVal )
      {
      if ( m_CVSCmd.empty() )
        {
        cmSystemTools::Error(updateVar, " specified without specifying CTEST_CVS_COMMAND.");
        return 12;
        }
      m_ExtraUpdates.push_back(updateVal);
      }
    }

  // in order to backup and restore we also must have the cvs root
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
  if (m_CTestRoot.empty() )
    {
    m_CTestRoot = cmSystemTools::GetFilenamePath(m_SourceDir).c_str();
    }

  // the script may override the minimum continuous interval
  if (minInterval)
    {
    m_MinimumInterval = 60 * atof(minInterval);
    }
  if (contDuration)
    {
    m_ContinuousDuration = 60.0 * atof(contDuration);
    }
  
  
  return 0;
}