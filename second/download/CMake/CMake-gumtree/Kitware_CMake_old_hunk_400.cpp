
      if(!result) {
        char *host=(char *)"";
        const char *proxyconn="";
        const char *useragent="";
        const char *http = (conn->proxytype == CURLPROXY_HTTP_1_0) ?
          "1.0" : "1.1";
        char *hostheader= /* host:port with IPv6 support */
          aprintf("%s%s%s:%hu", conn->bits.ipv6_ip?"[":"",
                  hostname, conn->bits.ipv6_ip?"]":"",
                  remote_port);
        if(!hostheader) {
          Curl_add_buffer_free(req_buffer);
