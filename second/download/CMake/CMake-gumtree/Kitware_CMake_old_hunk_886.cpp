  struct rar *rar = (struct rar *)(a->format->data);

  if (rar->bytes_remaining > 0) {
    br->next_in = __archive_read_ahead(a, 1, &(br->avail_in));
    if (br->next_in == NULL) {
      archive_set_error(&a->archive,
          ARCHIVE_ERRNO_FILE_FORMAT,
          "Truncated RAR file data");
      return (ARCHIVE_FATAL);
    }
    if (br->avail_in > rar->bytes_remaining)
      br->avail_in = rar->bytes_remaining;
    if (br->cache_avail == 0)
      (void)rar_br_fillup(a, br);
  }
