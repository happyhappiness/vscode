{
    const CommandLineArguments::Internal::String& parg = it->first;
    CommandLineArgumentsCallbackStructure* cs = &it->second;
    if (cs->ArgumentType == CommandLineArguments::NO_ARGUMENT ||
        cs->ArgumentType == CommandLineArguments::SPACE_ARGUMENT) {
      if (arg == parg) {
        matches->push_back(parg);
      }
    } else if (arg.find(parg) == 0) {
      matches->push_back(parg);
    }
  }