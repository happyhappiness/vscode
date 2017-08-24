{
#if defined(__hpux)
  unsigned long tv = 0;
  unsigned long tp = 0;
  unsigned long av = 0;
  unsigned long ap = 0;
  struct pst_static pst;
  struct pst_dynamic pdy;

  unsigned long ps = 0;
  if (pstat_getstatic(&pst, sizeof(pst), (size_t)1, 0) == -1) {
    return false;
  }

  ps = pst.page_size;
  tp = pst.physical_memory * ps;
  tv = (pst.physical_memory + pst.pst_maxmem) * ps;
  if (pstat_getdynamic(&pdy, sizeof(pdy), (size_t)1, 0) == -1) {
    return false;
  }

  ap = tp - pdy.psd_rm * ps;
  av = tv - pdy.psd_vm;
  this->TotalVirtualMemory = tv >> 10 >> 10;
  this->TotalPhysicalMemory = tp >> 10 >> 10;
  this->AvailableVirtualMemory = av >> 10 >> 10;
  this->AvailablePhysicalMemory = ap >> 10 >> 10;
  return true;
#else
  return false;
#endif
}