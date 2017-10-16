        char buffer[32];
        curl_off_t off;
        warnf(config,
              "A specified range MUST include at least one dash (-). "
              "Appending one for you!\n");
        off = curlx_strtoofft(nextarg, NULL, 10);
        snprintf(buffer, sizeof(buffer), "%" CURL_FORMAT_CURL_OFF_T "-", off);
        GetStr(&config->range, buffer);
      }
      {
        /* byte range requested */
        char* tmp_range;
        tmp_range=nextarg;
