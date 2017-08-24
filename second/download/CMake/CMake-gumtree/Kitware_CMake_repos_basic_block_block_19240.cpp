{
  unsigned int ticks = (unsigned int)sysconf(_SC_CLK_TCK);
  unsigned int multiplier = ((uint64_t)1000L / ticks);
  unsigned int cur = 0;
  uv_cpu_info_t* cpu_info;
  u_int64_t* cp_times;
  char model[512];
  u_int64_t cpuspeed;
  int numcpus;
  size_t size;
  int i;

  size = sizeof(model);
  if (sysctlbyname("machdep.cpu_brand", &model, &size, NULL, 0) &&
      sysctlbyname("hw.model", &model, &size, NULL, 0)) {
    return -errno;
  }

  size = sizeof(numcpus);
  if (sysctlbyname("hw.ncpu", &numcpus, &size, NULL, 0))
    return -errno;
  *count = numcpus;

  /* Only i386 and amd64 have machdep.tsc_freq */
  size = sizeof(cpuspeed);
  if (sysctlbyname("machdep.tsc_freq", &cpuspeed, &size, NULL, 0))
    cpuspeed = 0;

  size = numcpus * CPUSTATES * sizeof(*cp_times);
  cp_times = uv__malloc(size);
  if (cp_times == NULL)
    return -ENOMEM;

  if (sysctlbyname("kern.cp_time", cp_times, &size, NULL, 0))
    return -errno;

  *cpu_infos = uv__malloc(numcpus * sizeof(**cpu_infos));
  if (!(*cpu_infos)) {
    uv__free(cp_times);
    uv__free(*cpu_infos);
    return -ENOMEM;
  }

  for (i = 0; i < numcpus; i++) {
    cpu_info = &(*cpu_infos)[i];
    cpu_info->cpu_times.user = (uint64_t)(cp_times[CP_USER+cur]) * multiplier;
    cpu_info->cpu_times.nice = (uint64_t)(cp_times[CP_NICE+cur]) * multiplier;
    cpu_info->cpu_times.sys = (uint64_t)(cp_times[CP_SYS+cur]) * multiplier;
    cpu_info->cpu_times.idle = (uint64_t)(cp_times[CP_IDLE+cur]) * multiplier;
    cpu_info->cpu_times.irq = (uint64_t)(cp_times[CP_INTR+cur]) * multiplier;
    cpu_info->model = uv__strdup(model);
    cpu_info->speed = (int)(cpuspeed/(uint64_t) 1e6);
    cur += CPUSTATES;
  }
  uv__free(cp_times);
  return 0;
}