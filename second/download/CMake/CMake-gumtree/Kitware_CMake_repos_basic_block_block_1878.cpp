{
    // /proc/meminfo format for kernel older than 2.6.x

    unsigned long temp;
    unsigned long cachedMem;
    unsigned long buffersMem;
    // Skip "total: used:..."
    char* r = fgets(buffer, static_cast<int>(sizeof(buffer)), fd);
    int status = 0;
    if (r == buffer) {
      status += fscanf(fd, "Mem: %lu %lu %lu %lu %lu %lu\n", &tp, &temp, &ap,
                       &temp, &buffersMem, &cachedMem);
    }
    if (status == 6) {
      status += fscanf(fd, "Swap: %lu %lu %lu\n", &tv, &temp, &av);
    }
    if (status == 9) {
      this->TotalVirtualMemory = tv >> 10 >> 10;
      this->TotalPhysicalMemory = tp >> 10 >> 10;
      this->AvailableVirtualMemory = av >> 10 >> 10;
      this->AvailablePhysicalMemory =
        (ap + buffersMem + cachedMem) >> 10 >> 10;
    } else {
      std::cout << "Problem parsing /proc/meminfo" << std::endl;
      fclose(fd);
      return false;
    }
  }