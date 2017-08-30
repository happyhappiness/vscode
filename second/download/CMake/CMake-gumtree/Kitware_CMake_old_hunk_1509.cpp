    currentcwd += "/CMakeCache.txt";
    oldcwd += "/CMakeCache.txt";
    if(!cmSystemTools::SameFile(oldcwd.c_str(), currentcwd.c_str()))
      { 
      std::string message = 
        std::string("The current CMakeCache.txt directory ") +
        currentcwd + std::string(" is different than the directory ") + 
        std::string(this->GetCacheValue("CMAKE_CACHEFILE_DIR")) +
        std::string(" where CMackeCache.txt was created. This may result "
                    "in binaries being created in the wrong place. If you "
                    "are not sure, reedit the CMakeCache.txt");
      cmSystemTools::Error(message.c_str());   
      }
    }
  return true;
}

bool cmCacheManager::SaveCache(cmMakefile* mf) 
{
  return this->SaveCache(mf->GetHomeOutputDirectory());
}


bool cmCacheManager::SaveCache(const char* path) 
{
  std::string cacheFile = path;
  cacheFile += "/CMakeCache.txt";
  std::string tempFile = cacheFile;
  tempFile += ".tmp";
  std::ofstream fout(tempFile.c_str());
  if(!fout)
    {  
    cmSystemTools::Error("Unable to open cache file for save. ", 
                         cacheFile.c_str());
    cmSystemTools::ReportLastSystemError("");
    return false;
    }
  // before writing the cache, update the version numbers
  // to the 
  char temp[1024];
  sprintf(temp, "%d", cmMakefile::GetMinorVersion());
  this->AddCacheEntry("CMAKE_CACHE_MINOR_VERSION", temp,
