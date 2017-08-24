rc = Curl_socket_check(pp->sendleft?CURL_SOCKET_BAD:sock, /* reading */
                           CURL_SOCKET_BAD,
                           pp->sendleft?sock:CURL_SOCKET_BAD, /* writing */
                           interval_ms)