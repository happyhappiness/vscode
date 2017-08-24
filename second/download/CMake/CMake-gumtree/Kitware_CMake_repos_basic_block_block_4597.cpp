f(!strncmp(fmt, "I32", 3)) {
          flags |= FLAGS_LONG;
          fmt += 3;
        }
        else if(!strncmp(fmt, "I64", 3)) {
          flags |= FLAGS_LONGLONG;
          fmt += 3;
        }
        else
#endif

        switch(*fmt++) {
        case ' ':
          flags |= FLAGS_SPACE;
          break;
        case '+':
          flags |= FLAGS_SHOWSIGN;
          break;
        case '-':
          flags |= FLAGS_LEFT;
          flags &= ~FLAGS_PAD_NIL;
          break;
        case '#':
          flags |= FLAGS_ALT;
          break;
        case '.':
          if('*' == *fmt) {
            /* The precision is picked from a specified parameter */

            flags |= FLAGS_PRECPARAM;
            fmt++;
            param_num++;

            i = dprintf_DollarString(fmt, &fmt);
            if(i)
              precision = i;
            else
              precision = param_num;

            if(precision > max_param)
              max_param = precision;
          }
          else {
            flags |= FLAGS_PREC;
            precision = strtol(fmt, &fmt, 10);
          }
          break;
        case 'h':
          flags |= FLAGS_SHORT;
          break;
#if defined(MP_HAVE_INT_EXTENSIONS)
        case 'I':
#if (CURL_SIZEOF_CURL_OFF_T > CURL_SIZEOF_LONG)
          flags |= FLAGS_LONGLONG;
#else
          flags |= FLAGS_LONG;
#endif
          break;
#endif
        case 'l':
          if(flags & FLAGS_LONG)
            flags |= FLAGS_LONGLONG;
          else
            flags |= FLAGS_LONG;
          break;
        case 'L':
          flags |= FLAGS_LONGDOUBLE;
          break;
        case 'q':
          flags |= FLAGS_LONGLONG;
          break;
        case 'z':
          /* the code below generates a warning if -Wunreachable-code is
             used */
#if (SIZEOF_SIZE_T > CURL_SIZEOF_LONG)
          flags |= FLAGS_LONGLONG;
#else
          flags |= FLAGS_LONG;
#endif
          break;
        case 'O':
#if (CURL_SIZEOF_CURL_OFF_T > CURL_SIZEOF_LONG)
          flags |= FLAGS_LONGLONG;
#else
          flags |= FLAGS_LONG;
#endif
          break;
        case '0':
          if(!(flags & FLAGS_LEFT))
            flags |= FLAGS_PAD_NIL;
          /* FALLTHROUGH */
        case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
          flags |= FLAGS_WIDTH;
          width = strtol(fmt-1, &fmt, 10);
          break;
        case '*':  /* Special case */
          flags |= FLAGS_WIDTHPARAM;
          param_num++;

          i = dprintf_DollarString(fmt, &fmt);
          if(i)
            width = i;
          else
            width = param_num;
          if(width > max_param)
            max_param=width;
          break;
        default:
          break;
        }