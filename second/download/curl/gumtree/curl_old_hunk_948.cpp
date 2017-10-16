
        /* curl 7.17.1 */
        if(!config->nokeepalive) {
          my_setopt(curl, CURLOPT_TCP_KEEPALIVE, 1L);
          if(config->alivetime != 0) {
#if !defined(TCP_KEEPIDLE) || !defined(TCP_KEEPINTVL)
            warnf(config, "Keep-alive functionality somewhat crippled due to "
                "missing support in your operating system!\n");
#endif
            my_setopt(curl, CURLOPT_TCP_KEEPIDLE, config->alivetime);
            my_setopt(curl, CURLOPT_TCP_KEEPINTVL, config->alivetime);
          }
        }
        else
