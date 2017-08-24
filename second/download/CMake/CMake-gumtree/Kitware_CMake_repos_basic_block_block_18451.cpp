{
  case AF_INET:
    return (inet_pton4(src, dst));
  case AF_INET6: {
    int len;
    char tmp[UV__INET6_ADDRSTRLEN], *s, *p;
    s = (char*) src;
    p = strchr(src, '%');
    if (p != NULL) {
      s = tmp;
      len = p - src;
      if (len > UV__INET6_ADDRSTRLEN-1)
        return UV_EINVAL;
      memcpy(s, src, len);
      s[len] = '\0';
    }
    return inet_pton6(s, dst);
  }
  default:
    return UV_EAFNOSUPPORT;
  }