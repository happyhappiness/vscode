{
  unsigned int ticks = (unsigned int)sysconf(_SC_CLK_TCK),
               multiplier = ((uint64_t)1000L / ticks), cpuspeed;
  uint64_t info[CPUSTATES];
  char model[512];
  int numcpus = 1;
  int which[] = {CTL_HW,HW_MODEL,0};
  size_t size;
  int i;
  uv_cpu_info_t* cpu_info;

  size = sizeof(model);
  if (sysctl(which, 2, &model, &size, NULL, 0))
    return -errno;

  which[1] = HW_NCPU;
  size = sizeof(numcpus);
  if (sysctl(which, 2, &numcpus, &size, NULL, 0))
    return -errno;

  *cpu_infos = uv__malloc(numcpus * sizeof(**cpu_infos));
  if (!(*cpu_infos))
    return -ENOMEM;

  *count = numcpus;

  which[1] = HW_CPUSPEED;
  size = sizeof(cpuspeed);
  if (sysctl(which, 2, &cpuspeed, &size, NULL, 0)) {
    uv__free(*cpu_infos);
    return -errno;
  }

  size = sizeof(info);
  which[0] = CTL_KERN;
  which[1] = KERN_CPTIME2;
  for (i = 0; i < numcpus; i++) {
    which[2] = i;
    size = sizeof(info);
    if (sysctl(which, 3, &info, &size, NULL, 0)) {
      uv__free(*cpu_infos);
      return -errno;
    }

    cpu_info = &(*cpu_infos)[i];

    cpu_info->cpu_times.user = (uint64_t)(info[CP_USER]) * multiplier;
    cpu_info->cpu_times.nice = (uint64_t)(info[CP_NICE]) * multiplier;
    cpu_info->cpu_times.sys = (uint64_t)(info[CP_SYS]) * multiplier;
    cpu_info->cpu_times.idle = (uint64_t)(info[CP_IDLE]) * multiplier;
    cpu_info->cpu_times.irq = (uint64_t)(info[CP_INTR]) * multiplier;

    cpu_info->model = uv__strdup(model);
    cpu_info->speed = cpuspeed;
  }

  return 0;
}