{
    if (dir) {
      *dir = (WCHAR*)uv__malloc((i + 2) * sizeof(WCHAR));
      if (!*dir) {
        uv_fatal_error(ERROR_OUTOFMEMORY, "uv__malloc");
      }
      wcsncpy(*dir, filename, i + 1);
      (*dir)[i + 1] = L'\0';
    }

    *file = (WCHAR*)uv__malloc((len - i) * sizeof(WCHAR));
    if (!*file) {
      uv_fatal_error(ERROR_OUTOFMEMORY, "uv__malloc");
    }
    wcsncpy(*file, filename + i + 1, len - i - 1);
    (*file)[len - i - 1] = L'\0';
  }