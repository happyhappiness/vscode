void
parse_command_multiple(core::Download* download, const char* first, const char* last) {
  while (first != last) {
    // Should we check the return value? Probably not necessary as
    // parse_args throws on unquoted multi-word input.
    std::pair<torrent::Object, const char*> result = parse_command(download, first, last);

    first = result.second;
  }
}