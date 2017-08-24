{
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