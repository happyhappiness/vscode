  memcpy(&rar_header, p, sizeof(rar_header));
  rar->file_flags = archive_le16dec(rar_header.flags);
  header_size = archive_le16dec(rar_header.size);
  if (header_size < sizeof(file_header) + 7) {
    archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
      "Invalid header size");
    return (ARCHIVE_FATAL);
