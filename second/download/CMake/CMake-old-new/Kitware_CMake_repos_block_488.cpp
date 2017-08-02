{
        archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                          "Invalid PPMd sequence");
        return (ARCHIVE_FATAL);
      }