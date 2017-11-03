const char*
parse_skip_wspace(const char* first, const char* last) {
  while (first != last && parse_is_space(*first))
    first++;

  return first;
}