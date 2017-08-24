{
    extensions.push_back(".com");
    extensions.push_back(".exe");

    // first try with extensions if the os supports them
    for (std::vector<std::string>::iterator i = extensions.begin();
         i != extensions.end(); ++i) {
      tryPath = name;
      tryPath += *i;
      if (SystemTools::FileExists(tryPath, true)) {
        return SystemTools::CollapseFullPath(tryPath);
      }
    }
  }