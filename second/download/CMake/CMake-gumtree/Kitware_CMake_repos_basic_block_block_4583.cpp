h(vto[i].type) {
    case FORMAT_STRING:
      vto[i].data.str = va_arg(arglist, char *);
      break;

    case FORMAT_INTPTR:
    case FORMAT_UNKNOWN:
    case FORMAT_PTR:
      vto[i].data.ptr = va_arg(arglist, void *);
      break;

    case FORMAT_INT:
#ifdef HAVE_LONG_LONG_TYPE
      if((vto[i].flags & FLAGS_LONGLONG) && (vto[i].flags & FLAGS_UNSIGNED))
        vto[i].data.num.as_unsigned =
          (mp_uintmax_t)va_arg(arglist, mp_uintmax_t);
      else if(vto[i].flags & FLAGS_LONGLONG)
        vto[i].data.num.as_signed =
          (mp_intmax_t)va_arg(arglist, mp_intmax_t);
      else
#endif
      {
        if((vto[i].flags & FLAGS_LONG) && (vto[i].flags & FLAGS_UNSIGNED))
          vto[i].data.num.as_unsigned =
            (mp_uintmax_t)va_arg(arglist, unsigned long);
        else if(vto[i].flags & FLAGS_LONG)
          vto[i].data.num.as_signed =
            (mp_intmax_t)va_arg(arglist, long);
        else if(vto[i].flags & FLAGS_UNSIGNED)
          vto[i].data.num.as_unsigned =
            (mp_uintmax_t)va_arg(arglist, unsigned int);
        else
          vto[i].data.num.as_signed =
            (mp_intmax_t)va_arg(arglist, int);
      }
      break;

    case FORMAT_DOUBLE:
      vto[i].data.dnum = va_arg(arglist, double);
      break;

    case FORMAT_WIDTH:
      /* Argument has been read. Silently convert it into an integer
       * for later use
       */
      vto[i].type = FORMAT_INT;
      break;

    default:
      break;
    }