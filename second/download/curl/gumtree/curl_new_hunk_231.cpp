      cleanarg(nextarg);
      checkpasswd("proxy", &config->proxyuserpwd);
      break;
    case 'v':
      /* the '%' thing here will cause the trace get sent to stderr */
      GetStr(&config->trace_dump, (char *)"%");
      if(config->tracetype && (config->tracetype != TRACE_PLAIN))
        warnf(config,
              "-v/--verbose overrides an earlier trace/verbose option\n");
      config->tracetype = TRACE_PLAIN;
      break;
    case 'V':
    {
      const char * const *proto;

