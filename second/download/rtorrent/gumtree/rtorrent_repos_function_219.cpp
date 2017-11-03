void
parse_command_single(const char* first) {
  parse_command(NULL, first, first + std::strlen(first));
}