(!inQuotes) {
      std::string arg = command.substr(start + 1, pos - start - 1);

      // Remove the quotes if any
      size_t quotes = arg.find('"');
      while (quotes != std::string::npos) {
        arg.erase(quotes, 1);
        quotes = arg.find('"');
      }
      args.push_back(arg.c_str());
      start = pos;
    }