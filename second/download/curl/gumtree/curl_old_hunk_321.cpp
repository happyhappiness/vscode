          return PARAM_BAD_NUMERIC;
        break;
      case 'd': /* ciphers */
        GetStr(&config->cipher_list, nextarg);
        break;
      case 'e': /* --disable-epsv */
        config->disable_epsv ^= TRUE;
        break;
#ifdef USE_ENVIRONMENT
      case 'f':
        config->writeenv ^= TRUE;
        break;
#endif
      case 'g': /* --trace */
        GetStr(&config->trace_dump, nextarg);
        if(config->tracetype && (config->tracetype != TRACE_BIN))
          warnf(config, "--trace overrides an earlier trace/verbose option\n");
