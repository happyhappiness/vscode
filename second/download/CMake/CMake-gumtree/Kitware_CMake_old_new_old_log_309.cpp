aprintf("%s%s%s:%hu", conn->bits.ipv6_ip?"[":"",
                  hostname, conn->bits.ipv6_ip?"]":"",
                  remote_port);