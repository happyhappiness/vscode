{
        if (skip < 7 + sizeof(rar->reserved1) + sizeof(rar->reserved2)+1) {
          archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
            "Invalid header size");
          return (ARCHIVE_FATAL);
        }
        rar->encryptver = *(p + 7 + sizeof(rar->reserved1) +
                            sizeof(rar->reserved2));
      }