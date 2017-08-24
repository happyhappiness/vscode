{
    int on;

    on = (flags & UV_TCP_IPV6ONLY) != 0;

    /* TODO: how to handle errors? This may fail if there is no ipv4 stack */
    /* available, or when run on XP/2003 which have no support for dualstack */
    /* sockets. For now we're silently ignoring the error. */
    setsockopt(handle->socket,
               IPPROTO_IPV6,
               IPV6_V6ONLY,
               (const char*)&on,
               sizeof on);
  }