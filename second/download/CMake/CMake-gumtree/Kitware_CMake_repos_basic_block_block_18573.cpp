(uv__path_is_a_directory(handle->path) == 0) {
    p = handle->dir_filename;
  } else {
    p = strrchr(handle->path, '/');
    if (p == NULL)
      p = handle->path;
    else
      p++;
  }