{
    const CURLcode result = https_proxy_connect(conn, sockindex);
    if(result)
      return result;
    if(!conn->bits.proxy_ssl_connected[sockindex])
      return result; /* wait for HTTPS proxy SSL initialization to complete */
  }