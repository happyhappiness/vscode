        my_setopt(curl, CURLOPT_CRLF, config->crlf?1L:0L);
        my_setopt_slist(curl, CURLOPT_QUOTE, config->quote);
        my_setopt_slist(curl, CURLOPT_POSTQUOTE, config->postquote);
        my_setopt_slist(curl, CURLOPT_PREQUOTE, config->prequote);

#if !defined(CURL_DISABLE_HTTP) && !defined(CURL_DISABLE_COOKIES)
        if(config->cookie)
          my_setopt_str(curl, CURLOPT_COOKIE, config->cookie);

        if(config->cookiefile)
          my_setopt_str(curl, CURLOPT_COOKIEFILE, config->cookiefile);

        /* new in libcurl 7.9 */
        if(config->cookiejar)
          my_setopt_str(curl, CURLOPT_COOKIEJAR, config->cookiejar);

        /* new in libcurl 7.9.7 */
        my_setopt(curl, CURLOPT_COOKIESESSION, config->cookiesession?1L:0L);
#else
        if(config->cookie || config->cookiefile || config->cookiejar) {
          warnf(config, "cookie option(s) used even though cookie support "
                "is disabled!\n");
          return CURLE_NOT_BUILT_IN;
        }
#endif

        my_setopt_enum(curl, CURLOPT_SSLVERSION, config->ssl_version);
        my_setopt_enum(curl, CURLOPT_TIMECONDITION, (long)config->timecond);
        my_setopt(curl, CURLOPT_TIMEVALUE, (long)config->condtime);
