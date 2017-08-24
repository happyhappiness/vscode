{
  int cpuinfo[4] = { 0, 0, 0, 0 };

  // The extended CPUID is supported by various vendors starting with the
  // following CPU models:
  //
  //    Manufacturer & Chip Name      |    Family     Model    Revision
  //
  //    AMD K6, K6-2                  |       5       6      x
  //    Cyrix GXm, Cyrix III "Joshua" |       5       4      x
  //    IDT C6-2                      |       5       8      x
  //    VIA Cyrix III                 |       6       5      x
  //    Transmeta Crusoe              |       5       x      x
  //    Intel Pentium 4               |       f       x      x
  //

  // We check to see if a supported processor is present...
  if (this->ChipManufacturer == AMD) {
    if (this->ChipID.Family < 5)
      return false;
    if ((this->ChipID.Family == 5) && (this->ChipID.Model < 6))
      return false;
  } else if (this->ChipManufacturer == Cyrix) {
    if (this->ChipID.Family < 5)
      return false;
    if ((this->ChipID.Family == 5) && (this->ChipID.Model < 4))
      return false;
    if ((this->ChipID.Family == 6) && (this->ChipID.Model < 5))
      return false;
  } else if (this->ChipManufacturer == IDT) {
    if (this->ChipID.Family < 5)
      return false;
    if ((this->ChipID.Family == 5) && (this->ChipID.Model < 8))
      return false;
  } else if (this->ChipManufacturer == Transmeta) {
    if (this->ChipID.Family < 5)
      return false;
  } else if (this->ChipManufacturer == Intel) {
    if (this->ChipID.Family < 0xf) {
      return false;
    }
  }

#if USE_CPUID
  if (!call_cpuid(0x80000000, cpuinfo)) {
    return false;
  }
#endif

  // Now we have to check the level wanted vs level returned...
  int nLevelWanted = (CPULevelToCheck & 0x7FFFFFFF);
  int nLevelReturn = (cpuinfo[0] & 0x7FFFFFFF);

  // Check to see if the level provided is supported...
  if (nLevelWanted > nLevelReturn) {
    return false;
  }

  return true;
}