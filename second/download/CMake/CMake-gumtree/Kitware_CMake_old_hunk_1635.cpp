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

