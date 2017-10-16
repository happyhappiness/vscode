         claimed that to be a good way, why this code is added to work-around
         it. */
      if(ISDIGIT(*nextarg) && !strchr(nextarg, '-')) {
        char buffer[32];
        curl_off_t off;
        warnf(config,
              "A specfied range MUST include at least one dash (-). "
              "Appending one for you!\n");
        off = curlx_strtoofft(nextarg, NULL, 10);
        snprintf(buffer, sizeof(buffer), "%Od-", off);
        GetStr(&config->range, buffer);
      }
      {
