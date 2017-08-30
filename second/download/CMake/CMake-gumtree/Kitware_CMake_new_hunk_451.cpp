    if(0 == pollrc) {

      /* timeout! */

      ev->ms = 0;

      /* fprintf(stderr, "call curl_multi_socket_action(TIMEOUT)\n"); */

      mcode = curl_multi_socket_action(multi, CURL_SOCKET_TIMEOUT, 0,

                                       &ev->running_handles);

    }

