(fread(b, 1, 1, f) == 1 && b[0] == 0xBF) {
        return cmListFileLexer_BOM_UTF8;
      }