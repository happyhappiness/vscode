{
          archive_set_error(&a->archive, ENOMEM,
                            "Unable to allocate memory for node data.");
          return (ARCHIVE_FATAL);
        }