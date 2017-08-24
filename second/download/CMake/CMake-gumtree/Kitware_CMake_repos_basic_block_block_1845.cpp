{
    // Some platforms (e.g. PA-RISC) tell us their CPU name here.
    // Note: x86 does not.
    std::string cpuname = this->ExtractValueFromCpuInfoFile(buffer, "cpu");
    if (!cpuname.empty()) {
      this->ChipID.ProcessorName = cpuname;
    }
  }