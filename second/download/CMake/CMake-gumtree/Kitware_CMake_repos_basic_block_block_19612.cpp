{
      case AF_UNIX:
        return UV_NAMED_PIPE;
      case AF_INET:
      case AF_INET6:
        return UV_TCP;
      }