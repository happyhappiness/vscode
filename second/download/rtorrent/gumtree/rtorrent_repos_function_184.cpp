char*
print_object(char* first, char* last, const torrent::Object* src, int flags) {
  switch (src->type()) {
  case torrent::Object::TYPE_STRING:
  {
    const std::string& str = src->as_string();

    if ((flags & print_expand_tilde) && *str.c_str() == '~') {
      return rak::path_expand(str.c_str(), first, last);

    } else {
      if (first == last)
        return first;

      size_t n = std::min<size_t>(str.size(), std::distance(first, last) - 1);

      std::memcpy(first, str.c_str(), n);
      *(first += n) = '\0';

      return first;
    }
  }
  case torrent::Object::TYPE_VALUE:
    return std::max(first + snprintf(first, std::distance(first, last), "%lli", src->as_value()), last);

  case torrent::Object::TYPE_LIST:
    for (torrent::Object::list_type::const_iterator itr = src->as_list().begin(), itrEnd = src->as_list().end(); itr != itrEnd; itr++) {
      first = print_object(first, last, &*itr, flags);

      // Don't expand tilde after the first element in the list.
      flags &= ~print_expand_tilde;
    }

    return first;

  default:
    throw torrent::input_error("Invalid type.");
  }
}