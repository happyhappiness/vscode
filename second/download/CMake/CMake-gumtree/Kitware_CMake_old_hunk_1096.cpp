    return (ARCHIVE_EOF);

  }



  *buff = __archive_read_ahead(a, 1, &bytes_avail);

  if (bytes_avail <= 0)

  {

    archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,

                      "Truncated RAR file data");

    return (ARCHIVE_FATAL);

  }

  if (bytes_avail > rar->bytes_remaining)

    bytes_avail = rar->bytes_remaining;



  *size = bytes_avail;

  *offset = rar->offset;

  rar->offset += bytes_avail;

  rar->bytes_remaining -= bytes_avail;

  rar->bytes_unconsumed = bytes_avail;

  /* Calculate File CRC. */

  rar->crc_calculated = crc32(rar->crc_calculated, *buff, bytes_avail);

  return (ARCHIVE_OK);

}



