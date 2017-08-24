(sysctlbyname(maxcpus_key, &maxcpus, &size, NULL, 0)) {
    uv__free(*cpu_infos);
    return -errno;
  }