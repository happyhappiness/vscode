        my_setopt(curl, CURLOPT_CRLF, config->crlf?1L:0L);
        my_setopt_slist(curl, CURLOPT_QUOTE, config->quote);
        my_setopt_slist(curl, CURLOPT_POSTQUOTE, config->postquote);
        my_setopt_slist(curl, CURLOPT_PREQUOTE, config->prequote);

#if !defined(CURL_DISABLE_HTTP) && !defined(CURL_DISABLE_COOKIES)
        {
          /* TODO: Make this a run-time check instead of compile-time one. */

          if(config->cookie)
            my_setopt_str(curl, CURLOPT_COOKIE, config->cookie);

          if(config->cookiefile)
            my_setopt_str(curl, CURLOPT_COOKIEFILE, config->cookiefile);

          /* new in libcurl 7.9 */
          if(config->cookiejar)
            my_setopt_str(curl, CURLOPT_COOKIEJAR, config->cookiejar);

          /* new in libcurl 7.9.7 */
          my_setopt(curl, CURLOPT_COOKIESESSION, config->cookiesession?1L:0L);
        }
#endif

        my_setopt_enum(curl, CURLOPT_SSLVERSION, config->ssl_version);
        my_setopt_enum(curl, CURLOPT_TIMECONDITION, (long)config->timecond);
        my_setopt(curl, CURLOPT_TIMEVALUE, (long)config->condtime);
