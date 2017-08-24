{
      std::string& p = *i;
      if (p.empty() || *p.rbegin() != '/') {
        p += "/";
      }
    }