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
