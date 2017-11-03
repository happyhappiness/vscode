std::string
convert_list_to_string(torrent::Object::list_type::const_iterator first,
                       torrent::Object::list_type::const_iterator last) {
  std::string dest;

  while (first != last) {
    if (!first->is_string())
      throw torrent::input_error("Could not convert non-string list element to string.");

    // Meh.
    if (!dest.empty())
      dest += ",\"";
    else
      dest += '"';

    std::string::size_type quoteItr = dest.size();
    dest += first->as_string();

    // Finding a quote inside the string should be relatively rare, so
    // use something that is fast in the general case and ignore the
    // cost of the unusual one.
    while (quoteItr != dest.size()) {
      if (dest[quoteItr] == '"' || dest[quoteItr] == '\\')
        dest.insert(quoteItr++, 1, '\\');

      quoteItr++;
    }

    dest += '"';
    first++;
  }

  return dest;
}