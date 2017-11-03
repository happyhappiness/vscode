std::pair<torrent::Object, const char*>
parse_command(core::Download* download, const char* first, const char* last) {
  first = std::find_if(first, last, std::not1(command_map_is_space()));

  if (first == last || *first == '#')
    return std::make_pair(torrent::Object(), first);
  
  std::string key;
  first = parse_command_name(first, last, &key);
  first = std::find_if(first, last, std::not1(command_map_is_space()));
  
  if (first == last || *first != '=')
    throw torrent::input_error("Could not find '='.");

  torrent::Object args;
  first = parse_whole_list(first + 1, last, &args);

  // Find the last character that is part of this command, skipping
  // the whitespace at the end. This ensures us that the caller
  // doesn't need to do this nor check for junk at the end.
  first = std::find_if(first, last, std::not1(command_map_is_space()));
  
  if (first != last) {
    if (*first != '\n' && *first != ';' && *first != '\0')
      throw torrent::input_error("Junk at end of input.");

    first++;
  }

  // Replace any strings starting with '$' with the result of the
  // following command.
  parse_command_execute(download, &args);

  return std::make_pair(commands.call_command_d(key.c_str(), download, args), first);
}