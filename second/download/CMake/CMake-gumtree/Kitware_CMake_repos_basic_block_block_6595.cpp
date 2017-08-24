{
        /* fatal error */
        failf(data, "select/poll on SSL socket, errno: %d", SOCKERRNO);
        return CURLE_SSL_CONNECT_ERROR;
      }