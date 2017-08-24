f(checkprefix("https", proxy))
      proxytype = CURLPROXY_HTTPS;
    else if(checkprefix("socks5h", proxy))
      proxytype = CURLPROXY_SOCKS5_HOSTNAME;
    else if(checkprefix("socks5", proxy))
      proxytype = CURLPROXY_SOCKS5;
    else if(checkprefix("socks4a", proxy))
      proxytype = CURLPROXY_SOCKS4A;
    else if(checkprefix("socks4", proxy) || checkprefix("socks", proxy))
      proxytype = CURLPROXY_SOCKS4;
    else if(checkprefix("http:", proxy))
      ; /* leave it as HTTP or HTTP/1.0 */
    else {
      /* Any other xxx:// reject! */
      failf(data, "Unsupported proxy scheme for \'%s\'", proxy);
      return CURLE_COULDNT_CONNECT;
    }