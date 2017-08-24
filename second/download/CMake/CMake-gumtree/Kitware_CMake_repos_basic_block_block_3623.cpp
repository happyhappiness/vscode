( getenv("HTTP_PROXY_TYPE") )
      {
      /* HTTP/SOCKS4/SOCKS5 */
      if ( strcmp(getenv("HTTP_PROXY_TYPE"), "HTTP") == 0 )
        {
        proxy_type = 1;
        }
      else if ( strcmp(getenv("HTTP_PROXY_TYPE"), "SOCKS4") == 0 )
        {
        proxy_type = 2;
        }
      else if ( strcmp(getenv("HTTP_PROXY_TYPE"), "SOCKS5") == 0 )
        {
        proxy_type = 3;
        }
      }