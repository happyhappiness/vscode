        }
        if(ptr) {
          ftpc->newport = (unsigned short)(num & 0xffff);

          if(conn->bits.tunnel_proxy ||
             conn->proxytype == CURLPROXY_SOCKS5 ||
             conn->proxytype == CURLPROXY_SOCKS5_HOSTNAME ||
             conn->proxytype == CURLPROXY_SOCKS4 ||
             conn->proxytype == CURLPROXY_SOCKS4A)
            /* proxy tunnel -> use other host info because ip_addr_str is the
               proxy address not the ftp host */
            snprintf(ftpc->newhost, sizeof(ftpc->newhost), "%s",
                     conn->host.name);
          else
            /* use the same IP we are already connected to */
            snprintf(ftpc->newhost, NEWHOST_BUFSIZE, "%s", conn->ip_addr_str);
        }
      }
      else
