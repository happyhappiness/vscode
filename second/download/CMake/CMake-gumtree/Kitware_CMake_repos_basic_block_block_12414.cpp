(skip > 0) {
	      size_t to_read = skip;
	      ssize_t did_read;
	      if (to_read > 32 * 1024) {
		      to_read = 32 * 1024;
	      }
	      if ((h = __archive_read_ahead(a, to_read, &did_read)) == NULL) {
		      return (ARCHIVE_FATAL);
	      }
	      p = h;
	      crc32_val = crc32(crc32_val, (const unsigned char *)p, (unsigned)did_read);
	      __archive_read_consume(a, did_read);
	      skip -= did_read;
      }