{
#if defined(__SVR4) && defined(__sun)
// Solaris allows querying this value by sysconf, but if this is
// a 32 bit process on a 64 bit host the returned memory will be
// limited to 4GiB. So if this is a 32 bit process or if the sysconf
// method fails use the kstat interface.
#if SIZEOF_VOID_P == 8
  if (this->QueryMemoryBySysconf()) {
    return true;
  }
#endif

  char* tail;
  unsigned long totalMemory =
    strtoul(this->ParseValueFromKStat("-s physmem").c_str(), &tail, 0);
  this->TotalPhysicalMemory = totalMemory / 128;

  return true;
#else
  return false;
#endif
}