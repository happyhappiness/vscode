{
  this->NumberOfLogicalCPU = 0;
  this->NumberOfPhysicalCPU = 0;
  std::string buffer;

  FILE* fd = fopen("/proc/cpuinfo", "r");
  if (!fd) {
    std::cout << "Problem opening /proc/cpuinfo" << std::endl;
    return false;
  }

  size_t fileSize = 0;
  while (!feof(fd)) {
    buffer += static_cast<char>(fgetc(fd));
    fileSize++;
  }
  fclose(fd);
  buffer.resize(fileSize - 2);
  // Number of logical CPUs (combination of multiple processors, multi-core
  // and SMT)
  size_t pos = buffer.find("processor\t");
  while (pos != std::string::npos) {
    this->NumberOfLogicalCPU++;
    pos = buffer.find("processor\t", pos + 1);
  }

#ifdef __linux
  // Count sockets.
  std::set<int> PhysicalIDs;
  std::string idc = this->ExtractValueFromCpuInfoFile(buffer, "physical id");
  while (this->CurrentPositionInFile != std::string::npos) {
    int id = atoi(idc.c_str());
    PhysicalIDs.insert(id);
    idc = this->ExtractValueFromCpuInfoFile(buffer, "physical id",
                                            this->CurrentPositionInFile + 1);
  }
  uint64_t NumberOfSockets = PhysicalIDs.size();
  NumberOfSockets = std::max(NumberOfSockets, (uint64_t)1);
  // Physical ids returned by Linux don't distinguish cores.
  // We want to record the total number of cores in this->NumberOfPhysicalCPU
  // (checking only the first proc)
  std::string Cores = this->ExtractValueFromCpuInfoFile(buffer, "cpu cores");
  unsigned int NumberOfCoresPerSocket = (unsigned int)atoi(Cores.c_str());
  NumberOfCoresPerSocket = std::max(NumberOfCoresPerSocket, 1u);
  this->NumberOfPhysicalCPU =
    NumberOfCoresPerSocket * (unsigned int)NumberOfSockets;

#else // __CYGWIN__
  // does not have "physical id" entries, neither "cpu cores"
  // this has to be fixed for hyper-threading.
  std::string cpucount =
    this->ExtractValueFromCpuInfoFile(buffer, "cpu count");
  this->NumberOfPhysicalCPU = this->NumberOfLogicalCPU =
    atoi(cpucount.c_str());
#endif
  // gotta have one, and if this is 0 then we get a / by 0n
  // better to have a bad answer than a crash
  if (this->NumberOfPhysicalCPU <= 0) {
    this->NumberOfPhysicalCPU = 1;
  }
  // LogicalProcessorsPerPhysical>1 => SMT.
  this->Features.ExtendedFeatures.LogicalProcessorsPerPhysical =
    this->NumberOfLogicalCPU / this->NumberOfPhysicalCPU;

  // CPU speed (checking only the first processor)
  std::string CPUSpeed = this->ExtractValueFromCpuInfoFile(buffer, "cpu MHz");
  if (!CPUSpeed.empty()) {
    this->CPUSpeedInMHz = static_cast<float>(atof(CPUSpeed.c_str()));
  }
#ifdef __linux
  else {
    // Linux Sparc: CPU speed is in Hz and encoded in hexadecimal
    CPUSpeed = this->ExtractValueFromCpuInfoFile(buffer, "Cpu0ClkTck");
    this->CPUSpeedInMHz =
      static_cast<float>(strtoull(CPUSpeed.c_str(), 0, 16)) / 1000000.0f;
  }
#endif

  // Chip family
  std::string familyStr =
    this->ExtractValueFromCpuInfoFile(buffer, "cpu family");
  if (familyStr.empty()) {
    familyStr = this->ExtractValueFromCpuInfoFile(buffer, "CPU architecture");
  }
  this->ChipID.Family = atoi(familyStr.c_str());

  // Chip Vendor
  this->ChipID.Vendor = this->ExtractValueFromCpuInfoFile(buffer, "vendor_id");
  this->FindManufacturer(familyStr);

  // second try for setting family
  if (this->ChipID.Family == 0 && this->ChipManufacturer == HP) {
    if (familyStr == "PA-RISC 1.1a")
      this->ChipID.Family = 0x11a;
    else if (familyStr == "PA-RISC 2.0")
      this->ChipID.Family = 0x200;
    // If you really get CMake to work on a machine not belonging to
    // any of those families I owe you a dinner if you get it to
    // contribute nightly builds regularly.
  }

  // Chip Model
  this->ChipID.Model =
    atoi(this->ExtractValueFromCpuInfoFile(buffer, "model").c_str());
  if (!this->RetrieveClassicalCPUIdentity()) {
    // Some platforms (e.g. PA-RISC) tell us their CPU name here.
    // Note: x86 does not.
    std::string cpuname = this->ExtractValueFromCpuInfoFile(buffer, "cpu");
    if (!cpuname.empty()) {
      this->ChipID.ProcessorName = cpuname;
    }
  }

  // Chip revision
  std::string cpurev = this->ExtractValueFromCpuInfoFile(buffer, "stepping");
  if (cpurev.empty()) {
    cpurev = this->ExtractValueFromCpuInfoFile(buffer, "CPU revision");
  }
  this->ChipID.Revision = atoi(cpurev.c_str());

  // Chip Model Name
  this->ChipID.ModelName =
    this->ExtractValueFromCpuInfoFile(buffer, "model name").c_str();

  // L1 Cache size
  // Different architectures may show different names for the caches.
  // Sum up everything we find.
  std::vector<const char*> cachename;
  cachename.clear();

  cachename.push_back("cache size"); // e.g. x86
  cachename.push_back("I-cache");    // e.g. PA-RISC
  cachename.push_back("D-cache");    // e.g. PA-RISC

  this->Features.L1CacheSize = 0;
  for (size_t index = 0; index < cachename.size(); index++) {
    std::string cacheSize =
      this->ExtractValueFromCpuInfoFile(buffer, cachename[index]);
    if (!cacheSize.empty()) {
      pos = cacheSize.find(" KB");
      if (pos != std::string::npos) {
        cacheSize = cacheSize.substr(0, pos);
      }
      this->Features.L1CacheSize += atoi(cacheSize.c_str());
    }
  }

  // processor feature flags (probably x86 specific)
  std::string cpuflags = this->ExtractValueFromCpuInfoFile(buffer, "flags");
  if (!cpurev.empty()) {
    // now we can match every flags as space + flag + space
    cpuflags = " " + cpuflags + " ";
    if ((cpuflags.find(" fpu ") != std::string::npos)) {
      this->Features.HasFPU = true;
    }
    if ((cpuflags.find(" tsc ") != std::string::npos)) {
      this->Features.HasTSC = true;
    }
    if ((cpuflags.find(" mmx ") != std::string::npos)) {
      this->Features.HasMMX = true;
    }
    if ((cpuflags.find(" sse ") != std::string::npos)) {
      this->Features.HasSSE = true;
    }
    if ((cpuflags.find(" sse2 ") != std::string::npos)) {
      this->Features.HasSSE2 = true;
    }
    if ((cpuflags.find(" apic ") != std::string::npos)) {
      this->Features.HasAPIC = true;
    }
    if ((cpuflags.find(" cmov ") != std::string::npos)) {
      this->Features.HasCMOV = true;
    }
    if ((cpuflags.find(" mtrr ") != std::string::npos)) {
      this->Features.HasMTRR = true;
    }
    if ((cpuflags.find(" acpi ") != std::string::npos)) {
      this->Features.HasACPI = true;
    }
    if ((cpuflags.find(" 3dnow ") != std::string::npos)) {
      this->Features.ExtendedFeatures.Has3DNow = true;
    }
  }

  return true;
}