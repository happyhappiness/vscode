{
    assert(newArgv[cc]); /* Quiet Clang scan-build. */
    std::cout << "Unused argument[" << cc << "] = [" << newArgv[cc] << "]"
              << std::endl;
    if (cc >= 9) {
      std::cerr << "Too many unused arguments: " << cc << std::endl;
      res = 1;
    } else if (valid_unused_args[cc] &&
               strcmp(valid_unused_args[cc], newArgv[cc]) != 0) {
      std::cerr << "Bad unused argument [" << cc << "] \"" << newArgv[cc]
                << "\" should be: \"" << valid_unused_args[cc] << "\""
                << std::endl;
      res = 1;
    }
  }