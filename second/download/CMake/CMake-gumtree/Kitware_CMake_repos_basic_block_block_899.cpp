(cc = 0; cc < this->Internals->Argv.size(); cc++) {
    const std::string& arg = this->Internals->Argv[cc];
    CommandLineArguments_DEBUG("Process argument: " << arg);
    this->Internals->LastArgument = cc;
    if (this->GetMatchedArguments(&matches, arg)) {
      // Ok, we found one or more arguments that match what user specified.
      // Let's find the longest one.
      CommandLineArguments::Internal::VectorOfStrings::size_type kk;
      CommandLineArguments::Internal::VectorOfStrings::size_type maxidx = 0;
      CommandLineArguments::Internal::String::size_type maxlen = 0;
      for (kk = 0; kk < matches.size(); kk++) {
        if (matches[kk].size() > maxlen) {
          maxlen = matches[kk].size();
          maxidx = kk;
        }
      }
      // So, the longest one is probably the right one. Now see if it has any
      // additional value
      CommandLineArgumentsCallbackStructure* cs =
        &this->Internals->Callbacks[matches[maxidx]];
      const std::string& sarg = matches[maxidx];
      if (cs->Argument != sarg) {
        abort();
      }
      switch (cs->ArgumentType) {
        case NO_ARGUMENT:
          // No value
          if (!this->PopulateVariable(cs, 0)) {
            return 0;
          }
          break;
        case SPACE_ARGUMENT:
          if (cc == this->Internals->Argv.size() - 1) {
            this->Internals->LastArgument--;
            return 0;
          }
          CommandLineArguments_DEBUG("This is a space argument: "
                                     << arg << " value: "
                                     << this->Internals->Argv[cc + 1]);
          // Value is the next argument
          if (!this->PopulateVariable(cs,
                                      this->Internals->Argv[cc + 1].c_str())) {
            return 0;
          }
          cc++;
          break;
        case EQUAL_ARGUMENT:
          if (arg.size() == sarg.size() || arg.at(sarg.size()) != '=') {
            this->Internals->LastArgument--;
            return 0;
          }
          // Value is everythng followed the '=' sign
          if (!this->PopulateVariable(cs, arg.c_str() + sarg.size() + 1)) {
            return 0;
          }
          break;
        case CONCAT_ARGUMENT:
          // Value is whatever follows the argument
          if (!this->PopulateVariable(cs, arg.c_str() + sarg.size())) {
            return 0;
          }
          break;
        case MULTI_ARGUMENT:
          // Suck in all the rest of the arguments
          CommandLineArguments_DEBUG("This is a multi argument: " << arg);
          for (cc++; cc < this->Internals->Argv.size(); ++cc) {
            const std::string& marg = this->Internals->Argv[cc];
            CommandLineArguments_DEBUG(
              " check multi argument value: " << marg);
            if (this->GetMatchedArguments(&matches, marg)) {
              CommandLineArguments_DEBUG("End of multi argument "
                                         << arg << " with value: " << marg);
              break;
            }
            CommandLineArguments_DEBUG(
              " populate multi argument value: " << marg);
            if (!this->PopulateVariable(cs, marg.c_str())) {
              return 0;
            }
          }
          if (cc != this->Internals->Argv.size()) {
            CommandLineArguments_DEBUG("Again End of multi argument " << arg);
            cc--;
            continue;
          }
          break;
        default:
          std::cerr << "Got unknown argument type: \"" << cs->ArgumentType
                    << "\"" << std::endl;
          this->Internals->LastArgument--;
          return 0;
      }
    } else {
      // Handle unknown arguments
      if (this->Internals->UnknownArgumentCallback) {
        if (!this->Internals->UnknownArgumentCallback(
              arg.c_str(), this->Internals->ClientData)) {
          this->Internals->LastArgument--;
          return 0;
        }
        return 1;
      } else if (this->StoreUnusedArgumentsFlag) {
        CommandLineArguments_DEBUG("Store unused argument " << arg);
        this->Internals->UnusedArguments.push_back(arg);
      } else {
        std::cerr << "Got unknown argument: \"" << arg << "\"" << std::endl;
        this->Internals->LastArgument--;
        return 0;
      }
    }
  }