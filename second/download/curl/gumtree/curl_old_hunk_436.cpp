          } /* if retry_numretries */

          /* In all ordinary cases, just break out of loop here */
          retry_sleep = retry_sleep_default;
          break;

        } while(1);

        if((config->progressmode == CURL_PROGRESS_BAR) &&
           progressbar.calls)
          /* if the custom progress bar has been displayed, we output a
             newline here */
          fputs("\n", progressbar.out);
