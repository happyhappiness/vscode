f(!conn->http_proxy.host.rawalloc) {
        /* once a socks proxy */
        if(!conn->socks_proxy.user) {
          conn->socks_proxy.user = conn->http_proxy.user;
          conn->http_proxy.user = NULL;
          Curl_safefree(conn->socks_proxy.passwd);
          conn->socks_proxy.passwd = conn->http_proxy.passwd;
          conn->http_proxy.passwd = NULL;
        }
      }