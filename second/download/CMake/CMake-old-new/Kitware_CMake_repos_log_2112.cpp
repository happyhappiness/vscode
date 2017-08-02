sprintf(buffer, "Cache version: %d.%d, CMake version: %d.%d",
          info->CAPI->GetCacheMajorVersion(mf),
          info->CAPI->GetCacheMinorVersion(mf),
          info->CAPI->GetMajorVersion(mf), info->CAPI->GetMinorVersion(mf))