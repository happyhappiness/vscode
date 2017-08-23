void CommandLineArguments::GenerateHelp()
{
  std::ostringstream str;

  // Collapse all arguments into the map of vectors of all arguments that do
  // the same thing.
  CommandLineArguments::Internal::CallbacksMap::iterator it;
  typedef std::map<CommandLineArguments::Internal::String,
                   CommandLineArguments::Internal::SetOfStrings>
    MapArgs;
  MapArgs mp;
  MapArgs::iterator mpit, smpit;
  for (it = this->Internals->Callbacks.begin();
       it != this->Internals->Callbacks.end(); it++) {
    CommandLineArgumentsCallbackStructure* cs = &(it->second);
    mpit = mp.find(cs->Help);
    if (mpit != mp.end()) {
      mpit->second.insert(it->first);
      mp[it->first].insert(it->first);
    } else {
      mp[it->first].insert(it->first);
    }
  }
  for (it = this->Internals->Callbacks.begin();
       it != this->Internals->Callbacks.end(); it++) {
    CommandLineArgumentsCallbackStructure* cs = &(it->second);
    mpit = mp.find(cs->Help);
    if (mpit != mp.end()) {
      mpit->second.insert(it->first);
      smpit = mp.find(it->first);
      CommandLineArguments::Internal::SetOfStrings::iterator sit;
      for (sit = smpit->second.begin(); sit != smpit->second.end(); sit++) {
        mpit->second.insert(*sit);
      }
      mp.erase(smpit);
    } else {
      mp[it->first].insert(it->first);
    }
  }

  // Find the length of the longest string
  CommandLineArguments::Internal::String::size_type maxlen = 0;
  for (mpit = mp.begin(); mpit != mp.end(); mpit++) {
    CommandLineArguments::Internal::SetOfStrings::iterator sit;
    for (sit = mpit->second.begin(); sit != mpit->second.end(); sit++) {
      CommandLineArguments::Internal::String::size_type clen = sit->size();
      switch (this->Internals->Callbacks[*sit].ArgumentType) {
        case CommandLineArguments::NO_ARGUMENT:
          clen += 0;
          break;
        case CommandLineArguments::CONCAT_ARGUMENT:
          clen += 3;
          break;
        case CommandLineArguments::SPACE_ARGUMENT:
          clen += 4;
          break;
        case CommandLineArguments::EQUAL_ARGUMENT:
          clen += 4;
          break;
      }
      if (clen > maxlen) {
        maxlen = clen;
      }
    }
  }

  // Create format for that string
  char format[80];
  sprintf(format, "  %%-%us  ", static_cast<unsigned int>(maxlen));

  maxlen += 4; // For the space before and after the option

  // Print help for each option
  for (mpit = mp.begin(); mpit != mp.end(); mpit++) {
    CommandLineArguments::Internal::SetOfStrings::iterator sit;
    for (sit = mpit->second.begin(); sit != mpit->second.end(); sit++) {
      str << std::endl;
      char argument[100];
      sprintf(argument, "%s", sit->c_str());
      switch (this->Internals->Callbacks[*sit].ArgumentType) {
        case CommandLineArguments::NO_ARGUMENT:
          break;
        case CommandLineArguments::CONCAT_ARGUMENT:
          strcat(argument, "opt");
          break;
        case CommandLineArguments::SPACE_ARGUMENT:
          strcat(argument, " opt");
          break;
        case CommandLineArguments::EQUAL_ARGUMENT:
          strcat(argument, "=opt");
          break;
        case CommandLineArguments::MULTI_ARGUMENT:
          strcat(argument, " opt opt ...");
          break;
      }
      char buffer[80];
      sprintf(buffer, format, argument);
      str << buffer;
    }
    const char* ptr = this->Internals->Callbacks[mpit->first].Help;
    size_t len = strlen(ptr);
    int cnt = 0;
    while (len > 0) {
      // If argument with help is longer than line length, split it on previous
      // space (or tab) and continue on the next line
      CommandLineArguments::Internal::String::size_type cc;
      for (cc = 0; ptr[cc]; cc++) {
        if (*ptr == ' ' || *ptr == '\t') {
          ptr++;
          len--;
        }
      }
      if (cnt > 0) {
        for (cc = 0; cc < maxlen; cc++) {
          str << " ";
        }
      }
      CommandLineArguments::Internal::String::size_type skip = len;
      if (skip > this->LineLength - maxlen) {
        skip = this->LineLength - maxlen;
        for (cc = skip - 1; cc > 0; cc--) {
          if (ptr[cc] == ' ' || ptr[cc] == '\t') {
            break;
          }
        }
        if (cc != 0) {
          skip = cc;
        }
      }
      str.write(ptr, static_cast<std::streamsize>(skip));
      str << std::endl;
      ptr += skip;
      len -= skip;
      cnt++;
    }
  }
  /*
  // This can help debugging help string
  str << endl;
  unsigned int cc;
  for ( cc = 0; cc < this->LineLength; cc ++ )
    {
    str << cc % 10;
    }
  str << endl;
  */
  this->Help = str.str();
}