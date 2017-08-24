(!call_cpuid(0x80000006, L2Cache)) {
      return false;
    }