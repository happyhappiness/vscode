{
    len = sizeof(value);
    err = sysctlbyname("hw.pagesize", &value, &len, NULL, 0);
    int64_t available_memory = vmstat.free_count * value;
    this->AvailablePhysicalMemory =
      static_cast<size_t>(available_memory / 1048576);
  }