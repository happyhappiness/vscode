    }
  if ( !res )
    {
    m_CacheManager->AddCacheEntry("CMAKE_HOME_DIRECTORY", 
                                  this->GetHomeDirectory(),
                                  "Start directory with the top level CMakeLists.txt file for this project",
                                  cmCacheManager::INTERNAL);
    }
  
  // set the default BACKWARDS compatibility to the current version
  if(!m_CacheManager->GetCacheValue("CMAKE_BACKWARDS_COMPATIBILITY"))
    {
    char ver[256];
    sprintf(ver,"%i.%i",cmMakefile::GetMajorVersion(),
            cmMakefile::GetMinorVersion());
    this->m_CacheManager->AddCacheEntry
      ("CMAKE_BACKWARDS_COMPATIBILITY",ver, 
       "For backwards compatibility, what version of CMake commands and syntax should this version of CMake allow.",
       cmCacheManager::STRING);
    }  
  
  // no generator specified on the command line
  if(!m_GlobalGenerator)
    {
