{
  struct sysinfo info;

  if (sysinfo(&info) < 0)
    return -errno;

  *uptime = info.uptime;
  return 0;
}