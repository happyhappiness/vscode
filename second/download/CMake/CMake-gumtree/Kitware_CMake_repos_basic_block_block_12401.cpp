(total + window <= (1024 * 128)) {
    h = __archive_read_ahead(a, window, &bytes);
    if (h == NULL) {
      /* Remaining bytes are less than window. */
      window >>= 1;
      if (window < 0x40)
      	goto fatal;
      continue;
    }
    if (bytes < 0x40)
      goto fatal;
    p = h;
    q = p + bytes;

    /*
     * Scan ahead until we find something that looks
     * like the RAR header.
     */
    while (p + 7 < q) {
      if (memcmp(p, RAR_SIGNATURE, 7) == 0) {
      	skip = p - (const char *)h;
      	__archive_read_consume(a, skip);
      	return (ARCHIVE_OK);
      }
      p += 0x10;
    }
    skip = p - (const char *)h;
    __archive_read_consume(a, skip);
	total += skip;
  }