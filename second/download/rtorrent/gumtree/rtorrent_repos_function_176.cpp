const char*
parse_object(const char* first, const char* last, torrent::Object* dest, bool (*delim)(const char)) {
  if (*first == '{') {
    *dest = torrent::Object(torrent::Object::TYPE_LIST);
    first = parse_list(first + 1, last, dest, &parse_is_delim_list);
    first = parse_skip_wspace(first, last);
    
    if (first == last || *first != '}')
      throw torrent::input_error("Could not find closing '}'.");

    return ++first;

  } else {
    *dest = std::string();

    return parse_string(first, last, &dest->as_string(), delim);
  }
}