{
      case 4:
        wc = (wc << 8) | *(const unsigned char *) from++;
        wc = (wc << 8) | *(const unsigned char *) from++;
        /* fallthrough */
      case 2:
        wc = (wc << 8) | *(const unsigned char *) from++;
        /* fallthrough */
      default: /* case 1: */
        wc = (wc << 8) | *(const unsigned char *) from++;
      }