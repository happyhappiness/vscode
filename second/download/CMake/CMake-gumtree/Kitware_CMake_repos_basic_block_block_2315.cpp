{
  if (!filename || percent_bin < 0) {
    return SystemTools::FileTypeUnknown;
  }

  if (SystemTools::FileIsDirectory(filename)) {
    return SystemTools::FileTypeUnknown;
  }

  FILE* fp = Fopen(filename, "rb");
  if (!fp) {
    return SystemTools::FileTypeUnknown;
  }

  // Allocate buffer and read bytes

  unsigned char* buffer = new unsigned char[length];
  size_t read_length = fread(buffer, 1, length, fp);
  fclose(fp);
  if (read_length == 0) {
    delete[] buffer;
    return SystemTools::FileTypeUnknown;
  }

  // Loop over contents and count

  size_t text_count = 0;

  const unsigned char* ptr = buffer;
  const unsigned char* buffer_end = buffer + read_length;

  while (ptr != buffer_end) {
    if ((*ptr >= 0x20 && *ptr <= 0x7F) || *ptr == '\n' || *ptr == '\r' ||
        *ptr == '\t') {
      text_count++;
    }
    ptr++;
  }

  delete[] buffer;

  double current_percent_bin = (static_cast<double>(read_length - text_count) /
                                static_cast<double>(read_length));

  if (current_percent_bin >= percent_bin) {
    return SystemTools::FileTypeBinary;
  }

  return SystemTools::FileTypeText;
}