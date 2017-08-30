      switch ( this->Internals->Callbacks[*sit].ArgumentType )
        {
        case CommandLineArguments::NO_ARGUMENT: break;
        case CommandLineArguments::CONCAT_ARGUMENT: strcat(argument, "option"); break;
        case CommandLineArguments::SPACE_ARGUMENT:  strcat(argument, " option"); break;
        case CommandLineArguments::EQUAL_ARGUMENT:  strcat(argument, "=option"); break;
        }
      char buffer[80];
      sprintf(buffer, format, argument);
      str << buffer;
      }
    str << "\t";
    const char* ptr = this->Internals->Callbacks[mpit->first].Help;
    int len = strlen(ptr);
    int cnt = 0;
