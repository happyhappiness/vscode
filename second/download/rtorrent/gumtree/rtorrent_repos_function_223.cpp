const char*
parse_command_name(const char* first, const char* last, std::string* dest) {
  if (first == last || !std::isalpha(*first))
    throw torrent::input_error("Invalid start of name.");

  for ( ; first != last && (std::isalnum(*first) || *first == '_' || *first == '.'); ++first)
    dest->push_back(*first);

  return first;
}