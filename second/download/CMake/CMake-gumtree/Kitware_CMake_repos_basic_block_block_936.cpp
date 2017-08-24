{
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