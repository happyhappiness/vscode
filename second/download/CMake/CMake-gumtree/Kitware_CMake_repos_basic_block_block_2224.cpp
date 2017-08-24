{
  // See if the executable exists as written.
  if (SystemTools::FileExists(name, true)) {
    return SystemTools::CollapseFullPath(name);
  }

  // Add the system search path to our path.
  std::vector<std::string> path;
  SystemTools::GetPath(path);
  // now add the additional paths
  {
    for (std::vector<std::string>::const_iterator i = userPaths.begin();
         i != userPaths.end(); ++i) {
      path.push_back(*i);
    }
  }
  // Add a trailing slash to all paths to aid the search process.
  {
    for (std::vector<std::string>::iterator i = path.begin(); i != path.end();
         ++i) {
      std::string& p = *i;
      if (p.empty() || *p.rbegin() != '/') {
        p += "/";
      }
    }
  }
  std::string tryPath;
  for (std::vector<std::string>::const_iterator p = path.begin();
       p != path.end(); ++p) {
#if defined(__APPLE__)
    tryPath = *p;
    tryPath += name;
    tryPath += ".framework";
    if (SystemTools::FileIsDirectory(tryPath)) {
      return SystemTools::CollapseFullPath(tryPath);
    }
#endif
#if defined(_WIN32) && !defined(__CYGWIN__) && !defined(__MINGW32__)
    tryPath = *p;
    tryPath += name;
    tryPath += ".lib";
    if (SystemTools::FileExists(tryPath, true)) {
      return SystemTools::CollapseFullPath(tryPath);
    }
#else
    tryPath = *p;
    tryPath += "lib";
    tryPath += name;
    tryPath += ".so";
    if (SystemTools::FileExists(tryPath, true)) {
      return SystemTools::CollapseFullPath(tryPath);
    }
    tryPath = *p;
    tryPath += "lib";
    tryPath += name;
    tryPath += ".a";
    if (SystemTools::FileExists(tryPath, true)) {
      return SystemTools::CollapseFullPath(tryPath);
    }
    tryPath = *p;
    tryPath += "lib";
    tryPath += name;
    tryPath += ".sl";
    if (SystemTools::FileExists(tryPath, true)) {
      return SystemTools::CollapseFullPath(tryPath);
    }
    tryPath = *p;
    tryPath += "lib";
    tryPath += name;
    tryPath += ".dylib";
    if (SystemTools::FileExists(tryPath, true)) {
      return SystemTools::CollapseFullPath(tryPath);
    }
    tryPath = *p;
    tryPath += "lib";
    tryPath += name;
    tryPath += ".dll";
    if (SystemTools::FileExists(tryPath, true)) {
      return SystemTools::CollapseFullPath(tryPath);
    }
#endif
  }

  // Couldn't find the library.
  return "";
}