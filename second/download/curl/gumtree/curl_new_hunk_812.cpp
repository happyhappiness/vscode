      GetStr(&config->proxyuserpwd, nextarg);
      cleanarg(nextarg);
      break;
    case 'v':
      if(toggle) {
        /* the '%' thing here will cause the trace get sent to stderr */
        Curl_safefree(global->trace_dump);
        global->trace_dump = strdup("%");
        if(!global->trace_dump)
          return PARAM_NO_MEM;
        if(global->tracetype && (global->tracetype != TRACE_PLAIN))
          warnf(config,
                "-v, --verbose overrides an earlier trace/verbose option\n");
        global->tracetype = TRACE_PLAIN;
      }
      else
        /* verbose is disabled here */
        global->tracetype = TRACE_NONE;
      break;
    case 'V':
      if(toggle)    /* --no-version yields no output! */
        return PARAM_VERSION_INFO_REQUESTED;
      break;

    case 'w':
      /* get the output string */
      if('@' == *nextarg) {
        /* the data begins with a '@' letter, it means that a file name
           or - (stdin) follows */
        FILE *file;
