(r != ARCHIVE_OK) {
    __archive_read_free_filters(a);
    return (ARCHIVE_FATAL);
  }