{
    std::string::size_type endpos = pathEnv.find(pathSep, start);
    if (endpos != std::string::npos) {
      path.push_back(pathEnv.substr(start, endpos - start));
      start = endpos + 1;
    } else {
      done = true;
    }
  }