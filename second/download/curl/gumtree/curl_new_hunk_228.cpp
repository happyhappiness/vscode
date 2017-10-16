      case 'f':
        config->writeenv ^= TRUE;
        break;
#endif
      case 'g': /* --trace */
        GetStr(&config->trace_dump, nextarg);
        if(config->tracetype && (config->tracetype != TRACE_BIN))
          warnf(config, "--trace overrides an earlier trace/verbose option\n");
        config->tracetype = TRACE_BIN;
        break;
      case 'h': /* --trace-ascii */
        GetStr(&config->trace_dump, nextarg);
        if(config->tracetype && (config->tracetype != TRACE_ASCII))
          warnf(config,
                "--trace-ascii overrides an earlier trace/verbose option\n");
        config->tracetype = TRACE_ASCII;
        break;
      case 'i': /* --limit-rate */
        {
          /* We support G, M, K too */
          char *unit;
