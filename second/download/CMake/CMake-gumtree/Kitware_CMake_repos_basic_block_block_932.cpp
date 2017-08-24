{
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