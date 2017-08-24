{
  struct sysinfo info;

  if (sysinfo(&info) == 0)
    return (uint64_t) info.freeram * info.mem_unit;
  return 0;
}