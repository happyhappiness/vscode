(!call_cpuid(0x80000000, cpuinfo)) {
    return false;
  }