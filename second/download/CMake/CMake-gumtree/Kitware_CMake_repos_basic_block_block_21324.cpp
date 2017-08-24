(addr_st.ss_family == AF_INET6) {
    if (setsockopt(handle->socket,
                   IPPROTO_IPV6,
                   IPV6_MULTICAST_IF,
                   (char*) &addr6->sin6_scope_id,
                   sizeof(addr6->sin6_scope_id)) == SOCKET_ERROR) {
      return uv_translate_sys_error(WSAGetLastError());
    }
  }