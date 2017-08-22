                  hostname, conn->bits.ipv6_ip?"]":"",
                  remote_port);
        if(!hostheader) {
          free(req_buffer);
          return CURLE_OUT_OF_MEMORY;
        }

        if(!Curl_checkProxyheaders(conn, "Host:")) {
          host = aprintf("Host: %s\r\n", hostheader);
          if(!host) {
            free(hostheader);
            free(req_buffer);
            return CURLE_OUT_OF_MEMORY;
          }
        }
