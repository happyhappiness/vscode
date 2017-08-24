f(port >= 0) {
      proxyinfo->port = port;
      if(conn->port < 0 || sockstype || !conn->socks_proxy.host.rawalloc)
        conn->port = port;
    }