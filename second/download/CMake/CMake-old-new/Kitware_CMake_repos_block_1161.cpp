{
      archive_set_error(&a->archive, ARCHIVE_ERRNO_PROGRAMMER,
          "Internal error: Unable to append filter");
      return (ARCHIVE_FATAL);
    }