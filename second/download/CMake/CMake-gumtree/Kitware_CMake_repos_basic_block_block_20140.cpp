{
    DWORD r = MultiByteToWideChar(CP_UTF8,
                                  0,
                                  new_path,
                                  -1,
                                  (WCHAR*) pos,
                                  new_pathw_len);
    assert(r == (DWORD) new_pathw_len);
    req->fs.info.new_pathw = (WCHAR*) pos;
    pos += r * sizeof(WCHAR);
  }