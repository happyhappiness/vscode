const char*
parse_list(const char* first, const char* last, torrent::Object* dest, bool (*delim)(const char)) {
  if (!dest->is_list())
    throw torrent::internal_error("parse_list(...) !dest->is_list().");

  while (true) {
    torrent::Object tmp;

    first = parse_skip_wspace(first, last);
    first = parse_object(first, last, &tmp, delim);
    first = parse_skip_wspace(first, last);

    dest->as_list().push_back(tmp);
    
    if (first == last || !parse_is_seperator(*first))
      break;

    first++;
  }

  return first;
}