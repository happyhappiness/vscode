        /* IP addrs of DNS servers */
        GetStr(&config->dns_servers, nextarg);
        break;
      case 'g': /* --trace */
        GetStr(&global->trace_dump, nextarg);
        if(global->tracetype && (global->tracetype != TRACE_BIN))
          warnf(global, "--trace overrides an earlier trace/verbose option\n");
        global->tracetype = TRACE_BIN;
        break;
      case 'G': /* --npn */
        config->nonpn = (!toggle)?TRUE:FALSE;
        break;
      case 'h': /* --trace-ascii */
        GetStr(&global->trace_dump, nextarg);
        if(global->tracetype && (global->tracetype != TRACE_ASCII))
          warnf(global,
                "--trace-ascii overrides an earlier trace/verbose option\n");
        global->tracetype = TRACE_ASCII;
        break;
      case 'H': /* --alpn */
        config->noalpn = (!toggle)?TRUE:FALSE;
        break;
