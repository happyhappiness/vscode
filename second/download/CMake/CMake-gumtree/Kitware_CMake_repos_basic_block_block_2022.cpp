(view == SystemTools::KeyWOW64_32) {
    return mode | KWSYS_ST_KEY_WOW64_32KEY;
  } else if (view == SystemTools::KeyWOW64_64) {
    return mode | KWSYS_ST_KEY_WOW64_64KEY;
  }