        /* new in curl 7.11.1 */
        if(config->socks5proxy) {
          curl_easy_setopt(curl, CURLOPT_PROXY, config->socks5proxy);
          curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5);
        }

        /* curl 7.13.0 */
        curl_easy_setopt(curl, CURLOPT_SOURCE_URL, config->tp_url);
        curl_easy_setopt(curl, CURLOPT_SOURCE_USERPWD, config->tp_user);
        curl_easy_setopt(curl, CURLOPT_SOURCE_PREQUOTE, config->tp_prequote);
        curl_easy_setopt(curl, CURLOPT_SOURCE_POSTQUOTE, config->tp_postquote);
        curl_easy_setopt(curl, CURLOPT_SOURCE_QUOTE, config->tp_quote);
        curl_easy_setopt(curl, CURLOPT_FTP_ACCOUNT, config->ftp_account);

        retry_numretries = config->req_retry;

        retrystart = curlx_tvnow();

        do {
          res = curl_easy_perform(curl);

          /* if retry-max-time is non-zero, make sure we haven't exceeded the
             time */
          if(retry_numretries &&
             (!config->retry_maxtime ||
              (curlx_tvdiff(curlx_tvnow(), retrystart)<
               config->retry_maxtime*1000)) ) {
            enum {
              RETRY_NO,
              RETRY_TIMEOUT,
              RETRY_HTTP,
              RETRY_FTP,
              RETRY_LAST /* not used */
            } retry = RETRY_NO;
            if(CURLE_OPERATION_TIMEDOUT == res)
              /* retry timeout always */
              retry = RETRY_TIMEOUT;
            else if(CURLE_OK == res) {
              /* Check for HTTP transient errors */
              char *url=NULL;
              curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);
              if(url &&
                 curlx_strnequal(url, "http", 4)) {
                /* This was HTTP(S) */
                curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response);

                switch(response) {
                case 500: /* Internal Server Error */
                case 502: /* Bad Gateway */
                case 503: /* Service Unavailable */
                case 504: /* Gateway Timeout */
                  retry = RETRY_HTTP;
                  /*
                   * At this point, we have already written data to the output
                   * file (or terminal). If we write to a file, we must rewind
                   * or close/re-open the file so that the next attempt starts
                   * over from the beginning.
                   *
                   * TODO: similar action for the upload case. We might need
                   * to start over reading from a previous point if we have
                   * uploaded something when this was returned.
                   */
                  break;
                }
              }
            } /* if CURLE_OK */
            else if(CURLE_FTP_USER_PASSWORD_INCORRECT == res) {
              curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response);

              if(response/100 == 5)
                /*
                 * This is typically when the FTP server only allows a certain
                 * amount of users and we are not one of them. It mostly
                 * returns 530 in this case, but all 5xx codes are transient.
                 */
                retry = RETRY_FTP;
            }

            if(retry) {
              if(!(config->conf&CONF_MUTE)) {
                static const char * const m[]={NULL,
                                              "timeout",
                                              "HTTP error",
                                              "FTP error"
                };
                fprintf(stderr, "Transient problem: %s\n"
                        "Will retry in %ld seconds. "
                        "%ld retries left.\n",
                        m[retry],
                        retry_sleep/1000,
                        retry_numretries);
              }
              go_sleep(retry_sleep);
              retry_numretries--;
              if(!config->retry_delay) {
                retry_sleep *= 2;
                if(retry_sleep > RETRY_SLEEP_MAX)
                  retry_sleep = RETRY_SLEEP_MAX;
              }
              if(outs.bytes && outs.filename) {
                /* We have written data to a output file, we truncate file
                 */
                if(!(config->conf&CONF_MUTE))
                  fprintf(stderr, "Throwing away " CURL_FORMAT_OFF_T
                          " bytes\n", outs.bytes);
                fflush(outs.stream);
                /* truncate file at the position where we started appending */
                ftruncate( fileno(outs.stream), outs.init);
                /* now seek to the end of the file, the position where we
                   just truncated the file */
                fseek(outs.stream, 0, SEEK_END);
                outs.bytes = 0; /* clear for next round */
              }
              continue;
            }
          } /* if retry_numretries */

          /* In all ordinary cases, just break out of loop here */
          retry_sleep = retry_sleep_default;
          break;

        } while(1);

        if((config->progressmode == CURL_PROGRESS_BAR) &&
           progressbar.calls) {
          /* if the custom progress bar has been displayed, we output a
             newline here */
          fputs("\n", progressbar.out);
