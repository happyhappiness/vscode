{
    archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
                      "Huffman tree was not created.");
    return (ARCHIVE_FATAL);
  }