(sysctlbyname("hw.ncpu", &numcpus, &size, NULL, 0))
    return -errno;