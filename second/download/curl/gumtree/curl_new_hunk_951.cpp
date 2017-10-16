
    if(!(pp->name)) { /* unknown protocol */
      /* If they have specified only this protocol, we say treat it as
         if no protocols are allowed */
      if(action == set)
        *val = 0;
      warnf(config->global, "unrecognized protocol '%s'\n", token);
    }
  }
  Curl_safefree(buffer);
  return 0;
}

