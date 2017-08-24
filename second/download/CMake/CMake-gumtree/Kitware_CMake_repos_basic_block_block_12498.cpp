{
    size_t distance = p - (const char *)h;
    header_size += rar->packed_size;
    /* Make sure we have the extended data. */
    if ((h = __archive_read_ahead(a, (size_t)header_size - 7, NULL)) == NULL)
        return (ARCHIVE_FATAL);
    p = h;
    endp = p + header_size - 7;
    p += distance;
  }