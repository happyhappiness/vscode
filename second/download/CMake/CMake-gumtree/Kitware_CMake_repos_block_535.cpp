{
      archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
                        "Parsing filters is unsupported.");
      return (ARCHIVE_FAILED);
    }