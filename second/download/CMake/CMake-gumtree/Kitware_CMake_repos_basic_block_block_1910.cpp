{
    this->AvailableVirtualMemory =
      static_cast<size_t>(swap.xsu_avail / 1048576);
    this->TotalVirtualMemory = static_cast<size_t>(swap.xsu_total / 1048576);
  }