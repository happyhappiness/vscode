{
    unsigned long p = in.tellg();
    in.read(reinterpret_cast<char*>(bom + 2), 2);
    if (in.good() && bom[2] == 0x00 && bom[3] == 0x00) {
      return BOM_UTF32LE;
    }
    in.seekg(p);
    return BOM_UTF16LE;
  }