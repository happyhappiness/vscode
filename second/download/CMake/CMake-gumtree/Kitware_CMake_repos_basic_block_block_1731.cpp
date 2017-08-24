{
#if USE_CPUID
  int cpuinfo[4] = { 0, 0, 0, 0 };

  if (!call_cpuid(1, cpuinfo)) {
    return false;
  }

  // Retrieve the features of CPU present.
  this->Features.HasFPU =
    ((cpuinfo[3] & 0x00000001) != 0); // FPU Present --> Bit 0
  this->Features.HasTSC =
    ((cpuinfo[3] & 0x00000010) != 0); // TSC Present --> Bit 4
  this->Features.HasAPIC =
    ((cpuinfo[3] & 0x00000200) != 0); // APIC Present --> Bit 9
  this->Features.HasMTRR =
    ((cpuinfo[3] & 0x00001000) != 0); // MTRR Present --> Bit 12
  this->Features.HasCMOV =
    ((cpuinfo[3] & 0x00008000) != 0); // CMOV Present --> Bit 15
  this->Features.HasSerial =
    ((cpuinfo[3] & 0x00040000) != 0); // Serial Present --> Bit 18
  this->Features.HasACPI =
    ((cpuinfo[3] & 0x00400000) != 0); // ACPI Capable --> Bit 22
  this->Features.HasMMX =
    ((cpuinfo[3] & 0x00800000) != 0); // MMX Present --> Bit 23
  this->Features.HasSSE =
    ((cpuinfo[3] & 0x02000000) != 0); // SSE Present --> Bit 25
  this->Features.HasSSE2 =
    ((cpuinfo[3] & 0x04000000) != 0); // SSE2 Present --> Bit 26
  this->Features.HasThermal =
    ((cpuinfo[3] & 0x20000000) != 0); // Thermal Monitor Present --> Bit 29
  this->Features.HasIA64 =
    ((cpuinfo[3] & 0x40000000) != 0); // IA64 Present --> Bit 30

#if USE_ASM_INSTRUCTIONS
  // Retrieve extended SSE capabilities if SSE is available.
  if (this->Features.HasSSE) {

    // Attempt to __try some SSE FP instructions.
    __try {
      // Perform: orps xmm0, xmm0
      _asm
      {
        _emit 0x0f
        _emit 0x56
        _emit 0xc0
      }

      // SSE FP capable processor.
      this->Features.HasSSEFP = true;
    } __except (1) {
      // bad instruction - processor or OS cannot handle SSE FP.
      this->Features.HasSSEFP = false;
    }
  } else {
    // Set the advanced SSE capabilities to not available.
    this->Features.HasSSEFP = false;
  }
#else
  this->Features.HasSSEFP = false;
#endif

  // Retrieve Intel specific extended features.
  if (this->ChipManufacturer == Intel) {
    bool SupportsSMT =
      ((cpuinfo[3] & 0x10000000) != 0); // Intel specific: SMT --> Bit 28

    if ((SupportsSMT) && (this->Features.HasAPIC)) {
      // Retrieve APIC information if there is one present.
      this->Features.ExtendedFeatures.APIC_ID =
        ((cpuinfo[1] & 0xFF000000) >> 24);
    }
  }

  return true;

#else
  return false;
#endif
}