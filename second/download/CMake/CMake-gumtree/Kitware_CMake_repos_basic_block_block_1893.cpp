{
    // Fallback to approximate implementation on ancient Windows versions.
    SYSTEM_INFO info;
    ZeroMemory(&info, sizeof(info));
    GetSystemInfo(&info);
    this->NumberOfPhysicalCPU =
      static_cast<unsigned int>(info.dwNumberOfProcessors);
    this->NumberOfLogicalCPU = this->NumberOfPhysicalCPU;
    return;
  }