{
          without_fds++;
          if(without_fds > 2) {
            int sleep_ms = without_fds < 10 ? (1 << (without_fds - 1)) : 1000;
            Curl_wait_ms(sleep_ms);
          }
        }