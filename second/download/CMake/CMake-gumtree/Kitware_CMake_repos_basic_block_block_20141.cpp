{
    DWORD r = MultiByteToWideChar(CP_UTF8,
                                  0,
                                  path,
                                  -1,
                                  (WCHAR*) pos,
                                  pathw_len);
    assert(r == (DWORD) pathw_len);
    req->file.pathw = (WCHAR*) pos;
    pos += r * sizeof(WCHAR);
  }