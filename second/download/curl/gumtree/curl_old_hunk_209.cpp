        char buffer[32];
        curl_off_t off;
        warnf(config,
              "A specfied range MUST include at least one dash (-). "
              "Appending one for you!\n");
        off = curlx_strtoofft(nextarg, NULL, 10);
        snprintf(buffer, sizeof(buffer), CURL_FORMAT_OFF_T "-", off);
        GetStr(&config->range, buffer);
      }
      else
        /* byte range requested */
        GetStr(&config->range, nextarg);

