      GetStr(&config->proxyuserpwd, nextarg);
      cleanarg(nextarg);
      break;
    case 'v':
      if(toggle) {
        /* the '%' thing here will cause the trace get sent to stderr */
        Curl_safefree(config->trace_dump);
        config->trace_dump = strdup("%");
        if(!config->trace_dump)
          return PARAM_NO_MEM;
        if(config->tracetype && (config->tracetype != TRACE_PLAIN))
          warnf(config,
                "-v, --verbose overrides an earlier trace/verbose option\n");
        config->tracetype = TRACE_PLAIN;
      }
      else
        /* verbose is disabled here */
        config->tracetype = TRACE_NONE;
      break;
    case 'V':
    {
      const char *const *proto;

      if(!toggle)
        /* --no-version yields no output! */
        break;

      printf(CURL_ID "%s\n", curl_version());
      if(curlinfo->protocols) {
        printf("Protocols: ");
        for(proto = curlinfo->protocols; *proto; ++proto) {
          printf("%s ", *proto);
        }
        puts(""); /* newline */
      }
      if(curlinfo->features) {
        unsigned int i;
        printf("Features: ");
        for(i = 0; i < sizeof(feats)/sizeof(feats[0]); i++) {
          if(curlinfo->features & feats[i].bitmask)
            printf("%s ", feats[i].name);
        }
#ifdef USE_METALINK
        printf("Metalink ");
#endif
        puts(""); /* newline */
      }
    }
    return PARAM_HELP_REQUESTED;
    case 'w':
      /* get the output string */
      if('@' == *nextarg) {
        /* the data begins with a '@' letter, it means that a file name
           or - (stdin) follows */
        FILE *file;
