(new_path != NULL) {
    new_pathw_len = MultiByteToWideChar(CP_UTF8,
                                        0,
                                        new_path,
                                        -1,
                                        NULL,
                                        0);
    if (new_pathw_len == 0) {
      return GetLastError();
    }

    buf_sz += new_pathw_len * sizeof(WCHAR);
  }