{
      archive_set_error(&a->archive, ENOMEM,
                        "Unable to allocate memory for uncompressed data.");
      return (ARCHIVE_FATAL);
    }