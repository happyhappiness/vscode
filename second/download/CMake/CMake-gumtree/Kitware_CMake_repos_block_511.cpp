{
          /* Broken RAR files cause this case.
          * NOTE: If this case were possible on a normal RAR file
          * we would find out where it was actually bad and
          * what we would do to solve it. */
          archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                            "Internal error extracting RAR file");
          return (ARCHIVE_FATAL);
      }