(in_base) {
      // Use the given base path.
      SystemTools::SplitPath(in_base, base_components);
    } else {
      // Use the current working directory as a base path.
      char buf[2048];
      if (const char* cwd = Getcwd(buf, 2048)) {
        SystemTools::SplitPath(cwd, base_components);
      } else {
        base_components.push_back("");
      }
    }