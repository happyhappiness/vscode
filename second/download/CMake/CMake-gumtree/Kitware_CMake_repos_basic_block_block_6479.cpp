{
        failf(data, "Your version of the OS does not support SSLv3");
        return CURLE_SSL_CONNECT_ERROR;
      }