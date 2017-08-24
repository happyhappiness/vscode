{

  // Check that we are not using an Intel processor as it does not support
  // this.
  if (this->ChipManufacturer == Intel) {
    return false;
  }

  // Check to see if what we are about to do is supported...
  if (!RetrieveCPUExtendedLevelSupport(static_cast<int>(0x80000001))) {
    return false;
  }

#if USE_CPUID
  int localCPUExtendedFeatures[4] = { 0, 0, 0, 0 };

  if (!call_cpuid(0x80000001, localCPUExtendedFeatures)) {
    return false;
  }

  // Retrieve the extended features of CPU present.
  this->Features.ExtendedFeatures.Has3DNow =
    ((localCPUExtendedFeatures[3] & 0x80000000) !=
     0); // 3DNow Present --> Bit 31.
  this->Features.ExtendedFeatures.Has3DNowPlus =
    ((localCPUExtendedFeatures[3] & 0x40000000) !=
     0); // 3DNow+ Present -- > Bit 30.
  this->Features.ExtendedFeatures.HasSSEMMX =
    ((localCPUExtendedFeatures[3] & 0x00400000) !=
     0); // SSE MMX Present --> Bit 22.
  this->Features.ExtendedFeatures.SupportsMP =
    ((localCPUExtendedFeatures[3] & 0x00080000) !=
     0); // MP Capable -- > Bit 19.

  // Retrieve AMD specific extended features.
  if (this->ChipManufacturer == AMD) {
    this->Features.ExtendedFeatures.HasMMXPlus =
      ((localCPUExtendedFeatures[3] & 0x00400000) !=
       0); // AMD specific: MMX-SSE --> Bit 22
  }

  // Retrieve Cyrix specific extended features.
  if (this->ChipManufacturer == Cyrix) {
    this->Features.ExtendedFeatures.HasMMXPlus =
      ((localCPUExtendedFeatures[3] & 0x01000000) !=
       0); // Cyrix specific: Extended MMX --> Bit 24
  }

  return true;

#else
  return false;
#endif
}