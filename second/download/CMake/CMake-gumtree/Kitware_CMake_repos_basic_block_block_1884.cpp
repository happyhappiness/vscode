{
#ifdef __CYGWIN__
  // _SC_PAGE_SIZE does return the mmap() granularity on Cygwin,
  // see http://cygwin.com/ml/cygwin/2006-06/msg00350.html
  // Therefore just use 4096 as the page size of Windows.
  long m = sysconf(_SC_PHYS_PAGES);
  if (m < 0) {
    return false;
  }
  this->TotalPhysicalMemory = m >> 8;
  return true;
#else
  return false;
#endif
}