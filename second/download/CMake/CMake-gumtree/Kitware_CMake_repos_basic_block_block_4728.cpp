f(conn->tempsock[i] != CURL_SOCKET_BAD) {
      sock[s] = conn->tempsock[i];
      rc |= GETSOCK_WRITESOCK(s++);
    }