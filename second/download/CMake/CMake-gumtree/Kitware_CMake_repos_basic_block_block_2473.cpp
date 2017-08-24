{
      std::cerr << "Bad unused argument [" << cc << "] \"" << newArgv[cc]
                << "\" should be: \"" << valid_unused_args[cc] << "\""
                << std::endl;
      res = 1;
    }