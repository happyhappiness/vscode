(parser->PPDefinitions.find(macro) ==
             parser->PPDefinitions.end()) {
    parser->InPPFalseBranch = 1;
  }