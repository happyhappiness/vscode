{
    this->Features.ExtendedFeatures.HasMMXPlus =
      ((localCPUExtendedFeatures[3] & 0x00400000) !=
       0); // AMD specific: MMX-SSE --> Bit 22
  }