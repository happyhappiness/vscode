        /* new in curl 7.11.1 */
        if(config->socks5proxy) {
          curl_easy_setopt(curl, CURLOPT_PROXY, config->socks5proxy);
          curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5);
        }

        res = curl_easy_perform(curl);

        if((config->progressmode == CURL_PROGRESS_BAR) &&
           progressbar.calls) {
          /* if the custom progress bar has been displayed, we output a
             newline here */
          fputs("\n", progressbar.out);
