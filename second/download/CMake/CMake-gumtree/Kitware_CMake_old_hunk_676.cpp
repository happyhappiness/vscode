

    /* we got OK from server */

    if(data->set.ftp_skip_ip) {

      /* told to ignore the remotely given IP but instead use the one we used

         for the control connection */

      infof(data, "Skips %d.%d.%d.%d for data connection, uses %s instead\n",

            ip[0], ip[1], ip[2], ip[3],

            conn->ip_addr_str);

      if(conn->bits.tunnel_proxy ||

         conn->proxytype == CURLPROXY_SOCKS5 ||

         conn->proxytype == CURLPROXY_SOCKS5_HOSTNAME ||

         conn->proxytype == CURLPROXY_SOCKS4 ||

         conn->proxytype == CURLPROXY_SOCKS4A)

        /* proxy tunnel -> use other host info because ip_addr_str is the

           proxy address not the ftp host */

        snprintf(ftpc->newhost, sizeof(ftpc->newhost), "%s", conn->host.name);

      else

        snprintf(ftpc->newhost, sizeof(ftpc->newhost), "%s",

                 conn->ip_addr_str);

    }

    else

      snprintf(ftpc->newhost, sizeof(ftpc->newhost),

               "%d.%d.%d.%d", ip[0], ip[1], ip[2], ip[3]);

    ftpc->newport = (unsigned short)(((port[0]<<8) + port[1]) & 0xffff);

  }

  else if(ftpc->count1 == 0) {

