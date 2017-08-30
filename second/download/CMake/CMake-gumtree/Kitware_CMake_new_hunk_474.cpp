             &rar->lzss.window[windowoffs], firstpart);

      memcpy(&rar->unp_buffer[rar->unp_offset + firstpart],

             &rar->lzss.window[0], length - firstpart);

    } else {

      memcpy(&rar->unp_buffer[rar->unp_offset],

             &rar->lzss.window[windowoffs], length);

    }

  } else {

      archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,

                        "Bad RAR file data");

      return (ARCHIVE_FATAL);

  }

  rar->unp_offset += length;

  if (rar->unp_offset >= rar->unp_buffer_size)
