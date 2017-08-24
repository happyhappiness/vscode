    proxy_type = 1;
    if (getenv("HTTP_PROXY_PORT") )
      {
      sprintf("%s:%s", getenv("HTTP_PROXY"), getenv("HTTP_PROXY_PORT"));
      }
    else
      {
      sprintf("%s", getenv("HTTP_PROXY"));
      }
    if ( getenv("HTTP_PROXY_TYPE") )
      {
      // HTTP/SOCKS4/SOCKS5
      if ( strcmp(getenv("HTTP_PROXY_TYPE"), "HTTP") == 0 )
        {
        proxy_type = 1;
