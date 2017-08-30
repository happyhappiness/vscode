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
