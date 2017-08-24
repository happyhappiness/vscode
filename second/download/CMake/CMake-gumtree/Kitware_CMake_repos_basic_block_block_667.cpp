(b[0] == 0xEF && b[1] == 0xBB) {
      if (fread(b, 1, 1, f) == 1 && b[0] == 0xBF) {
        return cmListFileLexer_BOM_UTF8;
      }
    } else if (b[0] == 0xFE && b[1] == 0xFF) {
      /* UTF-16 BE */
      return cmListFileLexer_BOM_UTF16BE;
    } else if (b[0] == 0 && b[1] == 0) {
      if (fread(b, 1, 2, f) == 2 && b[0] == 0xFE && b[1] == 0xFF) {
        return cmListFileLexer_BOM_UTF32BE;
      }
    } else if (b[0] == 0xFF && b[1] == 0xFE) {
      fpos_t p;
      fgetpos(f, &p);
      if (fread(b, 1, 2, f) == 2 && b[0] == 0 && b[1] == 0) {
        return cmListFileLexer_BOM_UTF32LE;
      }
      if (fsetpos(f, &p) != 0) {
        return cmListFileLexer_BOM_Broken;
      }
      return cmListFileLexer_BOM_UTF16LE;
    }