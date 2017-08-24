{
    this->Features.ExtendedFeatures.HasMMXPlus =
      ((localCPUExtendedFeatures[3] & 0x01000000) !=
       0); // Cyrix specific: Extended MMX --> Bit 24
  }