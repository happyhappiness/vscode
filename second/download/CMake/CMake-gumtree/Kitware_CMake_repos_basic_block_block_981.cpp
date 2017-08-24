{
    ret = (char*)malloc(length);
    if (ret) {
      ret[0] = 0;
      kwsysEncoding_wcstombs(ret, str, length);
    }
  }