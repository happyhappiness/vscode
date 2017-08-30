

  if (rar->file_flags & FHD_PASSWORD)

  {

    archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,

                      "RAR encryption support unavailable.");

    return (ARCHIVE_FATAL);

  }



  if (rar->file_flags & FHD_LARGE)

