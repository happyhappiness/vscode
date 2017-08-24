(std::vector<std::string>::const_iterator p = path.begin();
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