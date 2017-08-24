{
#if USE_CPUID
  int L1Cache[4] = { 0, 0, 0, 0 };
  int L2Cache[4] = { 0, 0, 0, 0 };

  // Check to see if what we are about to do is supported...
  if (RetrieveCPUExtendedLevelSupport(0x80000005)) {
    if (!call_cpuid(0x80000005, L1Cache)) {
      return false;
    }
    // Save the L1 data cache size (in KB) from ecx: bits 31..24 as well as
    // data cache size from edx: bits 31..24.
    this->Features.L1CacheSize = ((L1Cache[2] & 0xFF000000) >> 24);
    this->Features.L1CacheSize += ((L1Cache[3] & 0xFF000000) >> 24);
  } else {
    // Store -1 to indicate the cache could not be queried.
    this->Features.L1CacheSize = -1;
  }

  // Check to see if what we are about to do is supported...
  if (RetrieveCPUExtendedLevelSupport(0x80000006)) {
    if (!call_cpuid(0x80000006, L2Cache)) {
      return false;
    }
    // Save the L2 unified cache size (in KB) from ecx: bits 31..16.
    this->Features.L2CacheSize = ((L2Cache[2] & 0xFFFF0000) >> 16);
  } else {
    // Store -1 to indicate the cache could not be queried.
    this->Features.L2CacheSize = -1;
  }

  // Define L3 as being not present as we cannot test for it.
  this->Features.L3CacheSize = -1;

#endif

  // Return failure if we cannot detect either cache with this method.
  return ((this->Features.L1CacheSize == -1) &&
          (this->Features.L2CacheSize == -1))
    ? false
    : true;
}