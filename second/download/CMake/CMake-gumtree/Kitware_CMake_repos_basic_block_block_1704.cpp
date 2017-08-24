{
    case SystemInformation::CPU_FEATURE_L1CACHE:
      return this->Features.L1CacheSize;
    case SystemInformation::CPU_FEATURE_L2CACHE:
      return this->Features.L2CacheSize;
    case SystemInformation::CPU_FEATURE_L3CACHE:
      return this->Features.L3CacheSize;
  }