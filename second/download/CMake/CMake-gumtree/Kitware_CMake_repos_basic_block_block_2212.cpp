{
  std::string tryPath;

#if defined(_WIN32) || defined(__CYGWIN__) || defined(__MINGW32__)
  std::vector<std::string> extensions;
  // check to see if the name already has a .xxx at
  // the end of it
  // on windows try .com then .exe
  if (name.size() <= 3 || name[name.size() - 4] != '.') {
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
#endif

  // now try just the name
  if (SystemTools::FileExists(name, true)) {
    return SystemTools::CollapseFullPath(name);
  }
  // now construct the path
  std::vector<std::string> path;
  // Add the system search path to our path.
  if (!no_system_path) {
    SystemTools::GetPath(path);
  }
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
  // Try each path
  for (std::vector<std::string>::iterator p = path.begin(); p != path.end();
       ++p) {
#ifdef _WIN32
    // Remove double quotes from the path on windows
    SystemTools::ReplaceString(*p, "\"", "");
#endif
#if defined(_WIN32) || defined(__CYGWIN__) || defined(__MINGW32__)
    // first try with extensions
    for (std::vector<std::string>::iterator ext = extensions.begin();
         ext != extensions.end(); ++ext) {
      tryPath = *p;
      tryPath += name;
      tryPath += *ext;
      if (SystemTools::FileExists(tryPath, true)) {
        return SystemTools::CollapseFullPath(tryPath);
      }
    }
#endif
    // now try it without them
    tryPath = *p;
    tryPath += name;
    if (SystemTools::FileExists(tryPath, true)) {
      return SystemTools::CollapseFullPath(tryPath);
    }
  }
  // Couldn't find the program.
  return "";
}