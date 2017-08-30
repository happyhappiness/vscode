    p += filename_size;
  }

  if (rar->file_flags & FHD_SALT)
  {
    if (p + 8 > endp) {
