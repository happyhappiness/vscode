    return (ARCHIVE_FATAL);

  }



  if ((h = __archive_read_ahead(a, header_size - 7, NULL)) == NULL)

    return (ARCHIVE_FATAL);



  /* File Header CRC check. */

  crc32_val = crc32(crc32_val, h, header_size - 7);

  if ((crc32_val & 0xffff) != archive_le16dec(rar_header.crc)) {

    archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,

      "Header CRC error");

