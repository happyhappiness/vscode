(i = 0; i < numcpus; i++) {
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