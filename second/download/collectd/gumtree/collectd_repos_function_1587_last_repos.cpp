static time_t uptime_get_sys(void) { /* {{{ */
  time_t result;
#if KERNEL_LINUX
  struct sysinfo info;
  int status;

  status = sysinfo(&info);
  if (status != 0) {
    char errbuf[1024];
    ERROR("uptime plugin: Error calling sysinfo: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }

  result = (time_t)info.uptime;
/* #endif KERNEL_LINUX */

#elif HAVE_LIBKSTAT
  kstat_t *ksp;
  kstat_named_t *knp;

  ksp = NULL;
  knp = NULL;

  /* kstats chain already opened by update_kstat (using *kc), verify everything
   * went fine. */
  if (kc == NULL) {
    ERROR("uptime plugin: kstat chain control structure not available.");
    return -1;
  }

  ksp = kstat_lookup(kc, "unix", 0, "system_misc");
  if (ksp == NULL) {
    ERROR("uptime plugin: Cannot find unix:0:system_misc kstat.");
    return -1;
  }

  if (kstat_read(kc, ksp, NULL) < 0) {
    ERROR("uptime plugin: kstat_read failed.");
    return -1;
  }

  knp = (kstat_named_t *)kstat_data_lookup(ksp, "boot_time");
  if (knp == NULL) {
    ERROR("uptime plugin: kstat_data_lookup (boot_time) failed.");
    return -1;
  }

  if (knp->value.ui32 == 0) {
    ERROR("uptime plugin: kstat_data_lookup returned success, "
          "but `boottime' is zero!");
    return -1;
  }

  result = time(NULL) - (time_t)knp->value.ui32;
/* #endif HAVE_LIBKSTAT */

#elif HAVE_SYS_SYSCTL_H
  struct timeval boottv = {0};
  size_t boottv_len;
  int status;

  int mib[] = {CTL_KERN, KERN_BOOTTIME};

  boottv_len = sizeof(boottv);

  status = sysctl(mib, STATIC_ARRAY_SIZE(mib), &boottv, &boottv_len,
                  /* new_value = */ NULL, /* new_length = */ 0);
  if (status != 0) {
    char errbuf[1024];
    ERROR("uptime plugin: No value read from sysctl interface: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }

  if (boottv.tv_sec == 0) {
    ERROR("uptime plugin: sysctl(3) returned success, "
          "but `boottime' is zero!");
    return -1;
  }

  result = time(NULL) - boottv.tv_sec;
/* #endif HAVE_SYS_SYSCTL_H */

#elif HAVE_PERFSTAT
  int status;
  perfstat_cpu_total_t cputotal;
  int hertz;

  status = perfstat_cpu_total(NULL, &cputotal, sizeof(perfstat_cpu_total_t), 1);
  if (status < 0) {
    char errbuf[1024];
    ERROR("uptime plugin: perfstat_cpu_total: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }

  hertz = sysconf(_SC_CLK_TCK);
  if (hertz <= 0)
    hertz = HZ;

  result = cputotal.lbolt / hertz;
#endif /* HAVE_PERFSTAT */

  return result;
}