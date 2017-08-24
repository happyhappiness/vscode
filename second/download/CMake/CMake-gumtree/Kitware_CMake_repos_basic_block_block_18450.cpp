{
      s = tmp;
      len = p - src;
      if (len > UV__INET6_ADDRSTRLEN-1)
        return UV_EINVAL;
      memcpy(s, src, len);
      s[len] = '\0';
    }