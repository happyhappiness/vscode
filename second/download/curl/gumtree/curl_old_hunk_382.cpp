                 * returns 530 in this case, but all 5xx codes are transient.
                 */
                retry = RETRY_FTP;
            }

            if(retry) {
              static const char * const m[]={NULL,
                                             "timeout",
                                             "HTTP error",
                                             "FTP error"
              };
              warnf(config, "Transient problem: %s "
                    "Will retry in %ld seconds. "
                    "%ld retries left.\n",
                    m[retry],
                    retry_sleep/1000,
                    retry_numretries);

              go_sleep(retry_sleep);
              retry_numretries--;
              if(!config->retry_delay) {
                retry_sleep *= 2;
                if(retry_sleep > RETRY_SLEEP_MAX)
