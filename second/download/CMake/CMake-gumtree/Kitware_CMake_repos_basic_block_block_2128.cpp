{
    std::string root = path.substr(0, rootEnd);
    std::string pathPart = path.substr(rootEnd + 2, pathEnd - rootEnd - 2);
    const char* pathCString = pathPart.c_str();
    const char* pos0 = pathCString;
    for (std::string::size_type pos = 0; *pos0; ++pos) {
      if (*pos0 == '.') {
        pathPart[pos] = '/';
      }
      pos0++;
    }
    path = "/" + root + "/" + pathPart;
  }