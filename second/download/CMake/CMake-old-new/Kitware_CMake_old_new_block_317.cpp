{
      str << std::endl;
      char argument[100];
      sprintf(argument, "%s", sit->c_str());
      switch ( this->Internals->Callbacks[*sit].ArgumentType )
        {
        case CommandLineArguments::NO_ARGUMENT: break;
        case CommandLineArguments::CONCAT_ARGUMENT: strcat(argument, "opt"); break;
        case CommandLineArguments::SPACE_ARGUMENT:  strcat(argument, " opt"); break;
        case CommandLineArguments::EQUAL_ARGUMENT:  strcat(argument, "=opt"); break;
        case CommandLineArguments::MULTI_ARGUMENT:  strcat(argument, " opt opt ..."); break;
        }
      char buffer[80];
      sprintf(buffer, format, argument);
      str << buffer;
      }