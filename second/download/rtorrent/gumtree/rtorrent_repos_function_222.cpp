bool
parse_command_file(const std::string& path) {
  std::fstream file(rak::path_expand(path).c_str(), std::ios::in);

  if (!file.is_open())
    return false;

  unsigned int lineNumber = 0;
  char buffer[4096];

  try {
    unsigned int getCount = 0;

    while (file.getline(buffer + getCount, 4096 - getCount).good()) {
      if (file.gcount() == 0)
        throw torrent::internal_error("parse_command_file(...) file.gcount() == 0.");

      int escaped = parse_count_escaped(buffer + getCount, buffer + getCount + file.gcount() - 1);

      lineNumber++;
      getCount += file.gcount() - 1;

      if (getCount == 4096 - 1)
        throw torrent::input_error("Exceeded max line lenght.");
      
      if (escaped & 0x1) {
        // Remove the escape characters and continue reading.
        getCount -= escaped;
        continue;
      }

      // Would be nice to make this zero-copy.
      parse_command(NULL, buffer, buffer + getCount);
      getCount = 0;
    }

  } catch (torrent::input_error& e) {
    snprintf(buffer, 2048, "Error in option file: %s:%u: %s", path.c_str(), lineNumber, e.what());

    throw torrent::input_error(buffer);
  }

  return true;
}