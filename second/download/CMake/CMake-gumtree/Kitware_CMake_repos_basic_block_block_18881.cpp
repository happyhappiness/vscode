(sysctlbyname("hw.clockrate", &cpuspeed, &size, NULL, 0)) {
    uv__free(*cpu_infos);
    return -errno;
  }