(s >= 0 && std::string(buf, s) == tool) {
      std::cerr << "Exists: '" << link << "' -> '" << tool << "'\n";
      return true;
    }