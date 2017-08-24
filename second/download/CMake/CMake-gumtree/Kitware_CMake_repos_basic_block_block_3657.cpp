f(Curl_ipv6works()) {
        res->num_pending = 2;

        /* areschannel is already setup in the Curl_open() function */
        ares_gethostbyname((ares_channel)data->state.resolver, hostname,
                            PF_INET, query_completed_cb, conn);
        ares_gethostbyname((ares_channel)data->state.resolver, hostname,
                            PF_INET6, query_completed_cb, conn);
      }
      else {
        res->num_pending = 1;

        /* areschannel is already setup in the Curl_open() function */
        ares_gethostbyname((ares_channel)data->state.resolver, hostname,
                            PF_INET, query_completed_cb, conn);
      }