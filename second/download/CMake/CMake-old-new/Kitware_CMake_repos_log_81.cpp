char *hostname_to_match = aprintf("%s%s%s",
                                      conn->bits.ipv6_ip ? "[" : "",
                                      conn->host.name,
                                      conn->bits.ipv6_ip ? "]" : "")