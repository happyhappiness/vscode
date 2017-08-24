{
  case AF_INET:
    return (inet_ntop4(src, dst, size));
  case AF_INET6:
    return (inet_ntop6(src, dst, size));
  default:
    return UV_EAFNOSUPPORT;
  }