const char*
parse_string(const char* first, const char* last, std::string* dest, bool (*delim)(const char)) {
  if (first == last)
    return first;

  bool quoted = parse_is_quote(*first);

  if (quoted)
    first++;

  while (first != last) {
    if (quoted) {
      if (parse_is_quote(*first))
        return ++first;

    } else {
      if (delim(*first))
        return first;
    }
        
    if (parse_is_escape(*first) && ++first == last)
      throw torrent::input_error("Escape character at end of input.");

    dest->push_back(*first);
    first++;
  }
  
  if (quoted)
    throw torrent::input_error("Missing closing quote.");

  return first;
}