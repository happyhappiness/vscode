(RetrieveCPUExtendedLevelSupport(0x80000006)) {
    if (!call_cpuid(0x80000006, L2Cache)) {
      return false;
    }
    // Save the L2 unified cache size (in KB) from ecx: bits 31..16.
    this->Features.L2CacheSize = ((L2Cache[2] & 0xFFFF0000) >> 16);
  } else {
    // Store -1 to indicate the cache could not be queried.
    this->Features.L2CacheSize = -1;
  }