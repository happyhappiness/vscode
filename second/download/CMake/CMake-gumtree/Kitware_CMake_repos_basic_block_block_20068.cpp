{
  WCHAR filename_w[32768];

  lib->handle = NULL;
  lib->errmsg = NULL;

  if (!MultiByteToWideChar(CP_UTF8,
                           0,
                           filename,
                           -1,
                           filename_w,
                           ARRAY_SIZE(filename_w))) {
    return uv__dlerror(lib, GetLastError());
  }

  lib->handle = LoadLibraryExW(filename_w, NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
  if (lib->handle == NULL) {
    return uv__dlerror(lib, GetLastError());
  }

  return 0;
}