{
    // all values other than x86 map to 64bit architectures
    this->OSIs64Bit = (strncmp(arch, "x86", 3) != 0);
  }