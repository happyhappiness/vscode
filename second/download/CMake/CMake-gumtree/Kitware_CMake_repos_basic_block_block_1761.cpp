{
#if USE_CPUID
  int TLBCode = -1, TLBData = -1, L1Code = -1, L1Data = -1, L1Trace = -1,
      L2Unified = -1, L3Unified = -1;
  int TLBCacheData[4] = { 0, 0, 0, 0 };
  int TLBPassCounter = 0;
  int TLBCacheUnit = 0;

  do {
    if (!call_cpuid(2, TLBCacheData)) {
      return false;
    }

    int bob = ((TLBCacheData[0] & 0x00FF0000) >> 16);
    (void)bob;
    // Process the returned TLB and cache information.
    for (int nCounter = 0; nCounter < TLBCACHE_INFO_UNITS; nCounter++) {
      // First of all - decide which unit we are dealing with.
      switch (nCounter) {
        // eax: bits 8..15 : bits 16..23 : bits 24..31
        case 0:
          TLBCacheUnit = ((TLBCacheData[0] & 0x0000FF00) >> 8);
          break;
        case 1:
          TLBCacheUnit = ((TLBCacheData[0] & 0x00FF0000) >> 16);
          break;
        case 2:
          TLBCacheUnit = ((TLBCacheData[0] & 0xFF000000) >> 24);
          break;

        // ebx: bits 0..7 : bits 8..15 : bits 16..23 : bits 24..31
        case 3:
          TLBCacheUnit = ((TLBCacheData[1] & 0x000000FF) >> 0);
          break;
        case 4:
          TLBCacheUnit = ((TLBCacheData[1] & 0x0000FF00) >> 8);
          break;
        case 5:
          TLBCacheUnit = ((TLBCacheData[1] & 0x00FF0000) >> 16);
          break;
        case 6:
          TLBCacheUnit = ((TLBCacheData[1] & 0xFF000000) >> 24);
          break;

        // ecx: bits 0..7 : bits 8..15 : bits 16..23 : bits 24..31
        case 7:
          TLBCacheUnit = ((TLBCacheData[2] & 0x000000FF) >> 0);
          break;
        case 8:
          TLBCacheUnit = ((TLBCacheData[2] & 0x0000FF00) >> 8);
          break;
        case 9:
          TLBCacheUnit = ((TLBCacheData[2] & 0x00FF0000) >> 16);
          break;
        case 10:
          TLBCacheUnit = ((TLBCacheData[2] & 0xFF000000) >> 24);
          break;

        // edx: bits 0..7 : bits 8..15 : bits 16..23 : bits 24..31
        case 11:
          TLBCacheUnit = ((TLBCacheData[3] & 0x000000FF) >> 0);
          break;
        case 12:
          TLBCacheUnit = ((TLBCacheData[3] & 0x0000FF00) >> 8);
          break;
        case 13:
          TLBCacheUnit = ((TLBCacheData[3] & 0x00FF0000) >> 16);
          break;
        case 14:
          TLBCacheUnit = ((TLBCacheData[3] & 0xFF000000) >> 24);
          break;

        // Default case - an error has occurred.
        default:
          return false;
      }

      // Now process the resulting unit to see what it means....
      switch (TLBCacheUnit) {
        case 0x00:
          break;
        case 0x01:
          STORE_TLBCACHE_INFO(TLBCode, 4);
          break;
        case 0x02:
          STORE_TLBCACHE_INFO(TLBCode, 4096);
          break;
        case 0x03:
          STORE_TLBCACHE_INFO(TLBData, 4);
          break;
        case 0x04:
          STORE_TLBCACHE_INFO(TLBData, 4096);
          break;
        case 0x06:
          STORE_TLBCACHE_INFO(L1Code, 8);
          break;
        case 0x08:
          STORE_TLBCACHE_INFO(L1Code, 16);
          break;
        case 0x0a:
          STORE_TLBCACHE_INFO(L1Data, 8);
          break;
        case 0x0c:
          STORE_TLBCACHE_INFO(L1Data, 16);
          break;
        case 0x10:
          STORE_TLBCACHE_INFO(L1Data, 16);
          break; // <-- FIXME: IA-64 Only
        case 0x15:
          STORE_TLBCACHE_INFO(L1Code, 16);
          break; // <-- FIXME: IA-64 Only
        case 0x1a:
          STORE_TLBCACHE_INFO(L2Unified, 96);
          break; // <-- FIXME: IA-64 Only
        case 0x22:
          STORE_TLBCACHE_INFO(L3Unified, 512);
          break;
        case 0x23:
          STORE_TLBCACHE_INFO(L3Unified, 1024);
          break;
        case 0x25:
          STORE_TLBCACHE_INFO(L3Unified, 2048);
          break;
        case 0x29:
          STORE_TLBCACHE_INFO(L3Unified, 4096);
          break;
        case 0x39:
          STORE_TLBCACHE_INFO(L2Unified, 128);
          break;
        case 0x3c:
          STORE_TLBCACHE_INFO(L2Unified, 256);
          break;
        case 0x40:
          STORE_TLBCACHE_INFO(L2Unified, 0);
          break; // <-- FIXME: No integrated L2 cache (P6 core) or L3 cache (P4
                 // core).
        case 0x41:
          STORE_TLBCACHE_INFO(L2Unified, 128);
          break;
        case 0x42:
          STORE_TLBCACHE_INFO(L2Unified, 256);
          break;
        case 0x43:
          STORE_TLBCACHE_INFO(L2Unified, 512);
          break;
        case 0x44:
          STORE_TLBCACHE_INFO(L2Unified, 1024);
          break;
        case 0x45:
          STORE_TLBCACHE_INFO(L2Unified, 2048);
          break;
        case 0x50:
          STORE_TLBCACHE_INFO(TLBCode, 4096);
          break;
        case 0x51:
          STORE_TLBCACHE_INFO(TLBCode, 4096);
          break;
        case 0x52:
          STORE_TLBCACHE_INFO(TLBCode, 4096);
          break;
        case 0x5b:
          STORE_TLBCACHE_INFO(TLBData, 4096);
          break;
        case 0x5c:
          STORE_TLBCACHE_INFO(TLBData, 4096);
          break;
        case 0x5d:
          STORE_TLBCACHE_INFO(TLBData, 4096);
          break;
        case 0x66:
          STORE_TLBCACHE_INFO(L1Data, 8);
          break;
        case 0x67:
          STORE_TLBCACHE_INFO(L1Data, 16);
          break;
        case 0x68:
          STORE_TLBCACHE_INFO(L1Data, 32);
          break;
        case 0x70:
          STORE_TLBCACHE_INFO(L1Trace, 12);
          break;
        case 0x71:
          STORE_TLBCACHE_INFO(L1Trace, 16);
          break;
        case 0x72:
          STORE_TLBCACHE_INFO(L1Trace, 32);
          break;
        case 0x77:
          STORE_TLBCACHE_INFO(L1Code, 16);
          break; // <-- FIXME: IA-64 Only
        case 0x79:
          STORE_TLBCACHE_INFO(L2Unified, 128);
          break;
        case 0x7a:
          STORE_TLBCACHE_INFO(L2Unified, 256);
          break;
        case 0x7b:
          STORE_TLBCACHE_INFO(L2Unified, 512);
          break;
        case 0x7c:
          STORE_TLBCACHE_INFO(L2Unified, 1024);
          break;
        case 0x7e:
          STORE_TLBCACHE_INFO(L2Unified, 256);
          break;
        case 0x81:
          STORE_TLBCACHE_INFO(L2Unified, 128);
          break;
        case 0x82:
          STORE_TLBCACHE_INFO(L2Unified, 256);
          break;
        case 0x83:
          STORE_TLBCACHE_INFO(L2Unified, 512);
          break;
        case 0x84:
          STORE_TLBCACHE_INFO(L2Unified, 1024);
          break;
        case 0x85:
          STORE_TLBCACHE_INFO(L2Unified, 2048);
          break;
        case 0x88:
          STORE_TLBCACHE_INFO(L3Unified, 2048);
          break; // <-- FIXME: IA-64 Only
        case 0x89:
          STORE_TLBCACHE_INFO(L3Unified, 4096);
          break; // <-- FIXME: IA-64 Only
        case 0x8a:
          STORE_TLBCACHE_INFO(L3Unified, 8192);
          break; // <-- FIXME: IA-64 Only
        case 0x8d:
          STORE_TLBCACHE_INFO(L3Unified, 3096);
          break; // <-- FIXME: IA-64 Only
        case 0x90:
          STORE_TLBCACHE_INFO(TLBCode, 262144);
          break; // <-- FIXME: IA-64 Only
        case 0x96:
          STORE_TLBCACHE_INFO(TLBCode, 262144);
          break; // <-- FIXME: IA-64 Only
        case 0x9b:
          STORE_TLBCACHE_INFO(TLBCode, 262144);
          break; // <-- FIXME: IA-64 Only

        // Default case - an error has occurred.
        default:
          return false;
      }
    }

    // Increment the TLB pass counter.
    TLBPassCounter++;
  } while ((TLBCacheData[0] & 0x000000FF) > TLBPassCounter);

  // Ok - we now have the maximum TLB, L1, L2, and L3 sizes...
  if ((L1Code == -1) && (L1Data == -1) && (L1Trace == -1)) {
    this->Features.L1CacheSize = -1;
  } else if ((L1Code == -1) && (L1Data == -1) && (L1Trace != -1)) {
    this->Features.L1CacheSize = L1Trace;
  } else if ((L1Code != -1) && (L1Data == -1)) {
    this->Features.L1CacheSize = L1Code;
  } else if ((L1Code == -1) && (L1Data != -1)) {
    this->Features.L1CacheSize = L1Data;
  } else if ((L1Code != -1) && (L1Data != -1)) {
    this->Features.L1CacheSize = L1Code + L1Data;
  } else {
    this->Features.L1CacheSize = -1;
  }

  // Ok - we now have the maximum TLB, L1, L2, and L3 sizes...
  if (L2Unified == -1) {
    this->Features.L2CacheSize = -1;
  } else {
    this->Features.L2CacheSize = L2Unified;
  }

  // Ok - we now have the maximum TLB, L1, L2, and L3 sizes...
  if (L3Unified == -1) {
    this->Features.L3CacheSize = -1;
  } else {
    this->Features.L3CacheSize = L3Unified;
  }

  return true;

#else
  return false;
#endif
}