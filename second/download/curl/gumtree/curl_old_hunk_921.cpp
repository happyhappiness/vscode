                        (config->no_body)?HTTPREQ_HEAD:HTTPREQ_GET,
                        &config->httpreq))
        return PARAM_BAD_USE;
      break;
    case 'J': /* --remote-header-name */
      if(config->include_headers) {
        warnf(config,
              "--include and --remote-header-name cannot be combined.\n");
        return PARAM_BAD_USE;
      }
      config->content_disposition = toggle;
      break;
    case 'k': /* allow insecure SSL connects */
      config->insecure_ok = toggle;
      break;
    case 'K': /* parse config file */
      if(parseconfig(nextarg, global))
        warnf(config, "error trying read config from the '%s' file\n",
              nextarg);
      break;
    case 'l':
      config->dirlistonly = toggle; /* only list the names of the FTP dir */
      break;
    case 'L':
