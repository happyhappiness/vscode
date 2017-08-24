{
  // Check to see if what we are about to do is supported...
  if (!RetrieveCPUExtendedLevelSupport(static_cast<int>(0x80000007))) {
    this->Features.ExtendedFeatures.PowerManagement.HasFrequencyID = false;
    this->Features.ExtendedFeatures.PowerManagement.HasVoltageID = false;
    this->Features.ExtendedFeatures.PowerManagement.HasTempSenseDiode = false;
    return false;
  }

#if USE_CPUID
  int localCPUPowerManagement[4] = { 0, 0, 0, 0 };

  if (!call_cpuid(0x80000007, localCPUPowerManagement)) {
    return false;
  }

  // Check for the power management capabilities of the CPU.
  this->Features.ExtendedFeatures.PowerManagement.HasTempSenseDiode =
    ((localCPUPowerManagement[3] & 0x00000001) != 0);
  this->Features.ExtendedFeatures.PowerManagement.HasFrequencyID =
    ((localCPUPowerManagement[3] & 0x00000002) != 0);
  this->Features.ExtendedFeatures.PowerManagement.HasVoltageID =
    ((localCPUPowerManagement[3] & 0x00000004) != 0);

  return true;

#else
  return false;
#endif
}