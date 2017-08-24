      "Invalid filename size");
    return (ARCHIVE_FATAL);
  }
  if (rar->filename_allocated < filename_size+2) {
    rar->filename = realloc(rar->filename, filename_size+2);
    if (rar->filename == NULL) {
      archive_set_error(&a->archive, ENOMEM,
                        "Couldn't allocate memory.");
      return (ARCHIVE_FATAL);
    }
  }
  filename = rar->filename;
  memcpy(filename, p, filename_size);
