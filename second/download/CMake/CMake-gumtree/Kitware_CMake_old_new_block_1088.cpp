{
    char ver[256];
    sprintf(ver,"%i.%i",cmVersion::GetMajorVersion(),
            cmVersion::GetMinorVersion());
    this->CacheManager->AddCacheEntry
      ("CMAKE_BACKWARDS_COMPATIBILITY",ver, 
       "For backwards compatibility, what version of CMake commands and "
       "syntax should this version of CMake allow.",
       cmCacheManager::INTERNAL);
    }