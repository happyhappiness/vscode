{
    in.read(reinterpret_cast<char*>(bom + 2), 2);
    if (in.good() && bom[2] == 0xFE && bom[3] == 0xFF) {
      return BOM_UTF32BE;
    }
  }