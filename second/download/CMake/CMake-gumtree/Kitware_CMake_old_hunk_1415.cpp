  if(!this->CacheManager->GetCacheValue("CMAKE_BACKWARDS_COMPATIBILITY"))

    {

    char ver[256];

    sprintf(ver,"%i.%i",cmMakefile::GetMajorVersion(),

            cmMakefile::GetMinorVersion());

    this->CacheManager->AddCacheEntry

      ("CMAKE_BACKWARDS_COMPATIBILITY",ver, 

       "For backwards compatibility, what version of CMake commands and "
