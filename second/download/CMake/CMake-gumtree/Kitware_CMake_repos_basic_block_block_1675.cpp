{
    size_t at = lines[i].find(name);
    if (at == std::string::npos) {
      continue;
    }
    std::istringstream is(lines[i].substr(at + name.size()));
    is >> value;
    return 0;
  }