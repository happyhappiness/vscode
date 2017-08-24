{
    DWORD path_len, r;

    path_len = GetEnvironmentVariableW(L"PATH", NULL, 0);
    if (path_len == 0) {
      err = GetLastError();
      goto done;
    }

    alloc_path = (WCHAR*) uv__malloc(path_len * sizeof(WCHAR));
    if (alloc_path == NULL) {
      err = ERROR_OUTOFMEMORY;
      goto done;
    }
    path = alloc_path;

    r = GetEnvironmentVariableW(L"PATH", path, path_len);
    if (r == 0 || r >= path_len) {
      err = GetLastError();
      goto done;
    }
  }