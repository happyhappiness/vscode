{
    ret = GetShortPathNameW(wtempPath.c_str(), &buffer[0],
                            static_cast<DWORD>(buffer.size()));
  }