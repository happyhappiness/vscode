{
      archive_set_error(&a->archive, ENOMEM,
                        "Couldn't allocate memory.");
      return (ARCHIVE_FATAL);
    }