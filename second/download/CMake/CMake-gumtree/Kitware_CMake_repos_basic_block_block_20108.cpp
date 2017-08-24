(!GetShortPathNameW(pathw, short_path, ARRAY_SIZE(short_path))) {
      short_path = NULL;
    }