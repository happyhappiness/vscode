(pos2 != std::string::npos) {
    paths.push_back(path.substr(pos1, pos2 - pos1));
    pos1 = pos2 + 1;
    pos2 = path.find(sep, pos1 + 1);
  }