{
  // Check to see if the processor supports the processor serial number.
  if (!this->Features.HasSerial) {
    return false;
  }

#if USE_CPUID
  int SerialNumber[4];

  if (!call_cpuid(3, SerialNumber)) {
    return false;
  }

  // Process the returned information.
  //    ; eax = 3 --> ebx: top 32 bits are the processor signature bits --> NB:
  //    Transmeta only ?!?
  //    ;        ecx: middle 32 bits are the processor signature bits
  //    ;        edx: bottom 32 bits are the processor signature bits
  char sn[128];
  sprintf(sn, "%.2x%.2x-%.2x%.2x-%.2x%.2x-%.2x%.2x-%.2x%.2x-%.2x%.2x",
          ((SerialNumber[1] & 0xff000000) >> 24),
          ((SerialNumber[1] & 0x00ff0000) >> 16),
          ((SerialNumber[1] & 0x0000ff00) >> 8),
          ((SerialNumber[1] & 0x000000ff) >> 0),
          ((SerialNumber[2] & 0xff000000) >> 24),
          ((SerialNumber[2] & 0x00ff0000) >> 16),
          ((SerialNumber[2] & 0x0000ff00) >> 8),
          ((SerialNumber[2] & 0x000000ff) >> 0),
          ((SerialNumber[3] & 0xff000000) >> 24),
          ((SerialNumber[3] & 0x00ff0000) >> 16),
          ((SerialNumber[3] & 0x0000ff00) >> 8),
          ((SerialNumber[3] & 0x000000ff) >> 0));
  this->ChipID.SerialNumber = sn;
  return true;

#else
  return false;
#endif
}