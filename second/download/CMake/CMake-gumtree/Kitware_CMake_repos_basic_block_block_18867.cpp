{
  unsigned long info;
  int which[] = {CTL_HW, HW_PHYSMEM};

  size_t size = sizeof(info);

  if (sysctl(which, 2, &info, &size, NULL, 0))
    return -errno;

  return (uint64_t) info;
}