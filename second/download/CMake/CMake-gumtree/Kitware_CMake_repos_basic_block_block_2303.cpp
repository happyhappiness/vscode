(rpos == std::string::npos) {
      // Line ends at end of string without a newline.
      lines.push_back(data.substr(lpos));
      return false;
    }