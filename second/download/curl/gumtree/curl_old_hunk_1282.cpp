        config->noalpn = (!toggle)?TRUE:FALSE;
        break;
      case 'i': /* --limit-rate */
      {
        /* We support G, M, K too */
        char *unit;
        curl_off_t value = curlx_strtoofft(nextarg, &unit, 0);

        if(!*unit)
          unit = (char *)"b";
        else if(strlen(unit) > 1)
          unit = (char *)"w"; /* unsupported */

