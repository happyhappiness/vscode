(std::vector<std::string>::iterator i = path.begin(); i != path.end();
         ++i) {
      std::string& p = *i;
      if (p.empty() || *p.rbegin() != '/') {
        p += "/";
      }
    }