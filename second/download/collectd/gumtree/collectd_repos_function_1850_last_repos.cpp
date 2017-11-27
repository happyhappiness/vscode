static int cs_read(void) {
#if HAVE_SYSCTLBYNAME
  int value = 0;
  size_t value_len = sizeof(value);
  int status;

  status = sysctlbyname("vm.stats.sys.v_swtch", &value, &value_len,
                        /* new pointer = */ NULL, /* new length = */ 0);
  if (status != 0) {
    ERROR("contextswitch plugin: sysctlbyname "
          "(vm.stats.sys.v_swtch) failed");
    return -1;
  }

  cs_submit(value);
/* #endif HAVE_SYSCTLBYNAME */

#elif KERNEL_LINUX
  FILE *fh;
  char buffer[64];
  int numfields;
  char *fields[3];
  derive_t result = 0;
  int status = -2;

  fh = fopen("/proc/stat", "r");
  if (fh == NULL) {
    ERROR("contextswitch plugin: unable to open /proc/stat: %s",
          sstrerror(errno, buffer, sizeof(buffer)));
    return -1;
  }

  while (fgets(buffer, sizeof(buffer), fh) != NULL) {
    char *endptr;

    numfields = strsplit(buffer, fields, STATIC_ARRAY_SIZE(fields));
    if (numfields != 2)
      continue;

    if (strcmp("ctxt", fields[0]) != 0)
      continue;

    errno = 0;
    endptr = NULL;
    result = (derive_t)strtoll(fields[1], &endptr, /* base = */ 10);
    if ((endptr == fields[1]) || (errno != 0)) {
      ERROR("contextswitch plugin: Cannot parse ctxt value: %s", fields[1]);
      status = -1;
      break;
    }

    cs_submit(result);
    status = 0;
    break;
  }
  fclose(fh);

  if (status == -2)
    ERROR("contextswitch plugin: Unable to find context switch value.");
/* #endif  KERNEL_LINUX */

#elif HAVE_PERFSTAT
  int status = 0;
  perfstat_cpu_total_t perfcputotal;

  status =
      perfstat_cpu_total(NULL, &perfcputotal, sizeof(perfstat_cpu_total_t), 1);
  if (status < 0) {
    char errbuf[1024];
    ERROR("contextswitch plugin: perfstat_cpu_total: %s",
          sstrerror(errno, errbuf, sizeof(errbuf)));
    return -1;
  }

  cs_submit(perfcputotal.pswitch);
  status = 0;
#endif /* defined(HAVE_PERFSTAT) */

  return status;
}