{
    archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
      "Header CRC error");
    return (ARCHIVE_FATAL);
  }