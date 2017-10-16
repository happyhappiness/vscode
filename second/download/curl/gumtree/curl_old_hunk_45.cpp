      /* Telnet options */
      config->telnet_options =
        curl_slist_append(config->telnet_options, nextarg);
      break;
    case 'T':
      /* we are uploading */
      config->conf |= CONF_UPLOAD;
      if(!curl_strequal("-", nextarg))
        /* make - equal stdin */
        GetStr(&config->infile, nextarg);
      break;
    case 'u':
      /* user:password  */
      GetStr(&config->userpwd, nextarg);
      cleanarg(nextarg);
      break;
    case 'U':
      /* Proxy user:password  */
      GetStr(&config->proxyuserpwd, nextarg);
      cleanarg(nextarg);
      break;
    case 'v':
      config->conf ^= CONF_VERBOSE; /* talk a lot */
      break;
    case 'V':
      printf(CURL_ID "%s\n", curl_version());
      return PARAM_HELP_REQUESTED;
    case 'w':
      /* get the output string */
      if('@' == *nextarg) {
        /* the data begins with a '@' letter, it means that a file name
           or - (stdin) follows */
        FILE *file;
