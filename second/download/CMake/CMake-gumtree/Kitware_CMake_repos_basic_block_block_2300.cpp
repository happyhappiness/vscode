{
  std::string data(str);
  std::string::size_type lpos = 0;
  while (lpos < data.length()) {
    std::string::size_type rpos = data.find_first_of(separator, lpos);
    if (rpos == std::string::npos) {
      // Line ends at end of string without a newline.
      lines.push_back(data.substr(lpos));
      return false;
    } else {
      // Line ends in a "\n", remove the character.
      lines.push_back(data.substr(lpos, rpos - lpos));
    }
    lpos = rpos + 1;
  }
  return true;
}