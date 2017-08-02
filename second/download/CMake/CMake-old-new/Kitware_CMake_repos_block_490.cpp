{
          free(precode.tree);
          free(precode.table);
          archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                            "Internal error extracting RAR file.");
          return (ARCHIVE_FATAL);
        }