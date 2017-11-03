const char*
parse_whole_list(const char* first, const char* last, torrent::Object* dest) {
  first = parse_skip_wspace(first, last);
  first = parse_object(first, last, dest);
  first = parse_skip_wspace(first, last);

  if (first != last && parse_is_seperator(*first)) {
    torrent::Object tmp = torrent::Object(torrent::Object::TYPE_LIST);
    tmp.swap(*dest);

    dest->as_list().push_back(tmp);
    first = parse_list(++first, last, dest);
  }

  return first;
}