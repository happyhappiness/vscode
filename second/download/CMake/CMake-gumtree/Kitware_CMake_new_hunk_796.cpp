    rar->unp_size = archive_le32dec(file_header.unp_size);
  }

  if (rar->packed_size < 0 || rar->unp_size < 0)
  {
    archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                      "Invalid sizes specified.");
    return (ARCHIVE_FATAL);
  }

  rar->bytes_remaining = rar->packed_size;

  /* TODO: RARv3 subblocks contain comments. For now the complete block is
   * consumed at the end.
   */
  if (head_type == NEWSUB_HEAD) {
    size_t distance = p - (const char *)h;
    header_size += rar->packed_size;
    /* Make sure we have the extended data. */
    if ((h = __archive_read_ahead(a, (size_t)header_size - 7, NULL)) == NULL)
        return (ARCHIVE_FATAL);
    p = h;
    endp = p + header_size - 7;
