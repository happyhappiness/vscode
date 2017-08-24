{
#if defined(_SC_PHYS_PAGES) && defined(_SC_PAGESIZE)
  // Assume the mmap() granularity as returned by _SC_PAGESIZE is also
  // the system page size. The only known system where this isn't true
  // is Cygwin.
  long p = sysconf(_SC_PHYS_PAGES);
  long m = sysconf(_SC_PAGESIZE);

  if (p < 0 || m < 0) {
    return false;
  }

  // assume pagesize is a power of 2 and smaller 1 MiB
  size_t pagediv = (1024 * 1024 / m);

  this->TotalPhysicalMemory = p;
  this->TotalPhysicalMemory /= pagediv;

#if defined(_SC_AVPHYS_PAGES)
  p = sysconf(_SC_AVPHYS_PAGES);
  if (p < 0) {
    return false;
  }

  this->AvailablePhysicalMemory = p;
  this->AvailablePhysicalMemory /= pagediv;
#endif

  return true;
#else
  return false;
#endif
}