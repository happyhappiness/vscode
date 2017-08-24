    }

  // setup CMAKE_ROOT and CMAKE_COMMAND
  if(!this->AddCMakePaths(m_CMakeCommand.c_str()))
    {
    return -3;
    }

  // set the default BACKWARDS compatibility to the current version
  if(!m_CacheManager->GetCacheValue("CMAKE_BACKWARDS_COMPATIBILITY"))
    {
    char ver[256];
    sprintf(ver,"%i.%i",cmMakefile::GetMajorVersion(),
            cmMakefile::GetMinorVersion());
    this->m_CacheManager->AddCacheEntry
      ("CMAKE_BACKWARDS_COMPATIBILITY",ver,
       "For backwards compatibility, what version of CMake commands and "
       "syntax should this version of CMake allow.",
       cmCacheManager::STRING);
