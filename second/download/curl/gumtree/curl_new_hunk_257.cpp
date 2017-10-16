    case 'K': /* parse config file */
      if(parseconfig(nextarg, config))
        warnf(config, "error trying read config from the '%s' file\n",
              nextarg);
      break;
    case 'l':
      config->conf ^= CONF_DIRLISTONLY; /* only list the names of the FTP dir */
      break;
    case 'L':
      config->conf ^= CONF_FOLLOWLOCATION; /* Follow Location: HTTP headers */
      switch (subletter) {
      case 't':
        /* Continue to send authentication (user+password) when following
