                            sizeof(rar->reserved2));
      }

      if (rar->main_flags & MHD_VOLUME ||
          rar->main_flags & MHD_FIRSTVOLUME)
      {
        archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                          "RAR volume support unavailable.");
        return (ARCHIVE_FATAL);
      }
      if (rar->main_flags & MHD_PASSWORD)
      {
        archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                          "RAR encryption support unavailable.");
        return (ARCHIVE_FATAL);
      }

      crc32_val = crc32(0, (const unsigned char *)p + 2, skip - 2);
      if ((crc32_val & 0xffff) != archive_le16dec(p)) {
        archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
          "Header CRC error");
