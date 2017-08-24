(fseek(f, 0, SEEK_SET) != 0) {
    return cmListFileLexer_BOM_Broken;
  }