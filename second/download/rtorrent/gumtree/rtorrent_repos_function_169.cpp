const char*
parse_skip_wspace(const char* first) {
  while (parse_is_space(*first))
    first++;

  return first;
}