        *usedarg = TRUE; /* mark it as used */
    }

    switch(letter) {
    case '*': /* options without a short option */
      switch(subletter) {
      case '4': /* --dns-ipv4-addr */
        /* addr in dot notation */
        GetStr(&config->dns_ipv4_addr, nextarg);
        break;
      case '6': /* --dns-ipv6-addr */
        /* addr in dot notation */
        GetStr(&config->dns_ipv6_addr, nextarg);
        break;
      case 'a': /* random-file */
        GetStr(&config->random_file, nextarg);
        break;
      case 'b': /* egd-file */
        GetStr(&config->egd_file, nextarg);
        break;
      case 'B': /* XOAUTH2 Bearer */
        GetStr(&config->xoauth2_bearer, nextarg);
        break;
      case 'c': /* connect-timeout */
        err = str2udouble(&config->connecttimeout, nextarg);
        if(err)
          return err;
        break;
      case 'd': /* ciphers */
        GetStr(&config->cipher_list, nextarg);
        break;
      case 'D': /* --dns-interface */
        /* interface name */
        GetStr(&config->dns_interface, nextarg);
        break;
      case 'e': /* --disable-epsv */
        config->disable_epsv = toggle;
        break;
      case 'E': /* --epsv */
        config->disable_epsv = (!toggle)?TRUE:FALSE;
        break;
#ifdef USE_ENVIRONMENT
      case 'f':
        config->writeenv = toggle;
        break;
#endif
      case 'F': /* --dns-servers */
        /* IP addrs of DNS servers */
        GetStr(&config->dns_servers, nextarg);
        break;
      case 'g': /* --trace */
        GetStr(&config->trace_dump, nextarg);
        if(config->tracetype && (config->tracetype != TRACE_BIN))
          warnf(config, "--trace overrides an earlier trace/verbose option\n");
        config->tracetype = TRACE_BIN;
        break;
