{
    std::vector<wchar_t> wchars(length);
    if (kwsysEncoding_mbstowcs(&wchars[0], cstr, length) > 0) {
      wstr = &wchars[0];
    }
  }