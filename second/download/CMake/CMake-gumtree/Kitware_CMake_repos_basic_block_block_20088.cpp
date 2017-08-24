{
      *dir = (WCHAR*)uv__malloc((MAX_PATH + 1) * sizeof(WCHAR));
      if (!*dir) {
        uv_fatal_error(ERROR_OUTOFMEMORY, "uv__malloc");
      }

      if (!GetCurrentDirectoryW(MAX_PATH, *dir)) {
        uv__free(*dir);
        *dir = NULL;
        return -1;
      }
    }