(uv_split_path(short_path, NULL, &handle->short_filew) != 0) {
      last_error = GetLastError();
      goto error;
    }