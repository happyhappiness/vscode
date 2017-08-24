{
    *curlcode = (ret == POLARSSL_ERR_NET_WANT_WRITE) ?
      CURLE_AGAIN : CURLE_SEND_ERROR;
    ret = -1;
  }