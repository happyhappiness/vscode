{
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