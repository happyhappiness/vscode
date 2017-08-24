{
      *dir = (WCHAR*)uv__malloc((i + 2) * sizeof(WCHAR));
      if (!*dir) {
        uv_fatal_error(ERROR_OUTOFMEMORY, "uv__malloc");
      }
      wcsncpy(*dir, filename, i + 1);
      (*dir)[i + 1] = L'\0';
    }