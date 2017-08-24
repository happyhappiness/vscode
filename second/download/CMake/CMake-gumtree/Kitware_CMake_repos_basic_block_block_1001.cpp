{
    in.read(reinterpret_cast<char*>(bom + 2), 1);
    if (in.good() && bom[2] == 0xBF) {
      return BOM_UTF8;
    }
  }