std::string
convert_list_to_command(torrent::Object::list_type::const_iterator first,
                        torrent::Object::list_type::const_iterator last) {
  if (first == last)
    throw torrent::input_error("Too few arguments.");

  std::string dest = (first++)->as_string();
  std::string::size_type quoteItr = dest.find('=');
  
  if (quoteItr == std::string::npos)
    throw torrent::input_error("Could not find '=' in command.");

  // We should only escape backslash, not quote here as the string
  // will start with the command name which isn't quoted.
  while ((quoteItr = dest.find('\\', quoteItr + 1)) != std::string::npos)
    dest.insert(quoteItr++, 1, '\\');

  while (first != last) {
    if (!first->is_string())
      throw torrent::input_error("Could not convert non-string list element to string.");

    dest += ",\"";

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