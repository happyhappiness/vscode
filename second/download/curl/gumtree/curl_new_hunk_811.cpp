      if(err)
        return err;
      break;
    case 'M': /* M for manual, huge help */
      if(toggle) { /* --no-manual shows no manual... */
#ifdef USE_MANUAL
        return PARAM_MANUAL_REQUESTED;
#else
        warnf(config,
              "built-in manual was disabled at build-time!\n");
        return PARAM_OPTION_UNKNOWN;
#endif
      }
