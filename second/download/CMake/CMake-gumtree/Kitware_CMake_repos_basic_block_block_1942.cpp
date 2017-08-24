{
#if defined(__OpenBSD__) || defined(__FreeBSD__) || defined(__NetBSD__) ||    \
  defined(__DragonFly__)
  int k;
  size_t sz = sizeof(k);
  int ctrl[2] = { CTL_HW, HW_NCPU };

  if (sysctl(ctrl, 2, &k, &sz, NULL, 0) != 0) {
    return false;
  }

  this->NumberOfPhysicalCPU = k;
  this->NumberOfLogicalCPU = this->NumberOfPhysicalCPU;

#if defined(HW_CPUSPEED)
  ctrl[1] = HW_CPUSPEED;

  if (sysctl(ctrl, 2, &k, &sz, NULL, 0) != 0) {
    return false;
  }

  this->CPUSpeedInMHz = (float)k;
#endif

#if defined(CPU_SSE)
  ctrl[0] = CTL_MACHDEP;
  ctrl[1] = CPU_SSE;

  if (sysctl(ctrl, 2, &k, &sz, NULL, 0) != 0) {
    return false;
  }

  this->Features.HasSSE = (k > 0);
#endif

#if defined(CPU_SSE2)
  ctrl[0] = CTL_MACHDEP;
  ctrl[1] = CPU_SSE2;

  if (sysctl(ctrl, 2, &k, &sz, NULL, 0) != 0) {
    return false;
  }

  this->Features.HasSSE2 = (k > 0);
#endif

#if defined(CPU_CPUVENDOR)
  ctrl[0] = CTL_MACHDEP;
  ctrl[1] = CPU_CPUVENDOR;
  char vbuf[25];
  ::memset(vbuf, 0, sizeof(vbuf));
  sz = sizeof(vbuf) - 1;
  if (sysctl(ctrl, 2, vbuf, &sz, NULL, 0) != 0) {
    return false;
  }

  this->ChipID.Vendor = vbuf;
  this->FindManufacturer();
#endif

  return true;
#else
  return false;
#endif
}