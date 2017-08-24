{
#if defined(KWSYS_CXX_HAS_GETLOADAVG)
  double loadavg[3] = { 0.0, 0.0, 0.0 };
  if (getloadavg(loadavg, 3) > 0) {
    return loadavg[0];
  }
  return -0.0;
#elif defined(KWSYS_SYSTEMINFORMATION_USE_GetSystemTimes)
  // Old windows.h headers do not provide GetSystemTimes.
  typedef BOOL(WINAPI * GetSystemTimesType)(LPFILETIME, LPFILETIME,
                                            LPFILETIME);
  static GetSystemTimesType pGetSystemTimes =
    (GetSystemTimesType)GetProcAddress(GetModuleHandleW(L"kernel32"),
                                       "GetSystemTimes");
  FILETIME idleTime, kernelTime, userTime;
  if (pGetSystemTimes && pGetSystemTimes(&idleTime, &kernelTime, &userTime)) {
    unsigned __int64 const idleTicks = fileTimeToUInt64(idleTime);
    unsigned __int64 const totalTicks =
      fileTimeToUInt64(kernelTime) + fileTimeToUInt64(userTime);
    return calculateCPULoad(idleTicks, totalTicks) * GetNumberOfPhysicalCPU();
  }
  return -0.0;
#else
  // Not implemented on this platform.
  return -0.0;
#endif
}