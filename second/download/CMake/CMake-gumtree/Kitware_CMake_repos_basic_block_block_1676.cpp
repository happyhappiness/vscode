{
  size_t nLines = lines.size();
  for (size_t i = 0; i < nLines; ++i) {
    size_t at = lines[i].find(name);
    if (at == std::string::npos) {
      continue;
    }
    std::istringstream is(lines[i].substr(at + name.size()));
    is >> value;
    return 0;
  }
  return -1;
}