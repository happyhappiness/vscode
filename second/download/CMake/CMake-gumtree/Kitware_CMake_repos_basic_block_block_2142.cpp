{
  std::string ret;
  // make it big enough for all of path and double quotes
  ret.reserve(path.size() + 3);
  // put path into the string
  ret = path;
  std::string::size_type pos = 0;
  // first convert all of the slashes
  while ((pos = ret.find('/', pos)) != std::string::npos) {
    ret[pos] = '\\';
    pos++;
  }
  // check for really small paths
  if (ret.size() < 2) {
    return ret;
  }
  // now clean up a bit and remove double slashes
  // Only if it is not the first position in the path which is a network
  // path on windows
  pos = 1; // start at position 1
  if (ret[0] == '\"') {
    pos = 2; // if the string is already quoted then start at 2
    if (ret.size() < 3) {
      return ret;
    }
  }
  while ((pos = ret.find("\\\\", pos)) != std::string::npos) {
    ret.erase(pos, 1);
  }
  // now double quote the path if it has spaces in it
  // and is not already double quoted
  if (ret.find(' ') != std::string::npos && ret[0] != '\"') {
    ret.insert(static_cast<std::string::size_type>(0),
               static_cast<std::string::size_type>(1), '\"');
    ret.append(1, '\"');
  }
  return ret;
}