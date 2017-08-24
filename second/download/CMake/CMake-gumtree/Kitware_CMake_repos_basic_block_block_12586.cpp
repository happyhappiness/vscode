(!rar_br_read_ahead(a, br, 1)) {
      archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                        "Truncated RAR file data");
      rar->valid = 0;
      return -1;
    }