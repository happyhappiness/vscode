        case '\0':
        case '\r':
        case '\n':
        case '#': /* comment */
          break;
        default:
          warnf(config, "%s:%d: warning: '%s' uses unquoted white space in the"
                " line that may cause side-effects!\n",
                filename, lineno, option);
        }
      }

      if(param && !*param) {
        /* do this so getparameter can check for required parameters.
