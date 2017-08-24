(sit = mpit->second.begin(); sit != mpit->second.end(); sit++) {
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