{
#if defined(__hpux)
#if defined(KWSYS_SYS_HAS_MPCTL_H)
  int c = mpctl(MPC_GETNUMSPUS_SYS, 0, 0);
  if (c <= 0) {
    return false;
  }

  this->NumberOfPhysicalCPU = c;
  this->NumberOfLogicalCPU = this->NumberOfPhysicalCPU;

  long t = sysconf(_SC_CPU_VERSION);

  if (t == -1) {
    return false;
  }

  switch (t) {
    case CPU_PA_RISC1_0:
      this->ChipID.Vendor = "Hewlett-Packard";
      this->ChipID.Family = 0x100;
      break;
    case CPU_PA_RISC1_1:
      this->ChipID.Vendor = "Hewlett-Packard";
      this->ChipID.Family = 0x110;
      break;
    case CPU_PA_RISC2_0:
      this->ChipID.Vendor = "Hewlett-Packard";
      this->ChipID.Family = 0x200;
      break;
#if defined(CPU_HP_INTEL_EM_1_0) || defined(CPU_IA64_ARCHREV_0)
#ifdef CPU_HP_INTEL_EM_1_0
    case CPU_HP_INTEL_EM_1_0:
#endif
#ifdef CPU_IA64_ARCHREV_0
    case CPU_IA64_ARCHREV_0:
#endif
      this->ChipID.Vendor = "GenuineIntel";
      this->Features.HasIA64 = true;
      break;
#endif
    default:
      return false;
  }

  this->FindManufacturer();

  return true;
#else
  return false;
#endif
#else
  return false;
#endif
}