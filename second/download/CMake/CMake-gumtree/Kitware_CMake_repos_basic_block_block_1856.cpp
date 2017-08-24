{
#if defined(_SC_NPROC_ONLN) && !defined(_SC_NPROCESSORS_ONLN)
// IRIX names this slightly different
#define _SC_NPROCESSORS_ONLN _SC_NPROC_ONLN
#endif

#ifdef _SC_NPROCESSORS_ONLN
  long c = sysconf(_SC_NPROCESSORS_ONLN);
  if (c <= 0) {
    return false;
  }

  this->NumberOfPhysicalCPU = static_cast<unsigned int>(c);
  this->NumberOfLogicalCPU = this->NumberOfPhysicalCPU;

  return true;
#else
  return false;
#endif
}