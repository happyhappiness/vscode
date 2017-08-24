return uv__setsockopt(handle,
                          IP_MULTICAST_LOOP,
                          IPV6_MULTICAST_LOOP,
                          &on,
                          sizeof(on));