        return PARAM_BAD_USE;
      if(SetHTTPrequest(config, HTTPREQ_POST, &config->httpreq))
        return PARAM_BAD_USE;
      break;

    case 'g': /* g disables URLglobbing */
      config->globoff = toggle;
      break;

    case 'G': /* HTTP GET */
      config->use_httpget = TRUE;
      break;

    case 'h': /* h for help */
      if(toggle) {
        help();
        return PARAM_HELP_REQUESTED;
      }
      /* we now actually support --no-help too! */
      break;
    case 'H':
      /* A custom header to append to a list */
      err = add2list(&config->headers, nextarg);
      if(err)
        return err;
      break;
    case 'i':
      config->include_headers = toggle; /* include the headers as well in the
                                           general output stream */
      break;
    case 'j':
      config->cookiesession = toggle;
      break;
    case 'I':
      /*
       * no_body will imply include_headers later on
       */
      config->no_body = toggle;
      if(SetHTTPrequest(config,
                        (config->no_body)?HTTPREQ_HEAD:HTTPREQ_GET,
                        &config->httpreq))
        return PARAM_BAD_USE;
      break;
    case 'k': /* allow insecure SSL connects */
      config->insecure_ok = toggle;
      break;
    case 'K': /* parse config file */
      if(parseconfig(nextarg, config))
        warnf(config, "error trying read config from the '%s' file\n",
              nextarg);
      break;
    case 'l':
      config->dirlistonly = toggle; /* only list the names of the FTP dir */
      break;
    case 'L':
      config->followlocation = toggle; /* Follow Location: HTTP headers */
      switch (subletter) {
      case 't':
        /* Continue to send authentication (user+password) when following
         * locations, even when hostname changed */
        config->unrestricted_auth = toggle;
        break;
      }
      break;
    case 'm':
      /* specified max time */
      if(str2num(&config->timeout, nextarg))
        return PARAM_BAD_NUMERIC;
      break;
    case 'M': /* M for manual, huge help */
      if(toggle) { /* --no-manual shows no manual... */
#ifdef USE_MANUAL
        hugehelp();
        return PARAM_HELP_REQUESTED;
#else
        warnf(config,
              "built-in manual was disabled at build-time!\n");
        return PARAM_OPTION_UNKNOWN;
#endif
      }
      break;
    case 'n':
      switch(subletter) {
      case 'o': /* CA info PEM file */
        /* use .netrc or URL */
        config->netrc_opt = toggle;
        break;
      default:
        /* pick info from .netrc, if this is used for http, curl will
           automatically enfore user+password with the request */
        config->netrc = toggle;
        break;
      }
      break;
    case 'N':
      /* disable the output I/O buffering */
      config->nobuffer = !toggle;
      break;
    case 'O': /* --remote-name */
      if(subletter == 'a') { /* --remote-name-all */
        config->default_node_flags = toggle?GETOUT_USEREMOTE:0;
        break;
      }
    /* fall-through! */
    case 'o': /* --output */
      /* output file */
      {
        struct getout *url;
        if(config->url_out || (config->url_out=config->url_list)) {
          /* there's a node here, if it already is filled-in continue to find
             an "empty" node */
