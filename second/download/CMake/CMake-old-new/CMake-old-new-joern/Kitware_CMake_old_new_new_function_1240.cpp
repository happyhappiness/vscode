int cmake::LoadCache()
{
  // could we not read the cache
  if (!this->CacheManager->LoadCache(this->GetHomeOutputDirectory()))
    {
    // if it does exist, but isn;t readable then warn the user
    std::string cacheFile = this->GetHomeOutputDirectory();
    cacheFile += "/CMakeCache.txt";
    if(cmSystemTools::FileExists(cacheFile.c_str()))
      {
      cmSystemTools::Error(
        "There is a CMakeCache.txt file for the current binary tree but "
        "cmake does not have permission to read it. Please check the "
        "permissions of the directory you are trying to run CMake on.");
      return -1;
      }
    }

  if (this->CMakeCommand.size() < 2)
    {
    cmSystemTools::Error(
      "cmake command was not specified prior to loading the cache in "
      "cmake.cxx");
    return -1;
    }

  // setup CMAKE_ROOT and CMAKE_COMMAND
  if(!this->AddCMakePaths(this->CMakeCommand.c_str()))
    {
    return -3;
    }

  // set the default BACKWARDS compatibility to the current version
  if(!this->CacheManager->GetCacheValue("CMAKE_BACKWARDS_COMPATIBILITY"))
    {
    char ver[256];
    sprintf(ver,"%i.%i",cmVersion::GetMajorVersion(),
            cmVersion::GetMinorVersion());
    this->CacheManager->AddCacheEntry
      ("CMAKE_BACKWARDS_COMPATIBILITY",ver, 
       "For backwards compatibility, what version of CMake commands and "
       "syntax should this version of CMake allow.",
       cmCacheManager::STRING);
    }

  return 0;
}