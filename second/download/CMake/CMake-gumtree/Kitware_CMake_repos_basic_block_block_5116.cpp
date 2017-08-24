f(!pp->sendleft && Curl_ssl_data_pending(conn, FIRSTSOCKET))
    /* We are receiving and there is data ready in the SSL library */
    rc = 1