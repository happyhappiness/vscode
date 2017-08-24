{
  // Check to see if what we are about to do is supported...
  if (!RetrieveCPUExtendedLevelSupport(static_cast<int>(0x80000002)))
    return false;
  if (!RetrieveCPUExtendedLevelSupport(static_cast<int>(0x80000003)))
    return false;
  if (!RetrieveCPUExtendedLevelSupport(static_cast<int>(0x80000004)))
    return false;

#if USE_CPUID
  int CPUExtendedIdentity[12];

  if (!call_cpuid(0x80000002, CPUExtendedIdentity)) {
    return false;
  }
  if (!call_cpuid(0x80000003, CPUExtendedIdentity + 4)) {
    return false;
  }
  if (!call_cpuid(0x80000004, CPUExtendedIdentity + 8)) {
    return false;
  }

  // Process the returned information.
  char nbuf[49];
  memcpy(&(nbuf[0]), &(CPUExtendedIdentity[0]), sizeof(int));
  memcpy(&(nbuf[4]), &(CPUExtendedIdentity[1]), sizeof(int));
  memcpy(&(nbuf[8]), &(CPUExtendedIdentity[2]), sizeof(int));
  memcpy(&(nbuf[12]), &(CPUExtendedIdentity[3]), sizeof(int));
  memcpy(&(nbuf[16]), &(CPUExtendedIdentity[4]), sizeof(int));
  memcpy(&(nbuf[20]), &(CPUExtendedIdentity[5]), sizeof(int));
  memcpy(&(nbuf[24]), &(CPUExtendedIdentity[6]), sizeof(int));
  memcpy(&(nbuf[28]), &(CPUExtendedIdentity[7]), sizeof(int));
  memcpy(&(nbuf[32]), &(CPUExtendedIdentity[8]), sizeof(int));
  memcpy(&(nbuf[36]), &(CPUExtendedIdentity[9]), sizeof(int));
  memcpy(&(nbuf[40]), &(CPUExtendedIdentity[10]), sizeof(int));
  memcpy(&(nbuf[44]), &(CPUExtendedIdentity[11]), sizeof(int));
  nbuf[48] = '\0';
  this->ChipID.ProcessorName = nbuf;
  this->ChipID.ModelName = nbuf;

  // Because some manufacturers have leading white space - we have to
  // post-process the name.
  SystemInformationStripLeadingSpace(this->ChipID.ProcessorName);
  return true;
#else
  return false;
#endif
}