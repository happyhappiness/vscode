         (and won't actually be range by definition). The man page previously
         claimed that to be a good way, why this code is added to work-around
         it. */
      if(ISDIGIT(*nextarg) && !strchr(nextarg, '-')) {
        char buffer[32];
        curl_off_t off;
        warnf(global,
              "A specified range MUST include at least one dash (-). "
              "Appending one for you!\n");
        off = curlx_strtoofft(nextarg, NULL, 10);
        snprintf(buffer, sizeof(buffer), "%" CURL_FORMAT_CURL_OFF_T "-", off);
        Curl_safefree(config->range);
        config->range = strdup(buffer);
        if(!config->range)
          return PARAM_NO_MEM;
      }
