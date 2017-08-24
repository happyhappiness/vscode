(this->StoreUnusedArgumentsFlag) {
        CommandLineArguments_DEBUG("Store unused argument " << arg);
        this->Internals->UnusedArguments.push_back(arg);
      }