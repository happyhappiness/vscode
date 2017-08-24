(addrlen == sizeof(uv_addr_ip4_any_)) {
      bind_addr = (const struct sockaddr*) &uv_addr_ip4_any_;
    } else if (addrlen == sizeof(uv_addr_ip6_any_)) {
      bind_addr = (const struct sockaddr*) &uv_addr_ip6_any_;
    } else {
      abort();
    }