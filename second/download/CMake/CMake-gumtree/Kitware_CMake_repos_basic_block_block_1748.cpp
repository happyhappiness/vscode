{
#if USE_CPUID
  int localCPUVendor[4];
  int localCPUSignature[4];

  if (!call_cpuid(0, localCPUVendor)) {
    return false;
  }
  if (!call_cpuid(1, localCPUSignature)) {
    return false;
  }

  // Process the returned information.
  //    ; eax = 0 --> eax: maximum value of CPUID instruction.
  //    ;        ebx: part 1 of 3; CPU signature.
  //    ;        edx: part 2 of 3; CPU signature.
  //    ;        ecx: part 3 of 3; CPU signature.
  char vbuf[13];
  memcpy(&(vbuf[0]), &(localCPUVendor[1]), sizeof(int));
  memcpy(&(vbuf[4]), &(localCPUVendor[3]), sizeof(int));
  memcpy(&(vbuf[8]), &(localCPUVendor[2]), sizeof(int));
  vbuf[12] = '\0';
  this->ChipID.Vendor = vbuf;

  // Retrieve the family of CPU present.
  //    ; eax = 1 --> eax: CPU ID - bits 31..16 - unused, bits 15..12 - type,
  //    bits 11..8 - family, bits 7..4 - model, bits 3..0 - mask revision
  //    ;        ebx: 31..24 - default APIC ID, 23..16 - logical processor ID,
  //    15..8 - CFLUSH chunk size , 7..0 - brand ID
  //    ;        edx: CPU feature flags
  this->ChipID.ExtendedFamily =
    ((localCPUSignature[0] & 0x0FF00000) >> 20); // Bits 27..20 Used
  this->ChipID.ExtendedModel =
    ((localCPUSignature[0] & 0x000F0000) >> 16); // Bits 19..16 Used
  this->ChipID.Type =
    ((localCPUSignature[0] & 0x0000F000) >> 12); // Bits 15..12 Used
  this->ChipID.Family =
    ((localCPUSignature[0] & 0x00000F00) >> 8); // Bits 11..8 Used
  this->ChipID.Model =
    ((localCPUSignature[0] & 0x000000F0) >> 4); // Bits 7..4 Used
  this->ChipID.Revision =
    ((localCPUSignature[0] & 0x0000000F) >> 0); // Bits 3..0 Used

  return true;

#else
  return false;
#endif
}