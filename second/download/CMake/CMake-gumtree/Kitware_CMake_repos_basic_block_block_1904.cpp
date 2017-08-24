{
      // now we can match every flags as space + flag + space
      buf[len + 1] = ' ';
      std::string cpuflags(buf, len + 2);

      if ((cpuflags.find(" FPU ") != std::string::npos)) {
        this->Features.HasFPU = true;
      }
      if ((cpuflags.find(" TSC ") != std::string::npos)) {
        this->Features.HasTSC = true;
      }
      if ((cpuflags.find(" MMX ") != std::string::npos)) {
        this->Features.HasMMX = true;
      }
      if ((cpuflags.find(" SSE ") != std::string::npos)) {
        this->Features.HasSSE = true;
      }
      if ((cpuflags.find(" SSE2 ") != std::string::npos)) {
        this->Features.HasSSE2 = true;
      }
      if ((cpuflags.find(" APIC ") != std::string::npos)) {
        this->Features.HasAPIC = true;
      }
      if ((cpuflags.find(" CMOV ") != std::string::npos)) {
        this->Features.HasCMOV = true;
      }
      if ((cpuflags.find(" MTRR ") != std::string::npos)) {
        this->Features.HasMTRR = true;
      }
      if ((cpuflags.find(" ACPI ") != std::string::npos)) {
        this->Features.HasACPI = true;
      }
    }