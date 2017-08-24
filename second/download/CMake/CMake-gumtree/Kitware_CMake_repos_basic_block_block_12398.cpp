(p + 7 < q) {
      if (memcmp(p, RAR_SIGNATURE, 7) == 0) {
      	skip = p - (const char *)h;
      	__archive_read_consume(a, skip);
      	return (ARCHIVE_OK);
      }
      p += 0x10;
    }