  }

  windowoffs = lzss_offset_for_position(&rar->lzss, startpos);
  if(windowoffs + length <= lzss_size(&rar->lzss))
    memcpy(&rar->unp_buffer[rar->unp_offset], &rar->lzss.window[windowoffs],
           length);
  else
  {
    firstpart = lzss_size(&rar->lzss) - windowoffs;
    if (firstpart < 0) {
      archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
