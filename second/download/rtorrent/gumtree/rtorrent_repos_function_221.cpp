void
parse_command_d_multiple(core::Download* download, const char* first) {
  parse_command_multiple(download, first, first + std::strlen(first));
}