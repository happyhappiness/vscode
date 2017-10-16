      case 'f':
        config->writeenv ^= TRUE;
        break;
#endif
      case 'g': /* --trace */
        GetStr(&config->trace_dump, nextarg);
        config->tracetype = TRACE_BIN;
        break;
      case 'h': /* --trace-ascii */
        GetStr(&config->trace_dump, nextarg);
        config->tracetype = TRACE_ASCII;
        break;
      case 'i': /* --limit-rate */
        {
          /* We support G, M, K too */
          char *unit;
