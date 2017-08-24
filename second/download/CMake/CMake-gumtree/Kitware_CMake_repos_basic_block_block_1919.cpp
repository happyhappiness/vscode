(quotes != std::string::npos) {
        arg.erase(quotes, 1);
        quotes = arg.find('"');
      }