{
        struct timeval after = curlx_tvnow();

        /* If it returns without any filedescriptor instantly, we need to
           avoid busy-looping during periods where it has nothing particular
           to wait for */
        if(curlx_tvdiff(after, before) <= 10) {
          without_fds++;
          if(without_fds > 2) {
            int sleep_ms = without_fds < 10 ? (1 << (without_fds - 1)) : 1000;
            Curl_wait_ms(sleep_ms);
          }
        }
        else
          /* it wasn't "instant", restart counter */
          without_fds = 0;
      }