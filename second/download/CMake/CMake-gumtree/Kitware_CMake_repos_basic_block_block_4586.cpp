{
      case 'S':
        flags |= FLAGS_ALT;
        /* FALLTHROUGH */
      case 's':
        vto[i].type = FORMAT_STRING;
        break;
      case 'n':
        vto[i].type = FORMAT_INTPTR;
        break;
      case 'p':
        vto[i].type = FORMAT_PTR;
        break;
      case 'd': case 'i':
        vto[i].type = FORMAT_INT;
        break;
      case 'u':
        vto[i].type = FORMAT_INT;
        flags |= FLAGS_UNSIGNED;
        break;
      case 'o':
        vto[i].type = FORMAT_INT;
        flags |= FLAGS_OCTAL;
        break;
      case 'x':
        vto[i].type = FORMAT_INT;
        flags |= FLAGS_HEX|FLAGS_UNSIGNED;
        break;
      case 'X':
        vto[i].type = FORMAT_INT;
        flags |= FLAGS_HEX|FLAGS_UPPER|FLAGS_UNSIGNED;
        break;
      case 'c':
        vto[i].type = FORMAT_INT;
        flags |= FLAGS_CHAR;
        break;
      case 'f':
        vto[i].type = FORMAT_DOUBLE;
        break;
      case 'e':
        vto[i].type = FORMAT_DOUBLE;
        flags |= FLAGS_FLOATE;
        break;
      case 'E':
        vto[i].type = FORMAT_DOUBLE;
        flags |= FLAGS_FLOATE|FLAGS_UPPER;
        break;
      case 'g':
        vto[i].type = FORMAT_DOUBLE;
        flags |= FLAGS_FLOATG;
        break;
      case 'G':
        vto[i].type = FORMAT_DOUBLE;
        flags |= FLAGS_FLOATG|FLAGS_UPPER;
        break;
      default:
        vto[i].type = FORMAT_UNKNOWN;
        break;
      }