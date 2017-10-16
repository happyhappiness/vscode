
    case 'g': /* g disables URLglobbing */
      config->globoff = toggle;
      break;

    case 'G': /* HTTP GET */
      config->use_httpget = TRUE;
      break;

    case 'h': /* h for help */
      if(toggle) {
        return PARAM_HELP_REQUESTED;
      }
      /* we now actually support --no-help too! */
      break;
    case 'H':
      /* A custom header to append to a list */
      if(subletter == 'p') /* --proxy-header */
        err = add2list(&config->proxyheaders, nextarg);
      else
        err = add2list(&config->headers, nextarg);
      if(err)
        return err;
      break;
    case 'i':
      config->include_headers = toggle; /* include the headers as well in the
                                           general output stream */
      break;
    case 'j':
