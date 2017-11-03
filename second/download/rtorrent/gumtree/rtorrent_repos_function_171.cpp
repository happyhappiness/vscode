void
parse_whole_string(const char* first, const char* last, std::string* dest) {
  first = parse_skip_wspace(first, last);
  first = parse_string(first, last, dest);
  first = parse_skip_wspace(first, last);
   
  if (first != last)
    throw torrent::input_error("Junk at end of input.");
}