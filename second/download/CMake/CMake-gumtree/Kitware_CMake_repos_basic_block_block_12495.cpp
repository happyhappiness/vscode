{
    char *newptr;
    size_t newsize = filename_size * 2 + 2;
    newptr = realloc(rar->filename, newsize);
    if (newptr == NULL) {
      archive_set_error(&a->archive, ENOMEM,
                        "Couldn't allocate memory.");
      return (ARCHIVE_FATAL);
    }
    rar->filename = newptr;
    rar->filename_allocated = newsize;
  }