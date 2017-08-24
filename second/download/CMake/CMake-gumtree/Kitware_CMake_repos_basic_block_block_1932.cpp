{
#if defined(__OpenBSD__) || defined(__FreeBSD__) || defined(__NetBSD__) ||    \
  defined(__DragonFly__)
  int ctrl[2] = { CTL_HW, HW_PHYSMEM };
#if defined(HW_PHYSMEM64)
  int64_t k;
  ctrl[1] = HW_PHYSMEM64;
#else
  int k;
#endif
  size_t sz = sizeof(k);

  if (sysctl(ctrl, 2, &k, &sz, NULL, 0) != 0) {
    return false;
  }

  this->TotalPhysicalMemory = k >> 10 >> 10;

  return true;
#else
  return false;
#endif
}