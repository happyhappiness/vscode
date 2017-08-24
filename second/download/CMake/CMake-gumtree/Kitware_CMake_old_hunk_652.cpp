                            sizeof(rar->reserved2));
      }

      if (rar->main_flags & MHD_PASSWORD)
      {
        archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                          "RAR encryption support unavailable.");
        return (ARCHIVE_FATAL);
      }
