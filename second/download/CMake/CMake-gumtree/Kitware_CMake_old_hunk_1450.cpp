        case CommandLineArguments::CONCAT_ARGUMENT: strcat(argument, "opt"); break;

        case CommandLineArguments::SPACE_ARGUMENT:  strcat(argument, " opt"); break;

        case CommandLineArguments::EQUAL_ARGUMENT:  strcat(argument, "=opt"); break;

        }

      char buffer[80];

      sprintf(buffer, format, argument);

