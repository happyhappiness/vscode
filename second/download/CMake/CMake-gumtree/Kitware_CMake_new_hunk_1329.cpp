      switch ( this->Internals->Callbacks[*sit].ArgumentType )
        {
        case CommandLineArguments::NO_ARGUMENT: break;
        case CommandLineArguments::CONCAT_ARGUMENT: strcat(argument, "opt"); break;
        case CommandLineArguments::SPACE_ARGUMENT:  strcat(argument, " opt"); break;
        case CommandLineArguments::EQUAL_ARGUMENT:  strcat(argument, "=opt"); break;
        }
      char buffer[80];
      sprintf(buffer, format, argument);
      str << buffer;
      }
    const char* ptr = this->Internals->Callbacks[mpit->first].Help;
    int len = strlen(ptr);
    int cnt = 0;
