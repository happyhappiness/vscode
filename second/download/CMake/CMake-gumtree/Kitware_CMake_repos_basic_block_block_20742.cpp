{
    /* Inherit cwd */
    DWORD cwd_len, r;

    cwd_len = GetCurrentDirectoryW(0, NULL);
    if (!cwd_len) {
      err = GetLastError();
      goto done;
    }

    cwd = (WCHAR*) uv__malloc(cwd_len * sizeof(WCHAR));
    if (cwd == NULL) {
      err = ERROR_OUTOFMEMORY;
      goto done;
    }

    r = GetCurrentDirectoryW(cwd_len, cwd);
    if (r == 0 || r >= cwd_len) {
      err = GetLastError();
      goto done;
    }
  }