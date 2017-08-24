{
    std::set<std::string>::iterator match;
    match = parser->PPDefinitions.find(macro);
    if (match != parser->PPDefinitions.end()) {
      parser->PPDefinitions.erase(match);
    }
  }