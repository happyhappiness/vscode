(fread(b, 1, 2, f) == 2 && b[0] == 0xFE && b[1] == 0xFF) {
        return cmListFileLexer_BOM_UTF32BE;
      }