hostheader= /* host:port with IPv6 support */
          aprintf("%s%s%s:%hu", ipv6_ip?"[":"", hostname, ipv6_ip?"]":"",
                  remote_port);